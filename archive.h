#ifndef ARCHIVE_H
#define ARCHIVE_H

#include "histonotes.h"


template <class X> class HistoNotes;

class Archive {
private:
    HistoNotes<Article>** articles;
    HistoNotes<Tache>** taches;
    HistoNotes<Multimedia>** multimedias; //ajout 13/06

    unsigned int nbArticles;
    unsigned int nbTaches;
    unsigned int nbMultimedias; //ajout 13/06

    unsigned int nbMaxArticles;
    unsigned int nbMaxTaches;
    unsigned int nbMaxMultimedias;  //ajout 13/06

    mutable QString fileArchive;

   // RelationManager* relationsMan;

public:
    Archive();
    ~Archive();

    //RelationManager* getRelationManager();


    void addHistoArticle(HistoNotes<Article>* h);
    void addHistoArticle(QString id, QString titr, QString txt, QDate dateCrea, QDate dateModif);


    void addHistoTache(HistoNotes<Tache>* h);
    void addHistoTache(QString id, QString t, QString act, QString stat, QDate d, QString prio, QDate dateCrea, QDate dateModif);

    void addHistoMulti(HistoNotes<Multimedia>* h);
    void addHistoMulti(QString id, QString t, QString desc, QString fich, QString typ, QDate dateCrea, QDate dateModif);

    HistoNotes<Article>* getHistoArticle(const QString &id);
    HistoNotes<Tache>* getHistoTache(const QString &id);
    HistoNotes<Multimedia>* getHistoMulti(const QString &id);

    void removeHistoArticle(HistoNotes<Article>* h);
    void removeHistoTache(HistoNotes<Tache>* h);
    void removeHistoMulti(HistoNotes<Multimedia>* h);

    void setFilename(const QString& f) { fileArchive=f; }

    void saveArchive();
    void loadArchive();



    template <class X>
    class iterator{
        HistoNotes<X>** current;
        iterator(HistoNotes<X> **a):current(a){}

        friend class Archive;

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

#endif // ARCHIVE_H
