#include "databank.h"
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>
#include <string>
#include <iostream>
#include <QString>
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
static void addrow(QSqlQuery query, string table, string chrom, long int pos, string id, char ref, char alt, string qual, bool filter, string info){


    string s = "INSERT INTO "+table+" VALUES ('"+chrom+"',"+to_string(pos)+",'"+id+"','"+ref+"','"+alt+"','"+qual+"','"+to_string(filter)+"','"+info+"')";
    //creates a string to be used as an query request
    QString es = QString::fromStdString(s);
    qDebug() << "Your query: " << es;
    query.prepare(es);
    if (query.exec(es)){ //run query and check if successfull if yes coinfirm to user
        qDebug() << "input succsesfull";
    }
    else {
        qDebug() << query.lastError();
    }

}


static void addrow(QSqlQuery query,string chrom, long int pos, string id, char ref, char alt, string qual, bool filter, string info){
    addrow(query,"varianten",chrom,pos,id,ref,alt,qual,filter,info);
}
//overloadet function with "varianten" as standart table
static void deleterow(QSqlQuery query, string table, string chrom,long int pos,char ref, char alt){

    string s = "DELETE FROM "+ table +" WHERE chrom = '"+chrom+"' AND pos = "+to_string(pos)+" AND ref = "+"'"+ref+"'"+" AND alt = "+"'"+alt+"'";
    //create a string to be used as query request
    QString es = QString::fromStdString(s);
    qDebug() << "Your query: " << es ;
    query.prepare(es);

    if (query.exec(es)){ //run query and check if successfull if yes confirm to user
        qDebug() << "Delete succsesfull";
    }
     qDebug() << query.lastError();
}

//overloadet with "varianten as table
static void deleterow(QSqlQuery query, string chrom,long int pos,char ref, char alt){
   deleterow(query,"varianten",chrom,pos,ref,alt);
}
//print a sql table to coutput
static void printtable(QSqlQuery query){

    int row = 0;
     while(query.next()){

     QString chrom =  query.value(0).toString();
     int pos = query.value(1).toInt();
     QString  id = query.value(2).toString();
     QString ref = query.value(3).toString();
     QString alt = query.value(4).toString();
     float qual = query.value(5).toFloat();
     bool filter = query.value(6).toBool();
     QString info = query.value(7).toString();

     qDebug()<< "Row:" << row << "chrom:" << chrom << "pos:" << pos << "id:" << id << "ref:" << ref <<  "alt:" << alt << "qual:" << qual << "filter:" << filter << "info:" << info ;
     row = row + 1;
     }

}


//searches for entrys in the qiven tabel with keywords, return true and table entry on success and false on no entry;
static bool searchtable(QSqlQuery query, string table, string chrom, long int pos, char ref, char alt){

    string search = "SELECT v.chrom, v.pos., v.ref, v.alt FROM "+ table + " AS v WHERE v.chrom = "+chrom+" AND pos = "+to_string(pos)+" AND v.ref = "+ref+" AND v.alt = "+alt;
    //string with query to execute
    QString searche = QString::fromStdString(search);
    if (query.exec(searche)){
        printtable(query);
        return true;
    }
    else {
      qDebug() << "No entry found in table";
      return false;
    }
}
//overloaded searchtabel with varianten as table
static bool searchtable(QSqlQuery query,string chrom, long int pos, char ref, char alt){
  return  searchtable(query,"varianten",chrom,pos,ref,alt);
}
