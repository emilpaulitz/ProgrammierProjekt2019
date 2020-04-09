#include "databank.h"
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
void databank::connect(){

QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
db.setHostName("localhost");
db.setDatabaseName("varianten");
db.setUserName("variantusr");
db.setPassword("variantpw");
db.open();
qDebug() << "Testing if open: " << db.open();
}

/**
 * @brief createTable, creats three tables in the connected databank, annotation,frequencies and transcriptcons.
 * Key in annotation is hgvs, is foreign key in frequencies und trancriptcons
 * @return void
 */
void databank::createTable()
{
   QSqlQuery query;

   QString query1 = "CREATE TABLE annotation "
                    "(hgvs text PRIMARY KEY,most_severe_consequence text)";

   QString query2 = "CREATE TABLE frequencies (hgvs text PRIMARY KEY,afr real, "
                    "eas real,gnomad_eas real,gnomad_nfe real,"
                    "gnomad_fin real,sas real,gnomad real,amr real,gnomad_sas real,"
                    "aa real ,gnomad_afr real,eur real,ea real,gnomad_asj real, "
                    "gnomad_amr real ,gnomad_oth real)";

   QString query3 = "CREATE TABLE transcripscons (hgvs text,transcript_id text, "
                    "impact text,variant_allele text,"
                    "gene_symbole text,gene_symbol_source text,gene_id text,"
                    "hgnc_id text,strand text,biotype text,distance text,terms text,"
                    "PRIMARY KEY(hgvs,transcript_id))";

   QString query4 = "ALTER TABLE frequencies ADD FOREIGN KEY (hgvs) "
                    "REFERENCES annotation ON DELETE CASCADE";
   QString query5 = "ALTER TABLE transcripsconsn ADD FOREIGN KEY (hgvs) "
                    "REFERENCES annotation ON DELETE CASCADE";
   query.exec(query1);
   query.exec(query2);
   query.exec(query3);
   query.exec(query4);
   query.exec(query5);

}

/**
 * @brief addRow,adds a new anotation to the databse from a given Annotation object
 * @param Annotation object
 * @return true if insertion successful, false if not
 */
bool databank::addRow(Annotation anno){

    
    QSqlQuery query;
    QString mostsevercons = anno.getMost_severe_consequence();
    QString hgvs = anno.getId();
    Frequencies freq = anno.getFrequencies();
    QList<Transcriptcons> transcons = anno.getTranscriptcons();
    bool first, second, third, final;

    //prepares query and adds a row to annotation table
    QString toquery = "INSERT INTO annotation VALUES('"+hgvs+"','"+mostsevercons+"')";
    first = query.exec(toquery);

    //prepares query and adds a row to the frequencies tabel with hgvs a forein key
    QString frequery = preparefreq(freq,hgvs);
    second = query.exec(frequery);


    //prepares and a query transcons
    QString consquery = preparetranscons(transcons,hgvs);
    third = query.exec(consquery);

    final = (first and second and third);
    return final;
}

/**
 * @brief preparefreq, creates a QString to be used in Addrow
 * @param Frequencies object freq,
 * @param QString hgvs as forein key
 * @return Qstring
 */
