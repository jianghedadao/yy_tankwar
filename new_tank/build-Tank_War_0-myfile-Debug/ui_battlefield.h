/********************************************************************************
** Form generated from reading UI file 'battlefield.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATTLEFIELD_H
#define UI_BATTLEFIELD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Battlefield
{
public:
    QLabel *testlabel;
    QLabel *mouse;

    void setupUi(QWidget *Battlefield)
    {
        if (Battlefield->objectName().isEmpty())
            Battlefield->setObjectName(QStringLiteral("Battlefield"));
        Battlefield->resize(1200, 600);
        testlabel = new QLabel(Battlefield);
        testlabel->setObjectName(QStringLiteral("testlabel"));
        testlabel->setGeometry(QRect(70, 100, 351, 31));
        mouse = new QLabel(Battlefield);
        mouse->setObjectName(QStringLiteral("mouse"));
        mouse->setGeometry(QRect(70, 150, 271, 21));

        retranslateUi(Battlefield);

        QMetaObject::connectSlotsByName(Battlefield);
    } // setupUi

    void retranslateUi(QWidget *Battlefield)
    {
        Battlefield->setWindowTitle(QApplication::translate("Battlefield", "Form", nullptr));
        testlabel->setText(QApplication::translate("Battlefield", "TextLabel", nullptr));
        mouse->setText(QApplication::translate("Battlefield", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Battlefield: public Ui_Battlefield {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATTLEFIELD_H
