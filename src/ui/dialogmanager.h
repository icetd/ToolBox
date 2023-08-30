#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include <QWidget>
#include <QList>
#include <QStandardItemModel>

#pragma execution_character_set("utf-8")

namespace Ui {
class DialogManager;
}

class DialogManager : public QWidget
{
    Q_OBJECT

public:
    explicit DialogManager(QWidget *parent = nullptr);
    ~DialogManager();

    void initPage(QString strCondition = "");

private slots:
    void on_le_searchValue_textChanged(const QString &value);
    void on_le_searchFootPrint_textChanged(const QString &value);
    void on_le_searchBoxName_textChanged(const QString &value);
    void on_btn_import_clicked();
    void on_btn_update_clicked();
    void on_btn_delete_clicked();

private:
    Ui::DialogManager *ui;
    QStandardItemModel itemModel;
};

#endif // DIALOGMANAGER_H
