#ifndef FENETRECREERARTICLE_H
#define FENETRECREERARTICLE_H

#include <QtWidgets>
#include "notes.h"


class FenetreCreerArticle : public QWidget
{
    Q_OBJECT
public:
    FenetreCreerArticle(QWidget *parent);

private:
    QLineEdit *id;
    QLineEdit *titre;
    QLineEdit *texte;
    QPushButton *ok;

signals:


public slots:
    void ajouterArticle();


};


#endif // FENETRECREERARTICLE_H