QString databank::preparefreq(Frequencies freq,QString hgvs){

    QString restring = "INSERT INTO frequencies VALUES('"+hgvs;
    for (int i = 0; i < FilterDialog::LASTREGION; i++) {
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
QString databank::preparetranscons(QList<Transcriptcons> transcons,QString hgvs){

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

        QList<QString> terms = singlecons.getConsequence_terms();
        QString mehstring;
        //creates a single string of terms -> no new table needed 
        for(int b = 0; b < terms.size(); b++){
            mehstring = mehstring + terms[b]+",";
        }

        restring = restring+"('"+hgvs+"','"+transcript_id+"','"+impact+"','"+variant_allele+"','"+
                   gene_symbole+"','"+gene_symbol_source+"','"+gene_id+"','"+hgnc_id+"','"+
                   strand+"','"+biotype+"','"+distance+"','"+mehstring+"')";

        //if not the last object add a "," to end of line
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
bool databank::searchDatabank(QString hgvs){

    QSqlQuery query;
    QString query1 = "SELECT t.hgvs FROM annotation AS t WHERE t.hgvs ='"+hgvs+"'";
    query.exec(query1);
    query.next();
    
    return query.isValid();

}
/**
 * @brief retrieveAnno
 * @param hgvs
 * @return Annotation
 */
Annotation & databank::retrieveAnno(QString hgvs){

    //retrieve most_severe_consequence, we already know hgvs
    QSqlQuery query;
    QString retrive = "SELECT t.most_severe_consequence FROM annotation AS t WHERE t.hgvs ='"+hgvs+"'";
    query.exec(retrive);
    query.next();
    QString most_severe_consequence = query.value(0).toString();

    //retrieve frequncies and assign them to variables
    retrive = "SELECT t.afr,t.eas,t.gnomad_eas,t.gnomad_nfe,t.gnomad_fin,t.sas,t.gnomad,t.amr,t.gnomad_sas,"
              "t.aa,t.gnomad_afr,t.eur,t.ea,t.gnomad_asj,t.gnomad_amr,t.gnomad_oth "
              "FROM frequencies AS t WHERE t.hgvs ='"+hgvs+"'";

    query.exec(retrive);
    query.next();
    qDebug() << "is freq query valid?: " << query.isValid();

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

    //frequncies object do create anno onject with later on
    Frequencies refreq = Frequencies( afr,  eas, gnomad_eas, gnomad_nfe, gnomad_fin,  sas,  gnomad,
                 amr,  gnomad_sas,  aa,  gnomad_afr,  eur,  ea,  gnomad_asj,
                 gnomad_amr,  gnomad_oth);

    // retrive transcriptcons
    retrive = "SELECT t.transcript_id,t.impact,t.variant_allele,t.gene_symbole,t.gene_symbol_source,t.gene_id"
              ",t.hgnc_id,t.strand,t.biotype,t.distance,t.terms FROM transcripscons AS t WHERE t.hgvs ='"+hgvs+"'";
    query.exec(retrive);
    //qDebug() <<"Transcripcons: " << query.lastError();
    //qDebug() << "Query" << query.lastQuery();


    QString transcript_id,impact, variant_allele,gene_symbole,gene_symbol_source,gene_id,
            hgnc_id,strand,biotype,distance,mehstring;

    QList<QString> terms;
    QList<Transcriptcons> relist;

   //cycle throu all Transcriptcons option in Query list
   while(query.next()){
    
       // create a new QList for consequence_terms and assing values to variables
       QList<QString> terms;
       transcript_id = query.value(0).toString();
       impact = query.value(1).toString();
       variant_allele = query.value(2).toString();
       gene_symbole = query.value(3).toString();
       gene_symbol_source = query.value(4).toString();
       gene_id = query.value(5).toString();
       hgnc_id = query.value(6).toString();
       strand = query.value(7).toString();
       biotype = query.value(8).toString();
       distance = query.value(9).toString();

       //split QString at every ',' and put into terms QList
       mehstring = query.value(10).toString();
       QStringList remeh = mehstring.split(',');
       for(int b = 0; b < remeh.size(); b++){
           terms << remeh[b];
       }
       //Transcriptcons object to put into list
       Transcriptcons retrans = Transcriptcons(transcript_id, impact, variant_allele,
                                               gene_symbole, gene_symbol_source,gene_id, hgnc_id, strand,
                                               biotype, distance,terms);

       //add Transcriptcons object to QList of Transcriptcons
       relist << retrans;

   }

    Annotation* reanno = new Annotation(refreq,relist,hgvs,most_severe_consequence);
   // qDebug() << "geht 3";
    return *reanno;
}

void databank::purgeDB() {
QSqlQuery query;

QString toexe = "DROP TABLE annotation, frequencies, transcripscons";
query.exec(toexe);
createTable();
}

void databank::deleterow(QString hgvs){
QSqlQuery query;
QString query1 = "DELETE FROM annotation AS t WHERE t.hgvs ='"+hgvs+"'";
}
















