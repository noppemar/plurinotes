#include "histonotes.h"

HistoNoteManager::HistoNoteManager():nbArticles(0),nbTaches(0),nbMaxArticles(0),nbMaxTaches(0),filename(""){}

HistoNoteManager::~HistoNoteManager(){
    for(unsigned int i=0; i<nbArticles; i++) delete articles[i];
    delete[] articles;

    for(unsigned int i=0; i<nbTaches; i++) delete taches[i];
    delete[] taches;
}

//SINGLETON
HistoNoteManager* HistoNoteManager::instance = 0; //initialisation + définition à nullptr

HistoNoteManager& HistoNoteManager::getInstance(){ //méthode qui vérifie qu'il n'y ait qu'une seule instance de NotesManager
    if(HistoNoteManager::instance==0)
        HistoNoteManager::instance = new HistoNoteManager; //crée une instance
    return *HistoNoteManager::instance;
}

void HistoNoteManager::libererInstance(){
    if(HistoNoteManager::instance !=0) //si instance existe
        delete HistoNoteManager::instance; // supprime
    HistoNoteManager::instance=0; //réinitialisation à nullptr
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
        stream.writeStartElement("article");
        stream.writeTextElement("id",articles[i]->getId());
        stream.writeTextElement("title",articles[i]->getTitre());
        stream.writeTextElement("texte",articles[i]->getText());
        stream.writeTextElement("dateCrea",articles[i]->getCrea().toString());
        stream.writeTextElement("dateModif",articles[i]->getModif().toString());
        stream.writeTextElement("nbVersion",QString::number(articles[i]->getNbVersions()));
        stream.writeTextElement("nbMaxVersion",QString::number(articles[i]->getNbMaxVersions()));
        for(unsigned int j=1; j<articles[i]->getNbVersions(); j++){
            articles[i]->getVersion(j)->save(&newfile);
             stream.writeEndElement();
        }
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}





/*void HistoNoteManager::load() {
    QFile fin("notes.xml");
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NotesException("Erreur ouverture fichier notes");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if(xml.name() == "notes") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "note") {
                qDebug()<<"new note\n";
                QString identificateur;
                QString titre;
                QDateTime dateC;
                QDateTime dateMod;
                bool act;
                bool supp;
                Version** v= new  Version*[1];
                unsigned int nbV;
                unsigned int nbMV;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "note")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }
                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found datecrea
                        if(xml.name() == "date crea") {
                            xml.readNext();
                            dateC.fromString(xml.text().toString());
                            qDebug()<<"dateCrea="<<dateC<<"\n";
                        }
                        // We've found datemodif
                        if(xml.name() == "date modif") {
                            xml.readNext();
                            dateMod.fromString(xml.text().toString());
                            qDebug()<<"dateModif="<<dateMod<<"\n";
                        }
                        // We've found active
                        if(xml.name() == "active") {
                            xml.readNext();
                            act=(xml.text().toString()).toInt();
                            qDebug()<<"active="<<act<<"\n";
                        }
                        // We've found supprime
                        if(xml.name() == "supprime") {
                            xml.readNext();
                            supp=(xml.text().toString()).toInt();
                            qDebug()<<"supprime="<<supp<<"\n";
                        }
                        // We've found nbVersion
                        if(xml.name() == "nb version") {
                            xml.readNext();
                            nbV=(xml.text().toString()).toInt();
                            qDebug()<<"nbVersion="<<nbV<<"\n";
                        }
                        // We've found nbMaxVersion
                        if(xml.name() == "nb max version") {
                            xml.readNext();
                            nbMV=(xml.text().toString()).toInt();
                            qDebug()<<"nbMaxVersion="<<nbMV<<"\n";
                        }
                         if(xml.name() == "article") {
                             qDebug()<<"new article\n";
                             QDateTime dateV;
                             QString texte;
                             QXmlStreamAttributes attributesV = xml.attributes();
                             xml.readNext();
                             while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "article")) {
                             if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                // We've found dateversion
                            if(xml.name() == "date version") {
                                xml.readNext();
                                dateV.fromString(xml.text().toString());
                                qDebug()<<"date="<<dateV<<"\n";
                        }
                        // We've found texte article
                        if(xml.name() == "texte") {
                            xml.readNext();
                            texte=xml.text().toString();
                            qDebug()<<"texte="<<texte<<"\n";
                        }
                         }
                             xml.readNext();
                         }
                             qDebug()<<"ajout version "<<dateV<<"\n";
                             editer()
                         }
                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout note "<<identificateur<<"\n";
                addNoteXML(identificateur,titre,dateC,dateMod,act,supp,nbV,nbMV,v);
            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}
*/
