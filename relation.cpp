#include "relation.h"

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


//A TESTER

void Relation::addCouple(Notes& n1, Notes& n2, QString l){
    //ORIENTATION A GERER

    //A FAIRE QUAND operator== définit pour HistoNote
    for(unsigned int i=0; i<nbCouples; i++){
        if (couples[i]->getNote1()==n1 && couples[i]->getNote2()==n2) throw RelationException("Erreur : couple déjà existant");
    }
    Couple* c=new Couple(n1,n2,l);
    addCouple(c);
}
