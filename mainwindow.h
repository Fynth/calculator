#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QString>
#include <QStringList>
#include <iostream>
#include <QDate>
#include <cmath>
#include <QMessageBox>
#include <QtSql>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlRecord>

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
    void on_databaseButton_clicked();
    void on_calculatorButton_clicked();

    void on_creditCountButton_clicked();

    void on_hypothecCountButton_clicked();

//    void on_searchButton_clicked();

//    void on_creditSaveButton_clicked();

    void on_depositCountButton_clicked();

private:
    int y = 0;

    QSqlDatabase db;
    QSqlQuery query;
    QSqlTableModel *model;
    QString userfirstname, userlastname;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
