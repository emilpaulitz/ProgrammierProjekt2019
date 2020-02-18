#include "datenbank.h"
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>
#include <string>
#include <iostream>
#include <QString>
#include <QJsonObject>
using namespace std;

databank::databank()
{

}
// connects to the psql database
static void connect(){

QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
db.setHostName("localhost");
db.setDatabaseName("varianten");
db.setUserName("variantusr");
db.setPassword("variantpw");
//db.setPort(5433);
db.open();
qDebug() << "Testing if open: " << db.open();
}

//addrow adds a row with given parameters to a table
static void addrow(QSqlQuery query, QString table, QString chrom, QString pos, QString id,
                   QString ref, QString alt,QString anno){


    QString querys = "INSERT INTO "+table+" VALUES ('"+chrom+"',"+pos+",'"+id+"','"+ref+"','"+alt+"',"+anno+")";
    //creates a string to be used as an query request
    qDebug() << "Your query: " << querys;
    query.prepare(querys);
    if (query.exec(querys)){ //run query and check if successfull if yes coinfirm to user
        qDebug() << "input succsesfull";
    }
    else {
        qDebug() << query.lastError();
    }

}

//overloadet function with "varianten" as standart table
static void addrow(QSqlQuery query,QString chrom,QString pos, QString id, QString ref, QString alt,QString anno){
    addrow(query,"varianten",chrom,pos,id,ref,alt,anno);
}

static void deleterow(QSqlQuery query, QString table, QString chrom,QString pos,QString ref,QString alt){
    //create a string to be used as query request
    QString querys = "DELETE FROM "+ table +" WHERE chrom = "+chrom+" AND pos = "+pos+" AND ref = "+ref+" AND alt = "+alt+";";
    qDebug() << "Your query: " << querys ;
    query.prepare(querys);

    if (query.exec(querys)){ //run query and check if successfull if yes confirm to user
        qDebug() << "Delete succsesfull";
    }
     qDebug() << query.lastError();
}

//overloadet with "varianten as table
static void deleterow(QSqlQuery query, QString chrom,QString pos,QString ref,QString alt){
   deleterow(query,"varianten",chrom,pos,ref,alt);
}

//print a sql table to coutput
static void printtable(QSqlQuery query){

    int row = 0;
     while(query.next()){

     QString chrom =  query.value(0).toString();
     QString pos = query.value(1).toString();
     QString id = query.value(2).toString();
     QString ref = query.value(3).toString();
     QString alt = query.value(4).toString();
     QString info = query.value(5).toString();
     QString anno = query.value(6).toString();
     qDebug()<< "Row:" << row << "chrom:" << chrom << "pos:" << pos << "id:" << id << "ref:"
             << ref <<  "alt:" << alt << "info:" << info << "anno" << anno;
     row = row + 1;
     }

}


//searches for entrys in the qiven tabel with keywords, return true and table entry on success and false on no entry;
static bool searchtable(QSqlQuery query, QString table, QString chrom, QString pos, QString ref, QString alt){

    //string with query to execute
    QString querys = "SELECT v.chrom, v.pos., v.ref, v.alt FROM "+ table + " AS v WHERE v.chrom"
    " = "+chrom+" AND pos = "+pos+" AND v.ref = "+ref+" AND v.alt = "+alt;
    if (query.exec(querys)){
        return true;
    }
    else {
      qDebug() << "No entry found in table";
      return false;
    }
}
//overloaded searchtabel with varianten as table
static bool searchtable(QSqlQuery query,QString chrom,QString pos,QString ref,QString alt){
  return  searchtable(query,"varianten",chrom,pos,ref,alt);
}

//retuns to annotation of a requested variant if exsist otherwise an empty JSON object
static QJsonObject getanno(QSqlQuery query,QString table,QString chrom, QString pos, QString ref, QString alt){
    QString querys = "SELECT v.chrom, v.pos., v.ref, v.alt FROM "+ table + " AS v WHERE v.chrom"
    " = "+chrom+" AND pos = "+pos+" AND v.ref = "+ref+" AND v.alt = "+alt;

    //return the annotation of requested varint as a JSON object
    if(query.exec(querys)){
        QJsonObject anno = query.value(6).toJsonObject();
        return anno;
    }
    else{
        // if there is no annotation retunr an empty JSON object, not an NULL object
        QJsonObject anno = {};
       return anno;

    }
}
