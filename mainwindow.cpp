#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui -> creditTable -> horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui -> hypothecTable -> horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui -> depositTable -> horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui -> stackedWidget -> setCurrentIndex(0);
//    db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("127.0.0.1");
//    db.setDatabaseName("Расчеты");
//    db.setUserName("root");
//    db.setPassword("Qwer1234!");
//    if(!db.open())
//    {
//        qDebug() << db.lastError().text();
//    }
//    else
//    {
//        qDebug() << "Success!";
//    }
//    query = QSqlQuery(db);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./Database.db");
    if(!db.open())
    {
        qDebug() << db.lastError().text();
    }
    else
    {
        qDebug() << "Success!";
    }
    query = QSqlQuery(db);

}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_databaseButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_calculatorButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_creditCountButton_clicked()
{
    long int CreditSumValue;
    QString CreditDateValue;
    double CreditPercentValue;
    int CreditTimeValue;
    double creditannuitypaymentmonth;
    int creditcleanpaymentmonth;
    int creditoverpayment = 0;
    double creditpercentvaluemonth;
    double creditpercentpaymentvalue;
    QString creditannuitypaymentmonthstring, creditpercentpaymentvaluestring, creditoverpaymentstring, creditcleanpaymentmonthstring, creditgeneralpaymentstring;
    y = 0;
    ui -> creditTable -> setRowCount(1);


    QDate CreditDatesrc = ui -> creditDate -> date();

    QString CreditPercentsrc = ui -> creditPercent -> text();
    CreditPercentValue = CreditPercentsrc.toDouble();

    QString CreditSumsrc = ui -> creditSum -> text();
    CreditSumValue = CreditSumsrc.toInt();

    QString CreditTimesrc = ui -> creditTime -> text();
    CreditTimeValue = CreditTimesrc.toInt();

//    creditpercentvaluemonth = (CreditPercentValue + 100.0 ) / 100;
//    creditpercentvaluemonth = pow(creditpercentvaluemonth, 1.0/12);
//    creditpercentvaluemonth -= 1.0;
//    creditpercentvaluemonth = double(round(creditpercentvaluemonth * 100.0) / 100.0);
    creditpercentvaluemonth = CreditPercentValue / 100 / 12;
    creditpercentvaluemonth = round(creditpercentvaluemonth * 1000.0) / 1000.0;

    creditannuitypaymentmonth = CreditSumValue * (creditpercentvaluemonth + (creditpercentvaluemonth / (pow(1.0 + creditpercentvaluemonth, CreditTimeValue) - 1)));
//    annuitypaymentmonth = CreditSumValue * (pow(1 + creditpercentvaluemonth, 1/12) - 1) / (1 - pow(1 + creditpercentvaluemonth, - (round(CreditTimeValue / 12 * 100) / 100)));
//    annuitypaymentmonth = CreditSumValue * (pow(1 + creditpercentvaluemonth, 1.0/12) - 1) / (1 - pow((1 + creditpercentvaluemonth), -(CreditTimeValue / 12)));
//    annuitypaymentmonth = (CreditSumValue * (CreditPercentValue / (12 * 1))) / (1 - (1 + (CreditPercentValue / (12 * 100) - CreditTimeValue/12)));


    creditannuitypaymentmonth = round(creditannuitypaymentmonth * 100) / 100;


    while (CreditSumValue != 0)
    {
        creditpercentpaymentvalue = creditpercentvaluemonth * CreditSumValue;
        creditcleanpaymentmonth = creditannuitypaymentmonth - creditpercentpaymentvalue;
        creditoverpayment += creditpercentpaymentvalue;
        if (CreditSumValue < creditannuitypaymentmonth)
        {
            creditannuitypaymentmonth = CreditSumValue;
            CreditSumValue = 0;
        }
        else
        {
            CreditSumValue = CreditSumValue -  creditcleanpaymentmonth;
        }


        QTableWidgetItem *creditcleanpaymentmonthitem = new QTableWidgetItem;
        creditcleanpaymentmonthstring = QString::number(creditcleanpaymentmonth);
        creditcleanpaymentmonthitem -> setText(creditcleanpaymentmonthstring);

        QTableWidgetItem *creditoverpaymentitem = new QTableWidgetItem;
        creditoverpaymentstring = QString::number(creditoverpayment);
        creditoverpaymentitem -> setText(creditoverpaymentstring);

        QTableWidgetItem *creditpercentpaymentvalueitem = new QTableWidgetItem;
        creditpercentpaymentvaluestring = QString::number(creditpercentpaymentvalue);
        creditpercentpaymentvalueitem -> setText(creditpercentpaymentvaluestring);

        QTableWidgetItem *creditannuitypaymentmonthitem = new QTableWidgetItem;
        creditannuitypaymentmonthstring = QString::number(creditannuitypaymentmonth);
        creditannuitypaymentmonthitem -> setText(creditannuitypaymentmonthstring);

        QTableWidgetItem *creditsumvalueitem = new QTableWidgetItem;
        CreditSumsrc = QString::number(CreditSumValue);
        creditsumvalueitem -> setText(CreditSumsrc);

        QTableWidgetItem *creditdatevalueitem = new QTableWidgetItem;
        CreditDatesrc = CreditDatesrc.addMonths(1);
        CreditDateValue = CreditDatesrc.toString("d.M.yyyy");
        creditdatevalueitem -> setText(CreditDateValue);

        ui -> creditTable -> setItem(y, 0, creditdatevalueitem);
        ui -> creditTable -> setItem(y, 1, creditannuitypaymentmonthitem);
        ui -> creditTable -> setItem(y, 2, creditpercentpaymentvalueitem);
        ui -> creditTable -> setItem(y, 3, creditcleanpaymentmonthitem);
        ui -> creditTable -> setItem(y, 4, creditoverpaymentitem);
        ui -> creditTable -> setItem(y, 5, creditsumvalueitem);
        y++;
        ui -> creditTable -> insertRow(y);
    }
    ui -> creditTable -> removeRow(y);
}

