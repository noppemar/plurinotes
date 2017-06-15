#ifndef HISTONOTES_H
#define HISTONOTES_H

#include "notes.h"
#include "relation.h"
#include "archive.h"
template <class X> class HistoNotes;
class Archive;


class HistoNoteManager {
private:
    HistoNotes<Article>** articles;
    HistoNotes<Tache>** taches;
    HistoNotes<Multimedia>** multimedias; //ajout 13/06

    mutable QString filename;

    unsigned int nbArticles;
    unsigned int nbTaches;
    unsigned int nbMultimedias; //ajout 13/06

    unsigned int nbMaxArticles;
    unsigned int nbMaxTaches;
    unsigned int nbMaxMultimedias;  //ajout 13/06
    
    Archive* archives;
    
    static HistoNoteManager *instance;
    HistoNoteManager();
    ~HistoNoteManager();
    HistoNoteManager(const HistoNoteManager& m);
    HistoNoteManager& operator=(const HistoNoteManager&);

    //RelationManager* relationsMan;

public:
    static HistoNoteManager& getInstance(); //DP singleton
    static void libererInstance(); //DP singleton

    Archive* getArchive(){return archives;}

    //RelationManager* getRelationManager(){return relationsMan;}
    
    const QString makeArticleId();
    const QString makeTacheId();
    const QString makeMultiId();

    void addHistoArticle(HistoNotes<Article>* h);
    void addHistoArticle(QString id, QString titr, QString txt);
    void addHistoArticle(QString id, QString titr, QString txt, QDate dateCrea, QDate dateModif);


    void addHistoTache(HistoNotes<Tache>* h);
    void addHistoTache(QString id, QString t, QString act, QString stat, QDate d, QString prio="");
    void addHistoTache(QString id, QString t, QString act, QString stat, QDate d, QString prio, QDate dateCrea, QDate dateModif);

    void addHistoMulti(HistoNotes<Multimedia>* h);
    void addHistoMulti(QString id, QString t, QString desc, QString fich, QString typ=""); //ajout 13/06
    void addHistoMulti(QString id, QString t, QString desc, QString fich, QString typ, QDate dateCrea, QDate dateModif);

    HistoNotes<Article>* getHistoArticle(const QString &id);
    HistoNotes<Tache>* getHistoTache(const QString &id);
    HistoNotes<Multimedia>* getHistoMulti(const QString &id);
    
    void removeHistoArticle(HistoNotes<Article>* h);
    void removeHistoTache(HistoNotes<Tache>* h);
    void removeHistoMulti(HistoNotes<Multimedia>* h);

    void archiver(HistoNotes<Article>* ha);
    void archiver(HistoNotes<Tache>* ht);
    void archiver(HistoNotes<Multimedia>* hm);

    void restaurer(HistoNotes<Article>* ha);
    void restaurer(HistoNotes<Tache>* ht);
    void restaurer(HistoNotes<Multimedia>* ht);

    
    QString getFilename() const { return filename; }
    void setFilename(const QString& f) { filename=f; }

    void save();
    void load();


    
    
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

    iterator<Multimedia> begin_multi(){ //1ère case du tableau multimedias    add le 13/06
        return iterator<Multimedia>(multimedias);
    }

    iterator<Multimedia> end_multi(){ //case juste après dernière case du tableau multimedias (condition boucle for : !=m.end)  add le 13/06
        return iterator<Multimedia>(multimedias + nbMultimedias);
    }


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
    void addVersion(QString id, QString t, QString act, QString stat, QDate d, QString prio); //tache
    void addVersion(QString id, QString t, QString desc, QString fich, QString typ=""); //multimedias

    void addVersion(QString i, QString t, QString txt, QDate dateCrea, QDate dateModif); //article
    void addVersion(QString id, QString t, QString act, QString stat, QDate d, QString prio, QDate dateCrea, QDate dateModif); //tache
    void addVersion(QString id, QString t, QString desc, QString fich, QString typ, QDate dateCrea, QDate dateModif); //multimedias



