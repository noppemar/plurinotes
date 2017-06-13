#ifndef FENETRECREERMULTI_H
#define FENETRECREERMULTI_H

#include <QtWidgets>                    // add 13/06 toute la fenetre
#include "notes.h"
#include "histonotes.h"
#include "fenprincipale.h"


class FenetreCreerMulti : public QWidget
{
    Q_OBJECT
public:
    FenetreCreerMulti(FenetrePrincipale *p);

private:
    QLineEdit *id;
    QLineEdit *titre;
    QLineEdit *description;
    QLineEdit *fichier;
    QComboBox *type;
    QPushButton *ok;
    FenetrePrincipale* pere;

signals:


public slots:
    void ajouterMulti();


};




#endif // FENETRECREERMULTI_H
