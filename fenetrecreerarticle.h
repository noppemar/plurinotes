#ifndef FENETRECREERARTICLE_H
#define FENETRECREERARTICLE_H

#include <QtWidgets>
#include "notes.h"
#include "histonotes.h"

class FenetreCreerArticle : public QWidget
{
    Q_OBJECT
public:
    FenetreCreerArticle();

private:
    QLineEdit *id;
    QLineEdit *titre;
    QLineEdit *texte;
    QPushButton *ok;

signals:


public slots:
    void ajouterArticle(QString id, QString titre, QString texte);


};


#endif // FENETRECREERARTICLE_H
