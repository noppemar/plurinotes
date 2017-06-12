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

    const QString makeArticleId();
    const QString makeTacheId();

    void addHistoArticle(HistoNotes<Article>* h);



    void addHistoArticle(QString id, QString titr, QString txt);

    void addHistoTache(HistoNotes<Tache>* h);
    void addHistoTache(QString id, QString t, QString act, QString stat, QDate d, QString prio="");

    HistoNotes<Article>* getHistoArticle(const QString &id);
    HistoNotes<Tache>* getHistoTache(const QString &id);


    template <class X>
    class iterator{
        HistoNotes<X>** current;
        iterator(HistoNotes<X> **a):current(a){}

        friend class HistoNoteManager;

    public:
        iterator():current(0){}
        HistoNotes<X>* getCurrent(){return *current;}
        HistoNotes<X>& operator*(){ //pour avoir contenu du double pointeur avec 1 seul *
            return **current;
        }

        iterator<X> &operator++(){
            ++current;
            return *this;
        }

        bool operator!=(iterator<X> it) const{
            return current != it.current;
        }
    };

    iterator<Article> begin_article(){ //1ère case du tableau articles
        return iterator<Article>(articles);
    }

    iterator<Article> end_article(){ //case juste après dernière case du tableau article (condition boucle for : !=m.end)
        return iterator<Article>(articles + nbArticles);
    }

    iterator<Tache> begin_tache(){ //1ère case du tableau taches
        return iterator<Tache>(taches);
    }

    iterator<Tache> end_tache(){ //case juste après dernière case du tableau tache (condition boucle for : !=m.end)
        return iterator<Tache>(taches + nbTaches);
    }


/*
    class const_iterator{ //pareil avec const partout
        Article **current;
        const_iterator(Article **a):current(a){}

        friend class NotesManager;
    public:
        const_iterator():current(0){}

        const Article &operator*() const {
            return **current;
        }

        const_iterator &operator++(){
            ++current;
            return *this;
        }

        bool operator!=(const_iterator it) const{
            return current != it.current;
        }

    };

    const_iterator begin() const{   //1ère case du tableau articles
        return const_iterator(articles);
    }
    const_iterator end() const{ //case juste après la dernière case du tableau articles (condition boucle for : !=m.end
        return const_iterator(articles + nbArticles);
    }


*/

};


template <class X> class HistoNotes
{
private:
    X** versions;
    unsigned int nbVersions;
    unsigned int nbMaxVersions;

public:
    HistoNotes():versions(nullptr),nbVersions(0),nbMaxVersions(0){}


    void addVersion(QString i, QString t, QString txt); //article
    void addVersion(QString id, QString t, QString act, QString stat, QDate d=0, QString prio=""); //tache
    //verif que param optionnelle oooook avc interface


    //void addVersion(QString i, QString t, QString a, char c); //tache


    X* getFirstVersion(){return versions[0];}
    X* getVersion(int n){return versions[n];}
    X* getLastVersion() {return versions[nbVersions-1];}

    const QString& getId(){
        return versions[0]->getId();
    }

    ~HistoNotes();

    /* INUTILE ????
    template <class Y>
    class iterator{
        Y** current;
        iterator(Y** a):current(a){}

        friend class HistoNotes;

    public:
        iterator():current(0){}

        Y& operator*(){ //pour avoir contenu du double pointeur avec 1 seul *
            return **current;
        }

        iterator<Y> &operator++(){
            ++current;
            return *this;
        }

        iterator<Y> &operator--(){
            --current;
            return *this;
        }

        bool operator!=(iterator<Y> it) const{
            return current != it.current;
        }
    };

     POUR POUVOIR SE BALADER DANS LES VERSIONS SUIVANTES ET PRECEDENTES */
    /*
    iterator<X> begin(){ //1ère case du tableau articles
        return iterator<X>(versions);
    }

    iterator<X> end(){ //case juste après dernière case du tableau article (condition boucle for : !=m.end)
        return iterator<X>(versions + nbVersions);
    } */
};


template <class X>
void HistoNotes<X>::addVersion(QString id, QString t, QString txt){
    if(nbVersions==nbMaxVersions){
        X** newVersions = new X*[nbMaxVersions+5];

        for(unsigned int i=0; i<nbVersions; i++) newVersions[i]=versions[i];
        X** oldVersions=versions;
        versions=newVersions;
        nbMaxVersions+=5;
        if(oldVersions) delete[] oldVersions;

    }
    versions[nbVersions++]= new Article(id,t,txt);
}

template <class X>
void HistoNotes<X>::addVersion(QString id, QString t, QString act, QString stat, QDate d, QString prio){
    if(nbVersions==nbMaxVersions){
        X** newVersions = new X*[nbMaxVersions+5];

        for(unsigned int i=0; i<nbVersions; i++) newVersions[i]=versions[i];
        X** oldVersions=versions;
        versions=newVersions;
        nbMaxVersions+=5;
        if(oldVersions) delete[] oldVersions;

    }
    versions[nbVersions++]= new Tache(id,t,act,stat,prio,d);
}



template <class X>
HistoNotes<X>::~HistoNotes(){
    for(unsigned int i=0; i<nbVersions; i++) delete versions[i];

    delete[] versions;
}



#endif // HISTONOTES_H
