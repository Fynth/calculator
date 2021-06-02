#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui -> creditTable -> setRowCount(10);
    ui -> creditTable_2 -> setRowCount(10);
    ui -> creditTable_3 -> setRowCount(10);
    ui -> creditTable -> horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui -> creditTable_2 -> horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui -> creditTable_3 -> horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

