#include "notes.h"
#include "noteediteur.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
bool Notes::operator==(const Notes& n){
    return id==n.getId();
}



void Article::afficher(){
}

void Tache::afficher(){
}

void Multimedia::afficher(){
    //TacheEditeur fenetre(*this);
   //fenetre.show();

}





