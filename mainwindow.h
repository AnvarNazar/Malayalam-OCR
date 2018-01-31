#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