    X* getFirstVersion(){return versions[0];}
    X* getVersion(int n){return versions[n];}
    X* getLastVersion() {return versions[nbVersions-1];}

    const QString& getId(){ return versions[0]->getId(); }    //accesseurs communs aux notes
    const QString& getTitre(){ return versions[0]->getTitre(); }
    const QDate& getModif(){ return versions[0]->getModif(); }
    const QDate& getCrea(){ return versions[0]->getCrea(); }
    unsigned int getNbVersions() { return nbVersions; }
    unsigned int getNbMaxVersions() { return nbMaxVersions; }


    const QString& getText(){ return versions[0]->getText(); }        // spécifique aux articles : texte

    const QString& getPrio(){ return versions[0]->getPriorite(); }        //specifique aux Taches : prio, action, dateEcheance, statut
    const QDate& getEcheance(){ return versions[0]->getEcheance(); }
    const QString& getAction(){ return versions[0]->getAction(); }
    const QString& getStatut(){ return versions[0]->getStatut(); }

    const QString& getDesc(){ return versions[0]->getDesc(); }   // spécifique aux Multi
    const QString& getType(){ return versions[0]->getType(); }
    const QString& getFichier(){ return versions[0]->getFichier(); }



    ~HistoNotes();

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
void HistoNotes<X>::addVersion(QString id, QString t, QString desc, QString fich, QString typ){
    if(nbVersions==nbMaxVersions){
        X** newVersions = new X*[nbMaxVersions+5];

        for(unsigned int i=0; i<nbVersions; i++) newVersions[i]=versions[i];
        X** oldVersions=versions;
        versions=newVersions;
        nbMaxVersions+=5;
        if(oldVersions) delete[] oldVersions;

    }
    versions[nbVersions++]= new Multimedia(id,t, desc, fich, typ);
}




template <class X>
void HistoNotes<X>::addVersion(QString id, QString t, QString txt, QDate dateCrea, QDate dateModif){
    if(nbVersions==nbMaxVersions){
        X** newVersions = new X*[nbMaxVersions+5];

        for(unsigned int i=0; i<nbVersions; i++) newVersions[i]=versions[i];
        X** oldVersions=versions;
        versions=newVersions;
        nbMaxVersions+=5;
        if(oldVersions) delete[] oldVersions;

    }
    versions[nbVersions++]= new Article(id,t,txt,dateCrea, dateModif);
}

template <class X>
void HistoNotes<X>::addVersion(QString id, QString t, QString act, QString stat, QDate d, QString prio, QDate dateCrea, QDate dateModif){
    if(nbVersions==nbMaxVersions){
        X** newVersions = new X*[nbMaxVersions+5];

        for(unsigned int i=0; i<nbVersions; i++) newVersions[i]=versions[i];
        X** oldVersions=versions;
        versions=newVersions;
        nbMaxVersions+=5;
        if(oldVersions) delete[] oldVersions;

    }
    versions[nbVersions++]= new Tache(id,t,act,stat,prio,d,dateCrea, dateModif);
}

template <class X>
void HistoNotes<X>::addVersion(QString id, QString t, QString desc, QString fich, QString typ, QDate dateCrea, QDate dateModif){
    if(nbVersions==nbMaxVersions){
        X** newVersions = new X*[nbMaxVersions+5];

        for(unsigned int i=0; i<nbVersions; i++) newVersions[i]=versions[i];
        X** oldVersions=versions;
        versions=newVersions;
        nbMaxVersions+=5;
        if(oldVersions) delete[] oldVersions;

    }
    versions[nbVersions++]= new Multimedia(id,t, desc, fich, typ,dateCrea, dateModif);
}




template <class X>
HistoNotes<X>::~HistoNotes(){
    for(unsigned int i=0; i<nbVersions; i++) delete versions[i];

    delete[] versions;
}



#endif // HISTONOTES_H
