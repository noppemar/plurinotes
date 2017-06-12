#ifndef HISTONOTES_H
#define HISTONOTES_H

#include "notes.h"
template <class X> class HistoNotes;


class HistoNoteManager {
private:
    HistoNotes<Article>** articles;
    HistoNotes<Tache>** taches;

    unsigned int nbArticles;
    unsigned int nbTaches;

    unsigned int nbMaxArticles;
    unsigned int nbMaxTaches;

    static HistoNoteManager *instance;
    HistoNoteManager();
    ~HistoNoteManager();
    HistoNoteManager(const HistoNoteManager& m);
    HistoNoteManager& operator=(const HistoNoteManager&);

public:
    static HistoNoteManager& getInstance(); //DP singleton
    static void libererInstance(); //DP singleton
    void addHistoArticle(HistoNotes<Article>* h);
    void addHistoTache(HistoNotes<Tache>* h);

    HistoNotes<Article>* getHistoArticle(){return articles[0];} //pour test addHistoArticle




};


template <class X> class HistoNotes
{
private:
    X** versions;
    unsigned int nbVersions;
    unsigned int nbMaxVersions;

public:
    HistoNotes():nbVersions(0),nbMaxVersions(0){}

    void addVersion(X* n);
    //Je sais pas si c'est à faire faut voir comment ça se passe pour récupérer les trucs avc Qt...
    //void addVersion(QString i, QString t, QString txt); //article
    //void addVersion(QString i, QString t, QString a, char c); //tache

    X* getFirstVersion(){return versions[0];}
    X* getVersion(int n){return versions[n];}
    X* getLastVersion() {return versions[nbVersions-1];}

    ~HistoNotes();
};

template <class X>
void HistoNotes<X>::addVersion(X* n){
    if(nbVersions==nbMaxVersions){
        X** newVersions = new X*[nbMaxVersions+5];

        for(unsigned int i=0; i<nbVersions; i++) newVersions[i]=versions[i];
        X** oldVersions=versions;
        versions=newVersions;
        nbMaxVersions+=5;
        if(oldVersions) delete[] oldVersions;

    }
    versions[nbVersions++]=n;
}

template <class X>
HistoNotes<X>::~HistoNotes(){
    for(unsigned int i=0; i<nbVersions; i++) delete versions[i];

    delete[] versions;
}

template <class X>
void HistoNotes<X>::addVersion(QString i, QString t, QString txt){
    Article a=Article(i,t,txt);
    addVersion(&a);
} //article


#endif // HISTONOTES_H
