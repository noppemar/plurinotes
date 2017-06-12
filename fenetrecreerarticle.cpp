#ifndef FENETRECREERARTICLE_CPP
#define FENETRECREERARTICLE_CPP

#include "FenetreCreerArticle.h"
#include <QDateTime>


FenetreCreerArticle::FenetreCreerArticle() : QWidget()
{
    QLineEdit *id = new QLineEdit;
    QLineEdit *titre = new QLineEdit;
    QLineEdit *texte = new QLineEdit;

    QFormLayout *formulaire = new QFormLayout;          // on crée un layout formulaire pour remplir les champs
    formulaire->addRow("id ", id);
    formulaire->addRow("titre", titre);
    formulaire->addRow("texte", texte);

   QPushButton *ok = new QPushButton("Valider");                                       // creation du bouton valider
   connect(ok, SIGNAL(clicked()), this, SLOT(ajouterArticle(id->text(), titre->text(), texte->text())));

    QVBoxLayout *mainLayout = new QVBoxLayout;         // le layout principal permet d'avoir le formulaire ET les différents boutons
        mainLayout->addLayout(formulaire);
        mainLayout->addWidget(ok);


    this->setLayout(mainLayout);
}


void FenetreCreerArticle::ajouterArticle(QString id, QString titre, QString texte) {
    HistoNoteManager::getInstance().addHistoArticle(id, titre, texte );
}

#endif // FENETRECREERARTICLE_CPP
