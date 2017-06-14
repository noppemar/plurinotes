#include "noteediteur.h"
#include <QApplication>
#include <QString>

#include <QLineEdit>
#include "Notes.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QTextEdit>
#include "histonotes.h"





NoteEditeur::NoteEditeur(Notes& n, FenetrePrincipale *p): pere(p), note(&n)
{
    id=new QLineEdit(this);
    titre=new QLineEdit(this);

    id1= new QLabel("Identificateur", this);
    titre1=new QLabel("Titre", this);

    cid=new QHBoxLayout;
    cid->addWidget(id1);
    cid->addWidget(id);

    ctitre=new QHBoxLayout;
    ctitre->addWidget(titre1);
    ctitre->addWidget(titre);



    couche= new QVBoxLayout;
    couche->addLayout(cid);
    couche->addLayout(ctitre);

    id->setReadOnly(true);

    id->setText(note->getId());
    titre->setText(note->getTitre());


}


NoteEditeur::NoteEditeur(FenetrePrincipale *p):pere(p)
{
    id=new QLineEdit(this);
    titre=new QLineEdit(this);

    id1= new QLabel("Identificateur", this);
    titre1=new QLabel("Titre", this);

    cid=new QHBoxLayout;
    cid->addWidget(id1);
    cid->addWidget(id);

    ctitre=new QHBoxLayout;
    ctitre->addWidget(titre1);
    ctitre->addWidget(titre);




    couche= new QVBoxLayout;
    couche->addLayout(cid);
    couche->addLayout(ctitre);
    //couche->addLayout(cbutton);

    id->setReadOnly(true);

}

ArticleEditeur::ArticleEditeur(Article& art, FenetrePrincipale *p):
    NoteEditeur(art,p), article(&art)
{

    text= new QTextEdit(this);
    text1= new QLabel("Texte", this);
    ctext=new QHBoxLayout;
    ctext->addWidget(text1);
    ctext->addWidget(text);


    save= new QPushButton("Sauver", this);
    archiver=new QPushButton("Archiver", this);

    cbutton=new QHBoxLayout;
    cbutton->addWidget(save);
    cbutton->addWidget(archiver);



    QVBoxLayout* c=getCouche();
    c->addLayout(ctext);
    c->addLayout(cbutton);

    text->setText(article->getText());

    setLayout(c);

    QObject::connect(save, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(archiver, SIGNAL(clicked()), this, SLOT(archiver()));



}

TacheEditeur::TacheEditeur(Tache& ta, FenetrePrincipale *p):
    NoteEditeur(ta,p), tache(&ta)
{

    act= new QTextEdit(this);
    act1= new QLabel("Texte", this);
    cact=new QHBoxLayout;
    cact->addWidget(act1);
    cact->addWidget(act);

    save= new QPushButton("Sauver", this);
    archiver=new QPushButton("Archiver", this);

    cbutton=new QHBoxLayout;
    cbutton->addWidget(save);
    cbutton->addWidget(archiver);

    QVBoxLayout* c=getCouche();
    c->addLayout(cact);
    c->addLayout(cbutton);

    act->setText(tache->getAction());

    setLayout(c);


    QObject::connect(save, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(archiver, SIGNAL(clicked()), this, SLOT(archiver()));

}

void ArticleEditeur::saveArticle(){
    HistoNoteManager& m=HistoNoteManager::getInstance();
    m.getHistoArticle(article->getId())->addVersion(article->getId(),getTitre(),text->toPlainText());
    this->close();
}


void TacheEditeur::saveTache(){
    /*
    HistoNoteManager& m=HistoNoteManager::getInstance();
    m.getHistoTache(tache->getId())->addVersion(tache->getId(),getTitre(),act->toPlainText());
    */
}

void ArticleEditeur::archiverArticle(){

}

void TacheEditeur::archiverTache(){

}
