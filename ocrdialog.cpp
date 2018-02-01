#include "ocrdialog.h"
#include "ui_ocrdialog.h"

OCRDialog::OCRDialog(QWidget *parent, cv::Mat classificationNumbers,
                     cv::Mat trainingImagesAsFlattenedFloats,
                     int minContourArea, int imageWidth, int imageHeight) :
    QDialog(parent),
    ui(new Ui::OCRDialog)
{
    ui->setupUi(this);
    this->classificationNumbers = classificationNumbers;
    this->trainingImagesAsFlattenedFloats = trainingImagesAsFlattenedFloats;
    this->minContourArea = minContourArea;
    this->imageWidth = imageWidth;
    this->imageHeight = imageHeight;

    cv::findContours(image, ptContours, v4iHierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    for(auto x:ptContours) {
        ContourWithData contour;
        contour.ptContour = x.data();
        contour.boundingRect = cv::boundingRect(contour.ptContour);
        contour.area = cv::contourArea(contour.ptContour);
        allContoursWithData.push_back(contour);
    }

    // find the valid contours;
    for(auto x:allContoursWithData) {
        if(x.checkIfContourIsValid(this->minContourArea)) { validContoursWithData.push_back(allContoursWithData); }
    }

    // sort contours from left to right
    std::sort(validContoursWithData.begin(), validContoursWithData.end(), ContourWithData::sorByBoundingRectXPosition);

    // train the ml algorithm
    kNearest->train(trainingImagesAsFlattenedFloats, cv::ml::ROW_SAMPLE, classificationNumbers);
}

OCRDialog::~OCRDialog()
{
    delete ui;
}
