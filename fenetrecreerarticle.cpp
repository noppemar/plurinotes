#ifndef FENETRECREERARTICLE_CPP
#define FENETRECREERARTICLE_CPP

#include "FenetreCreerArticle.h"
#include <QDateTime>


FenetreCreerArticle::FenetreCreerArticle(QWidget *parent = 0) : QWidget()
{
    QLineEdit *id = new QLineEdit;
    QLineEdit *titre = new QLineEdit;
    QLineEdit *texte = new QLineEdit;

    QFormLayout *formulaire = new QFormLayout;          // on crée un layout formulaire pour remplir les champs
    formulaire->addRow("id ", id);
    formulaire->addRow("titre", titre);
    formulaire->addRow("texte", texte);

   QPushButton *ok = new QPushButton("Valider");                                       // creation du bouton valider
   connect(ok, SIGNAL(clicked()), this, SLOT(ajouterArticle()));

    QVBoxLayout *mainLayout = new QVBoxLayout;         // le layout principal permet d'avoir le formulaire ET les différents boutons
        mainLayout->addLayout(formulaire);
        mainLayout->addWidget(ok);


    this->setLayout(mainLayout);
}


void FenetreCreerArticle::ajouterArticle() {

    QTextStream cin(stdin);
    QTextStream cout(stdout);
    Article art(id->text(), titre->text(),texte->text());
    cout << art.getText() <<endl;
}


#endif // FENETRECREERARTICLE_CPP
