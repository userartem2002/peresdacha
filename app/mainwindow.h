#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog_login.h"
#include "viewing.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();//кнопка для перехода в режим просмотра
    void on_pushButton_2_clicked();//кнопка для перехода в режим редактирования

private:
    Ui::MainWindow *ui;
    Dialog_login *auth;
    Viewing *view;
};

#endif // MAINWINDOW_H
