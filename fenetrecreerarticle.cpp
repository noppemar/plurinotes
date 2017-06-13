#ifndef FENETRECREERARTICLE_CPP
#define FENETRECREERARTICLE_CPP

#include "fenprincipale.h"
#include "FenetreCreerArticle.h"
#include <QDateTime>



FenetreCreerArticle::FenetreCreerArticle(FenetrePrincipale *p ) : pere(p)
{
    titre= new QLineEdit(this);
    texte = new QLineEdit(this);

    QFormLayout *formulaire = new QFormLayout;          // on crée un layout formulaire pour remplir les champs
    formulaire->addRow("titre", titre);
    formulaire->addRow("texte", texte);

    ok = new QPushButton("Valider", this);                                       // creation du bouton valider


   connect(ok, SIGNAL(clicked()), this, SLOT(ajouterArticle())  );

    QVBoxLayout *mainLayout = new QVBoxLayout;         // le layout principal permet d'avoir le formulaire ET les différents boutons
        mainLayout->addLayout(formulaire);
        mainLayout->addWidget(ok);


    this->setLayout(mainLayout);
}


void FenetreCreerArticle::ajouterArticle() {
   HistoNoteManager& m = HistoNoteManager::getInstance();
   m.addHistoArticle(m.makeArticleId(), titre->text(), texte->text());
   pere->clear();
   pere->updateNotes();
   this->close();
}

#endif // FENETRECREERARTICLE_CPP
