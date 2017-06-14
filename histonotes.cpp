#include "histonotes.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QString>

HistoNoteManager::HistoNoteManager():filename(""), nbArticles(0),nbTaches(0),nbMultimedias(0), nbMaxArticles(0),nbMaxTaches(0),nbMaxMultimedias(0){

}

HistoNoteManager::~HistoNoteManager(){
    for(unsigned int i=0; i<nbArticles; i++) delete articles[i];
    delete[] articles;

    for(unsigned int i=0; i<nbTaches; i++) delete taches[i];
    delete[] taches;

    for(unsigned int i=0; i<nbMultimedias; i++) delete multimedias[i];
    delete[] multimedias;
}

//SINGLETON
HistoNoteManager* HistoNoteManager::instance = 0; //initialisation + définition à nullptr
HistoNoteManager* HistoNoteManager::archives = 0;

HistoNoteManager& HistoNoteManager::getInstance(){ //méthode qui vérifie qu'il n'y ait qu'une seule instance de NotesManager
    if(HistoNoteManager::instance==0)
        HistoNoteManager::instance = new HistoNoteManager; //crée une instance
    return *HistoNoteManager::instance;
}

HistoNoteManager& HistoNoteManager::getArchive(){ 
    if(HistoNoteManager::archives==0)
        HistoNoteManager::archives = new HistoNoteManager; 
    return *HistoNoteManager::archives;
}

void HistoNoteManager::libererInstance(){
    if(HistoNoteManager::instance !=0) //si instance existe
        delete HistoNoteManager::instance; // supprime
    HistoNoteManager::instance=0; //réinitialisation à nullptr
}

void HistoNoteManager::libererArchive(){
    if(HistoNoteManager::archives !=0) //si instance existe
        delete HistoNoteManager::archives; // supprime
    HistoNoteManager::archives=0; //réinitialisation à nullptr
}

void HistoNoteManager::addHistoArticle(HistoNotes<Article>* h){
    if(nbArticles==nbMaxArticles){
        HistoNotes<Article>** newArt = new HistoNotes<Article>*[nbMaxArticles+5];
        for(unsigned int i=0; i<nbArticles; i++) newArt[i]=articles[i];
            HistoNotes<Article>** oldArt=articles;
            articles=newArt;
            nbMaxArticles+=5;
            if(oldArt) delete[] oldArt;
    }
    articles[nbArticles++]=h;

}

void HistoNoteManager::addHistoArticle(QString id, QString titr, QString txt){

    HistoNotes<Article>* ha= new HistoNotes<Article>();
    ha->addVersion(id,titr,txt);
    addHistoArticle(ha);
}

void HistoNoteManager::addHistoArticle(QString id, QString titr, QString txt, QDate dateCrea, QDate dateModif){

    HistoNotes<Article>* ha= new HistoNotes<Article>();
    ha->addVersion(id,titr,txt, dateCrea, dateModif);
    addHistoArticle(ha);
}


void HistoNoteManager::addHistoTache(HistoNotes<Tache>* h){
    if(nbTaches==nbMaxTaches){
        HistoNotes<Tache>** newTache = new HistoNotes<Tache>*[nbMaxTaches+5];
        for(unsigned int i=0; i<nbTaches; i++) newTache[i]=taches[i];
            HistoNotes<Tache>** oldTache=taches;
            taches=newTache;
            nbMaxTaches+=5;
            if(oldTache) delete[] oldTache;
    }
    taches[nbTaches++]=h;
}

void HistoNoteManager::addHistoTache(QString id, QString t, QString act, QString stat, QDate d, QString prio){

    HistoNotes<Tache>* ht= new HistoNotes<Tache>();
    ht->addVersion(id,t,act,stat,d,prio);
    addHistoTache(ht);
}

void HistoNoteManager::addHistoTache(QString id, QString t, QString act, QString stat, QDate d, QString prio, QDate dateCrea, QDate dateModif){

    HistoNotes<Tache>* ht= new HistoNotes<Tache>();
    ht->addVersion(id,t,act,stat,d,prio,  dateCrea,  dateModif);
    addHistoTache(ht);
}



void HistoNoteManager::addHistoMulti(HistoNotes<Multimedia>* h){
    if(nbMultimedias==nbMaxMultimedias){
        HistoNotes<Multimedia>** newMulti = new HistoNotes<Multimedia>*[nbMaxMultimedias+5];
        for(unsigned int i=0; i<nbMultimedias; i++) newMulti[i]=multimedias[i];
            HistoNotes<Multimedia>** oldMulti=multimedias;
            multimedias=newMulti;
            nbMaxMultimedias+=5;
            if(oldMulti) delete[] oldMulti;
    }
    multimedias[nbMultimedias++]=h;
}

