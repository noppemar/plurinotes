#ifndef FENETRECREERRELATION_H
#define FENETRECREERRELATION_H

#include <QtWidgets>
#include "notes.h"
#include "fenprincipale.h"
#include "relation.h"
/*!
 * \brief The FenetreCreerRelation class
 * fenetre pour creer une relation
 */

class FenetreCreerRelation : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief FenetreCreerRelation
     * \param p
     */
    FenetreCreerRelation(FenetrePrincipale *p);
private:
    QLineEdit *titre;
    QLineEdit *description;
    QCheckBox *orientation;
    QPushButton *ok;
    FenetrePrincipale* pere;

signals:


public slots:
    /*!
     * \brief ajouterRelation
     * gere insertion dans HistoNoteManager
     */
    void ajouterRelation();


};




#endif // FENETRECREERRELATION_H
