#include "histonotes.h"

HistoNoteManager::HistoNoteManager():nbTaches(0),nbMaxTaches(0),nbArticles(0),nbMaxArticles(0){}

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
void HistoNoteManager::addHistoArticle(QString id, QString tit, QString txt){
    HistoNotes<Article> h;
    h.addVersion(id,tit,txt);
    addHistoArticle(&h);
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
