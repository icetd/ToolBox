#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogmain.h"
#include "dialogmanager.h"

#pragma execution_character_set("utf-8")

namespace Ui {
class MainWindow;
}

typedef enum {
    MAIN,
    MANAGER
} DialogIndex_t;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void changePage();
    void changeTheme();
    void exit();

private:
    Ui::MainWindow *ui;
    DialogMain *dialogMain;
    DialogManager *dialogManager;
    DialogIndex_t currentDialog;
    bool currentTheme = 0;

    void initPage();
};

#endif // MAINWINDOW_H
