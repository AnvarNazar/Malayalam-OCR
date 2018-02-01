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
    fileName = QFileDialog::getOpenFileName(this, "Open Image", QDir::currentPath(), tr("Image Files(*.jpg *.png *.gif *.bmp)"));
    if(fileName.empty()) {
        return;
    }
    image.release();
    processImage();
    displayImage();
}

void MainWindow::processImage()
{
    if(image.empty()) {
        image = cv::imread(fileName);
        if(image.empty()) {
            QMessageBox::information(this, "Error", "Failed to open image");
            return;
        }
        cv::cvtColor(image, imageGrayscale, CV_BGR2GRAY);
    }
    cv::GaussianBlur(imageGrayscale, imageBlurred, cv::Size(blurSize, blurSize), 0);
    cv::adaptiveThreshold(imageBlurred, imageGrayscale, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, blockSize, 2);
    imageThresholdedCopy = imageThresholded.clone();
}

void MainWindow::displayImage()
{
    this->dImage = QImage(imageThresholdedCopy.data, imageThresholdedCopy.cols,
                          imageThresholdedCopy.rows, QImage::Format_Grayscale8);

    ui->label->setPixmap(QPixmap::fromImage(dImage));
}
