#include "dialogmanager.h"
#include "ui_dialogmanager.h"
#include "SqlManager.h"
#include <QDebug>
#include <QMessageBox>
#include "dialogupdate.h"

DialogManager::DialogManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogManager)
{
    ui->setupUi(this);
}

DialogManager::~DialogManager()
{
    delete ui;
}

void DialogManager::initPage(QString strCondition)
{
    // 查询数据库并显示

    QVector<QStringList> list = SqlManager::getInstance()->getComponents(strCondition);

    itemModel.clear();
    ui->tableView->setModel(&itemModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList headList;
    headList.insert(0, "编号");
    headList.insert(1, "数值");
    headList.insert(2, "代号");
    headList.insert(3, "封装");
    headList.insert(4, "其他1");
    headList.insert(5, "其他2");
    headList.insert(6, "其他3");
    headList.insert(7, "盒号");
    headList.insert(8, "行号");
    headList.insert(9, "列号");
    headList.insert(10, "嘉立创编号");

    itemModel.setHorizontalHeaderLabels(headList);

    for (int i = 0; i < list.size(); i++) {
        QList<QStandardItem*> items;
        for (int j = 0; j < 11; j ++) {
            items.append(new QStandardItem(list[i][j]));
            items.at(j)->setTextAlignment(Qt::AlignCenter);
        }
        itemModel.appendRow(items);
    }
}

void DialogManager::on_le_searchValue_textChanged(const QString &value)
{
    QString condition;
    QString conditionValue = QString("where value like '%%1%'").arg(value);
    QString conditionFootPrint = ui->le_searchFootPrint->text();
    QString conditionBoxName = ui->le_searchBoxName->text();

    condition += conditionValue;

    if((conditionFootPrint != "") && (conditionBoxName != "")) {
        condition = condition +
            QString(" and footPrint like '%%1%'").arg(conditionFootPrint) +
            QString(" and boxName like '%%1%'").arg(conditionBoxName);
    } else if (conditionFootPrint != "") {
        condition = condition + QString(" and footPrint like '%%1%'").arg(conditionFootPrint);
    } else if (conditionBoxName != "") {
        condition = condition + QString(" and boxName like '%%1%'").arg(conditionBoxName);
    }


    initPage(condition);
}

void DialogManager::on_le_searchFootPrint_textChanged(const QString &value)
{
    QString condition;
    QString conditionValue = ui->le_searchValue->text();
    QString conditionFootPrint = QString("where footPrint like '%%1%'").arg(value);
    QString conditionBoxName = ui->le_searchBoxName->text();

    condition += conditionFootPrint;

    if((conditionValue != "") && (conditionBoxName != "")) {
        condition = condition +
                    QString(" and value like '%%1%'").arg(conditionValue) +
                    QString(" and boxName like '%%1%'").arg(conditionBoxName);
    } else if (conditionValue != "") {
        condition = condition + QString(" and value like '%%1%'").arg(conditionValue);
    } else if (conditionBoxName != "") {
        condition = condition + QString(" and boxName like '%%1%'").arg(conditionBoxName);
    }

    initPage(condition);
}

void DialogManager::on_le_searchBoxName_textChanged(const QString &value)
{
    QString condition;
    QString conditionValue = ui->le_searchValue->text();
    QString conditionFootPrint = ui->le_searchFootPrint->text();
    QString conditionBoxName =  QString("where boxName like '%%1%'").arg(value);

    condition += conditionBoxName;

    if((conditionValue != "") && (conditionFootPrint != "")) {
        condition = condition +
                    QString(" and value like '%%1%'").arg(conditionValue) +
                    QString(" and footPrint like '%%1%'").arg(conditionFootPrint);
    } else if (conditionValue != "") {
        condition = condition + QString(" and value like '%%1%'").arg(conditionValue);
    } else if (conditionFootPrint != "") {
        condition = condition + QString(" and footPrint like '%%1%'").arg(conditionFootPrint);
    }

    initPage(condition);
}

void DialogManager::on_btn_import_clicked()
{
    DialogUpdate dialogUpdate;
    dialogUpdate.setType(false);
    dialogUpdate.exec();
    initPage();
    qDebug() << sender()->objectName();
}

void DialogManager::on_btn_update_clicked()
{
    DialogUpdate dialogUpdate;
    dialogUpdate.setType(true);
    dialogUpdate.exec();
    initPage();
    qDebug() << sender()->objectName();
}

void DialogManager::on_btn_delete_clicked()
{
    int row = ui->tableView->currentIndex().row();
    if (row < 0) {
        QMessageBox::information(nullptr, "信息", "请选中元件");
    } else {
	QMessageBox::StandardButton box;
	box = QMessageBox::question(this, "提示", "确实要删除吗?", QMessageBox::Yes | QMessageBox::No);
	if (box == QMessageBox::No)
                return;
	QString id = itemModel.item(row, 0)->text();
        qDebug() << id;
        SqlManager::getInstance()->delComponents(id);
        initPage();
    }

    qDebug() << sender()->objectName();
}