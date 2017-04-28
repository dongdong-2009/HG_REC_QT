/********************************************************************************
** Form generated from reading UI file 'drawing.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWING_H
#define UI_DRAWING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Drawing
{
public:
    QGroupBox *groupBox;
    QLabel *label_drawing;
    QToolButton *toolButton_backMainWindow;

    void setupUi(QWidget *Drawing)
    {
        if (Drawing->objectName().isEmpty())
            Drawing->setObjectName(QString::fromUtf8("Drawing"));
        Drawing->resize(800, 500);
        groupBox = new QGroupBox(Drawing);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 800, 500));
        label_drawing = new QLabel(groupBox);
        label_drawing->setObjectName(QString::fromUtf8("label_drawing"));
        label_drawing->setGeometry(QRect(0, 40, 800, 460));
        toolButton_backMainWindow = new QToolButton(groupBox);
        toolButton_backMainWindow->setObjectName(QString::fromUtf8("toolButton_backMainWindow"));
        toolButton_backMainWindow->setGeometry(QRect(740, 10, 31, 31));
        toolButton_backMainWindow->setStyleSheet(QString::fromUtf8("border-image: url(:/back.jpg);"));

        retranslateUi(Drawing);

        QMetaObject::connectSlotsByName(Drawing);
    } // setupUi

    void retranslateUi(QWidget *Drawing)
    {
        Drawing->setWindowTitle(QApplication::translate("Drawing", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Drawing", "  Drawing", 0, QApplication::UnicodeUTF8));
        label_drawing->setText(QString());
        toolButton_backMainWindow->setText(QApplication::translate("Drawing", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Drawing: public Ui_Drawing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWING_H
