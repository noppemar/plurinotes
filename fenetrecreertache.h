#ifndef FENETRECREERTACHE_H
#define FENETRECREERTACHE_H

#include <QtWidgets>
#include "notes.h"
#include "histonotes.h"


class FenetreCreerTache : public QWidget
{
    Q_OBJECT
public:
    FenetreCreerTache();

private:
    QLineEdit *id;
    QLineEdit *titre;
    QLineEdit *action;
    QComboBox *priorite;
    QDateTimeEdit *dateEcheance;
    QComboBox *statut;
    QPushButton *ok;

signals:


public slots:
    void ajouterTache();


};


#endif // FENETRECREERTACHE_H
