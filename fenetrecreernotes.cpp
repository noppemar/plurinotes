#include "FenetreCreerNotes.h"
#include "FenetreCreerArticle.h"
#include <QtWidgets>

FenetreCreerNotes::FenetreCreerNotes() : QWidget()
{

    Tache = new QPushButton("Nouvelle Tache", this);
    Tache->setToolTip("Permet de creer une nouvelle tache");
    QObject::connect(Tache, SIGNAL(clicked()), this, SLOT(afficherCreerTache()));

    Article = new QPushButton("Nouvel Article", this);
    Article->setToolTip("Permet de creer un nouvel Article");
    QObject::connect(Article, SIGNAL(clicked()), this, SLOT(afficherCreerArticle()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(Tache,10,0,4,2);
    layout->addWidget(Article,10,10,4,2);

    this->setLayout(layout);
}


void FenetreCreerNotes::afficherCreerArticle() {
    FenetreCreerArticle *fenetre = new FenetreCreerArticle(this);
    fenetre->show();
}
