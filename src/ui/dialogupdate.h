#ifndef DIALOGUPDATE_H
#define DIALOGUPDATE_H

#include <QDialog>

namespace Ui {
class DialogUpdate;
}

class DialogUpdate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUpdate(QWidget *parent = nullptr);
    ~DialogUpdate();
    void setType(bool isUpdate);

private slots:
    void on_btn_ok_clicked();
    void on_btn_cancel_clicked();

private:
    Ui::DialogUpdate *ui;
    int m_id = -1;
    bool m_isUpdate = false;
};

#endif // DIALOGUPDATE_H
