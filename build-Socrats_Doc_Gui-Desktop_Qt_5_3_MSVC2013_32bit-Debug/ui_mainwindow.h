/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCarregar_estado;
    QAction *actionSalvar_estado;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_12;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxX;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *spinBox_N_agentes;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QSpinBox *spinBoxRaio;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QSpinBox *spinBoxMinPts;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_9;
    QDoubleSpinBox *doubleSpinBoxEps;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpinBox *spinBox_MemLength;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButtonIndividual;
    QRadioButton *radioButtonGrupal;
    QPushButton *pushButtonGeraMundo;
    QPushButton *pushButtonRodaUm;
    QPushButton *pushButtonRodaIniciar;
    QPushButton *pushButtonMov_Clust;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSpinBox *spinBoxContaTurnos;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_10;
    QSpinBox *spinBoxClusters;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menuBar;
    QMenu *menuArquivo;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroupMemType;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(737, 545);
        actionCarregar_estado = new QAction(MainWindow);
        actionCarregar_estado->setObjectName(QStringLiteral("actionCarregar_estado"));
        actionSalvar_estado = new QAction(MainWindow);
        actionSalvar_estado->setObjectName(QStringLiteral("actionSalvar_estado"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_12 = new QHBoxLayout(centralWidget);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        doubleSpinBoxX = new QDoubleSpinBox(centralWidget);
        doubleSpinBoxX->setObjectName(QStringLiteral("doubleSpinBoxX"));
        doubleSpinBoxX->setMaximum(1e+09);
        doubleSpinBoxX->setValue(25);

        horizontalLayout->addWidget(doubleSpinBoxX);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        spinBox_N_agentes = new QSpinBox(centralWidget);
        spinBox_N_agentes->setObjectName(QStringLiteral("spinBox_N_agentes"));
        spinBox_N_agentes->setMaximum(999999999);
        spinBox_N_agentes->setValue(100);

        horizontalLayout_2->addWidget(spinBox_N_agentes);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_3->addWidget(label_6);

        spinBoxRaio = new QSpinBox(centralWidget);
        spinBoxRaio->setObjectName(QStringLiteral("spinBoxRaio"));
        spinBoxRaio->setValue(2);

        horizontalLayout_3->addWidget(spinBoxRaio);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_9->addWidget(label_8);

        spinBoxMinPts = new QSpinBox(centralWidget);
        spinBoxMinPts->setObjectName(QStringLiteral("spinBoxMinPts"));
        spinBoxMinPts->setValue(3);

        horizontalLayout_9->addWidget(spinBoxMinPts);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_10->addWidget(label_9);

        doubleSpinBoxEps = new QDoubleSpinBox(centralWidget);
        doubleSpinBoxEps->setObjectName(QStringLiteral("doubleSpinBoxEps"));
        doubleSpinBoxEps->setValue(3);

        horizontalLayout_10->addWidget(doubleSpinBoxEps);


        verticalLayout_3->addLayout(horizontalLayout_10);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        spinBox_MemLength = new QSpinBox(centralWidget);
        spinBox_MemLength->setObjectName(QStringLiteral("spinBox_MemLength"));
        spinBox_MemLength->setMaximum(999999);
        spinBox_MemLength->setValue(20);

        horizontalLayout_4->addWidget(spinBox_MemLength);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_6->addWidget(label_5);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        radioButtonIndividual = new QRadioButton(centralWidget);
        buttonGroupMemType = new QButtonGroup(MainWindow);
        buttonGroupMemType->setObjectName(QStringLiteral("buttonGroupMemType"));
        buttonGroupMemType->addButton(radioButtonIndividual);
        radioButtonIndividual->setObjectName(QStringLiteral("radioButtonIndividual"));
        radioButtonIndividual->setChecked(true);

        verticalLayout->addWidget(radioButtonIndividual);

        radioButtonGrupal = new QRadioButton(centralWidget);
        buttonGroupMemType->addButton(radioButtonGrupal);
        radioButtonGrupal->setObjectName(QStringLiteral("radioButtonGrupal"));
        radioButtonGrupal->setChecked(false);

        verticalLayout->addWidget(radioButtonGrupal);


        horizontalLayout_6->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout_6);

        pushButtonGeraMundo = new QPushButton(centralWidget);
        pushButtonGeraMundo->setObjectName(QStringLiteral("pushButtonGeraMundo"));

        verticalLayout_3->addWidget(pushButtonGeraMundo);

        pushButtonRodaUm = new QPushButton(centralWidget);
        pushButtonRodaUm->setObjectName(QStringLiteral("pushButtonRodaUm"));

        verticalLayout_3->addWidget(pushButtonRodaUm);

        pushButtonRodaIniciar = new QPushButton(centralWidget);
        pushButtonRodaIniciar->setObjectName(QStringLiteral("pushButtonRodaIniciar"));

        verticalLayout_3->addWidget(pushButtonRodaIniciar);

        pushButtonMov_Clust = new QPushButton(centralWidget);
        pushButtonMov_Clust->setObjectName(QStringLiteral("pushButtonMov_Clust"));

        verticalLayout_3->addWidget(pushButtonMov_Clust);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_5->addWidget(label_4);

        spinBoxContaTurnos = new QSpinBox(centralWidget);
        spinBoxContaTurnos->setObjectName(QStringLiteral("spinBoxContaTurnos"));
        spinBoxContaTurnos->setMaximum(999999999);

        horizontalLayout_5->addWidget(spinBoxContaTurnos);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_11->addWidget(label_10);

        spinBoxClusters = new QSpinBox(centralWidget);
        spinBoxClusters->setObjectName(QStringLiteral("spinBoxClusters"));

        horizontalLayout_11->addWidget(spinBoxClusters);


        verticalLayout_3->addLayout(horizontalLayout_11);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_8->addLayout(verticalLayout_3);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 170, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(0, 255, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(0, 212, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(0, 85, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(0, 113, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush7(QColor(0, 255, 127, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush7);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush8(QColor(127, 212, 127, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush8);
        QBrush brush9(QColor(255, 255, 220, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        groupBox->setPalette(palette);
        groupBox->setAutoFillBackground(false);
        horizontalLayout_7 = new QHBoxLayout(groupBox);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer = new QSpacerItem(510, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        verticalSpacer_2 = new QSpacerItem(20, 377, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_7->addItem(verticalSpacer_2);


        horizontalLayout_8->addWidget(groupBox);


        horizontalLayout_12->addLayout(horizontalLayout_8);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 737, 21));
        menuArquivo = new QMenu(menuBar);
        menuArquivo->setObjectName(QStringLiteral("menuArquivo"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuArquivo->menuAction());
        menuArquivo->addAction(actionCarregar_estado);
        menuArquivo->addAction(actionSalvar_estado);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Socrats", 0));
        actionCarregar_estado->setText(QApplication::translate("MainWindow", "Carregar estado", 0));
        actionSalvar_estado->setText(QApplication::translate("MainWindow", "Salvar estado", 0));
        label->setText(QApplication::translate("MainWindow", "Lado do mundo", 0));
        label_2->setText(QApplication::translate("MainWindow", "Quantidade de agentes", 0));
        label_6->setText(QApplication::translate("MainWindow", "Raio", 0));
        label_8->setText(QApplication::translate("MainWindow", "MinPts", 0));
        label_9->setText(QApplication::translate("MainWindow", "Eps", 0));
        label_3->setText(QApplication::translate("MainWindow", "Tamanho da Memoria", 0));
        label_5->setText(QApplication::translate("MainWindow", "Tipo de mem\303\263ria", 0));
        radioButtonIndividual->setText(QApplication::translate("MainWindow", "Individual", 0));
        radioButtonGrupal->setText(QApplication::translate("MainWindow", "Coletivo", 0));
        pushButtonGeraMundo->setText(QApplication::translate("MainWindow", "Gerar Mundo", 0));
        pushButtonRodaUm->setText(QApplication::translate("MainWindow", "Rodar um passo", 0));
        pushButtonRodaIniciar->setText(QApplication::translate("MainWindow", "Iniciar Simula\303\247\303\243o", 0));
        pushButtonMov_Clust->setText(QApplication::translate("MainWindow", "Moving clusters", 0));
        label_4->setText(QApplication::translate("MainWindow", "Numero de turnos", 0));
        label_10->setText(QApplication::translate("MainWindow", "N. Clusters", 0));
        groupBox->setTitle(QString());
        menuArquivo->setTitle(QApplication::translate("MainWindow", "Arquivo", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
