#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <student.h>

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
    void clr_table();
    void fill_table();
    void size_table();
    void refresh_table();
    void refresh_add_input();
    void refresh_edit_input();
    void refresh_edit_content();
    void sort();

    void on_action_Open_triggered();
    void on_action_Save_triggered();
    void on_pushButton_add_clicked();
    void on_pushButton_add_clear_clicked();

    void on_pushButton_edit_save_clicked();

    void on_pushButton_edit_delete_clicked();

private:
    Ui::MainWindow *ui;
    QList<Student> Students;
};
#endif // MAINWINDOW_H
