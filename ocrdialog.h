#ifndef OCRDIALOG_H
#define OCRDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml.hpp>

#include <vector>

#include "contourwithdata.h"
#include "letters.h"

namespace Ui {
class OCRDialog;
}

class OCRDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OCRDialog(QWidget *parent = 0,
                       cv::Mat classificationNumbers = cv::Mat(),
                       cv::Mat trainingImagesAsFlattenedFloats = cv::Mat(),
                       cv::Mat image = cv::Mat(),
                       int minContourArea = 100,
                       int imageWidth = 20,
                       int imageHeight = 30);
    ~OCRDialog();

private:
    Ui::OCRDialog *ui;
    cv::Mat image;
    cv::Mat classificationNumbers, trainingImagesAsFlattenedFloats;

    int minContourArea;
    int imageWidth;
    int imageHeight;

    Letters *letters;

    std::vector<ContourWithData> allContoursWithData;
    std::vector<ContourWithData> validContoursWithData;
    std::vector<std::vector<cv::Point>> ptContours;
    std::vector<cv::Vec4i> v4iHierarchy;
    std::string finalString;

    // Ptr array for KNearest machine learning algorithm
    cv::Ptr<cv::ml::KNearest> kNearest;

    void findText();
    void setText();
};

#endif // OCRDIALOG_H
