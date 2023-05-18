#include "DBase.h"

#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#define _DB_NAME "DataBase"

DBase::DBase()
{
    this->dbInstance = QSqlDatabase::addDatabase("QSQLITE");
    this->dbInstance.setDatabaseName(_DB_NAME);
    if (!this->dbInstance.open()) {
        qDebug() << this->dbInstance.lastError().text();
    };
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dbName");
    if (db.open())
    {
        qDebug("connected to database");
    }
    else
    {
        qDebug("Error occured in connection to database");
    }
}

DBase::~DBase() {
    this->dbInstance.close();
}

QSqlQuery DBase::doSQLQuery(QString stringQuery) {
    QSqlQuery query(this->dbInstance);
    if(!query.exec(stringQuery)) {
        qDebug() << "Error SQL query:" << query.lastError().text();
    }
    return query;
}

BaseDestroyer DBase::destroyer;
DBase* DBase::pInstance = nullptr;
QSqlDatabase DBase::dbInstance;
