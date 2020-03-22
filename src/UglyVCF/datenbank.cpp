#include "datenbank.h"
#include "Annotation.h"
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
/**
 * @brief connect, connects to the local host database "varianten" with usr "variantusr"
 */
void connect(){

QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
db.setHostName("localhost");
db.setDatabaseName("varianten");
db.setUserName("variantusr");
db.setPassword("variantpw");
//db.setPort(5433);
db.open();
qDebug() << "Testing if open: " << db.open();
}


/**
 * @brief createTable, creats three tables in the connected databank, annotation,frequencies and transcriptcons.
 * Key in annotation is hgvs, is foreign key in frequencies und trancriptcons
 * @return void
 */
static void createTable()
{
   QSqlQuery query;

   QString query1 = "CREATE TABLE annotation (hgvs text,most_severe_consequence text)";

   QString query2 = "CREATE TABLE frequencies (hgvs text,afr real,eas real,gnomad_eas real,gnomad_nfe real,"
                    "gnomad_fin real,sas real,gnomad real,amr real,gnomad_sas real,"
                    "aa real ,gnomad_afr real,eur real,ea real,gnomad_asj real,gnomad_amr real ,gnomad_oth real)";

   QString query3 = "CREATE TABLE transcripscons (hgvs text,transcript_id text,impact text,variant_allele text,"
                    "gene_symbole text,gene_symbol_source text,gene_id text,"
                    "hgnc_id text,strand text,biotype text,distance text)";
   query.prepare(query1);
   query.exec(query1);
   query.prepare(query2);
   query.exec(query2);
   query.prepare(query3);
   query.exec(query3);
}
/**
 * @brief addRow,adds a new anotation to the databse from a given Annotation object
 * @param Annotation object
 * @return true if insertion successful, false if not
 */
bool addRow(Annotation anno){

    QSqlQuery query;
    QString mostsevercons = anno.getMost_severe_consequence();
    QString hgvs = anno.getId();
    Frequencies freq = anno.getFrequencies();
    QList<Transcriptcons> transcons = anno.getTranscriptcons();

    //prepares query and adds a row to annotation table
    QString toquery = "INSERT INTO annotation VALUES('"+hgvs+"','"+mostsevercons+"')";
    query.exec(toquery);
    qDebug() << query.lastError();

    //prepares query and adds a row to the frequencies tabel with hgvs a forein key
    QString frequery = preparefreq(freq,hgvs);
    query.exec(frequery);
    qDebug() << query.lastError();

    //prepares and a
    QString consquery = preparetranscons(transcons,hgvs);
    query.exec(consquery);
    qDebug() << query.lastError();

}

/**
 * @brief preparefreq, creates a QString to be used in Addrow
 * @param Frequencies object freq,
 * @param QString hgvs as forein key
 * @return Qstring
 */
QString preparefreq(Frequencies freq,QString hgvs){

    QString restring = "INSERT INTO frequencies VALUES('"+hgvs;
    for (int i = 0; i < FilterDialog::LASTENUM; i++) {
        FilterDialog::Region reg = (FilterDialog::Region) i;
        restring += "','" + QString::number(freq.getFreq(reg));
    }

    return restring + "')";
}


/**
 * @brief preparetranscons, creates a Qstring of all transcrip cons to be used in Addrow
 * @param transcons, QList<Transcriptcons> object
 * @param hgvs QString
 * @return a QString with all transcript consequnces to be loaded into database
 */
QString preparetranscons(QList<Transcriptcons> transcons,QString hgvs){

    QString transcript_id,impact, variant_allele,
            gene_symbole,gene_symbol_source,gene_id,
            hgnc_id,strand,biotype,distance;

    //First row of values,rows of values are appended later;
    QString restring = "INSERT INTO transcripscons VALUES";

    //iterate over list and create a new row of values, add to restring
    for(int i = 0; i < transcons.size(); i++){
        Transcriptcons singlecons = transcons[i];

        //pull all values from current Transcriptcons object
        transcript_id = singlecons.getTranscript_id();
        impact = singlecons.getImpact();
        variant_allele = singlecons.getVariant_allele();
        gene_symbole = singlecons.getGene_symbole();
        gene_symbol_source = singlecons.getGene_symbol_source();
        gene_id = singlecons.getGene_id();
        hgnc_id = singlecons.getHgnc_id();
        strand = singlecons.getStrand();
        biotype = singlecons.getBiotype();
        distance = singlecons.getDistance();

        restring = restring+"('"+hgvs+"','"+transcript_id+"','"+impact+"','"+variant_allele+"','"+
                   gene_symbole+"','"+gene_symbol_source+"','"+gene_id+"','"+hgnc_id+"','"+
                   strand+"','"+biotype+"','"+distance+"')";

        QList<QString> terms = singlecons.getConsequence_terms();

        //if not the last object add a , to end of line
        if(i+1 < transcons.size()){
            restring = restring+",";
        }
    }
    return restring;

}


/**
 * @brief searchDatabank, searches the databank for an entry with the given hgvs string
 * @param hgvs QString,
 * @return bool, is in databank -> true, else false
 */
static bool searchDatabank(QString hgvs){

    QSqlQuery query;
    QString query1 = "SELECT t.hgvs FROM annotation AS t WHERE t.hgvs = '"+hgvs+"'";
    query.prepare(query1);
    query.exec(query1);
    query.next();
    QString chrom =  query.value(0).toString();
    if(not chrom.isNull())
        return true;
    else{
        return false;
    }

}
/**
 * @brief retriveAnno
 * @param hgvs
 * @return
 */
Annotation retriveAnno(QString hgvs){

    QSqlQuery query;
    QString retrive = "SELECT t.most_severe_consequence FROM annotation AS t WHERE t.hgvs ='"+hgvs;

    query.exec(retrive);
    query.next();

    QString most_severe_consequence = query.value(0).toString();

    retrive = "SELECT t.afr,t.eas,t.gnomad_eas,t.gnomad_nfe,t.gnomad_fint,t.sas,t.gnomad,t.amr,t.gnomad_sas,"
              "t.aa,t.gnomad_afr,t.eur,t.ea,t.gnomad_asj,t.gnomad_amr,t.gnomad_oth,t.restring"
              "FROM frequencies AS t WHERE t.hgvs ='"+hgvs+"')";

    query.exec(retrive);
    query.next();

    double afr,eas,gnomad_eas,gnomad_nfe,gnomad_fin,sas,gnomad,amr,gnomad_sas,
    aa,gnomad_afr,eur,ea,gnomad_asj,gnomad_amr,gnomad_oth;

    afr = query.value(0).toDouble();
    eas = query.value(1).toDouble();
    gnomad_eas = query.value(2).toDouble();
    gnomad_nfe = query.value(3).toDouble();
    gnomad_fin = query.value(4).toDouble();
    sas = query.value(5).toDouble();
    gnomad = query.value(6).toDouble();
    amr = query.value(7).toDouble();
    gnomad_sas = query.value(8).toDouble();
    aa = query.value(9).toDouble();
    gnomad_afr = query.value(10).toDouble();
    eur = query.value(11).toDouble();
    ea = query.value(12).toDouble();
    gnomad_asj = query.value(13).toDouble();
    gnomad_amr = query.value(14).toDouble();
    gnomad_oth = query.value(15).toDouble();



}


/*
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
**/