void MainWindow::on_hypothecCountButton_clicked()
{
    long int hypothecSumValue;
    int hypothecfirstpaymentValue;
    QString hypothecDateValue;
    double hypothecPercentValue;
    double hypothecTimeValue;
    double hypothecannuitypaymentmonth, hypotheccleanpaymentmonth, hypothecoverpayment = 0;
    double hypothecpercentvaluemonth;
    double hypothecpercentpaymentvalue;
    QString hypothecannuitypaymentmonthstring, hypothecpercentpaymentvaluestring, hypothecoverpaymentstring, hypotheccleanpaymentmonthstring;
    y = 0;
    ui -> hypothecTable -> setRowCount(1);

    QString hypothecFirstPayment = ui -> hypothecFirstPayment -> text();
    hypothecfirstpaymentValue = hypothecFirstPayment.toInt();

    QDate hypothecDatesrc = ui -> hypothecDate -> date();

    QString hypothecPercentsrc = ui -> hypothecPercent -> text();
    hypothecPercentValue = hypothecPercentsrc.toDouble();

    QString hypothecSumsrc = ui -> hypothecSum -> text();
    hypothecSumValue = hypothecSumsrc.toInt();

    if (hypothecfirstpaymentValue < hypothecSumValue * 0.15 or hypothecfirstpaymentValue > hypothecSumValue * 0.6)
    {
        QMessageBox::about(this, "Ошибка", "Неправильное значение первоначального взноса");
    }
    else
    {

    QString hypothecTimesrc = ui -> hypothecTime -> text();
    hypothecTimeValue = hypothecTimesrc.toInt();
    hypothecTimeValue *= 12;

    hypothecSumValue -= hypothecfirstpaymentValue;

    hypothecpercentvaluemonth = hypothecPercentValue / 12.0 / 100;
    hypothecpercentvaluemonth = round(hypothecpercentvaluemonth * 1000.0) / 1000.0;

    hypothecannuitypaymentmonth = hypothecSumValue * (hypothecpercentvaluemonth + (hypothecpercentvaluemonth / (pow(1.0 + hypothecpercentvaluemonth, hypothecTimeValue) - 1)));
    hypothecannuitypaymentmonth = round(hypothecannuitypaymentmonth * 100) / 100;


    while (hypothecSumValue != 0)
    {
        if (hypothecSumValue < hypothecannuitypaymentmonth)
        {
            hypothecannuitypaymentmonth = hypothecSumValue;
            hypothecSumValue = 0;
        }
        else
        {
            hypothecSumValue = hypothecSumValue -  hypotheccleanpaymentmonth;
        }
        hypothecpercentpaymentvalue = hypothecpercentvaluemonth * hypothecSumValue;
        hypotheccleanpaymentmonth = hypothecannuitypaymentmonth - hypothecpercentpaymentvalue;
        hypothecoverpayment += hypothecpercentpaymentvalue;

        QTableWidgetItem *hypothecoverpaymentitem = new QTableWidgetItem;
        hypothecoverpaymentstring = QString::number(hypothecoverpayment);
        hypothecoverpaymentitem -> setText(hypothecoverpaymentstring);

        QTableWidgetItem *hypothecpercentpaymentvalueitem = new QTableWidgetItem;
        hypothecpercentpaymentvaluestring = QString::number(hypothecpercentpaymentvalue);
        hypothecpercentpaymentvalueitem -> setText(hypothecpercentpaymentvaluestring);

        QTableWidgetItem *hypothecannuitypaymentmonthitem = new QTableWidgetItem;
        hypothecannuitypaymentmonthstring = QString::number(hypothecannuitypaymentmonth);
        hypothecannuitypaymentmonthitem -> setText(hypothecannuitypaymentmonthstring);

        QTableWidgetItem *hypotheccleanpaymentmonthitem = new QTableWidgetItem;
        hypotheccleanpaymentmonthstring = QString::number(hypotheccleanpaymentmonth);
        hypotheccleanpaymentmonthitem -> setText(hypotheccleanpaymentmonthstring);


        QTableWidgetItem *hypothecsumvalueitem = new QTableWidgetItem;
        hypothecSumsrc = QString::number(hypothecSumValue);
        hypothecsumvalueitem -> setText(hypothecSumsrc);

        QTableWidgetItem *hypothecdatevalueitem = new QTableWidgetItem;
        hypothecDatesrc = hypothecDatesrc.addMonths(1);
        hypothecDateValue = hypothecDatesrc.toString("d.M.yyyy");
        hypothecdatevalueitem -> setText(hypothecDateValue);

        ui -> hypothecTable -> setItem(y, 0, hypothecdatevalueitem);
        ui -> hypothecTable -> setItem(y, 1, hypothecannuitypaymentmonthitem);
        ui -> hypothecTable -> setItem(y, 2, hypothecpercentpaymentvalueitem);
        ui -> hypothecTable -> setItem(y, 3, hypotheccleanpaymentmonthitem);
        ui -> hypothecTable -> setItem(y, 4, hypothecoverpaymentitem);
        ui -> hypothecTable -> setItem(y, 5, hypothecsumvalueitem);
        y++;
        ui -> hypothecTable -> insertRow(y);
    }
    ui -> hypothecTable -> removeRow(y);
}}




