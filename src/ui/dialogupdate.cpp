#include "dialogupdate.h"
#include "ui_dialogupdate.h"
#include "SqlManager.h"

DialogUpdate::DialogUpdate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUpdate)
{
    ui->setupUi(this);
}

DialogUpdate::~DialogUpdate()
{
    delete ui;
}

void DialogUpdate::setType(bool isupdate)
{
    m_isUpdate = isupdate;
}

void DialogUpdate::on_btn_ok_clicked()
{
    QStringList list;
    if (m_isUpdate) {
        m_id = ui->le_id->text().toInt();
    } else {
        m_id = -1;
    }

    list << ui->le_id->text();
    list << ui->le_value->text();
    list << ui->le_codeName->text();
    list << ui->le_footPrint->text();
    list << ui->le_other1->text();
    list << ui->le_other2->text();
    list << ui->le_other3->text();
    list << ui->cb_boxName->currentText();
    list << ui->cb_lineNumber->currentText();
    list << ui->cb_colimnNumber->currentText();
    list << ui->le_jlcNumber->text();
    if (m_id != -1) {
        //update
        SqlManager::getInstance()->updateComponents(list);
        this->hide();
    } else {
        //add
        QVector<QStringList> vec;
        vec.push_back(list);
        SqlManager::getInstance()->addComponents(vec);
        this->hide();
    }
}

void DialogUpdate::on_btn_cancel_clicked()
{
    this->hide();
}