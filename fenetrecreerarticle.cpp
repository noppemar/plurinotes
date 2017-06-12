#ifndef FENETRECREERARTICLE_CPP
#define FENETRECREERARTICLE_CPP

#include "FenetreCreerArticle.h"
#include <QDateTime>


FenetreCreerArticle::FenetreCreerArticle() : QWidget()
{
    id = new QLineEdit(this);
    titre= new QLineEdit(this);
    texte = new QLineEdit(this);

    QFormLayout *formulaire = new QFormLayout;          // on crée un layout formulaire pour remplir les champs
    formulaire->addRow("id ", id);
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
   HistoNoteManager::getInstance().addHistoArticle(id->text(), titre->text(), texte->text());
    this->close();
}

#endif // FENETRECREERARTICLE_CPP
