#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QtWidgets>

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
    public:
        FenetrePrincipale();
        void updateArticles();
        void updateMulti();
        void updateTaches();
        void updateArchives();
        void updateRelation();
        
    public slots:
        void afficherCreerArticle();
        void afficherCreerTache();
        void afficherCreerMulti();   // add 13/06
        void afficherCreerRelation();

        void afficherArticle();
        void afficherTache();
        void afficherMulti();
        void afficherArchive();
        //void afficherRelation();

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
