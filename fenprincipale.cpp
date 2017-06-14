#include "FenPrincipale.h"
#include "FenetreCreerArticle.h"
#include "FenetreCreerTache.h"

#include "noteediteur.h"



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



             QAction *actionQuitter = new QAction("&Quitter", this);
             menuFichier->addAction(actionQuitter);
             connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));


             QDockWidget *ensembleNotes  = new QDockWidget("Voici toutes les notes");
             ensembleNotes->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

             listeNotes = new QListWidget(ensembleNotes);

             listeTaches = new QListWidget(ensembleNotes);

             listeArchives = new QListWidget(ensembleNotes);

             QWidget *ensNotes = new QWidget;
             QLabel *labelN = new QLabel("Notes :");
             QLabel *labelT = new QLabel("Taches :");
             QLabel *labelA = new QLabel("Taches :");
             QVBoxLayout *ensembleNotesLayout = new QVBoxLayout;
             ensembleNotesLayout->addWidget(labelN);
             ensembleNotesLayout->addWidget(listeNotes);
             ensembleNotesLayout->addWidget(labelT);
             ensembleNotesLayout->addWidget(listeTaches);

             ensNotes->setLayout(ensembleNotesLayout);
             ensembleNotes->setWidget(ensNotes);


             QObject::connect(listeNotes, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(afficherArticle()));



             addDockWidget(Qt::LeftDockWidgetArea, ensembleNotes);



             histoNote = new QDockWidget("Voici toutes les versions de cette note");
             histoNote->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
             addDockWidget(Qt::RightDockWidgetArea, histoNote);



    setCentralWidget(zoneCentrale);
}


void FenetrePrincipale::afficherCreerTache() {
    FenetreCreerTache *fenetreCreerTache = new FenetreCreerTache(this);
    fenetreCreerTache->show();
}

void FenetrePrincipale::afficherCreerArticle() {
    FenetreCreerArticle *fenetreCreerArticle = new FenetreCreerArticle(this);
    fenetreCreerArticle->show();
}


void FenetrePrincipale::afficherArticle(){
    /*FenetreCreerTache *fenetreCreerTache = new FenetreCreerTache(this);
    this->setCentralWidget(fenetreCreerTache);
    fenetreCreerTache->show();*/

    HistoNoteManager& m=HistoNoteManager::getInstance();
    int indice = listeNotes->currentRow();
    HistoNotes<Article>* h=m.getHistoArticle(notes_id[indice]);


    ArticleEditeur *fenetre= new ArticleEditeur(*(h->getLastVersion()),this);
    this->setCentralWidget(fenetre);
    fenetre->show();




};
void FenetrePrincipale::afficherTache(){

};



void FenetrePrincipale::updateNotes() {
    listeNotes->clear();
    HistoNoteManager& m=HistoNoteManager::getInstance();
    for(HistoNoteManager::iterator<Article> it=m.begin_article(); it!=m.end_article();++it){
        listeNotes->addItem(it.getCurrent()->getLastVersion()->getTitre());
        notes_id.append(it.getCurrent()->getId());
    }
    /* Pr multi
    for(HistoNoteManager::iterator<Multimedia> it=m.begin_multi(); it!=m.end_multi();++it){
        listeNotes->addItem(it.getCurrent()->getLastVersion()->getTitre());
        tab_id.append(it.getCurrent()->getId());
    }
      */
}

void FenetrePrincipale::updateTaches(){
    listeTaches->clear();
    HistoNoteManager& m=HistoNoteManager::getInstance();
    for(HistoNoteManager::iterator<Tache> it=m.begin_tache(); it!=m.end_tache();++it){
        listeTaches->addItem(it.getCurrent()->getLastVersion()->getTitre());
        taches_id.append(it.getCurrent()->getId());
    }
};

