#include "relation.h"



RelationManager::~RelationManager(){
    for(unsigned int i=0; i<nbRelations; i++) delete relations[i];
    delete[] relations;
}

RelationManager* RelationManager::instance = 0; //initialisation + définition à nullptr
RelationPreexistente* RelationPreexistente::instance_RelationPreexistente = 0; //initialisation + définition à nullptr


RelationManager& RelationManager::getInstance(){ //méthode qui vérifie qu'il n'y ait qu'une seule instance de NotesManager
    if(RelationManager::instance==0)
        RelationManager::instance = new RelationManager; //crée une instance
    return *RelationManager::instance;
}

void RelationManager::libererInstance(){
    if(RelationManager::instance !=0) //si instance existe
        delete RelationManager::instance; // supprime
    RelationManager::instance=0; //réinitialisation à nullptr
}



void RelationManager::addRelation(RelationNormale *newRelation){
    if (nbRelations == nbMaxRelations){
        RelationNormale** newRelations = new RelationNormale*[nbMaxRelations+10];
        for (unsigned int i=0; i < nbRelations; i++) newRelations[i] = relations[i];
        RelationNormale** oldRelations = relations;
        relations = newRelations;
        delete[] oldRelations;
        nbMaxRelations += 10;
    }
    relations[++nbRelations] = newRelation;
}


void RelationManager::addRelation(QString id, QString titre, QString desc, bool orientation){

    RelationNormale* rN= new RelationNormale(id, titre, desc, orientation);
    addRelation(rN);
}



const QString RelationManager::makeRelationId(){
    QString newId="Relation"+ QString::number(nbRelations+1); // +1 pour que commence à partir de 1
    return newId;

}



RelationNormale* RelationManager::getRelationNormal(const QString& id){
    iterator it=begin_relationManager();
    while(it!=end_relationManager()){
        if (it.getCurrent()->getId()==id) return *(it.current);
        ++it;
    }
    return nullptr;
}





bool Couple::operator ==(const Couple& c){
    return (note1==c.getNote1() && note2==c.getNote2());
}


void Relation::addCouple(Couple* c){
    for(unsigned int i=0;i<nbCouples;i++){
        if(couples[i]==c) throw RelationException("couple existe deja");
    }
    //Fonctionne pour les deux cas d'orientation, car le traitement ne change pas.
    if(nbCouples==nbMaxCouples){
        Couple** newCouples = new Couple*[nbMaxCouples+5];

        for(unsigned int i=0; i<nbCouples; i++) newCouples[i]=couples[i];
        Couple** oldCouples=couples;
        couples=newCouples;
        nbMaxCouples+=5;
        if(oldCouples) delete[] oldCouples;

    }

    couples[nbCouples++]=c;
}



void Relation::addCouple(Notes& n1, Notes& n2, QString l){  //A FAIRE
    for(unsigned int i=0; i<nbCouples; i++){
        if (couples[i]->getNote1()==n1 && couples[i]->getNote2()==n2) throw RelationException("Erreur : couple déjà existant");
    }
    Couple* c=new Couple(n1,n2,l);
    addCouple(c);
}






