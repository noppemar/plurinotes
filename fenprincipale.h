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
        
    public slots:
        void afficherCreerArticle();
        void afficherCreerTache();
        void afficherCreerMulti();   // add 13/06
        void afficherCreerRelation();

        void afficherArticle();
        void afficherTache();
        void afficherMulti();
        void afficherArchive();

    private:

        QMdiArea *zoneCentrale;
        
        QListWidget *listeArticle;
        QListWidget *listeMulti;
        QListWidget *listeTaches;
        QListWidget *listeArchives;
        
        QDockWidget *histoNote;
        
        QList<QString> articles_id;
        QList<QString> multi_id;
        QList<QString> taches_id;
        QList<QString> archives_id;

};



#endif //FENPRINCIPALE_H
