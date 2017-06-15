#ifndef FENETRECREERARTICLE_H
#define FENETRECREERARTICLE_H

#include <QtWidgets>
#include "notes.h"
#include "histonotes.h"
#include "fenprincipale.h"

/*!
 * \brief The FenetreCreerArticle class
 * fenetre pour créer un article
 */
class FenetreCreerArticle : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief FenetreCreerArticle
     * \param p fenetre principale
     */
    FenetreCreerArticle(FenetrePrincipale *p);
private:
    QLineEdit *titre;
    QLineEdit *texte;
    QPushButton *ok;
    FenetrePrincipale* pere;

signals:


public slots:
    /*!
     * \brief ajouterArticle
     * gère insertion dans HistoNotesManager
     */
    void ajouterArticle();


};


#endif // FENETRECREERARTICLE_H
