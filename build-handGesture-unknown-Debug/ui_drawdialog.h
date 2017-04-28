/********************************************************************************
** Form generated from reading UI file 'drawdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWDIALOG_H
#define UI_DRAWDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_drawDialog
{
public:
    QGroupBox *groupBox;
    QLabel *label_drawing;
    QToolButton *toolButton_backMainWindow;

    void setupUi(QDialog *drawDialog)
    {
        if (drawDialog->objectName().isEmpty())
            drawDialog->setObjectName(QString::fromUtf8("drawDialog"));
        drawDialog->resize(800, 500);
        groupBox = new QGroupBox(drawDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 800, 500));
        label_drawing = new QLabel(groupBox);
        label_drawing->setObjectName(QString::fromUtf8("label_drawing"));
        label_drawing->setGeometry(QRect(0, 40, 800, 460));
        toolButton_backMainWindow = new QToolButton(groupBox);
        toolButton_backMainWindow->setObjectName(QString::fromUtf8("toolButton_backMainWindow"));
        toolButton_backMainWindow->setGeometry(QRect(730, 10, 51, 31));

        retranslateUi(drawDialog);

        QMetaObject::connectSlotsByName(drawDialog);
    } // setupUi

    void retranslateUi(QDialog *drawDialog)
    {
        drawDialog->setWindowTitle(QApplication::translate("drawDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("drawDialog", "    DrawingBoard", 0, QApplication::UnicodeUTF8));
        label_drawing->setText(QString());
        toolButton_backMainWindow->setText(QApplication::translate("drawDialog", "back", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class drawDialog: public Ui_drawDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWDIALOG_H
