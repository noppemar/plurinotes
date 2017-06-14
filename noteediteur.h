#ifndef NOTEEDITEUR_H
#define NOTEEDITEUR_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>


#include "notes.h"
#include "FenPrincipale.h"




class NoteEditeur : public QWidget
{
    Q_OBJECT
    QLineEdit *id;
    QLineEdit *titre;

    QLabel *id1;
    QLabel *titre1;

    QHBoxLayout *cid;
    QHBoxLayout *ctitre;



    QVBoxLayout *couche;

    FenetrePrincipale* pere;
    Notes *note;
    



    //gérer affichage date création, date modif

public:
   NoteEditeur(Notes& n, FenetrePrincipale *p);
   NoteEditeur(FenetrePrincipale *p);
   QVBoxLayout* getCouche(){return couche;}
   QString getTitre(){return titre->text();}




signals:

public slots:


};

class ArticleEditeur : public NoteEditeur
{
    Q_OBJECT

    QTextEdit *text;
    QLabel *text1;
    QHBoxLayout *ctext;


    QPushButton *save;
    QPushButton *archiver;

    QHBoxLayout *cbutton;

    Article* article;

public:
    ArticleEditeur(Article& art, FenetrePrincipale *p);
signals:

public slots:
    void saveArticle();
    void archiverArticle();
};

class TacheEditeur : public NoteEditeur
{
    Q_OBJECT

    QTextEdit *act;
    QLabel *act1;
    QHBoxLayout *cact;

    QPushButton *save;
    QPushButton *archiver;

    QHBoxLayout *cbutton;



    //gérer prio, date échéance & statut à afficher

    Tache* tache;


public:
    TacheEditeur(Tache& ta, FenetrePrincipale *p=0);

signals:

public slots:
    void saveTache();
    void archiverTache();
};

#endif // NOTEEDITEUR_H
