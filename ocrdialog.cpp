#include "ocrdialog.h"
#include "ui_ocrdialog.h"

OCRDialog::OCRDialog(QWidget *parent, cv::Mat classificationNumbers,
                     cv::Mat trainingImagesAsFlattenedFloats, cv::Mat image,
                     int minContourArea, int imageWidth, int imageHeight) :
    QDialog(parent),
    ui(new Ui::OCRDialog)
{
    ui->setupUi(this);
    this->classificationNumbers = classificationNumbers;
    this->trainingImagesAsFlattenedFloats = trainingImagesAsFlattenedFloats;
    this->minContourArea = minContourArea;
    this->image = image;
    this->imageWidth = imageWidth;
    this->imageHeight = imageHeight;

    cv::findContours(image, ptContours, v4iHierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    for(unsigned int i = 0; i < ptContours.size(); i++) {
        ContourWithData contour;
        contour.ptContour = ptContours[i];
        contour.boundingRect = cv::boundingRect(contour.ptContour);
        contour.area = cv::contourArea(contour.ptContour);
        allContoursWithData.push_back(contour);
    }

    // find the valid contours;
    for(unsigned int i = 0; i < allContoursWithData.size(); i++) {
        if(allContoursWithData[i].checkIfContourIsValid(this->minContourArea)) { validContoursWithData.push_back(allContoursWithData[i]);}
    }

    // sort contours from left to right
    std::sort(validContoursWithData.begin(), validContoursWithData.end(), ContourWithData::sorByBoundingRectXPosition);

    // create KNearest
    this->kNearest = cv::Ptr<cv::ml::KNearest>(cv::ml::KNearest::create());

    // train the ml algorithm
    kNearest->train(trainingImagesAsFlattenedFloats, cv::ml::ROW_SAMPLE, classificationNumbers);
    findText();
}

void OCRDialog::findText()
{
    letters = new Letters("Letters");
    if(validContoursWithData.empty()) {
        QMessageBox::information(this, "Informations", "No valid text found in the image");
        return;
    }
    for(unsigned int i = 0; i < validContoursWithData.size(); i++) {
        cv::rectangle(classificationNumbers,
                      validContoursWithData[i].boundingRect,
                      cv::Scalar(0, 255, 0), 2);

        cv::Mat matROI = image(validContoursWithData[i].boundingRect);
        cv::Mat matROIResized;
        cv::resize(matROI, matROIResized, cv::Size(imageWidth, imageHeight));

        cv::Mat matROIFloat;
        matROIResized.convertTo(matROIFloat, CV_32FC1);
        cv::Mat flattenedFloat = matROIFloat.reshape(1, 1);
        cv::Mat currentChar(0, 0, CV_32F);
        kNearest->findNearest(flattenedFloat, 1, currentChar);
        float fCurrentChar = (float) currentChar.at<float>(0, 0);
        std::string str = letters->getChar((int) fCurrentChar);
        std::cout<<str;
        this->finalString += str;
    }
    setText();
}

OCRDialog::~OCRDialog()
{
    delete ui;
}

void OCRDialog::setText()
{
    ui->displayText->setText(QString::fromStdString(finalString));
}
