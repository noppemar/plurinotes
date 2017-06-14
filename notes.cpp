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

void Article::save(QFile* f) const
                    {QXmlStreamWriter stream(f);
                    stream.writeStartElement("article");
                    stream.writeTextElement("dateArticle",getModif().toString());
                    stream.writeTextElement("texte",texte );
}

void Tache::save(QFile* f) const
                    {QXmlStreamWriter stream(f);
                    stream.writeStartElement("tache");
                    stream.writeTextElement("dateVersion",getModif().toString());
                    stream.writeTextElement("action", action);
}

void Multimedia::save(QFile* f) const
                    {QXmlStreamWriter stream(f);
                    stream.writeStartElement("multimedia");
                    stream.writeTextElement("dateVersion",getModif().toString());
                   // stream.writeTextElement("action", action);
}



