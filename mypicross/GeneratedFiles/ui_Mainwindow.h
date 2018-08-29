/********************************************************************************
** Form generated from reading UI file 'Mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainwindowClass
{
public:
    QWidget *centralWidget;
    QLabel *table;
    QPushButton *gameStart;
    QLabel *numUp;
    QLabel *numDown;
    QLabel *test;
    QPushButton *imgSelection;
    QSlider *difficulty;
    QLCDNumber *timeRecorder;
    QLCDNumber *record;
    QLabel *label;
    QLabel *label_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *hboxLayout;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainwindowClass)
    {
        if (MainwindowClass->objectName().isEmpty())
            MainwindowClass->setObjectName(QStringLiteral("MainwindowClass"));
        MainwindowClass->resize(1132, 866);
        centralWidget = new QWidget(MainwindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        table = new QLabel(centralWidget);
        table->setObjectName(QStringLiteral("table"));
        table->setGeometry(QRect(300, 250, 561, 511));
        gameStart = new QPushButton(centralWidget);
        gameStart->setObjectName(QStringLiteral("gameStart"));
        gameStart->setGeometry(QRect(880, 390, 141, 61));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(18);
        gameStart->setFont(font);
        numUp = new QLabel(centralWidget);
        numUp->setObjectName(QStringLiteral("numUp"));
        numUp->setGeometry(QRect(300, 60, 581, 181));
        numDown = new QLabel(centralWidget);
        numDown->setObjectName(QStringLiteral("numDown"));
        numDown->setGeometry(QRect(50, 260, 581, 541));
        test = new QLabel(centralWidget);
        test->setObjectName(QStringLiteral("test"));
        test->setGeometry(QRect(70, 90, 331, 721));
        imgSelection = new QPushButton(centralWidget);
        imgSelection->setObjectName(QStringLiteral("imgSelection"));
        imgSelection->setGeometry(QRect(880, 480, 141, 61));
        imgSelection->setFont(font);
        difficulty = new QSlider(centralWidget);
        difficulty->setObjectName(QStringLiteral("difficulty"));
        difficulty->setGeometry(QRect(870, 600, 160, 22));
        difficulty->setMaximum(2);
        difficulty->setSliderPosition(1);
        difficulty->setOrientation(Qt::Horizontal);
        difficulty->setTickPosition(QSlider::TicksBelow);
        timeRecorder = new QLCDNumber(centralWidget);
        timeRecorder->setObjectName(QStringLiteral("timeRecorder"));
        timeRecorder->setGeometry(QRect(100, 100, 121, 41));
        record = new QLCDNumber(centralWidget);
        record->setObjectName(QStringLiteral("record"));
        record->setGeometry(QRect(100, 40, 121, 41));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 50, 91, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font1.setPointSize(12);
        label->setFont(font1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 110, 91, 21));
        label_2->setFont(font1);
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(860, 610, 221, 51));
        hboxLayout = new QHBoxLayout(horizontalLayoutWidget);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        label_3->setFont(font2);

        hboxLayout->addWidget(label_3);

        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font2);

        hboxLayout->addWidget(label_4);

        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font2);

        hboxLayout->addWidget(label_5);

        MainwindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainwindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1132, 26));
        MainwindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainwindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainwindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainwindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainwindowClass->setStatusBar(statusBar);

        retranslateUi(MainwindowClass);

        QMetaObject::connectSlotsByName(MainwindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainwindowClass)
    {
        MainwindowClass->setWindowTitle(QApplication::translate("MainwindowClass", "Mainwindow", nullptr));
        table->setText(QApplication::translate("MainwindowClass", "TextLabel", nullptr));
        gameStart->setText(QApplication::translate("MainwindowClass", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        numUp->setText(QString());
        numDown->setText(QString());
        test->setText(QString());
        imgSelection->setText(QApplication::translate("MainwindowClass", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        label->setText(QApplication::translate("MainwindowClass", " \344\270\252\344\272\272\347\272\252\345\275\225", nullptr));
        label_2->setText(QApplication::translate("MainwindowClass", "\350\256\241\346\227\266\345\231\250", nullptr));
        label_3->setText(QApplication::translate("MainwindowClass", "\347\256\200\345\215\225", nullptr));
        label_4->setText(QApplication::translate("MainwindowClass", "\346\231\256\351\200\232", nullptr));
        label_5->setText(QApplication::translate("MainwindowClass", "\345\233\260\351\232\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainwindowClass: public Ui_MainwindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