void HistoNoteManager::addHistoMulti(QString id, QString t, QString desc, QString fich, QString typ){

    HistoNotes<Multimedia>* ht= new HistoNotes<Multimedia>();
    ht->addVersion(id,t,desc, fich, typ);
    addHistoMulti(ht);
}

void HistoNoteManager::addHistoMulti(QString id, QString t, QString desc, QString fich, QString typ, QDate dateCrea, QDate dateModif){

    HistoNotes<Multimedia>* ht= new HistoNotes<Multimedia>();
    ht->addVersion(id,t,desc, fich, typ, dateCrea, dateModif);
    addHistoMulti(ht);
}










HistoNotes<Article>* HistoNoteManager::getHistoArticle(const QString& id){
    iterator<Article> it=begin_article();
    while(it!=end_article()){
        if (it.getCurrent()->getId()==id) return *(it.current);
        ++it;

    }
    return nullptr;
}

HistoNotes<Tache>* HistoNoteManager::getHistoTache(const QString& id){
    iterator<Tache> it=begin_tache();
    while(it!=end_tache()){
        if (it.getCurrent()->getId()==id) return *(it.current);
        ++it;

    }
    return nullptr;
}

HistoNotes<Multimedia>* HistoNoteManager::getHistoMulti(const QString& id){
    iterator<Multimedia> it=begin_multi();
    while(it!=end_multi()){
        if (it.getCurrent()->getId()==id) return *(it.current);
        ++it;

    }
    return nullptr;
}

RelationManager* HistoNoteManager::getRelationManager(){ //méthode qui vérifie qu'il n'y ait qu'une seule instance de RelationManager
    if(HistoNoteManager::relationsMan==0)
        HistoNoteManager::relationsMan = new RelationManager; //crée une instance
    return HistoNoteManager::relationsMan;
}
const QString HistoNoteManager::makeArticleId(){
    QString newId="Article"+ QString::number(nbArticles+1); // +1 pour que commence à partir de 1
    return newId;

}

const QString HistoNoteManager::makeTacheId(){
    QString newId="Tache"+ QString::number(nbTaches+1);
    return newId;
}

const QString HistoNoteManager::makeMultiId(){
    QString newId="Multimedia"+ QString::number(nbMultimedias+1);
    return newId;
}

void HistoNoteManager::archiver(HistoNotes<Article>* ha){
   archives->addHistoArticle(ha);
   removeHistoArticle(ha);

}
void HistoNoteManager::archiver(HistoNotes<Tache>* ht){
    archives->addHistoTache(ht);
    removeHistoTache(ht);
}

void HistoNoteManager::archiver(HistoNotes<Multimedia>* hm){
    archives->addHistoMulti(hm);
    removeHistoMulti(hm);
}

void HistoNoteManager::restaurer(HistoNotes<Article>* ha){
    addHistoArticle(ha);
    archives->removeHistoArticle(ha);
}

void HistoNoteManager::restaurer(HistoNotes<Tache>* ht){
    addHistoTache(ht);
    archives->removeHistoTache(ht);
}

void HistoNoteManager::restaurer(HistoNotes<Multimedia>* hm){
    addHistoMulti(hm);
    archives->removeHistoMulti(hm);
}

void HistoNoteManager::removeHistoArticle(HistoNotes<Article>* h){
    unsigned int i=0;
    while(i<nbArticles && articles[i]!=h){
        i++;
    }
    articles[i]=nullptr;

    for(unsigned int j=i; j<nbArticles-1; j++){
        articles[j]=articles[j+1];
    }
    articles[nbArticles-1]=nullptr;
    nbArticles--;

}


void HistoNoteManager::removeHistoTache(HistoNotes<Tache>* h){
    unsigned int i=0;
    while(i<nbTaches && taches[i]!=h){
        i++;
    }
    taches[i]=nullptr;

    for(unsigned int j=i;j<nbTaches-1;j++){
        taches[j]=taches[j+1];
    }
    taches[nbTaches-1]=nullptr;
    nbTaches--;
}

void HistoNoteManager::removeHistoMulti(HistoNotes<Multimedia>* h){
    unsigned int i=0;
    while(i<nbMultimedias && multimedias[i]!=h){
        i++;
    }
    multimedias[i]=nullptr;

    for(unsigned int j=i;j<nbMultimedias-1;j++){
        multimedias[j]=multimedias[j+1];
    }
    multimedias[nbMultimedias-1]=nullptr;
    nbMultimedias--;
}



