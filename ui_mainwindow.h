/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QScrollBar *horizontalScrollBar_ant;
    QLCDNumber *lcdNumber_ant;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QScrollBar *horizontalScrollBar_city;
    QLCDNumber *lcdNumber_city;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QScrollBar *horizontalScrollBar_iter;
    QLCDNumber *lcdNumber_iter;
    QGroupBox *groupBox_2;
    QDoubleSpinBox *doubleSpinBox_alpha;
    QGroupBox *groupBox_3;
    QDoubleSpinBox *doubleSpinBox_beta;
    QGroupBox *groupBox_4;
    QDoubleSpinBox *doubleSpinBox_rho;
    QTextBrowser *textBrowser;
    QPlainTextEdit *plainTextEdit_it;
    QPlainTextEdit *plainTextEdit_time;
    QToolButton *toolButton;
    QPushButton *pushButton_start;
    QPlainTextEdit *plainTextEdit_start;
    QPushButton *pushButton_initial;
    QGraphicsView *graphicsView_display;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 450);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1024, 450));
        MainWindow->setMaximumSize(QSize(1024, 450));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 10, 1021, 201));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        horizontalLayoutWidget = new QWidget(groupBox);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 30, 314, 38));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        horizontalScrollBar_ant = new QScrollBar(horizontalLayoutWidget);
        horizontalScrollBar_ant->setObjectName(QStringLiteral("horizontalScrollBar_ant"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(horizontalScrollBar_ant->sizePolicy().hasHeightForWidth());
        horizontalScrollBar_ant->setSizePolicy(sizePolicy2);
        horizontalScrollBar_ant->setMinimum(1);
        horizontalScrollBar_ant->setMaximum(300);
        horizontalScrollBar_ant->setPageStep(1);
        horizontalScrollBar_ant->setValue(5);
        horizontalScrollBar_ant->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalScrollBar_ant);

        lcdNumber_ant = new QLCDNumber(horizontalLayoutWidget);
        lcdNumber_ant->setObjectName(QStringLiteral("lcdNumber_ant"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lcdNumber_ant->sizePolicy().hasHeightForWidth());
        lcdNumber_ant->setSizePolicy(sizePolicy3);
        lcdNumber_ant->setDigitCount(3);

        horizontalLayout->addWidget(lcdNumber_ant);

        horizontalLayoutWidget_2 = new QWidget(groupBox);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(340, 30, 326, 38));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        horizontalScrollBar_city = new QScrollBar(horizontalLayoutWidget_2);
        horizontalScrollBar_city->setObjectName(QStringLiteral("horizontalScrollBar_city"));
        sizePolicy2.setHeightForWidth(horizontalScrollBar_city->sizePolicy().hasHeightForWidth());
        horizontalScrollBar_city->setSizePolicy(sizePolicy2);
        horizontalScrollBar_city->setMinimum(3);
        horizontalScrollBar_city->setMaximum(120);
        horizontalScrollBar_city->setPageStep(1);
        horizontalScrollBar_city->setValue(8);
        horizontalScrollBar_city->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalScrollBar_city);

        lcdNumber_city = new QLCDNumber(horizontalLayoutWidget_2);
        lcdNumber_city->setObjectName(QStringLiteral("lcdNumber_city"));
        sizePolicy3.setHeightForWidth(lcdNumber_city->sizePolicy().hasHeightForWidth());
        lcdNumber_city->setSizePolicy(sizePolicy3);
        lcdNumber_city->setDigitCount(3);

        horizontalLayout_2->addWidget(lcdNumber_city);

        horizontalLayoutWidget_3 = new QWidget(groupBox);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(680, 30, 331, 40));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setFont(font);

        horizontalLayout_3->addWidget(label_3);

        horizontalScrollBar_iter = new QScrollBar(horizontalLayoutWidget_3);
        horizontalScrollBar_iter->setObjectName(QStringLiteral("horizontalScrollBar_iter"));
        sizePolicy2.setHeightForWidth(horizontalScrollBar_iter->sizePolicy().hasHeightForWidth());
        horizontalScrollBar_iter->setSizePolicy(sizePolicy2);
        horizontalScrollBar_iter->setMinimum(1);
        horizontalScrollBar_iter->setMaximum(1000);
        horizontalScrollBar_iter->setPageStep(1);
        horizontalScrollBar_iter->setValue(50);
        horizontalScrollBar_iter->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalScrollBar_iter);

        lcdNumber_iter = new QLCDNumber(horizontalLayoutWidget_3);
        lcdNumber_iter->setObjectName(QStringLiteral("lcdNumber_iter"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        lcdNumber_iter->setFont(font1);
        lcdNumber_iter->setDigitCount(4);

        horizontalLayout_3->addWidget(lcdNumber_iter);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 70, 120, 80));
        QFont font2;
        font2.setFamily(QStringLiteral("Courier New"));
        groupBox_2->setFont(font2);
        doubleSpinBox_alpha = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_alpha->setObjectName(QStringLiteral("doubleSpinBox_alpha"));
        doubleSpinBox_alpha->setGeometry(QRect(20, 30, 91, 31));
        doubleSpinBox_alpha->setMinimum(0.01);
        doubleSpinBox_alpha->setMaximum(5);
        doubleSpinBox_alpha->setSingleStep(0.01);
        doubleSpinBox_alpha->setValue(1);
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(130, 70, 120, 80));
        groupBox_3->setFont(font2);
        doubleSpinBox_beta = new QDoubleSpinBox(groupBox_3);
        doubleSpinBox_beta->setObjectName(QStringLiteral("doubleSpinBox_beta"));
        doubleSpinBox_beta->setGeometry(QRect(20, 30, 91, 31));
        doubleSpinBox_beta->setMinimum(0.01);
        doubleSpinBox_beta->setMaximum(150000);
        doubleSpinBox_beta->setSingleStep(0.01);
        doubleSpinBox_beta->setValue(5);
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(260, 70, 120, 80));
        groupBox_4->setFont(font2);
        doubleSpinBox_rho = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_rho->setObjectName(QStringLiteral("doubleSpinBox_rho"));
        doubleSpinBox_rho->setGeometry(QRect(20, 30, 91, 31));
        doubleSpinBox_rho->setMinimum(0.01);
        doubleSpinBox_rho->setMaximum(0.99);
        doubleSpinBox_rho->setSingleStep(0.01);
        doubleSpinBox_rho->setValue(0.95);
        textBrowser = new QTextBrowser(groupBox);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(390, 80, 620, 111));
        QFont font3;
        font3.setFamily(QStringLiteral("Courier New"));
        font3.setPointSize(13);
        textBrowser->setFont(font3);
        plainTextEdit_it = new QPlainTextEdit(groupBox);
        plainTextEdit_it->setObjectName(QStringLiteral("plainTextEdit_it"));
        plainTextEdit_it->setGeometry(QRect(10, 140, 360, 30));
        plainTextEdit_time = new QPlainTextEdit(groupBox);
        plainTextEdit_time->setObjectName(QStringLiteral("plainTextEdit_time"));
        plainTextEdit_time->setGeometry(QRect(10, 170, 360, 30));
        toolButton = new QToolButton(groupBox);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(420, 0, 141, 22));
        QFont font4;
        font4.setPointSize(13);
        toolButton->setFont(font4);
        pushButton_start = new QPushButton(centralWidget);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));
        pushButton_start->setEnabled(false);
        pushButton_start->setGeometry(QRect(880, 350, 114, 51));
        pushButton_start->setFont(font);
        plainTextEdit_start = new QPlainTextEdit(centralWidget);
        plainTextEdit_start->setObjectName(QStringLiteral("plainTextEdit_start"));
        plainTextEdit_start->setGeometry(QRect(10, 210, 851, 190));
        QFont font5;
        font5.setFamily(QStringLiteral("Courier New"));
        font5.setPointSize(13);
        font5.setBold(true);
        font5.setWeight(75);
        plainTextEdit_start->setFont(font5);
        plainTextEdit_start->setReadOnly(true);
        pushButton_initial = new QPushButton(centralWidget);
        pushButton_initial->setObjectName(QStringLiteral("pushButton_initial"));
        pushButton_initial->setGeometry(QRect(880, 310, 114, 51));
        pushButton_initial->setFont(font);
        graphicsView_display = new QGraphicsView(centralWidget);
        graphicsView_display->setObjectName(QStringLiteral("graphicsView_display"));
        graphicsView_display->setGeometry(QRect(780, 360, 81, 41));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(870, 220, 130, 20));
        checkBox->setChecked(true);
        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(870, 280, 150, 20));
        checkBox_2->setChecked(true);
        checkBox_3 = new QCheckBox(centralWidget);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setGeometry(QRect(870, 250, 151, 20));
        MainWindow->setCentralWidget(centralWidget);
        graphicsView_display->raise();
        groupBox->raise();
        pushButton_start->raise();
        plainTextEdit_start->raise();
        pushButton_initial->raise();
        checkBox->raise();
        checkBox_2->raise();
        checkBox_3->raise();
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Travelling Salesman Problem (TSP) using Ant Colony Optimization (ACO) algorithm", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Parameters", nullptr));
        label->setText(QApplication::translate("MainWindow", "Number of ants:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Number of cities:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Number of iterations:", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Alpha value:", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Beta value:", nullptr));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Rho value:", nullptr));
        textBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Courier New'; font-size:13pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Menlo'; color:#090408; background-color:#ffffff;\">Rho: pheromone\342\200\231s evaporation rate</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Menlo'; color:#090408; background-color:#ffffff;\">Alpha(\316\261): importance of the pheromone level that affects ants\342\200\231 path selection</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0"
                        "px; background-color:#ffffff;\"><span style=\" font-family:'Menlo'; color:#090408; background-color:#ffffff;\">Beta(\316\262): importance of the path\342\200\231s visibility</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'Menlo'; color:#090408; background-color:#ffffff;\">m: the number of ants</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'Menlo'; color:#090408; background-color:#ffffff;\">n: the number of cities</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; background-color:#ffffff;\"><span style=\" font-family:'Menlo'; color:#090408; background-color:#ffffff;\">Iteration: the max iteration times for searching</span></p></body></html>", nullptr));
        plainTextEdit_it->setPlainText(QApplication::translate("MainWindow", "Progress...", nullptr));
        plainTextEdit_time->setPlainText(QApplication::translate("MainWindow", "Running time...", nullptr));
        toolButton->setText(QApplication::translate("MainWindow", "Load city map ...", nullptr));
        pushButton_start->setText(QApplication::translate("MainWindow", "Start", nullptr));
        plainTextEdit_start->setPlainText(QApplication::translate("MainWindow", "Message:", nullptr));
        pushButton_initial->setText(QApplication::translate("MainWindow", "Random map", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "Display message", nullptr));
        checkBox_2->setText(QApplication::translate("MainWindow", "Show ACO result", nullptr));
        checkBox_3->setText(QApplication::translate("MainWindow", "Show Brute Force", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
