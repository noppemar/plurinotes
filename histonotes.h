#ifndef HISTONOTES_H
#define HISTONOTES_H

#include "notes.h"
#include "relation.h"
#include "archive.h"
template <class X> class HistoNotes;
class Archive;

/*!
 * \brief The HistoNoteManager class
 * HistoNoteManager est la classe principale de l'application :
 * il n'existe qu'une seule instance de cette classe ( design pattern singleton).
 * Cette classe permet de manipuler les différents HistoNotes ( Article, Tache, Mutimedia ) à l'aide de 3 attributs
 * ( de type double pointeur sur HistoNotes) : articles, taches, multimedias.
 * HistoNoteManager est le point de départ de toutes créations : c'est elle qui permet la creation des HistoNotes, et donc des Notes.
 */
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

    /*!
     * \brief HistoNoteManager
     */
    HistoNoteManager();

    ~HistoNoteManager();
    /*!
     * \brief HistoNoteManager
     * \param m
     */
    HistoNoteManager(const HistoNoteManager& m);

    /*!
     * \brief operator =
     * \return
     */
    HistoNoteManager& operator=(const HistoNoteManager&);

    //RelationManager* relationsMan;

public:
    /*!
     * \brief getInstance
     * \return
     * méthode renvoyant une référence vers l'unique instance de HistoNoteManager
     */
    static HistoNoteManager& getInstance(); //DP singleton

    /*!
     * \brief libererInstance
     * Methode permettant de libérer l'instance actuelle et de l'instancier à nullptr
     */
    static void libererInstance(); //DP singleton

    /*!
     * \brief getArchive
     * \return
     * permet de retourner un pointeur vers la seule instance de la classe archive liée à HistoNoteManager
     */
    Archive* getArchive(){return archives;}

    //RelationManager* getRelationManager(){return relationsMan;}
    /*!
     * \brief makeArticleId
     * \return
     * permet la creation automatique des IDs des Articles ("Article" + nombre)
     */
    const QString makeArticleId();

    /*!
     * \brief makeTacheId
     * \return
     * permet la creation automatique des IDs des Taches ("Tache" + nombre)
     */
    const QString makeTacheId();

    /*!
     * \brief makeMultiId
     * \return
     * permet la creation automatique des IDs des Multimedias ("Multimedia" + nombre)
     */
    const QString makeMultiId();

    /*!
     * \brief addHistoArticle
     * \param h
     * Methode permettant d'ajouter un objet h de type HistoArticle au tableau articles de HistoNoteManager
     */
    void addHistoArticle(HistoNotes<Article>* h);

    /*!
     * \brief addHistoArticle
     * \param id
     * \param titr
     * \param txt
     * Methode permettant de créer un objet de type HistoArticle à partir de 3 paramètres ( cas de la création dans le logiciel)
     */
    void addHistoArticle(QString id, QString titr, QString txt);

    /*!
     * \brief addHistoArticle
     * \param id
     * \param titr
     * \param txt
     * \param dateCrea
     * \param dateModif
     * Methode permettant de créer un objet de type HistoArticle à partir de 5 paramètres ( cas du chargement à partir du fichier XML)
     */
    void addHistoArticle(QString id, QString titr, QString txt, QDate dateCrea, QDate dateModif);

    /*!
     * \brief addHistoTache
     * \param h
     * Methode permettant d'ajouter un objet h de type HistoTache au tableau taches de HistoNoteManager
     */
    void addHistoTache(HistoNotes<Tache>* h);

    /*!
     * \brief addHistoTache
     * \param id
     * \param t
     * \param act
     * \param stat
     * \param d
     * \param prio
     * Methode permettant de créer un objet de type HistoTache à partir de 6 paramètres ( cas de la création dans le logiciel)
     */
    void addHistoTache(QString id, QString t, QString act, QString stat, QDate d, QString prio="");

    /*!
     * \brief addHistoTache
     * \param id
     * \param t
     * \param act
     * \param stat
     * \param d
     * \param prio
     * \param dateCrea
     * \param dateModif
     * Methode permettant de créer un objet de type HistoTache à partir de 8 paramètres ( cas du chargement à partir du fichier XML)
     */
    void addHistoTache(QString id, QString t, QString act, QString stat, QDate d, QString prio, QDate dateCrea, QDate dateModif);

    /*!
     * \brief addHistoMulti
     * \param h
     * Methode permettant d'ajouter un objet h de type HistoMulti au tableau multi de HistoNoteManager
     */
    void addHistoMulti(HistoNotes<Multimedia>* h);

    /*!
     * \brief addHistoMulti
     * \param id
     * \param t
     * \param desc
     * \param fich
     * \param typ
     * Methode permettant de créer un objet de type HistoMulti à partir de 5 paramètres ( cas de la création dans le logiciel)
     */
    void addHistoMulti(QString id, QString t, QString desc, QString fich, QString typ=""); //ajout 13/06

    /*!
     * \brief addHistoMulti
     * \param id
     * \param t
     * \param desc
     * \param fich
     * \param typ
     * \param dateCrea
     * \param dateModif
     * Methode permettant de créer un objet de type HistoMulti à partir de 7 paramètres ( cas du chargement à partir du fichier XML)
     */
    void addHistoMulti(QString id, QString t, QString desc, QString fich, QString typ, QDate dateCrea, QDate dateModif);

    /*!
     * \brief getHistoArticle
     * \param id
     * \return
     * Methode renvoyant un pointeur vers un HistoArticle à partir de son ID
     */
    HistoNotes<Article>* getHistoArticle(const QString &id);

    /*!
     * \brief getHistoTache
     * \param id
     * \return
     *  Methode renvoyant un pointeur vers un HistoTache à partir de son ID
     */
    HistoNotes<Tache>* getHistoTache(const QString &id);

    /*!
     * \brief getHistoMulti
     * \param id
     * \return
     *  Methode renvoyant un pointeur vers un HistoMulti à partir de son ID
     */
    HistoNotes<Multimedia>* getHistoMulti(const QString &id);
    
    /*!
     * \brief removeHistoArticle
     * \param h
     * Methode supprimant l'objet de type HistoArticle passé en paramètre
     */
    void removeHistoArticle(HistoNotes<Article>* h);

    /*!
     * \brief removeHistoTache
     * \param h
     * Methode supprimant l'objet de type HistoTache passé en paramètre
     */
    void removeHistoTache(HistoNotes<Tache>* h);

    /*!
     * \brief removeHistoMulti
     * \param h
     * Methode supprimant l'objet de type HistoMulti passé en paramètre
     */
    void removeHistoMulti(HistoNotes<Multimedia>* h);

    /*!
     * \brief archiver
     * \param ha
     * Methode permettant d'archiver l'objet ha de type HistoArticle passé en paramètre
     */
    void archiver(HistoNotes<Article>* ha);

    /*!
     * \brief archiver
     * \param ht
     * Methode permettant d'archiver l'objet ht de type HistoTache passé en paramètre
     */
    void archiver(HistoNotes<Tache>* ht);

    /*!
     * \brief archiver
     * \param hm
     * Methode permettant d'archiver l'objet hm de type HistoMulti passé en paramètre
     */
    void archiver(HistoNotes<Multimedia>* hm);

    /*!
     * \brief restaurer
     * \param ha
     * Methode permettant de restaurer l'objet ha de type HistoArticle passé en paramètre
     */
    void restaurer(HistoNotes<Article>* ha);

    /*!
     * \brief restaurer
     * \param ht
     * Methode permettant de restaurer l'objet ht de type HistoTache passé en paramètre
     */
    void restaurer(HistoNotes<Tache>* ht);

    /*!
     * \brief restaurer
     * \param ht
     * Methode permettant de restaurer l'objet ht de type HistoMulti passé en paramètre
     */
    void restaurer(HistoNotes<Multimedia>* ht);

    /*!
     * \brief getFilename
     * \return
     * retourne la valeur de l'attribut filename
     */
    QString getFilename() const { return filename; }

    /*!
     * \brief setFilename
     * \param f
     * modifie la valeur de l'attribut filename
     */
    void setFilename(const QString& f) { filename=f; }

    /*!
     * \brief save
     * Méthodes permettant de stocker dans un fichier XML tous les Historiques de toutes les notes actives
     */
    void save();

    /*!
     * \brief load
     * Méthodes permettant d'importer d'un fichier XML tous les Historiques de toutes les notes actives
     */
    void load();


    template <class X>
    /*!
     * \brief The iterator class
     * Classe permettant de parcourir tous les tableaux de pointeur de HistoNoteManager sans que la structure des données utilisée soit revelée
     * Pour cela nous avons surcharger plusieurs operateurs et créer des fonctions permettant d'accéder au début ou à la fin de la structure de donnée
     */
    class iterator{
        HistoNotes<X>** current;
        iterator(HistoNotes<X> **a):current(a){}

        friend class HistoNoteManager;

    public:
        /*!
         * \brief iterator
         */
        iterator():current(0){}

        /*!
         * \brief getCurrent
         * \return
         */
        HistoNotes<X>* getCurrent(){return *current;}

        /*!
         * \brief operator *
         * \return
         */
        HistoNotes<X>& operator*(){ //pour avoir contenu du double pointeur avec 1 seul *
            return **current;
        }

        /*!
         * \brief operator ++
         * \return
         */
        iterator<X> &operator++(){
            ++current;
            return *this;
        }

        /*!
         * \brief operator !=
         * \param it
         * \return
         */
        bool operator!=(iterator<X> it) const{
            return current != it.current;
        }
    };

    /*!
     * \brief begin_article
     * \return
     */
    iterator<Article> begin_article(){ //1ère case du tableau articles
        return iterator<Article>(articles);
    }

    /*!
     * \brief end_article
     * \return
     */
    iterator<Article> end_article(){ //case juste après dernière case du tableau article (condition boucle for : !=m.end)
        return iterator<Article>(articles + nbArticles);
    }

    /*!
     * \brief begin_tache
     * \return
     */
    iterator<Tache> begin_tache(){ //1ère case du tableau taches
        return iterator<Tache>(taches);
    }

    /*!
     * \brief end_tache
     * \return
     */
    iterator<Tache> end_tache(){ //case juste après dernière case du tableau tache (condition boucle for : !=m.end)
        return iterator<Tache>(taches + nbTaches);
    }

    /*!
     * \brief begin_multi
     * \return
     */
    iterator<Multimedia> begin_multi(){ //1ère case du tableau multimedias    add le 13/06
        return iterator<Multimedia>(multimedias);
    }

    /*!
     * \brief end_multi
     * \return
     */
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

    /*!
     * \brief addVersion
     * \param i
     * \param t
     * \param txt
     * Méthode permettant de créer un article à partir des 3 attributs passés en paramètre puis de l'ajouter à un histoArticle
     * (utilisation dans l'application)
     */
    void addVersion(QString i, QString t, QString txt); //article

    /*!
     * \brief addVersion
     * \param id
     * \param t
     * \param act
     * \param stat
     * \param d
     * \param prio
     * Méthode permettant de créer une tache à partir des 6 attributs passés en paramètre puis de l'ajouter à un histoTache
     * (utilisation dans l'application)
     */
    void addVersion(QString id, QString t, QString act, QString stat, QDate d, QString prio); //tache

    /*!
     * \brief addVersion
     * \param id
     * \param t
     * \param desc
     * \param fich
     * \param typ
     * Méthode permettant de créer un multimedia à partir des 5 attributs passés en paramètre puis de l'ajouter à un histoMulti
     * (utilisation dans l'application)
     */
    void addVersion(QString id, QString t, QString desc, QString fich, QString typ=""); //multimedias


    /*!
     * \brief addVersion
     * \param i
     * \param t
     * \param txt
     * \param dateCrea
     * \param dateModif
     * Méthode permettant de créer un article à partir des 5 attributs passés en paramètre puis de l'ajouter à un histoArticle
     * (utilisation pour charger depuis le XML)
     */
    void addVersion(QString i, QString t, QString txt, QDate dateCrea, QDate dateModif); //article

    /*!
     * \brief addVersion
     * \param id
     * \param t
     * \param act
     * \param stat
     * \param d
     * \param prio
     * \param dateCrea
     * \param dateModif
     * Méthode permettant de créer une tache à partir des 8 attributs passés en paramètre puis de l'ajouter à un histoTache
     * (utilisation pour charger depuis le XML)
     */
    void addVersion(QString id, QString t, QString act, QString stat, QDate d, QString prio, QDate dateCrea, QDate dateModif); //tache

    /*!
     * \brief addVersion
     * \param id
     * \param t
     * \param desc
     * \param fich
     * \param typ
     * \param dateCrea
     * \param dateModif
     * Méthode permettant de créer un multimedia à partir des 7 attributs passés en paramètre puis de l'ajouter à un histoMulti
     * (utilisation pour charger depuis le XML)
     */
    void addVersion(QString id, QString t, QString desc, QString fich, QString typ, QDate dateCrea, QDate dateModif); //multimedias



    /*!
     * \brief getFirstVersion
     * \return
     * Methode renvoyant la première version d'une Note
     */
    X* getFirstVersion(){return versions[0];}

    /*!
     * \brief getVersion
     * \param n
     * \return
     * Methode renvoyant la n°eme version d'une Note
     */
    X* getVersion(int n){return versions[n];}

    /*!
     * \brief getLastVersion
     * \return
     * Methode renvoyant la dernière version d'une Note
     */
    X* getLastVersion() {return versions[nbVersions-1];}

    /*!
     * \brief getId
     * \return
     */
    const QString& getId(){ return versions[0]->getId(); }    //accesseurs communs aux notes

    /*!
     * \brief getNbVersions
     * \return
     */
    unsigned int getNbVersions() { return nbVersions; }

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
