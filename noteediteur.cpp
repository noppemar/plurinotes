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

    dateCrea= new QDateTimeEdit(this);
    dateCrea1= new QLabel("Date Creation", this);
    cdateCrea=new QHBoxLayout;
    cdateCrea->addWidget(dateCrea1);
    cdateCrea->addWidget(dateCrea);

    dateModif= new QDateTimeEdit(this);
    dateModif1= new QLabel("Date Derniere Modification", this);
    cdateModif=new QHBoxLayout;
    cdateModif->addWidget(dateModif1);
    cdateModif->addWidget(dateModif);


    couche= new QVBoxLayout;
    couche->addLayout(cid);
    couche->addLayout(ctitre);
    couche->addLayout(cdateCrea);
    couche->addLayout(cdateModif);

    id->setReadOnly(true);
    dateCrea->setReadOnly(true);
    dateModif->setReadOnly(true);

    id->setText(note->getId());
    titre->setText(note->getTitre());
    dateCrea->setDate(note->getCrea());
    dateModif->setDate(note->getModif());


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

    QObject::connect(save, SIGNAL(clicked()), this, SLOT(saveArticle()));
    QObject::connect(archiver, SIGNAL(clicked()), this, SLOT(archiverArticle()));



}

ArticleEditeur::ArticleEditeur(Article& art, FenetrePrincipale *p,int j):
    NoteEditeur(art,p), i(j), article(&art)
{

    text= new QTextEdit(this);
    text1= new QLabel("Texte", this);
    ctext=new QHBoxLayout;
    ctext->addWidget(text1);
    ctext->addWidget(text);



    restaurer=new QPushButton("Restaurer", this);

    cbutton=new QHBoxLayout;
    cbutton->addWidget(restaurer);




    QVBoxLayout* c=getCouche();
    c->addLayout(ctext);
    c->addLayout(cbutton);

    text->setText(article->getText());

    text->setReadOnly(true);
    Titre()->setReadOnly(true);

    setLayout(c);


    QObject::connect(restaurer, SIGNAL(clicked()), this, SLOT(restaurerArticle()));


}

TacheEditeur::TacheEditeur(Tache& ta, FenetrePrincipale *p):
    NoteEditeur(ta,p), tache(&ta)
{

    act= new QTextEdit(this);
    act1= new QLabel("Action", this);
    cact=new QHBoxLayout;
    cact->addWidget(act1);
    cact->addWidget(act);

    priorite= new QComboBox(this);
    priorite->addItem("ça ne presse pas");             //liste deroulante
    priorite->addItem("à faire");
    priorite->addItem("à faire en prio absolue");
    prio1= new QLabel("Priorite", this);
    cprio=new QHBoxLayout;
    cprio->addWidget(prio1);
    cprio->addWidget(priorite);

    dateEcheance= new QDateEdit(this);
    dateEcheance1= new QLabel("Date echeance", this);
    cdateEcheance=new QHBoxLayout;
    cdateEcheance->addWidget(dateEcheance1);
    cdateEcheance->addWidget(dateEcheance);

    statut= new QComboBox(this);
    statut->addItem("enAttente");                       //liste deroulante
    statut->addItem("enCours");
    statut->addItem("terminee");
    stat1= new QLabel("Statut", this);
    cstat=new QHBoxLayout;
    cstat->addWidget(stat1);
    cstat->addWidget(statut);



    save= new QPushButton("Sauver", this);
    archiver=new QPushButton("Archiver", this);

    cbutton=new QHBoxLayout;
    cbutton->addWidget(save);
    cbutton->addWidget(archiver);

    QVBoxLayout* c=getCouche();
    c->addLayout(cact);
    c->addLayout(cprio);
    c->addLayout(cdateEcheance);
    c->addLayout(cstat);
    c->addLayout(cbutton);

    act->setText(tache->getAction());
    dateEcheance->setDate(tache->getEcheance());

    //je sais pas pour prio et statut comment afficher + pouvoir les modifier
    setLayout(c);


    QObject::connect(save, SIGNAL(clicked()), this, SLOT(saveTache()));
    QObject::connect(archiver, SIGNAL(clicked()), this, SLOT(archiverTache()));

}

