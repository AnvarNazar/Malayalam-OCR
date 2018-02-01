#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml.hpp>

#include <vector>

#include "letters.h"

#include "ocrdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int blurSize = 5;
    int charWidth = 20;
    int charHeight = 30;
    int contourArea = 100;
    int blockSize = 11;

    cv::Mat image, imageGrayscale, imageBlurred, imageThresholded, imageThresholdedCopy;
    QImage dImage;

    std::string fileName;
    std::string trainingFileName;
    Letters *letters;

    cv::Mat classificationNumbers, trainingImagesAsFlattenedFloats;

private:
    void openTrainingFile();

private slots:
    void on_actionOpen_triggered();

    void processImage();
    void displayImage();

    void on_actionImage_triggered();

    void on_actionTraining_File_triggered();
    void on_pushButton_clicked();

    void on_blurSizeSlider_valueChanged(int value);

    void on_blurSizeBox_valueChanged(int arg1);

    void on_charWidthSlider_valueChanged(int value);

    void on_charWidthBox_valueChanged(int arg1);

    void on_charHeightSlider_valueChanged(int value);

    void on_charHeightBox_valueChanged(int arg1);

    void on_contourAreaSlider_valueChanged(int value);

    void on_contourAreaBox_valueChanged(int arg1);

    void on_blockSizeSlider_valueChanged(int value);

    void on_blockSizeBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
