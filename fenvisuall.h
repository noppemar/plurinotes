#ifndef FENVISUALL_H
#define FENVISUALL_H

#include "histonotes.h"

#include <QWidget>
#include <QList>

#include <QListWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>

#include <QPushButton>

class FenVisuAll : public QWidget {

    Q_OBJECT

public:
    FenVisuAll(QWidget *parent = 0);

    QString getTitre() {return titre->text(); }
    QLabel *getTitreWidget() {return titre; }
    QListWidget* getListe() {return liste;}
    QString getIdIndice(int indice) const {
        if(indice > tab_id.size())
            throw "erreur";
        else
            return tab_id[indice];
    }

private:

    QList<QString> tab_id;

    QVBoxLayout *fenetre_vbox;

    QLabel *titre;
    QListWidget *liste;
    QString NoteId;

    QHBoxLayout *button_layout;
    QPushButton *button_open;
    QPushButton *button_close;
};

#endif // FENVISUALL_H
