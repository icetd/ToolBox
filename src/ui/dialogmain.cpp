#include "dialogmain.h"
#include "ui_dialogmain.h"

DialogMain::DialogMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogMain)
{
    ui->setupUi(this);
}

DialogMain::~DialogMain()
{
    delete ui;
}
