#ifndef FENETRECREERTACHE_H
#define FENETRECREERTACHE_H

#include <QtWidgets>
#include "notes.h"


class FenetreCreerTache : public QWidget
{
    Q_OBJECT
public:
    FenetreCreerTache(QWidget *parent);

private:
    QLineEdit *id;
    QLineEdit *titre;
    QLineEdit *action;
    QComboBox *priorite;
    QDateEdit *dateEcheance;
    QComboBox *statut;
    QPushButton *ok;

signals:


public slots:
    void ajouterTache();


};


#endif // FENETRECREERTACHE_H
