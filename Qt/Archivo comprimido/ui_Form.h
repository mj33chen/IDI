/********************************************************************************
** Form generated from reading UI file 'Form.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <MyLCD.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpecialSlider
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    MyLCD *lcdNumber;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;

    void setupUi(QWidget *SpecialSlider)
    {
        if (SpecialSlider->objectName().isEmpty())
            SpecialSlider->setObjectName(QStringLiteral("SpecialSlider"));
        SpecialSlider->resize(525, 65);
        verticalLayout = new QVBoxLayout(SpecialSlider);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lcdNumber = new MyLCD(SpecialSlider);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setMinimumSize(QSize(100, 50));

        horizontalLayout->addWidget(lcdNumber);

        horizontalSlider = new QSlider(SpecialSlider);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMinimumSize(QSize(250, 0));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton = new QPushButton(SpecialSlider);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(SpecialSlider);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(SpecialSlider);
        QObject::connect(pushButton_2, SIGNAL(clicked()), SpecialSlider, SLOT(close()));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), lcdNumber, SLOT(setColorToNumber(int)));
        QObject::connect(pushButton, SIGNAL(clicked()), lcdNumber, SLOT(setToZero()));

        QMetaObject::connectSlotsByName(SpecialSlider);
    } // setupUi

    void retranslateUi(QWidget *SpecialSlider)
    {
        SpecialSlider->setWindowTitle(QApplication::translate("SpecialSlider", "Form", 0));
        pushButton->setText(QApplication::translate("SpecialSlider", "&Zero", 0));
        pushButton_2->setText(QApplication::translate("SpecialSlider", "&Exit", 0));
    } // retranslateUi

};

namespace Ui {
    class SpecialSlider: public Ui_SpecialSlider {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H

