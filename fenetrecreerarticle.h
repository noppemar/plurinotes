#ifndef FENETRECREERARTICLE_H
#define FENETRECREERARTICLE_H

#include <QtWidgets>
#include "notes.h"
#include "histonotes.h"
#include "fenprincipale.h"

class FenetreCreerArticle : public QWidget
{
    Q_OBJECT
public:
    FenetreCreerArticle(FenetrePrincipale *p);
private:
    QLineEdit *titre;
    QLineEdit *texte;
    QPushButton *ok;
    FenetrePrincipale* pere;

signals:


public slots:
    void ajouterArticle();


};


#endif // FENETRECREERARTICLE_H
