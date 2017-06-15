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


    QDateTimeEdit *dateCrea;
    QLabel *dateCrea1;
    QHBoxLayout *cdateCrea;

    QDateTimeEdit *dateModif;
    QLabel *dateModif1;
    QHBoxLayout *cdateModif;

    QVBoxLayout *couche;

    FenetrePrincipale* pere;
    Notes *note;




    //gérer affichage date création, date modif

public:
   NoteEditeur(Notes& n, FenetrePrincipale *p);
   NoteEditeur(FenetrePrincipale *p);
   QVBoxLayout* getCouche(){return couche;}
   QString getTitre(){return titre->text();}
   QLineEdit* Titre(){return titre;}
   FenetrePrincipale* getPere(){return pere;}




signals:

public slots:


};

class ArticleEditeur : public NoteEditeur
{
    Q_OBJECT

    int i;

    QTextEdit *text;
    QLabel *text1;
    QHBoxLayout *ctext;


    QPushButton *save;
    QPushButton *archiver;
    QPushButton *restaurer;

    QHBoxLayout *cbutton;

    Article* article;

public:
    ArticleEditeur(Article& art, FenetrePrincipale *p);
    ArticleEditeur(Article& art, FenetrePrincipale *p,int j);

signals:

public slots:
    void saveArticle();
    void archiverArticle();
    void restaurerArticle();
};

class TacheEditeur : public NoteEditeur
{
    Q_OBJECT

    int i;
    QTextEdit *act;
    QLabel *act1;
    QHBoxLayout *cact;

    QComboBox *priorite;
    QLabel *prio1;
    QHBoxLayout *cprio;

    QDateEdit *dateEcheance;
    QLabel *dateEcheance1;
    QHBoxLayout *cdateEcheance;

    QComboBox *statut;
    QLabel *stat1;
    QHBoxLayout *cstat;

    QPushButton *save;
    QPushButton *archiver;
    QPushButton *restaurer;

    QHBoxLayout *cbutton;



    //gérer prio, date échéance & statut à afficher

    Tache* tache;


public:
    TacheEditeur(Tache& ta, FenetrePrincipale *p);
    TacheEditeur(Tache& ta, FenetrePrincipale *p, int j);

signals:

public slots:
    void saveTache();
    void archiverTache();
    void restaurerTache();
};

class MultiEditeur : public NoteEditeur
{
    Q_OBJECT

    int i;
    QHBoxLayout *ctype;
    QLineEdit *type;

    QTextEdit *desc;
    QLabel *desc1;
    QHBoxLayout *cdesc;

    QLineEdit *fichier;
    QLabel *fichier1;
    QHBoxLayout *cfichier;





    QPushButton *save;
    QPushButton *archiver;
    QPushButton *restaurer;

    QHBoxLayout *cbutton;

    Multimedia* multimedia;

public:
    MultiEditeur(Multimedia& multi, FenetrePrincipale *p);
    MultiEditeur(Multimedia& multi, FenetrePrincipale *p, int j);
signals:

public slots:
    void saveMulti();
    void archiverMulti();
    void restaurerMulti();
};

#endif // NOTEEDITEUR_H