TacheEditeur::TacheEditeur(Tache& ta, FenetrePrincipale *p, int j):
    NoteEditeur(ta,p), i(j), tache(&ta)
{

    act= new QTextEdit(this);
    act1= new QLabel("Action", this);
    cact=new QHBoxLayout;
    cact->addWidget(act1);
    cact->addWidget(act);

    priorite= new QComboBox(this);
    priorite->addItem("ça ne presse pas");             //liste deroulante
    priorite->addItem("à faire");
    priorite->addItem("à faire en prio absolue");
    prio1= new QLabel("Priorite", this);
    cprio=new QHBoxLayout;
    cprio->addWidget(prio1);
    cprio->addWidget(priorite);

    dateEcheance= new QDateEdit(this);
    dateEcheance1= new QLabel("Date echeance", this);
    cdateEcheance=new QHBoxLayout;
    cdateEcheance->addWidget(dateEcheance1);
    cdateEcheance->addWidget(dateEcheance);

    statut= new QComboBox(this);
    statut->addItem("enAttente");                       //liste deroulante
    statut->addItem("enCours");
    statut->addItem("terminee");
    stat1= new QLabel("Statut", this);
    cstat=new QHBoxLayout;
    cstat->addWidget(stat1);
    cstat->addWidget(statut);

    restaurer=new QPushButton("Restaurer", this);

    cbutton=new QHBoxLayout;
    cbutton->addWidget(restaurer);


    QVBoxLayout* c=getCouche();
    c->addLayout(cact);
    c->addLayout(cprio);
    c->addLayout(cdateEcheance);
    c->addLayout(cstat);
    c->addLayout(cbutton);

    act->setText(tache->getAction());
    act->setReadOnly(true);
    dateEcheance->setDate(tache->getEcheance());
    dateEcheance->setReadOnly(true);
    Titre()->setReadOnly(true);

    QObject::connect(restaurer, SIGNAL(clicked()), this, SLOT(restaurerTache()));

    //je sais pas pour prio et statut comment afficher + pouvoir les modifier
    setLayout(c);




}

MultiEditeur::MultiEditeur(Multimedia& multi, FenetrePrincipale *p):
    NoteEditeur(multi,p), multimedia(&multi)
{

    type=new QLineEdit(this);
    ctype=new QHBoxLayout;
    ctype->addWidget(type);

    desc= new QTextEdit(this);
    desc1= new QLabel("Description", this);
    cdesc=new QHBoxLayout;
    cdesc->addWidget(desc1);
    cdesc->addWidget(desc);

    fichier= new QLineEdit(this);
    fichier1= new QLabel("Fichier", this);
    cfichier=new QHBoxLayout;
    cfichier->addWidget(fichier1);
    cfichier->addWidget(fichier);

    save= new QPushButton("Sauver", this);
    archiver=new QPushButton("Archiver", this);

    cbutton=new QHBoxLayout;
    cbutton->addWidget(save);
    cbutton->addWidget(archiver);



    QVBoxLayout* c=getCouche();
    c->addLayout(ctype);
    c->addLayout(cdesc);
    c->addLayout(cfichier);
    c->addLayout(cbutton);

    type->setText(multimedia->getType());
    desc->setText(multimedia->getDesc());
    fichier->setText(multimedia->getFichier());

    type->setReadOnly(true);
    setLayout(c);

    QObject::connect(save, SIGNAL(clicked()), this, SLOT(saveMulti()));
    QObject::connect(archiver, SIGNAL(clicked()), this, SLOT(archiverMulti()));



}

