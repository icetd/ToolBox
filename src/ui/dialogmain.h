#ifndef DIALOGMAIN_H
#define DIALOGMAIN_H

#include <QWidget>

#pragma execution_character_set("utf-8")

namespace Ui {
class DialogMain;
}

class DialogMain : public QWidget
{
    Q_OBJECT

public:
    explicit DialogMain(QWidget *parent = nullptr);
    ~DialogMain();

private:
    Ui::DialogMain *ui;
};

#endif // DIALOGMAIN_H
