#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ToolBox");
    QFile qss(":theme/macos.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    initPage();

    connect(ui->actionHome, SIGNAL(triggered(bool)), this, SLOT(changePage()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(exit()));
    connect(ui->actionManagerComponent, SIGNAL(triggered(bool)), this, SLOT(changePage()));
    connect(ui->actionChangeTheme, SIGNAL(triggered(bool)), this, SLOT(changeTheme()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initPage()
{
    dialogMain = new DialogMain(this);
    dialogManager = new DialogManager(this);

    ui->stackedWidget->addWidget(dialogMain);
    ui->stackedWidget->addWidget(dialogManager);
    ui->stackedWidget->setCurrentIndex(DialogIndex_t::MANAGER);
    dialogManager->initPage();
}

void MainWindow::changePage()
{
    auto name = sender()->objectName();
    if (name == "actionHome") {
        ui->stackedWidget->setCurrentIndex(DialogIndex_t::MAIN);
    } else if (name == "actionManagerComponent") {
        ui->stackedWidget->setCurrentIndex(DialogIndex_t::MANAGER);
        dialogManager->initPage();
    }
}

void MainWindow::changeTheme()
{
    if (currentTheme == 0) {
        /*Load qss*/
        QFile qss(":theme/ubuntu.qss");
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
        currentTheme = 1;
    } else if (currentTheme == 1) {
        QFile qss(":theme/macos.qss");
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
        currentTheme = 0;
    }
}

void MainWindow::exit() {
    this->close();
}