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



/*!
 * \brief The NoteEditeur class
 * permet afficher partie note d'un article, tache ou multi
 */
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
    /*!
    * \brief NoteEditeur
    * \param n note a afficher
    * \param p FenetrePrincipale dans laquelle afficher
    */
   NoteEditeur(Notes& n, FenetrePrincipale *p);
   NoteEditeur(FenetrePrincipale *p);
   QVBoxLayout* getCouche(){return couche;}
   QString getTitre(){return titre->text();}
   QLineEdit* Titre(){return titre;}
   FenetrePrincipale* getPere(){return pere;}




signals:

public slots:


};
/*!
 * \brief The ArticleEditeur class
 * permet afficher Article, herite de NoteEditeur
 */
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
    /*!
     * \brief ArticleEditeur
     * \param art article à afficher
     * \param p FenetrePrincipale dans laquelle afficher
     */
    ArticleEditeur(Article& art, FenetrePrincipale *p);
    /*!
     * \brief ArticleEditeur
     * \param art article à afficher
     * \param p FenetrePrincipale dans laquelle afficher
     * \param j pour savoir si archive ou pas
     */
    ArticleEditeur(Article& art, FenetrePrincipale *p,int j);

signals:

public slots:
    /*!
     * \brief saveArticle
     * enregistrer modif article
     */
    void saveArticle();
    /*!
     * \brief archiverArticle
     * archiver un article
     */
    void archiverArticle();
    /*!
     * \brief restaurerArticle
     * restaurer un article
     */
    void restaurerArticle();
};

/*!
 * \brief The TacheEditeur class
 * permet afficher Tache, herite de NoteEditeur
 */
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
    /*!
     * \brief TacheEditeur
     * \param ta tache à afficher
     * \param p FenetrePrincipale dans laquelle afficher
     */
    TacheEditeur(Tache& ta, FenetrePrincipale *p);
    /*!
     * \brief TacheEditeur
     * \param ta tache à afficher
     * \param p FenetrePrincipale dans laquelle afficher
     * \param j pour savoir si archive ou pas
     */
    TacheEditeur(Tache& ta, FenetrePrincipale *p, int j);

signals:

public slots:
    /*!
     * \brief saveTache
     * enregistrer modif tache
     */
    void saveTache();

    /*!
     * \brief archiverTache
     * archiver une tache
     */

    void archiverTache();

    /*!
     * \brief restaurerTache
     * restaurer une tache
     */
    void restaurerTache();
};

/*!
 * \brief The MultiEditeur class
 * permet afficher Multimedia, herite NoteEditeur
 */
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
    /*!
     * \brief MultiEditeur
     * \param multi multimedia à afficher
     * \param p FenetrePrincipale dans laquelle afficher
     */
    MultiEditeur(Multimedia& multi, FenetrePrincipale *p);
    /*!
     * \brief MultiEditeur
     * \param multi multimedia à afficher
     * \param p FenetrePrincipale dans laquelle afficher
     * \param j pour savoir si archive
     */
    MultiEditeur(Multimedia& multi, FenetrePrincipale *p, int j);
signals:

public slots:
    /*!
     * \brief saveMulti
     * enregistrer modif multimedia
     */
    void saveMulti();
    /*!
     * \brief archiverMulti
     * archiver un multimedia
     */
    void archiverMulti();
    /*!
     * \brief restaurerMulti
     * restaurer un multimedia
     */
    void restaurerMulti();
};

#endif // NOTEEDITEUR_H
