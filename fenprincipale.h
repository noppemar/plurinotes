#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <QtWidgets>

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
    public:
        FenetrePrincipale();
        void updateNotes();
        void clear();
        
    public slots:
        void afficherCreerArticle();
        void afficherCreerTache();

        void afficherEditerArticle();
        void afficherEditerTache();

    private:

        QMdiArea *zoneCentrale;
        QListWidget *listeNotes;
        QDockWidget *histoNote;
        QList<QString> tab_id;
};



#endif