MultiEditeur::MultiEditeur(Multimedia& multi, FenetrePrincipale *p, int j):
    NoteEditeur(multi,p), i(j), multimedia(&multi)
{

    type=new QLineEdit(this);
    ctype=new QHBoxLayout;
    ctype->addWidget(type);

    desc= new QTextEdit(this);
    desc1= new QLabel("Description", this);
    cdesc=new QHBoxLayout;
    cdesc->addWidget(desc1);
    cdesc->addWidget(desc);

    fichier= new QLineEdit(this);
    fichier1= new QLabel("Fichier", this);
    cfichier=new QHBoxLayout;
    cfichier->addWidget(fichier1);
    cfichier->addWidget(fichier);

    restaurer=new QPushButton("Restaurer");

    cbutton=new QHBoxLayout;
    cbutton->addWidget(restaurer);




    QVBoxLayout* c=getCouche();
    c->addLayout(ctype);
    c->addLayout(cdesc);
    c->addLayout(cfichier);
    c->addLayout(cbutton);

    type->setText(multimedia->getType());
    desc->setText(multimedia->getDesc());
    fichier->setText(multimedia->getFichier());


    desc->setReadOnly(true);
    fichier->setReadOnly(true);
    Titre()->setReadOnly(true);


    type->setReadOnly(true);
    setLayout(c);

    QObject::connect(restaurer, SIGNAL(clicked()), this, SLOT(restaurerMulti()));



}

void ArticleEditeur::saveArticle(){
    HistoNoteManager& m=HistoNoteManager::getInstance();
    m.getHistoArticle(article->getId())->addVersion(article->getId(),getTitre(),text->toPlainText());
    getPere()->updateArticles();
    m.save();
    this->close();
}


void TacheEditeur::saveTache(){
    HistoNoteManager& m=HistoNoteManager::getInstance();
    m.getHistoTache(tache->getId())->addVersion(tache->getId(),getTitre(),act->toPlainText(),statut->currentText(), dateEcheance->date(), priorite->currentText());
    getPere()->updateTaches();
    m.save();
    this->close();
}

void MultiEditeur::saveMulti(){
    HistoNoteManager& m=HistoNoteManager::getInstance();
    m.getHistoMulti(multimedia->getId())->addVersion(multimedia->getId(),getTitre(),desc->toPlainText(),fichier->text(),type->text());
    getPere()->updateMulti();
    m.save();
    this->close();
}

void ArticleEditeur::archiverArticle(){
    HistoNoteManager& m=HistoNoteManager::getInstance();

    HistoNotes<Article>* h=m.getHistoArticle(article->getId());
    m.archiver(h);
    getPere()->updateArticles();
    getPere()->updateArchives();
    this->close();

}

void TacheEditeur::archiverTache(){
    HistoNoteManager& m=HistoNoteManager::getInstance();

    HistoNotes<Tache>* h=m.getHistoTache(tache->getId());
    m.archiver(h);
    getPere()->updateTaches();
    getPere()->updateArchives();
    this->close();
}

void MultiEditeur::archiverMulti(){
    HistoNoteManager& m=HistoNoteManager::getInstance();

    HistoNotes<Multimedia>* h=m.getHistoMulti(multimedia->getId());
    m.archiver(h);
    getPere()->updateMulti();
    getPere()->updateArchives();
    this->close();
}

void ArticleEditeur::restaurerArticle(){
    HistoNoteManager& m=HistoNoteManager::getInstance();
    Archive* a=m.getArchive();

    HistoNotes<Article>* h=a->getHistoArticle(article->getId());
    m.restaurer(h);
    getPere()->updateArticles();
    getPere()->updateArchives();
    this->close();

}

void TacheEditeur::restaurerTache(){
    HistoNoteManager& m=HistoNoteManager::getInstance();
    Archive* a=m.getArchive();

    HistoNotes<Tache>* h=a->getHistoTache(tache->getId());
    m.restaurer(h);
    getPere()->updateTaches();
    getPere()->updateArchives();
    this->close();

}

void MultiEditeur::restaurerMulti(){
    HistoNoteManager& m=HistoNoteManager::getInstance();
    Archive* a=m.getArchive();

    HistoNotes<Multimedia>* h=a->getHistoMulti(multimedia->getId());
    m.restaurer(h);
    getPere()->updateMulti();
    getPere()->updateArchives();
    this->close();

}
