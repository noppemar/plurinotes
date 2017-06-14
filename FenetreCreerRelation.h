#ifndef FENETRECREERRELATION_H
#define FENETRECREERRELATION_H

#include <QtWidgets>
#include "notes.h"
#include "fenprincipale.h"
#include "relation.h"

class FenetreCreerRelation : public QWidget
{
    Q_OBJECT
public:
    FenetreCreerRelation(FenetrePrincipale *p);
private:
    QLineEdit *titre;
    QLineEdit *description;
    QCheckBox *orientation;
    QPushButton *ok;
    FenetrePrincipale* pere;

signals:


public slots:
    void ajouterRelation();


};




#endif // FENETRECREERRELATION_H
