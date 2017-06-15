#include "archive.h"

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