//void MainWindow::on_searchButton_clicked()
//{
//    if(db.open())
//    {
//        userfirstname = ui -> firstname -> text();
//        userlastname = ui -> lastname -> text();
//        QSqlQuery qry;
//        qry.prepare()
//    }
//}


//void MainWindow::on_creditSaveButton_clicked()
//{
//    if(db.open())
//    {
//        query.exec("CREATE TABLE :name(id INT PRIMARY KEY, date INT, monthpayment INT, percent INT, cleanpayment INT, overpayment INT, rest INT)");

//    }
//}


void MainWindow::on_depositCountButton_clicked()
{
    ui -> depositTable -> setRowCount(1);

    long int depositSumValue;
    int depositTimeValue;
    y = 0;
    double depositPercentValue, depositpercentpaymentValue, depositpercentpaymentsumValue = 0;
    QString depositpercentpaymentsumsrc;
    QString depositDateValue;
    QDate depositDatesrc;
    QString depositSumsrc, depositTimesrc, depositPercentsrc;
    depositSumsrc = ui -> depositSum -> text();
    depositSumValue = depositSumsrc.toInt();

    depositTimesrc = ui -> depositTime -> text();
    depositTimeValue = depositTimesrc.toInt();

    depositPercentsrc = ui -> depositPercent -> text();
    depositPercentValue = depositPercentsrc.toDouble();

    depositpercentpaymentValue = depositSumValue * pow((1.0 + ((depositPercentValue / 100.0) / 12.0)), depositTimeValue);
    depositpercentpaymentValue -= depositSumValue;

    depositDatesrc = ui -> depositDate -> date();

    while (y <= depositTimeValue)
    {
        depositSumValue += depositpercentpaymentValue;
        depositSumsrc = QString::number(depositSumValue);
        QTableWidgetItem *depositpercentgotValueitem = new QTableWidgetItem;
        depositpercentpaymentsumValue +=depositpercentpaymentValue;
        depositpercentpaymentsumsrc = QString::number(depositpercentpaymentsumValue);
        depositpercentgotValueitem -> setText(depositpercentpaymentsumsrc);

        QTableWidgetItem *depositdatevalueitem = new QTableWidgetItem;
        depositDatesrc = depositDatesrc.addMonths(1);
        depositDateValue = depositDatesrc.toString("d.M.yyyy");
        depositdatevalueitem -> setText(depositDateValue);

        QTableWidgetItem *depositSumValueitem = new QTableWidgetItem;
        depositSumValueitem -> setText(depositSumsrc);

        ui -> depositTable -> setItem(y, 0, depositdatevalueitem);
        ui -> depositTable -> setItem(y, 1, depositpercentgotValueitem);
        ui -> depositTable -> setItem(y, 2, depositSumValueitem);
        y++;
        ui -> depositTable -> insertRow(y);
    }
    ui -> depositTable -> removeRow(y);
}

