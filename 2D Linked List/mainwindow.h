#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "twodlinkedlist.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow,public twoDLinkedList
{
    Q_OBJECT

    private:
        Ui::MainWindow *ui;
        twoDLinkedList twoDList;

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
private slots:
        void on_Pos_01_textChanged(const QString &arg1);
        void on_Pos_00_textChanged(const QString &arg1);
        void on_Pos_02_textChanged(const QString &arg1);
        void on_Pos_10_textChanged(const QString &arg1);
        void on_Pos_11_textChanged(const QString &arg1);
        void on_Pos_12_textChanged(const QString &arg1);
        void on_Pos_20_textChanged(const QString &arg1);
        void on_Pos_21_textChanged(const QString &arg1);
        void on_Pos_22_textChanged(const QString &arg1);
        void on_pushButton_clicked();
        void on_perimeter_2_clicked();
        void on_diagonalSum_2_clicked();
        void on_transpose_2_clicked();
        void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
