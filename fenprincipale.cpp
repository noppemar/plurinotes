#include "FenPrincipale.h"
#include "FenetreCreerArticle.h"
#include "FenetreCreerTache.h"
#include "FenetreCreermulti.h"
#include "FenetreCreerRelation.h"
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

    QAction *actionNouvelMulti = new QAction("Nouveau Multimedia", this);    //  Multimedia  add 13/06
    actionNouvelleNote->addAction(actionNouvelMulti);
    connect(actionNouvelMulti, SIGNAL(triggered()), this, SLOT(afficherCreerMulti()));

    QMenu *actionNewRelation = menuFichier->addMenu("Nouvelle Relation");
    QAction *actionNouvelleRelation = new QAction("Nouvelle Relation", this);
    actionNewRelation->addAction(actionNouvelleRelation);
    connect(actionNouvelleRelation, SIGNAL(triggered()), this, SLOT(afficherCreerRelation()));


    QAction *actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionQuitter);
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    QDockWidget *ensembleNotes  = new QDockWidget("Voici toutes les notes");
    ensembleNotes->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    listeArticle = new QListWidget(ensembleNotes);

    listeTaches = new QListWidget(ensembleNotes);

    listeMulti = new QListWidget(ensembleNotes);

    listeArchives = new QListWidget(ensembleNotes);

    QWidget *ensNotes = new QWidget;
    QLabel *labelN = new QLabel("Articles :");
    QLabel *labelM = new QLabel("Multimedia :");
    QLabel *labelT = new QLabel("Taches :");
    QLabel *labelA = new QLabel("Archives :");
    QVBoxLayout *ensembleNotesLayout = new QVBoxLayout;
    ensembleNotesLayout->addWidget(labelN);
    ensembleNotesLayout->addWidget(listeArticle);
    ensembleNotesLayout->addWidget(labelM);
    ensembleNotesLayout->addWidget(listeMulti);
    ensembleNotesLayout->addWidget(labelT);
    ensembleNotesLayout->addWidget(listeTaches);
    ensembleNotesLayout->addWidget(labelA);
    ensembleNotesLayout->addWidget(listeArchives);

    ensNotes->setLayout(ensembleNotesLayout);
    ensembleNotes->setWidget(ensNotes);


    QObject::connect(listeArticle, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(afficherArticle()));
    QObject::connect(listeMulti, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(afficherMulti()));
    QObject::connect(listeTaches, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(afficherTache()));
    QObject::connect(listeArchives, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(afficherArchive()));




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

void FenetrePrincipale::afficherCreerMulti() {
    FenetreCreerMulti *fenetreCreerMulti = new FenetreCreerMulti(this);
    fenetreCreerMulti->show();
}

void FenetrePrincipale::afficherCreerRelation() {
    FenetreCreerRelation *fenetreCreerRelation = new FenetreCreerRelation(this);
    fenetreCreerRelation->show();
}


void FenetrePrincipale::afficherArticle(){
    HistoNoteManager& m=HistoNoteManager::getInstance();
    int indice = listeArticle->currentRow();
    HistoNotes<Article>* h=m.getHistoArticle(articles_id[indice]);


    ArticleEditeur *fenetre= new ArticleEditeur(*(h->getLastVersion()),this);
    this->setCentralWidget(fenetre);
    fenetre->show();
};

void FenetrePrincipale::afficherTache(){
    HistoNoteManager& m=HistoNoteManager::getInstance();
    int indice = listeTaches->currentRow();
    HistoNotes<Tache>* h=m.getHistoTache(taches_id[indice]);


    TacheEditeur *fenetre= new TacheEditeur(*(h->getLastVersion()),this);
    this->setCentralWidget(fenetre);
    fenetre->show();
};

void FenetrePrincipale::afficherMulti(){
    HistoNoteManager& m=HistoNoteManager::getInstance();
    int indice = listeMulti->currentRow();
    HistoNotes<Multimedia>* h=m.getHistoMulti(multi_id[indice]);


    MultiEditeur *fenetre= new MultiEditeur(*(h->getLastVersion()),this);
    this->setCentralWidget(fenetre);
    fenetre->show();

};

void FenetrePrincipale::afficherArchive(){

}

void FenetrePrincipale::updateArticles() {
    listeArticle->clear();
    articles_id.clear();
    HistoNoteManager& m=HistoNoteManager::getInstance();
    for(HistoNoteManager::iterator<Article> it=m.begin_article(); it!=m.end_article();++it){
        listeArticle->addItem(it.getCurrent()->getLastVersion()->getTitre());
        articles_id.append(it.getCurrent()->getId());
    }

}

void FenetrePrincipale::updateMulti(){
    listeMulti->clear();
    multi_id.clear();
    HistoNoteManager& m=HistoNoteManager::getInstance();
    for(HistoNoteManager::iterator<Multimedia> it=m.begin_multi(); it!=m.end_multi();++it){
        listeMulti->addItem(it.getCurrent()->getLastVersion()->getTitre());
        multi_id.append(it.getCurrent()->getId());
    }
}

void FenetrePrincipale::updateTaches(){
    listeTaches->clear();
    taches_id.clear();
    HistoNoteManager& m=HistoNoteManager::getInstance();
    for(HistoNoteManager::iterator<Tache> it=m.begin_tache(); it!=m.end_tache();++it){
        listeTaches->addItem(it.getCurrent()->getLastVersion()->getTitre());
        taches_id.append(it.getCurrent()->getId());
    }
}

void FenetrePrincipale::updateArchives(){

}
