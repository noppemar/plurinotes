#ifndef FENETRECREERMULTI_CPP
#define FENETRECREERMULTI_CPP

#include "fenprincipale.h"
#include "fenetrecreermulti.h"
#include <QDateTime>


FenetreCreerMulti::FenetreCreerMulti(FenetrePrincipale *p ) : pere(p)
{
    titre= new QLineEdit(this);
    description = new QLineEdit(this);
    fichier = new QLineEdit(this);
    type = new QComboBox(this);

    type->addItem("Image");             //liste deroulante
    type->addItem("Video");
    type->addItem("Audio");



    QFormLayout *formulaire = new QFormLayout;          // on crée un layout formulaire pour remplir les champs
    formulaire->addRow("titre", titre);
    formulaire->addRow("description", description);
    formulaire->addRow("fichier", fichier);
    formulaire->addRow("type", type);
    ok = new QPushButton("Valider", this);                                       // creation du bouton valider


   connect(ok, SIGNAL(clicked()), this, SLOT(ajouterMulti())  );


   QVBoxLayout *mainLayout = new QVBoxLayout;         // le layout principal permet d'avoir le formulaire ET les différents boutons
       mainLayout->addLayout(formulaire);
       mainLayout->addWidget(ok);


   this->setLayout(mainLayout);
}


void FenetreCreerMulti::ajouterMulti() {   //add 13/06
   HistoNoteManager& m = HistoNoteManager::getInstance();
   m.addHistoMulti(m.makeMultiId(), titre->text(), description->text(), fichier->text(), type->currentText());
  // pere->updateNotes();
   this->close();
}

#endif // FENETRECREERMULTIE_CPP


