#include "histonotes.h"

HistoNoteManager::HistoNoteManager():nbArticles(0),nbTaches(0),nbMaxArticles(0),nbMaxTaches(0){}

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

const QString HistoNoteManager::makeArticleId(){
    QString newId="Article"+ QString::number(nbArticles+1); // +1 pour que commence à partir de 1
    return newId;

}

const QString HistoNoteManager::makeTacheId(){
    QString newId="Tache"+ QString::number(nbTaches+1);
    return newId;
}
