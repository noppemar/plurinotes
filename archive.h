#ifndef ARCHIVE_H
#define ARCHIVE_H

#include "histonotes.h"

template <class X> class HistoNotes;

/*!
 * \brief The Archive class
 * Gère les archives
 */
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


public:
    /*!
     * \brief Constructeur archive
     */
    Archive();


    ~Archive();


    /*!
     * \brief addHistoArticle
     * \param h pointeur sur HistoNotes<Article>
     * ajout d'un HistoAarticle dans articles
     */

    void addHistoArticle(HistoNotes<Article>* h);

    /*!
     * \brief addHistoArticle
     * \param id
     * \param titr
     * \param txt
     * \param dateCrea
     * \param dateModif
     * ajout et creation d'un HistoAarticle dans articles (pour load())
     */
    void addHistoArticle(QString id, QString titr, QString txt, QDate dateCrea, QDate dateModif);

    /*!
     * \brief addHistoTache
     * \param h pointeur sur HistoNotes<Tache>
     * ajout d'un HistoTache dans taches
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
     * \param dateCrea
     * \param dateModif
     * ajout et creation d'un HistoTache dans taches (pour load())
     */

    void addHistoTache(QString id, QString t, QString act, QString stat, QDate d, QString prio, QDate dateCrea, QDate dateModif);

    /*!
     * \brief addHistoMulti
     * \param h pointeur sur HistoNotes<Multimedia>
     * ajout d'un HistoMulti dans multimedia
     */

    void addHistoMulti(HistoNotes<Multimedia>* h);
    /*!
     * \brief addHistoMulti
     * \param id
     * \param t
     * \param desc
     * \param fich
     * \param typ
     * \param dateCrea
     * \param dateModif
     * ajout et creation d'un HistoMulti dans multimedia (pour load())
     */
    void addHistoMulti(QString id, QString t, QString desc, QString fich, QString typ, QDate dateCrea, QDate dateModif);

    /*!
     * \brief getHistoArticle
     * \param id
     * \return renvoie pointeur Histonotes<Article> qui correspond a id ou nullptr
     */



    HistoNotes<Article>* getHistoArticle(const QString &id);

    /*!
     * \brief getHistoTache
     * \param id
     * \return renvoie pointeur Histonotes<Tache> qui correspond a id ou nullptr
     */
    HistoNotes<Tache>* getHistoTache(const QString &id);

    /*!
     * \brief getHistoMulti
     * \param id
     * \return renvoie pointeur Histonotes<Multi> qui correspond a id ou nullptr
     */
    HistoNotes<Multimedia>* getHistoMulti(const QString &id);

    /*!
     * \brief removeHistoArticle
     * \param h pointeur sur HistoNotes<Article>
     * supprime le pointeur sur l'histo et update le reste du tableau articles
     * utile pour archiver et restaurer
     */
    void removeHistoArticle(HistoNotes<Article>* h);

    /*!
     * \brief removeHistoTache
     * \param h pointeur sur HistoNotes<Tache>
     * supprime le pointeur sur l'histo et update le reste du tableau taches
     * utile pour archiver et restaurer
     */
    void removeHistoTache(HistoNotes<Tache>* h);

    /*!
     * \brief removeHistoMulti
     * \param h pointeur sur HistoNotes<Multimedia>
     * supprime le pointeur sur l'histo et update le reste du tableau multimedias
     * utile pour archiver et restaurer
     */
    void removeHistoMulti(HistoNotes<Multimedia>* h);

    /*!
     * \brief setFilename
     * \param f
     * accesseur en écriture
     */
    void setFilename(const QString& f) { fileArchive=f; }

    /*!
     * \brief saveArchive
     * enregistre toute la partie archive dans fichier archive.xml
     */
    void saveArchive();
    /*!
     * \brief loadArchive
     * charge toute la partie archive du fichier archive.xml
     */
    void loadArchive();


    template <class X>
    /*!
     * \brief The iterator class
     * template class
     */
    class iterator{
        HistoNotes<X>** current;
        iterator(HistoNotes<X> **a):current(a){}

        friend class Archive;

    public:
        /*!
         * \brief iterator
         */
        iterator():current(0){}
        /*!
         * \brief getCurrent
         * \return pointeur sur HistoNotes<X>
         */
        HistoNotes<X>* getCurrent(){return *current;}
        /*!
         * \brief operator *
         * \return reference sur HistoNotes<X>
         */
        HistoNotes<X>& operator*(){ //pour avoir contenu du double pointeur avec 1 seul *
            return **current;
        }
        /*!
         * \brief operator ++
         * \return iterator<X>
         */
        iterator<X> &operator++(){
            ++current;
            return *this;
        }
        /*!
         * \brief operator !=
         * \param it
         * \return bool
         */

        bool operator!=(iterator<X> it) const{
            return current != it.current;
        }
    };

    /*!
     * \brief begin_article
     * \return iterator<Article> sur premiere case tableau articles
     */
    iterator<Article> begin_article(){ //1ère case du tableau articles
        return iterator<Article>(articles);
    }
    /*!
     * \brief end_article
     * \return iterator<Article> sur derniere case tableau articles
     */
    iterator<Article> end_article(){ //case juste après dernière case du tableau article (condition boucle for : !=m.end)
        return iterator<Article>(articles + nbArticles);
    }

    /*!
     * \brief begin_tache
     * \return iterator<Tache> sur premiere case tableau taches
     */
    iterator<Tache> begin_tache(){ //1ère case du tableau taches
        return iterator<Tache>(taches);
    }
    /*!
     * \brief end_tache
     * \return iterator<Tache> sur derniere case tableau taches
     */
    iterator<Tache> end_tache(){ //case juste après dernière case du tableau tache (condition boucle for : !=m.end)
        return iterator<Tache>(taches + nbTaches);
    }

    /*!
     * \brief begin_multi
     * \return iterator<Multimedia> sur premiere case tableau multimedias
     */
    iterator<Multimedia> begin_multi(){ //1ère case du tableau multimedias    add le 13/06
        return iterator<Multimedia>(multimedias);
    }
    /*!
     * \brief end_multi
     * \return iterator<Multimedia> sur derniere case tableau multimedias
     */
    iterator<Multimedia> end_multi(){ //case juste après dernière case du tableau multimedias (condition boucle for : !=m.end)  add le 13/06
        return iterator<Multimedia>(multimedias + nbMultimedias);
    }

};

#endif // ARCHIVE_H
