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


             ensembleNotes = new QDockWidget("Voici toutes les notes");
             exemple1 = new QTextEdit(ensembleNotes);
             ensembleNotes->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
             addDockWidget(Qt::LeftDockWidgetArea, ensembleNotes);
    
         /* Marche pas pour l'instant
     QWidget *dockContenu = new QWidget;
     ensembleNotes->setWidget(dockContenu);
     QVBoxLayout *dockLayout= new QVBoxLayout;
     FenVisuAll *allArticle= new FenVisuAll;
     allArticle->show();

     dockLayout->addWidget(allArticle);
     dockContenu->setLayout(dockLayout); */

             histoNote = new QDockWidget("Voici toutes les versions de cette note");
             exemple2 = new QTextEdit(histoNote);
             histoNote->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
             addDockWidget(Qt::RightDockWidgetArea, histoNote);
    
    //add Menu Afficher mais jutse en attendant de pouvoir le faire direct
    QMenu *menuVisu = menuBar()->addMenu("&Afficher");
    QAction *actionAfficherTousArticles=new QAction("&Article",this);
    menuVisu->addAction(actionAfficherTousArticles);
    connect(actionAfficherTousArticles, SIGNAL(triggered()), this, SLOT(ouvrir_visu()));



    setCentralWidget(zoneCentrale);
}


void FenetrePrincipale::afficherCreerTache() {
    FenetreCreerTache *fenetreCreerTache = new FenetreCreerTache();
    fenetreCreerTache->show();
}

void FenetrePrincipale::afficherCreerArticle() {
    FenetreCreerArticle *fenetreCreerArticle = new FenetreCreerArticle();
    fenetreCreerArticle->show();
}


void FenetrePrincipale::afficherEditerTache() {

}

void FenetrePrincipale::afficherEditerArticle() {

}

void FenetrePrincipale::ouvrir_visu(){
   FenVisuAll *visuArticle = new FenVisuAll();
   visuArticle->show();
}
