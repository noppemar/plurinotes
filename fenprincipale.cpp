#include "FenPrincipale.h"
#include "FenetreCreerArticle.h"
#include "FenetreCreerTache.h"



FenetrePrincipale::FenetrePrincipale()
{
    QMdiArea *zoneCentrale = new QMdiArea;

    QMenu *menuFichier = menuBar()->addMenu("&Fichier");                          // creation du menu fichier

        QMenu *actionNouvelleNote = menuFichier->addMenu("Nouvelle Note");       //creation  sous menu permettant de creer une nouvelle note :

            QAction *actionNouvelleTache = new QAction("Nouvelle Tache", this);    //  tache
                actionNouvelleNote->addAction(actionNouvelleTache);
                connect(actionNouvelleTache, SIGNAL(triggered()), this, SLOT(afficherCreerTache()));

            QAction *actionNouvelArticle = new QAction("Nouvel Article", this);    //  Article
                 actionNouvelleNote->addAction(actionNouvelArticle);
                 connect(actionNouvelArticle, SIGNAL(triggered()), this, SLOT(afficherCreerArticle()));


         QMenu *actionEditerNote = menuFichier->addMenu("Editer Note");       //creation  sous menu permettant d'éditer une note:

             QAction *actionEditerTache = new QAction("Editer Tache", this);    //  tache
                  actionEditerNote->addAction(actionEditerTache);
                  connect(actionEditerTache, SIGNAL(triggered()), this, SLOT(afficherEditerTache()));

             QAction *actionEditerArticle = new QAction("Editer Article", this);    //  Article
                  actionEditerNote->addAction(actionEditerArticle);
                  connect(actionEditerArticle, SIGNAL(triggered()), this, SLOT(afficherEditerArticle()));

         QAction *actionQuitter = new QAction("&Quitter", this);
             menuFichier->addAction(actionQuitter);
             connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));


    setCentralWidget(zoneCentrale);
}


void FenetrePrincipale::afficherCreerTache() {
    FenetreCreerTache *fenetreCreerTache = new FenetreCreerTache(this);
    setCentralWidget(fenetreCreerTache);
}

void FenetrePrincipale::afficherCreerArticle() {
    FenetreCreerArticle *fenetreCreerArticle = new FenetreCreerArticle(this);
    setCentralWidget(fenetreCreerArticle);
}


void FenetrePrincipale::afficherEditerTache() {

}

void FenetrePrincipale::afficherEditerArticle() {

}
