#ifndef FENETRECREERNOTES_H
#define FENETRECREERNOTES_H


#include <QWidget>
#include <QtWidgets/QPushButton>


class FenetreCreerNotes : public QWidget
{
    Q_OBJECT
public:
    FenetreCreerNotes();

private:
    QPushButton *Tache;
    QPushButton *Article;

signals:

public slots:
    void afficherCreerArticle();

};

#endif
