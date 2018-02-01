#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->blurSizeSlider->setValue(blurSize);
    ui->blurSizeBox->setValue(blurSize);

    ui->charWidthBox->setValue(charWidth);
    ui->charWidthSlider->setValue(charWidth);

    ui->charHeightBox->setValue(charHeight);
    ui->charHeightSlider->setValue(charHeight);

    ui->contourAreaBox->setValue(contourArea);
    ui->contourAreaSlider->setValue(contourArea);

    ui->blockSizeBox->setValue(blockSize);
    ui->blockSizeSlider->setValue(blockSize);

    connect(ui->blurSizeSlider, SIGNAL(valueChanged(int)), ui->blurSizeBox, SLOT(setValue(int)));
    connect(ui->blurSizeBox, SIGNAL(valueChanged(int)), ui->blurSizeSlider, SLOT(setValue(int)));

    connect(ui->charWidthSlider, SIGNAL(valueChanged(int)), ui->charWidthBox, SLOT(setValue(int)));
    connect(ui->charWidthBox, SIGNAL(valueChanged(int)), ui->charWidthSlider, SLOT(setValue(int)));

    connect(ui->charHeightSlider, SIGNAL(valueChanged(int)), ui->charHeightBox, SLOT(setValue(int)));
    connect(ui->charHeightBox, SIGNAL(valueChanged(int)), ui->charHeightSlider, SLOT(setValue(int)));

    connect(ui->contourAreaSlider, SIGNAL(valueChanged(int)), ui->contourAreaBox, SLOT(setValue(int)));
    connect(ui->contourAreaBox, SIGNAL(valueChanged(int)), ui->contourAreaSlider, SLOT(setValue(int)));

    connect(ui->blockSizeSlider, SIGNAL(valueChanged(int)), ui->blockSizeBox, SLOT(setValue(int)));
    connect(ui->blockSizeBox, SIGNAL(valueChanged(int)), ui->blockSizeSlider, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::processImage()
{
    if(image.empty()) {
        return;
    }
    cv::cvtColor(image, imageGrayscale, CV_BGR2GRAY);
    cv::GaussianBlur(imageGrayscale, imageBlurred, cv::Size(blurSize, blurSize), 0);
    cv::adaptiveThreshold(imageBlurred, imageThresholded, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, blockSize, 2);
    imageThresholdedCopy = imageThresholded.clone();
}

void MainWindow::displayImage()
{
    this->dImage = QImage(imageThresholdedCopy.data, imageThresholdedCopy.cols,
                          imageThresholdedCopy.rows, QImage::Format_Grayscale8);

    ui->imageLabel->setPixmap(QPixmap::fromImage(dImage));
}

void MainWindow::on_actionImage_triggered()
{
    fileName = QFileDialog::getOpenFileName(this, "Open Image", QDir::currentPath(), tr("Image Files(*.jpg *.png *.gif *.bmp)")).toStdString();
    if(fileName.empty()) {
        return;
    } else {
        image = cv::imread(fileName);
    }
    processImage();
    displayImage();
    ui->blurSizeBox->setEnabled(true);
    ui->blurSizeSlider->setEnabled(true);
    ui->charWidthBox->setEnabled(true);
    ui->charWidthSlider->setEnabled(true);
    ui->charHeightBox->setEnabled(true);
    ui->charHeightSlider->setEnabled(true);
    ui->contourAreaBox->setEnabled(true);
    ui->contourAreaSlider->setEnabled(true);
    ui->blockSizeBox->setEnabled(true);
    ui->blockSizeSlider->setEnabled(true);
    ui->contourAreaSlider->setEnabled(true);
    ui->contourAreaBox->setEnabled(true);
    if(!classificationNumbers.empty() && !trainingImagesAsFlattenedFloats.empty()) {
        ui->pushButton->setEnabled(true);
    }
}

void MainWindow::on_actionTraining_File_triggered()
{
    trainingFileName = QFileDialog::getOpenFileName(this, "Open Training File", QDir::currentPath()).toStdString();
    if(trainingFileName.empty()) {
        return;
    } else {
        openTrainingFile();
    }
}

void MainWindow::openTrainingFile()
{
    cv::FileStorage fs(trainingFileName, cv::FileStorage::READ);
    fs["classifications"] >> classificationNumbers;
    fs["images"] >> trainingImagesAsFlattenedFloats;
    if(classificationNumbers.empty() || trainingImagesAsFlattenedFloats.empty()) {
        QMessageBox::information(this, "Error", "Error opening training file");
        return;
    }
    QMessageBox::information(this, "Done", "Training File opened");
    fs.release();
    if(!image.empty()) {
        ui->pushButton->setEnabled(true);
    }
}

void MainWindow::on_pushButton_clicked()
{
    OCRDialog dialog(this, classificationNumbers, trainingImagesAsFlattenedFloats, imageThresholded);
    dialog.exec();
}

void MainWindow::on_blurSizeSlider_valueChanged(int value)
{
    if(value > 1 && value % 2 == 1) {
        blurSize = value;
        processImage();
        displayImage();
    }
}

void MainWindow::on_blurSizeBox_valueChanged(int arg1)
{
    if(arg1 > 1 && arg1 % 2 == 1) {
        blurSize = arg1;
        processImage();
        displayImage();
    }
}

void MainWindow::on_charWidthSlider_valueChanged(int value)
{
    charWidth = value;
}

void MainWindow::on_charWidthBox_valueChanged(int arg1)
{
    charWidth = arg1;
}

void MainWindow::on_charHeightSlider_valueChanged(int value)
{
    charHeight = value;
}

void MainWindow::on_charHeightBox_valueChanged(int arg1)
{
    charHeight = arg1;
}

void MainWindow::on_contourAreaSlider_valueChanged(int value)
{
    contourArea = value;
}

void MainWindow::on_contourAreaBox_valueChanged(int arg1)
{
    contourArea = arg1;
}

void MainWindow::on_blockSizeSlider_valueChanged(int value)
{
    if(value > 1 && value % 2 == 1) {
        blockSize = value;
        processImage();
        displayImage();
    }
}

void MainWindow::on_blockSizeBox_valueChanged(int arg1)
{
    if(arg1 > 1 && arg1 % 2 == 1) {
        blockSize = arg1;
        processImage();
        displayImage();
    }
}
