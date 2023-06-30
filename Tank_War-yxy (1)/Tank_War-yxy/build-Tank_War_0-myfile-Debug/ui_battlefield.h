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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Battlefield
{
public:

    void setupUi(QWidget *Battlefield)
    {
        if (Battlefield->objectName().isEmpty())
            Battlefield->setObjectName(QStringLiteral("Battlefield"));
        Battlefield->resize(1210, 610);

        retranslateUi(Battlefield);

        QMetaObject::connectSlotsByName(Battlefield);
    } // setupUi

    void retranslateUi(QWidget *Battlefield)
    {
        Battlefield->setWindowTitle(QApplication::translate("Battlefield", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Battlefield: public Ui_Battlefield {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATTLEFIELD_H
