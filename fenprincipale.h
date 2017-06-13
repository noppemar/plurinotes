#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <QtWidgets>

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
    public:
        FenetrePrincipale();
        void updateNotes();
        void updateTaches();
        
    public slots:
        void afficherCreerArticle();
        void afficherCreerTache();
        void afficherCreerMulti();   // add 13/06

        void afficherEditerArticle();
        void afficherEditerTache();
        void afficherEditerMulti(); // add 13/06

    private:

        QMdiArea *zoneCentrale;
        QListWidget *listeNotes;
        QListWidget *listeTaches;
        QListWidget *archives;
        QDockWidget *histoNote;
        
        QList<QString> notes_id;
        QList<QString> taches_id;
};



#endif
