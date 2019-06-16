#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>

using namespace std;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->perimeter_2->setVisible(false);
    ui->diagonalSum_2->setVisible(false);
    ui->transpose_2->setVisible(false);
    ui->perimeter->setVisible(false);
    ui->diagonalSum->setVisible(false);
    ui->transpose->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Pos_00_textChanged(const QString &arg1)
{
    twoDList.setMatrixElement(0,0,arg1.toInt());
}

void MainWindow::on_Pos_01_textChanged(const QString &arg1)
{
    twoDList.setMatrixElement(0,1,arg1.toInt());
}

void MainWindow::on_Pos_02_textChanged(const QString &arg1)
{
    twoDList.setMatrixElement(0,2,arg1.toInt());
}

void MainWindow::on_Pos_10_textChanged(const QString &arg1)
{
    twoDList.setMatrixElement(1,0,arg1.toInt());
}

void MainWindow::on_Pos_11_textChanged(const QString &arg1)
{
    twoDList.setMatrixElement(1,1,arg1.toInt());
}

void MainWindow::on_Pos_12_textChanged(const QString &arg1)
{
    twoDList.setMatrixElement(1,2,arg1.toInt());
}

void MainWindow::on_Pos_20_textChanged(const QString &arg1)
{
    twoDList.setMatrixElement(2,0,arg1.toInt());
}

void MainWindow::on_Pos_21_textChanged(const QString &arg1)
{
    twoDList.setMatrixElement(2,1,arg1.toInt());
}

void MainWindow::on_Pos_22_textChanged(const QString &arg1)
{
    twoDList.setMatrixElement(2,2,arg1.toInt());
}

void MainWindow::on_pushButton_clicked()
{
    twoDList.create2DList();
    ui->NPos_00->setText(QVariant(twoDList.getMatrixElement(0,0)).toString());
    ui->NPos_01->setText(QVariant(twoDList.getMatrixElement(0,1)).toString());
    ui->NPos_02->setText(QVariant(twoDList.getMatrixElement(0,2)).toString());
    ui->NPos_10->setText(QVariant(twoDList.getMatrixElement(1,0)).toString());
    ui->NPos_11->setText(QVariant(twoDList.getMatrixElement(1,1)).toString());
    ui->NPos_12->setText(QVariant(twoDList.getMatrixElement(1,2)).toString());
    ui->NPos_20->setText(QVariant(twoDList.getMatrixElement(2,0)).toString());
    ui->NPos_21->setText(QVariant(twoDList.getMatrixElement(2,1)).toString());
    ui->NPos_22->setText(QVariant(twoDList.getMatrixElement(2,2)).toString());

    ui->perimeter_2->setVisible(true);
    ui->diagonalSum_2->setVisible(true);
    ui->transpose_2->setVisible(true);
    ui->perimeter->setVisible(true);
    ui->diagonalSum->setVisible(true);
    ui->transpose->setVisible(true);

}

void MainWindow::on_perimeter_2_clicked()
{
    twoDList.calPerimeter();
    ui->perimeter->setText(QVariant(twoDList.getPerimeter()).toString());
}



void MainWindow::on_diagonalSum_2_clicked()
{
    twoDList.sumDiagonal();
    ui->diagonalSum->setText(QVariant(twoDList.getDiagonalSum()).toString());
}

void MainWindow::on_transpose_2_clicked()
{
    twoDList.transpose();
    twoDList.transposeMatrix();
    ui->NPos_00->setText(QVariant(twoDList.getMatrixElement(0,0)).toString());
    ui->NPos_01->setText(QVariant(twoDList.getMatrixElement(0,1)).toString());
    ui->NPos_02->setText(QVariant(twoDList.getMatrixElement(0,2)).toString());
    ui->NPos_10->setText(QVariant(twoDList.getMatrixElement(1,0)).toString());
    ui->NPos_11->setText(QVariant(twoDList.getMatrixElement(1,1)).toString());
    ui->NPos_12->setText(QVariant(twoDList.getMatrixElement(1,2)).toString());
    ui->NPos_20->setText(QVariant(twoDList.getMatrixElement(2,0)).toString());
    ui->NPos_21->setText(QVariant(twoDList.getMatrixElement(2,1)).toString());
    ui->NPos_22->setText(QVariant(twoDList.getMatrixElement(2,2)).toString());
    ui->perimeter->setText("0");
    ui->diagonalSum->setText("0");
    twoDList.reset();
    ui->transpose->setText("SUCCESSFUL!");
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->NPos_00->setText("0");
    ui->NPos_01->setText("0");
    ui->NPos_02->setText("0");
    ui->NPos_10->setText("0");
    ui->NPos_11->setText("0");
    ui->NPos_12->setText("0");
    ui->NPos_20->setText("0");
    ui->NPos_21->setText("0");
    ui->NPos_22->setText("0");

    ui->Pos_00->setText("0");
    ui->Pos_01->setText("0");
    ui->Pos_02->setText("0");
    ui->Pos_10->setText("0");
    ui->Pos_11->setText("0");
    ui->Pos_12->setText("0");
    ui->Pos_20->setText("0");
    ui->Pos_21->setText("0");
    ui->Pos_22->setText("0");

    ui->perimeter->setText("0");
    ui->diagonalSum->setText("0");
    twoDList.reset();
    ui->transpose->setText("NONE");

    twoDList.setHead(nullptr);
}
