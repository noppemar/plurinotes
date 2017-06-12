#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <QtWidgets>

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
    public:
        FenetrePrincipale();
        QMdiArea *zoneCentrale;
        QDockWidget *ensembleNotes;
        QDockWidget *histoNote;
        QTextEdit *exemple1;
        QTextEdit *exemple2;

    public slots:
        void afficherCreerArticle();
        void afficherCreerTache();

        void afficherEditerArticle();
        void afficherEditerTache();

    private:


};

#endif
