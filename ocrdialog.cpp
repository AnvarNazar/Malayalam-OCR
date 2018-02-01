#include "ocrdialog.h"
#include "ui_ocrdialog.h"

OCRDialog::OCRDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OCRDialog)
{
    ui->setupUi(this);
}

OCRDialog::~OCRDialog()
{
    delete ui;
}
