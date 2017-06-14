#ifndef FENETRECREERTACHE_CPP
#define FENETRECREERTACHE_CPP

#include "FenetreCreerTache.h"
#include <QDateTime>


FenetreCreerTache::FenetreCreerTache(FenetrePrincipale *p ) : pere(p)
{
    //id = new QLineEdit(this);
    titre = new QLineEdit(this);
    action = new QLineEdit(this);
    priorite = new QComboBox(this);
    dateEcheance = new QDateTimeEdit(this);
    statut = new QComboBox(this);

    priorite->addItem("ça ne presse pas");             //liste deroulante
    priorite->addItem("à faire");
    priorite->addItem("à faire en prio absolue");

    statut->addItem("enAttente");                       //liste deroulante
    statut->addItem("enCours");
    statut->addItem("terminee");


    QFormLayout *formulaire = new QFormLayout;          // on crée un layout formulaire pour remplir les champs
   // formulaire->addRow("id ", id);
    formulaire->addRow("titre", titre);
    formulaire->addRow("action", action);
    formulaire->addRow("priorite", priorite);
    formulaire->addRow("dateEcheance", dateEcheance);
    formulaire->addRow("statut", statut);


   ok = new QPushButton("Valider", this);                                       // creation du bouton valider

   connect(ok, SIGNAL(clicked()), this, SLOT(ajouterTache()));

    QVBoxLayout *mainLayout = new QVBoxLayout;         // le layout principal permet d'avoir le formulaire ET les différents boutons
        mainLayout->addLayout(formulaire);
        mainLayout->addWidget(ok);


    this->setLayout(mainLayout);
}


void FenetreCreerTache::ajouterTache() {
    HistoNoteManager& m = HistoNoteManager::getInstance();
    m.addHistoTache(m.makeTacheId(), titre->text(), action->text(), priorite->currentText(), dateEcheance->date(),statut->currentText());
    pere->updateTaches();
    HistoNoteManager::getInstance().save();
    this->close();

}


#endif // FENETRECREERTACHE_CPP
