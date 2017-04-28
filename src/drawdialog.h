#ifndef DRAWDIALOG_H
#define DRAWDIALOG_H

#include <QDialog>
#include <QTimer>
#include "common.h"

namespace Ui {
class drawDialog;
}

class drawDialog : public QDialog
{
    Q_OBJECT

public:
    explicit drawDialog(QWidget *parent = 0);
    ~drawDialog();

private slots:

    void on_toolButton_backMainWindow_clicked();


private:
    Ui::drawDialog *ui;

};

#endif // DRAWDIALOG_H