void HistoNoteManager::save() {
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
         return;
        //throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");
    for(unsigned int i=0; i<nbArticles; i++){
        stream.writeStartElement("histoArticle");
        stream.writeTextElement("id",articles[i]->getId());
        stream.writeTextElement("nbVersion",QString::number(articles[i]->getNbVersions()));
        stream.writeTextElement("nbMaxVersion",QString::number(articles[i]->getNbMaxVersions()));
        stream.writeTextElement("titre",articles[i]->getTitre());
        stream.writeTextElement("texte",articles[i]->getText());
        stream.writeTextElement("dateCrea",articles[i]->getCrea().toString());
        stream.writeTextElement("dateModif",articles[i]->getModif().toString());

        for(unsigned int j=1; j<articles[i]->getNbVersions(); j++){
            articles[i]->getVersion(j)->save(&newfile);
             stream.writeEndElement();
        }
        stream.writeEndElement();
    }

    for(unsigned int i=0; i<nbTaches; i++){
        stream.writeStartElement("histoTache");
        stream.writeTextElement("id",taches[i]->getId());
        stream.writeTextElement("nbVersion",QString::number(taches[i]->getNbVersions()));
        stream.writeTextElement("nbMaxVersion",QString::number(taches[i]->getNbMaxVersions()));
        stream.writeTextElement("titre",taches[i]->getTitre());
        stream.writeTextElement("dateCrea",taches[i]->getCrea().toString());
        stream.writeTextElement("dateModif",taches[i]->getModif().toString());
        stream.writeTextElement("dateEcheance",taches[i]->getEcheance().toString());
        stream.writeTextElement("prio",taches[i]->getPrio());
        stream.writeTextElement("action",taches[i]->getAction());
        stream.writeTextElement("statut",taches[i]->getStatut());

        for(unsigned int j=1; j<taches[i]->getNbVersions(); j++){
            taches[i]->getVersion(j)->save(&newfile);
             stream.writeEndElement();
        }
        stream.writeEndElement();
    }

    for(unsigned int i=0; i<nbMultimedias; i++){
        stream.writeStartElement("histoMultimedia");
        stream.writeTextElement("id",multimedias[i]->getId());
        stream.writeTextElement("nbVersion",QString::number(multimedias[i]->getNbVersions()));
        stream.writeTextElement("nbMaxVersion",QString::number(multimedias[i]->getNbMaxVersions()));
        stream.writeTextElement("titre",multimedias[i]->getTitre());
        stream.writeTextElement("dateCrea",multimedias[i]->getCrea().toString());
        stream.writeTextElement("dateModif",multimedias[i]->getModif().toString());
        stream.writeTextElement("type",multimedias[i]->getType());
        stream.writeTextElement("fichier",multimedias[i]->getFichier());
        stream.writeTextElement("description",multimedias[i]->getDesc());

        for(unsigned int j=1; j<multimedias[i]->getNbVersions(); j++){
            multimedias[i]->getVersion(j)->save(&newfile);
             stream.writeEndElement();
        }
        stream.writeEndElement();
    }

    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}





