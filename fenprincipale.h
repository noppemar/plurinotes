#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QtWidgets>

/*!
 * \brief The FenetrePrincipale class
 */
class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
    public:
        /*!
         * \brief FenetrePrincipale
         */
        FenetrePrincipale();
        /*!
         * \brief updateArticles
         * gere affichage liste article
         */
        void updateArticles();
        /*!
         * \brief updateMulti
         * gere affichage liste multi
         */
        void updateMulti();
        /*!
         * \brief updateTache
         * gere affichage liste tache
         */
        void updateTaches();
        /*!
         * \brief updateArchives
         * gere affichage liste archive
         */
        void updateArchives();
        /*!
         * \brief updateRelation
         * gere affichage liste relation
         */
        void updateRelation();
        
    public slots:
        /*!
         * \brief afficherCreerArticle
         * ouvre fenetre pour creer un article
         */
        void afficherCreerArticle();
        /*!
         * \brief afficherCreerTache
         * ouvre fenetre pour creer un tache
         */
        void afficherCreerTache();
        /*!
         * \brief afficherCreerMulti
         * ouvre fenetre pour creer un multimedia
         */
        void afficherCreerMulti();
        /*!
         * \brief afficherCreerRelation
         * ouvre fenetre pour creer une relation
         */
        void afficherCreerRelation();

        /*!
         * \brief afficherArticle
         * affiche article selectionné au milieu
         */
        void afficherArticle();
        /*!
         * \brief afficherTache
         * affiche tache selectionné au milieu
         */
        void afficherTache();
        /*!
         * \brief afficherMulti
         * affiche multimedia selectionné au milieu
         */
        void afficherMulti();
        /*!
         * \brief afficherArchive
         * affiche archive selectionné au milieu
         */
        void afficherArchive();


    private:

        QMdiArea *zoneCentrale;
        
        QListWidget *listeArticle;
        QListWidget *listeMulti;
        QListWidget *listeTaches;
        QListWidget *listeArchives;
        QListWidget *listeRelations;
        
        QDockWidget *histoNote;
        
        QList<QString> articles_id;
        QList<QString> multi_id;
        QList<QString> taches_id;
        QList<QString> archives_id;
        QList<QString> relations_id;

};



#endif //FENPRINCIPALE_H
