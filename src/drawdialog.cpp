#include "drawdialog.h"
#include "ui_drawdialog.h"
#include "handgesture.h"

drawDialog::drawDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::drawDialog)
{
    ui->setupUi(this);

}

drawDialog::~drawDialog()
{
    delete ui;

}


void drawDialog::on_toolButton_backMainWindow_clicked()
{
    PRT_INFO("\n");
    this->close();
}
