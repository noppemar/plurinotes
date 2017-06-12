#ifndef FENETRECREERTACHE_CPP
#define FENETRECREERTACHE_CPP

#include "FenetreCreerTache.h"
#include <QDateTime>


FenetreCreerTache::FenetreCreerTache() : QWidget()
{
    QLineEdit *id = new QLineEdit;
    QLineEdit *titre = new QLineEdit;
    QLineEdit *action = new QLineEdit;
    QComboBox *priorite = new QComboBox;
    QDateTimeEdit *dateEcheance = new QDateTimeEdit;
    QComboBox *statut = new QComboBox;

    priorite->addItem("ça ne presse pas");             //liste deroulante
    priorite->addItem("à faire");
    priorite->addItem("à faire en prio absolue");

    statut->addItem("enAttente");                       //liste deroulante
    statut->addItem("enCours");
    statut->addItem("terminee");


    QFormLayout *formulaire = new QFormLayout;          // on crée un layout formulaire pour remplir les champs
    formulaire->addRow("id ", id);
    formulaire->addRow("titre", titre);
    formulaire->addRow("action", action);
    formulaire->addRow("priorite", priorite);
    formulaire->addRow("dateEcheance", dateEcheance);
    formulaire->addRow("statut", statut);


   QPushButton *ok = new QPushButton("Valider");                                       // creation du bouton valider

   connect(ok, SIGNAL(clicked()), this, SLOT(ajouterTache()));

    QVBoxLayout *mainLayout = new QVBoxLayout;         // le layout principal permet d'avoir le formulaire ET les différents boutons
        mainLayout->addLayout(formulaire);
        mainLayout->addWidget(ok);


    this->setLayout(mainLayout);
}


void FenetreCreerTache::ajouterTache() {


}


#endif // FENETRECREERTACHE_CPP
