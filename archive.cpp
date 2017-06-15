#include "archive.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QString>

Archive::Archive():nbArticles(0),nbTaches(0),nbMultimedias(0), nbMaxArticles(0),nbMaxTaches(0),nbMaxMultimedias(0){}


Archive::~Archive(){
    for(unsigned int i=0; i<nbArticles; i++) delete articles[i];
    delete[] articles;

    for(unsigned int i=0; i<nbTaches; i++) delete taches[i];
    delete[] taches;

    for(unsigned int i=0; i<nbMultimedias; i++) delete multimedias[i];
    delete[] multimedias;
}

void Archive::addHistoArticle(HistoNotes<Article>* h){
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

    void Archive::addHistoArticle(QString id, QString titr, QString txt, QDate dateCrea, QDate dateModif){

        HistoNotes<Article>* ha= new HistoNotes<Article>();
        ha->addVersion(id,titr,txt, dateCrea, dateModif);
        addHistoArticle(ha);
    }


void Archive::addHistoTache(HistoNotes<Tache>* h){
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


void Archive::addHistoTache(QString id, QString t, QString act, QString stat, QDate d, QString prio, QDate dateCrea, QDate dateModif){

    HistoNotes<Tache>* ht= new HistoNotes<Tache>();
    ht->addVersion(id,t,act,stat,d,prio,  dateCrea,  dateModif);
    addHistoTache(ht);
}

void Archive::addHistoMulti(HistoNotes<Multimedia>* h){
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

void Archive::addHistoMulti(QString id, QString t, QString desc, QString fich, QString typ, QDate dateCrea, QDate dateModif){

    HistoNotes<Multimedia>* ht= new HistoNotes<Multimedia>();
    ht->addVersion(id,t,desc, fich, typ, dateCrea, dateModif);
    addHistoMulti(ht);
}


HistoNotes<Article>* Archive::getHistoArticle(const QString& id){
    iterator<Article> it=begin_article();
    while(it!=end_article()){
        if (it.getCurrent()->getId()==id) return *(it.current);
        ++it;

    }
    return nullptr;
}

HistoNotes<Tache>* Archive::getHistoTache(const QString& id){
    iterator<Tache> it=begin_tache();
    while(it!=end_tache()){
        if (it.getCurrent()->getId()==id) return *(it.current);
        ++it;

    }
    return nullptr;
}

HistoNotes<Multimedia>* Archive::getHistoMulti(const QString& id){
    iterator<Multimedia> it=begin_multi();
    while(it!=end_multi()){
        if (it.getCurrent()->getId()==id) return *(it.current);
        ++it;

    }
    return nullptr;
}

void Archive::removeHistoArticle(HistoNotes<Article>* h){
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


void Archive::removeHistoTache(HistoNotes<Tache>* h){
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

void Archive::removeHistoMulti(HistoNotes<Multimedia>* h){
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



void Archive::saveArchive() {
    QFile newfile(fileArchive);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
         return;
        //throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartElement("pluri");
    for(unsigned int i=0; i<nbArticles; i++){
        stream.writeStartElement("histoArticle");
        for(unsigned int j=0; j<articles[i]->getNbVersions(); j++){
             stream.writeStartElement("article");
             stream.writeTextElement("id",articles[i]->getVersion(j)->getId());
             stream.writeTextElement("titre",articles[i]->getVersion(j)->getTitre());
             stream.writeTextElement("dateCrea",articles[i]->getVersion(j)->getCrea().toString());
             stream.writeTextElement("dateModif",articles[i]->getVersion(j)->getModif().toString());
             stream.writeTextElement("texte",articles[i]->getVersion(j)->getText());
             stream.writeEndElement();
        }
        stream.writeEndElement();
    }

    for(unsigned int i=0; i<nbTaches; i++){
        stream.writeStartElement("histoTache");
        for(unsigned int j=0; j<taches[i]->getNbVersions(); j++){
            stream.writeStartElement("tache");
            stream.writeTextElement("id",taches[i]->getVersion(j)->getId());
            stream.writeTextElement("titre",taches[i]->getVersion(j)->getTitre());
            stream.writeTextElement("dateCrea",taches[i]->getVersion(j)->getCrea().toString());
            stream.writeTextElement("dateModif",taches[i]->getVersion(j)->getModif().toString());
            stream.writeTextElement("action",taches[i]->getVersion(j)->getAction());
            stream.writeTextElement("statut",taches[i]->getVersion(j)->getStatut());
            stream.writeTextElement("prio",taches[i]->getVersion(j)->getPriorite());
            stream.writeTextElement("dateEcheance",taches[i]->getVersion(j)->getEcheance().toString());
            stream.writeEndElement();
        }
        stream.writeEndElement();
    }

    for(unsigned int i=0; i<nbMultimedias; i++){
        stream.writeStartElement("histoMultimedia");
        for(unsigned int j=0; j<multimedias[i]->getNbVersions(); j++){
            stream.writeStartElement("multimedia");
            stream.writeTextElement("id",multimedias[i]->getVersion(j)->getId());
            stream.writeTextElement("titre",multimedias[i]->getVersion(j)->getTitre());
            stream.writeTextElement("dateCrea",multimedias[i]->getVersion(j)->getCrea().toString());
            stream.writeTextElement("dateModif",multimedias[i]->getVersion(j)->getModif().toString());
            stream.writeTextElement("description",multimedias[i]->getVersion(j)->getDesc());
            stream.writeTextElement("fichier",multimedias[i]->getVersion(j)->getFichier());
            stream.writeTextElement("type",multimedias[i]->getVersion(j)->getType());
            stream.writeEndElement();
        }
        stream.writeEndElement();
    }

    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}





void Archive::loadArchive() {
    QFile fin(fileArchive);
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
        if(token == QXmlStreamReader::StartElement ) {

            if(xml.name() == "histoArticle") {
                qDebug()<<"new histoArticle\n";
                QString identificateur;
                QString titre;
                QString texte;
                QDate dateCrea;
                QDate dateModif;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named histoArticle.
                int compteur=0;
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "histoArticle")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {

                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext();
                            identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
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

                        if(xml.name() == "article") {
                            xml.readNext();
                                if (compteur==1){
                                    qDebug()<<"ajout histo "<<identificateur<<"\n";
                                    Archive::addHistoArticle(identificateur,titre,texte,dateCrea, dateModif);
                                }

                                if(compteur>1) {
                                    qDebug()<<"ajout Article="<<titre<<"\n";
                                    Archive::getHistoArticle(identificateur)->addVersion(identificateur, titre, texte, dateCrea, dateModif);
                                    }
                            compteur++;
                        }



                    }
                    // ...and next...
                    xml.readNext();

                }
                if (compteur==1){
                    qDebug()<<"ajout histo "<<identificateur<<"\n";
                    Archive::addHistoArticle(identificateur,titre,texte,dateCrea, dateModif);
                }

                if(compteur>1) {
                    qDebug()<<"ajout Article="<<titre<<"\n";
                    Archive::getHistoArticle(identificateur)->addVersion(identificateur, titre, texte, dateCrea, dateModif);
                    }
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
                int compteur=0;
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

                       if(xml.name() == "tache") {
                           xml.readNext();
                               if (compteur==1){
                                   qDebug()<<"ajout histo "<<identificateur<<"\n";
                                   Archive::addHistoTache(identificateur,titre,action, statut, dateEcheance, priorite, dateCrea, dateModif);
                               }

                               if(compteur>1) {
                                   qDebug()<<"ajout tache="<<titre<<"\n";
                                   Archive::getHistoTache(identificateur)->addVersion(identificateur,titre,action, statut, dateEcheance, priorite, dateCrea, dateModif);
                                   }
                           compteur++;
                       }

                    }
                    // ...and next...
                    xml.readNext();
                }
                if (compteur==1){
                    qDebug()<<"ajout histo "<<identificateur<<"\n";
                    Archive::addHistoTache(identificateur,titre,action, statut, dateEcheance, priorite, dateCrea, dateModif);
                }

                if(compteur>1) {
                    qDebug()<<"ajout tache="<<titre<<"\n";
                    Archive::getHistoTache(identificateur)->addVersion(identificateur,titre,action, statut, dateEcheance, priorite, dateCrea, dateModif);
                    }
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
                int compteur=0;
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

                       if(xml.name() == "multimedia") {
                           xml.readNext();
                               if (compteur==1){
                                   qDebug()<<"ajout histo "<<identificateur<<"\n";
                                   Archive::addHistoMulti(identificateur,titre,description,fichier,type, dateCrea, dateModif);
                               }

                               if(compteur>1) {
                                   qDebug()<<"ajout tache="<<titre<<"\n";
                                   Archive::getHistoMulti(identificateur)->addVersion(identificateur,titre,description,fichier,type, dateCrea, dateModif);
                                   }
                           compteur++;
                       }

                    }
                    // ...and next...
                    xml.readNext();
                }
                if (compteur==1){
                    qDebug()<<"ajout histo "<<identificateur<<"\n";
                    Archive::addHistoMulti(identificateur,titre,description,fichier,type, dateCrea, dateModif);
                }

                if(compteur>1) {
                    qDebug()<<"ajout tache="<<titre<<"\n";
                    Archive::getHistoMulti(identificateur)->addVersion(identificateur,titre,description,fichier,type, dateCrea, dateModif);
                    }
            }

        }
    }
    // Error handling.
    if(xml.hasError()) {
        //throw NotesException("Erreur lecteur fichier notes, parser xml");
        //return;
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}

