/********************************************************************************
** Form generated from reading UI file 'handgesture.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HANDGESTURE_H
#define UI_HANDGESTURE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_handGesture
{
public:
    QGroupBox *groupBox;
    QLabel *label_srcScreen;
    QLabel *label_cvtScreen;
    QGroupBox *groupBox_2;
    QLabel *label_result;
    QGroupBox *groupBox_3;
    QPushButton *pushButton_openCamera;
    QPushButton *pushButton_startRecognize;
    QPushButton *pushButton_captureImage;
    QPushButton *pushButton_DirectionRecognize;

    void setupUi(QWidget *handGesture)
    {
        if (handGesture->objectName().isEmpty())
            handGesture->setObjectName(QString::fromUtf8("handGesture"));
        handGesture->resize(900, 518);
        groupBox = new QGroupBox(handGesture);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 871, 360));
        label_srcScreen = new QLabel(groupBox);
        label_srcScreen->setObjectName(QString::fromUtf8("label_srcScreen"));
        label_srcScreen->setGeometry(QRect(20, 20, 400, 350));
        label_cvtScreen = new QLabel(groupBox);
        label_cvtScreen->setObjectName(QString::fromUtf8("label_cvtScreen"));
        label_cvtScreen->setGeometry(QRect(440, 20, 400, 350));
        groupBox_2 = new QGroupBox(handGesture);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 420, 171, 90));
        label_result = new QLabel(groupBox_2);
        label_result->setObjectName(QString::fromUtf8("label_result"));
        label_result->setGeometry(QRect(0, 20, 151, 61));
        groupBox_3 = new QGroupBox(handGesture);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(230, 400, 321, 101));
        pushButton_openCamera = new QPushButton(groupBox_3);
        pushButton_openCamera->setObjectName(QString::fromUtf8("pushButton_openCamera"));
        pushButton_openCamera->setGeometry(QRect(20, 30, 140, 30));
        pushButton_startRecognize = new QPushButton(groupBox_3);
        pushButton_startRecognize->setObjectName(QString::fromUtf8("pushButton_startRecognize"));
        pushButton_startRecognize->setGeometry(QRect(20, 70, 140, 30));
        pushButton_captureImage = new QPushButton(groupBox_3);
        pushButton_captureImage->setObjectName(QString::fromUtf8("pushButton_captureImage"));
        pushButton_captureImage->setGeometry(QRect(190, 70, 121, 31));
        pushButton_DirectionRecognize = new QPushButton(groupBox_3);
        pushButton_DirectionRecognize->setObjectName(QString::fromUtf8("pushButton_DirectionRecognize"));
        pushButton_DirectionRecognize->setGeometry(QRect(190, 30, 121, 31));

        retranslateUi(handGesture);

        QMetaObject::connectSlotsByName(handGesture);
    } // setupUi

    void retranslateUi(QWidget *handGesture)
    {
        handGesture->setWindowTitle(QApplication::translate("handGesture", "handGesture", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("handGesture", "Camera", 0, QApplication::UnicodeUTF8));
        label_srcScreen->setText(QApplication::translate("handGesture", "<html><head/><body><p align=\"center\"><br/></p><p align=\"center\"><span style=\" font-size:24pt; font-weight:600;\">\345\216\237\345\247\213\345\233\276\345\203\217</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_cvtScreen->setText(QApplication::translate("handGesture", "<html><head/><body><p align=\"center\"><br/></p><p align=\"center\"><span style=\" font-size:24pt; font-weight:600;\">\350\257\206\345\210\253\345\233\276\345\203\217</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("handGesture", "Recongnize Result", 0, QApplication::UnicodeUTF8));
        label_result->setText(QApplication::translate("handGesture", "<html><head/><body><p align=\"center\"><br/><span style=\" font-size:18pt; font-weight:600;\">\350\257\206\345\210\253\347\273\223\346\236\234</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("handGesture", "Operation Area", 0, QApplication::UnicodeUTF8));
        pushButton_openCamera->setText(QApplication::translate("handGesture", "Open Camera", 0, QApplication::UnicodeUTF8));
        pushButton_startRecognize->setText(QApplication::translate("handGesture", "Digit Recognize", 0, QApplication::UnicodeUTF8));
        pushButton_captureImage->setText(QApplication::translate("handGesture", "Capture Image", 0, QApplication::UnicodeUTF8));
        pushButton_DirectionRecognize->setText(QApplication::translate("handGesture", "Dir Recognize", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class handGesture: public Ui_handGesture {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HANDGESTURE_H
