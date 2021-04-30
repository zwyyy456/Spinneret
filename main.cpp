#include "mainwindow.h"

#include <QApplication>

#include <QMessageBox>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <QDebug>
int main(int argc, char *argv[])
{
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MyDataBase.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." ;
    }
    else
    {
        qDebug() << "Succeed to connect database." ;
    }

    QSqlQuery sql_query;


   //创建表格
    if(!sql_query.exec("create table user(bIfAdmin bool, cName text,cPassword text)"))
    {
        qDebug() << "Error: Fail to create table.";
    }
    else
    {
        qDebug() << "Table created!";
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
