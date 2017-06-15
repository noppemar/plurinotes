#ifndef FENETRECREERMULTI_H
#define FENETRECREERMULTI_H

#include <QtWidgets>                    // add 13/06 toute la fenetre
#include "notes.h"
#include "notes.h"
#include "histonotes.h"
#include "fenprincipale.h"

/*!
 * \brief The FenetreCreerMulti class
 * fenetre pour creer un multimedia
 */
class FenetreCreerMulti : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief FenetreCreerMulti
     * \param p
     */
    FenetreCreerMulti(FenetrePrincipale *p);

private:
    QLineEdit *titre;
    QLineEdit *description;
    QLineEdit *fichier;
    QComboBox *type;
    QPushButton *ok;
    FenetrePrincipale* pere;

signals:


public slots:
    /*!
     * \brief ajouterMulti
     * gere insertion du multimedia dans HistoNoteManager
     */
    void ajouterMulti();


};




#endif // FENETRECREERMULTI_H