void HistoNoteManager::load() {
    QFile fin(filename);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //throw NotesException("Erreur ouverture fichier notes");
        return;
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {

            if(xml.name() == "notes") continue;


            if(xml.name() == "histoArticle") {
                qDebug()<<"new histoArticle\n";
                QString identificateur;
                QString nbVersion;
                QString nbMaxVersion;
                QString titre;
                QString texte;
                QDate dateCrea;
                QDate dateModif;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named histoArticle.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "histoArticle")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {

                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext();
                            identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }

                        // We've found nbVersions.
                        if(xml.name() == "nbVersion") {
                            xml.readNext();
                            nbVersion=xml.text().toString();
                            qDebug()<<"nbVersion="<<nbVersion<<"\n";
                        }

                        // We've found nbMaxVersions.
                        if(xml.name() == "nbMaxVersion") {
                            xml.readNext();
                            nbMaxVersion=xml.text().toString();
                            qDebug()<<"nbMaxVersion="<<nbMaxVersion<<"\n";
                        }


                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext();
                            titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found text
                        if(xml.name() == "texte") {
                            xml.readNext();
                            texte=xml.text().toString();
                            qDebug()<<"texte="<<texte<<"\n";
                        }

                        if(xml.name() == "dateCrea") {
                            xml.readNext();
                            dateCrea=QDate::fromString(xml.text().toString());
                            qDebug()<<"dateCrea="<<dateCrea<<"\n";
                        }

                        if(xml.name() == "dateModif") {
                            xml.readNext();
                            dateModif=QDate::fromString(xml.text().toString());
                            qDebug()<<"dateModif="<<dateModif<<"\n";
                        }


                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout histo "<<identificateur<<"\n";
                HistoNoteManager::addHistoArticle(identificateur,titre,texte,dateCrea, dateModif);
            }



            if(xml.name() == "histoTache") {
                qDebug()<<"new histoTache\n";
                QString identificateur;
                QString nbVersion;
                QString nbMaxVersion;
                QString titre;
                QDate dateEcheance;
                QDate dateCrea;
                QDate dateModif;
                QString priorite;
                QString action;
                QString statut;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named histoTache
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "histoTache")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {

                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext();
                            identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }

                        // We've found nbVersions.
                        if(xml.name() == "nbVersion") {
                            xml.readNext();
                            nbVersion=xml.text().toString();
                            qDebug()<<"nbVersion="<<nbVersion<<"\n";
                        }

                        // We've found nbMaxVersions.
                        if(xml.name() == "nbMaxVersion") {
                            xml.readNext();
                            nbMaxVersion=xml.text().toString();
                            qDebug()<<"nbMaxVersion="<<nbMaxVersion<<"\n";
                        }


                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext();
                            titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found echeance
                        if(xml.name() == "dateEcheance") {
                            xml.readNext();
                            dateEcheance=QDate::fromString(xml.text().toString());
                            qDebug()<<"dateEcheance="<<dateEcheance<<"\n";
                        }

                        // We've found cre
                        if(xml.name() == "dateCrea") {
                            xml.readNext();
                            dateCrea=QDate::fromString(xml.text().toString());
                            qDebug()<<"dateCrea="<<dateCrea<<"\n";
                        }

                            //we've found modif
                        if(xml.name() == "dateModif") {
                            xml.readNext();
                            dateModif=QDate::fromString(xml.text().toString());
                            qDebug()<<"dateModif="<<dateModif<<"\n";
                        }

                         //we've found action
                        if(xml.name() == "action") {
                        xml.readNext();
                        action=xml.text().toString();
                        qDebug()<<"action="<<action<<"\n";
                        }

                        // We've found priorite
                        if(xml.name() == "priorite") {
                            xml.readNext();
                            priorite=xml.text().toString();
                            qDebug()<<"priorite="<<priorite<<"\n";
                        }


                        //we've found statut
                       if(xml.name() == "statut") {
                        xml.readNext();
                        statut=xml.text().toString();
                        qDebug()<<"statut="<<statut<<"\n";
                       }

                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout histo "<<identificateur<<"\n";
                HistoNoteManager::addHistoTache(identificateur,titre,action, priorite, dateEcheance, statut, dateCrea, dateModif);
            }



            if(xml.name() == "histoMultimedia") {
                qDebug()<<"new histoMutimedia\n";
                QString identificateur;
                QString nbVersion;
                QString nbMaxVersion;
                QString titre;
                QDate dateCrea;
                QDate dateModif;
                QString type;
                QString fichier;
                QString description;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named histoArticle.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "histoMultimedia")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {

                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext();
                            identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }

                        // We've found nbVersions.
                        if(xml.name() == "nbVersion") {
                            xml.readNext();
                            nbVersion=xml.text().toString();
                            qDebug()<<"nbVersion="<<nbVersion<<"\n";
                        }

                        // We've found nbMaxVersions.
                        if(xml.name() == "nbMaxVersion") {
                            xml.readNext();
                            nbMaxVersion=xml.text().toString();
                            qDebug()<<"nbMaxVersion="<<nbMaxVersion<<"\n";
                        }


                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext();
                            titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }


                        // We've found cre
                        if(xml.name() == "dateCrea") {
                            xml.readNext();
                            dateCrea=QDate::fromString(xml.text().toString());
                            qDebug()<<"dateCrea="<<dateCrea<<"\n";
                        }

                            //we've found modif
                        if(xml.name() == "dateModif") {
                            xml.readNext();
                            dateModif=QDate::fromString(xml.text().toString());
                            qDebug()<<"dateModif="<<dateModif<<"\n";
                        }

                         //we've found type
                        if(xml.name() == "type") {
                        xml.readNext();
                        type=xml.text().toString();
                        qDebug()<<"type="<<type<<"\n";
                        }

                        // We've found fichier
                        if(xml.name() == "fichier") {
                            xml.readNext();
                            fichier=xml.text().toString();
                            qDebug()<<"fichier="<<fichier<<"\n";
                        }


                        //we've found statut
                       if(xml.name() == "description") {
                        xml.readNext();
                        description=xml.text().toString();
                        qDebug()<<"description="<<description<<"\n";
                       }

                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout histo "<<identificateur<<"\n";
                HistoNoteManager::addHistoMulti(identificateur,titre,description, fichier, type, dateCrea, dateModif);
            }



        }
    }
    // Error handling.
    if(xml.hasError()) {
        //throw NotesException("Erreur lecteur fichier notes, parser xml");
        return;
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}


