#include "notes.h"
#include "noteediteur.h"

bool Notes::operator==(const Notes& n){
    return id==n.getId();
}


/* A TESTER QUAND SAIT FIXER SUR FENETRE MAIN */
void Article::afficher(){
    ArticleEditeur fenetre(*this);
    fenetre.show();

}

void Tache::afficher(){
    TacheEditeur fenetre(*this);
    fenetre.show();

}

void Multimedia::afficher(){
    //TacheEditeur fenetre(*this);
   //fenetre.show();

}

void Article::save(QFile* f) const
                    {QXmlStreamWriter stream(f);
                    stream.writeStartElement("article");
                    stream.writeTextElement("dateVersion",getModif().toString());
                    stream.writeTextElement("texte",texte );
}

void Tache::save(QFile* f) const
                    {QXmlStreamWriter stream(f);
                    stream.writeStartElement("article");
                    stream.writeTextElement("dateVersion",getModif().toString());
                    stream.writeTextElement("action", action);
}

