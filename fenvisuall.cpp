#include "fenvisuall.h"

FenVisuAll::FenVisuAll(QWidget *parent):QWidget(parent)
{
    setFixedSize(200, 400);
    move(0, 40);

    fenetre_vbox = new QVBoxLayout;

    titre = new QLabel("toutes les notes");

    liste = new QListWidget(this);

    HistoNoteManager& m=HistoNoteManager::getInstance();

    for(HistoNoteManager::iterator<Article> it=m.begin_article(); it!=m.end_article();++it){
        liste->addItem(it.getCurrent()->getLastVersion()->getTitre());
        tab_id.append(it.getCurrent()->getId());
    }

    fenetre_vbox->addWidget(titre);
    fenetre_vbox->addWidget(liste);

}
