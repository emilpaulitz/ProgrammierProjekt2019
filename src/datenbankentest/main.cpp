#include <QCoreApplication>
#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>
#include <string>
#include <iostream>
#include <QString>
#include <databank.cpp>
#include <QNetworkAccessManager>
using namespace std;




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


   connect();
   QSqlQuery NGSdata;

            if (NGSdata.exec("SELECT * FROM varianten")) {
               printtable(NGSdata);
            }
                else {
                 NGSdata.exec("CREATE DOMAIN nucleotide AS char(1) CHECK (VALUE IN ('A', 'G', 'C', 'T'))");
                 //CREATES DOMAIN os type char(1) for nucleotides

                 NGSdata.exec("CREATE TABLE varianten(chrom varchar(5) NOT NULL, pos bigint NOT NULL,id text NOT NULL, ref nucleotide NOT NULL, alt nucleotide NOT NULL,"
                              "qual real NOT NULL, filter bool NOT NULL,info text NOT NULL)");
                 //create tables with rows chrom, pos, id, ref, alt, qual, filter and info ALL collums NOT NULL

                }
          // beispiele
          // addrow(NGSdata,"varianten","chr2",2345,"acs123",'F','C',"345.4",true,"test ob add funktioniert");
          // deleterow(NGSdata,"varianten","chr1",2222,'A', 'C');
           NGSdata.exec("INSERT INTO varianten VALUES ('chr1', 2222, 'ac234', 'A', 'C', 234.2, TRUE, 'ther frist test entry')");
            // qDebug() << NGSdata.lastError();



            // db.close();
           
          
           
           
        
           
    return 0;
}
