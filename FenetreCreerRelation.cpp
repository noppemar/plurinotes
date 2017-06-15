#include "fenprincipale.h"
#include "fenetrecreerrelation.h"
#include "relation.h"
#include "histonotes.h"
#include <QDateTime>

FenetreCreerRelation::FenetreCreerRelation(FenetrePrincipale *p ) : pere(p)
{
    //id = new QLineEdit(this);
    titre = new QLineEdit(this);
    description= new QLineEdit(this);
    orientation = new QCheckBox(this);




    QFormLayout *formulaire = new QFormLayout;          // on crée un layout formulaire pour remplir les champs
    formulaire->addRow("titre", titre);
    formulaire->addRow("description", description);
    formulaire->addRow("Orientation", orientation);
    ok = new QPushButton("Valider", this);                                       // creation du bouton valider

    connect(ok, SIGNAL(clicked()), this, SLOT(ajouterRelation()));

     QVBoxLayout *mainLayout = new QVBoxLayout;         // le layout principal permet d'avoir le formulaire ET les différents boutons
         mainLayout->addLayout(formulaire);
         mainLayout->addWidget(ok);


     this->setLayout(mainLayout);
 }


void FenetreCreerRelation::ajouterRelation() {
    RelationManager& rm = RelationManager::getInstance();
    rm.addRelation(rm.makeRelationId(), titre->text(), description->text(), orientation->isChecked());
   pere->updateRelation();
   // RelationManager::getInstance().save();
    this->close();
}
