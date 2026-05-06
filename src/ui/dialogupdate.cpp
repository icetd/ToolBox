#include "dialogupdate.h"
#include "ui_dialogupdate.h"
#include "SqlManager.h"
#include <QDebug>
#include "ini.h"
#include "INIREader.h"

DialogUpdate::DialogUpdate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUpdate)
{
    ui->setupUi(this);
    initComboBoxFromConfig();
}

DialogUpdate::~DialogUpdate()
{
    delete ui;
}

void DialogUpdate::setType(bool isupdate)
{
    m_isUpdate = isupdate;
}

void DialogUpdate::setComponentInfo(const QStringList& info)
{
    if (info.size() < 11) return;

    m_id = info[0].toInt(); 
    
    ui->le_id->setText(info[0]);                    // 编号
    ui->le_value->setText(info[1]);                 // 数值
    ui->le_codeName->setText(info[2]);              // 代号
    ui->le_footPrint->setText(info[3]);             // 封装
    ui->le_other1->setText(info[4]);                // 其他1
    ui->le_other2->setText(info[5]);                // 其他2
    ui->le_other3->setText(info[6]);                // 其他3
    ui->cb_boxName->setCurrentText(info[7]);        // 盒号
    ui->cb_lineNumber->setCurrentText(info[8]);     // 行号
    ui->cb_colimnNumber->setCurrentText(info[9]);   // 列号
    ui->le_jlcNumber->setText(info[10]);            // 嘉立创编号
}

void DialogUpdate::setAutoId(const QString& id)
{
    ui->le_id->setText(id);
    ui->le_id->setReadOnly(true);  // 设为只读，不让用户修改
}

void DialogUpdate::on_btn_ok_clicked()
{
    QStringList list;
    
    if (m_isUpdate) {
        // 修改模式：使用保存的 m_id，而不是从界面读取
        list << QString::number(m_id);  // 使用保存的ID
    } else {
        // 新增模式：ID留空或-1
        list << "";  // 或者 list << "-1";
    }
    
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
    
    if (m_isUpdate) {
        // 修改
        SqlManager::getInstance()->updateComponents(list);
    } else {
        // 新增
        QVector<QStringList> vec;
        vec.push_back(list);
        SqlManager::getInstance()->addComponents(vec);
    }
    
    this->hide();
}

void DialogUpdate::on_btn_cancel_clicked()
{
    this->hide();
}

void DialogUpdate::initComboBoxFromConfig()
{
    // 使用 INIReader 读取配置文件
    INIReader reader("config/config.ini");
    
    if (reader.ParseError() != 0) {
        qDebug() << "Error parsing config file";
        return;
    }
    
    // 读取配置，Get 的参数是 (section, key, default_value)
    std::string boxNamesStr = reader.Get("PATH", "boxName", "");
    std::string lineNumbersStr = reader.Get("PATH", "lineNumber", "");
    std::string columnNumbersStr = reader.Get("PATH", "columnNumber", "");
    
    QString boxNames = QString::fromStdString(boxNamesStr);
    QString lineNumbers = QString::fromStdString(lineNumbersStr);
    QString columnNumbers = QString::fromStdString(columnNumbersStr);
    
    qDebug() << "boxNames:" << boxNames;
    qDebug() << "lineNumbers:" << lineNumbers;
    qDebug() << "columnNumbers:" << columnNumbers;
    
    if (!boxNames.isEmpty()) {
        ui->cb_boxName->addItems(boxNames.split(","));
    }
    
    if (!lineNumbers.isEmpty()) {
        ui->cb_lineNumber->addItems(lineNumbers.split(","));
    }
    
    if (!columnNumbers.isEmpty()) {
        ui->cb_colimnNumber->addItems(columnNumbers.split(","));
    }
}