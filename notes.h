#ifndef NOTES_H
#define NOTES_H


#include <QString>
#include <QDateTime>
#include <QDate>
#include <iostream>
#include <QTextStream>
#include <QFile>


/*!
 * \brief The Notes class
 * Classe abstraite
 */
class Notes
{
private :
    QString id;
    QString titre;
    QDate dateModif;
    QDate dateCrea;
public:
    /*!
     * \brief Notes
     * \param i id
     * \param t titre
     * et initialise date de creation et date de dernière modification avec la date actuelle
     */
    Notes(const QString i, const QString t) : id(i), titre(t) {
        dateModif=QDate::currentDate();
        dateCrea=QDate::currentDate();
    }

    /*!
     * \brief Notes
     * \param i
     * \param t
     * \param dateModif
     * \param dateCrea
     * surcharge constructeur pour methode load()
     */
    Notes(const QString i, const QString t, const QDate dateModif, const QDate dateCrea) :  id(i), titre(t), dateModif(dateModif), dateCrea(dateCrea)  {}



    virtual ~Notes(){};
    /*!
     * \brief afficher
     * methode virtuelle pure (on a oublié de s'en servir dans les classes filles)
     */
    virtual void afficher()=0;

    /*!
     * \brief getId
     * \return identifiant de la note
     * accesseur en lecture
     */
    const QString& getId() const { return id; }

    /*!
     * \brief getTitre
     * \return titre de la note
     * accesseur en lecture
     */
    const QString& getTitre() const { return titre; }

    /*!
     * \brief getModif
     * \return la date de dernière modif
     * accesseur en lecture
     */
    const QDate& getModif() const { return dateModif; }
    /*!
     * \brief getCrea
     * \return la date de creation
     * accesseur en lecture
     */
    const QDate& getCrea() const { return dateCrea; }
    /*!
     * \brief setTitre
     * \param s
     * accesseur en ecriture
     */
    void setTitre(const QString& s ) { titre=s;}
    /*!
     * \brief setModif
     * \param d
     * accesseur en ecriture pour date modif
     */
    void setModif(const QDate& d) { dateModif=d;}
    /*!
     * \brief setCrea
     * \param d
     * accesseur en ecriture pour date crea
     */
    void setCrea(const QDate& d) { dateCrea=d;}
    /*!
     * \brief operator ==
     * \param n
     * \return bool
     * surcharge operator==
     */
    bool operator==(const Notes& n);


};
/*!
 * \brief The Article class
 */
class Article : public Notes {
    private :
        QString texte;

    public :
        /*!
         * \brief getText
         * \return texte de l'article
         */
        const QString& getText() const { return texte; }
        /*!
         * \brief setTexte
         * \param s
         */
        void setTexte(const QString& s ) { texte=s;}
        /*!
         * \brief Article
         * \param i
         * \param titr
         * \param text
         * constructeur
         */
        Article(const QString i, const QString titr, const QString text) : Notes(i,titr), texte(text)  {}
        /*!
         * \brief Article
         * \param i
         * \param titr
         * \param text
         * \param dateCrea
         * \param dateModif
         surcharge constructeur pour load
         */
        Article(const QString i, const QString titr, const QString text, QDate dateCrea, QDate dateModif) : Notes(i,titr,dateCrea,dateModif), texte(text) {}

        /*!
         * \brief afficher
         */
        void afficher();



};

//enum Statut {enAttente,enCours,terminee};

class Tache : public Notes {
    private :
        QString action;
        QString statut;
        QString priorite;
        QDate dateEcheance;


    public :
        /*!
         * \brief getAction
         * \return
         */
        const QString& getAction() const { return action; }
        /*!
         * \brief setAction
         * \param a
         */
        void setAction(const QString& a ) { action=a;}

        /*!
         * \brief getPriorite
         * \return
         */

        const QString& getPriorite() const { return priorite; }
        /*!
         * \brief setPrio
         * \param p
         */
        void setPrio(const int p ) { priorite=p;}
        /*!
         * \brief getEcheance
         * \return
         */
        const QDate& getEcheance() const { return dateEcheance; }
        /*!
         * \brief setEcheance
         * \param d
         */
        void setEcheance(const QDate& d ) { dateEcheance=d;}
        /*!
         * \brief getStatut
         * \return
         */
        const QString& getStatut() const { return statut; }
        /*!
         * \brief setStatut
         * \param s
         */
        void setStatut(const QString& s ) { statut=s;}

        /*!
         * \brief Tache
         * \param i
         * \param titr
         * \param act
         * \param stat
         * constructeur
         */
        Tache(const QString i, const QString titr, const QString act, const QString stat) : Notes(i,titr), action(act), statut(stat){}
        /*!
        /*! * \brief Tache
        /*! * \param i
        /*! * \param titr
        /*! * \param act
        /*! * \param stat
        /*! * \param prio
         * surcharge constructeur
         */
        Tache(const QString i, const QString titr, const QString act, const QString stat, const QString prio) : Notes(i,titr), action(act), statut(stat), priorite(prio){}

        /*!
         * \brief Tache
         * \param i
         * \param titr
         * \param act
         * \param stat
         * \param d
         * surcharge constructeur
         */
        Tache(const QString i, const QString titr, const QString act, const QString stat, const QDate& d) : Notes(i,titr), action(act), statut(stat), dateEcheance(d){}
        /*!
         * \brief Tache
         * \param i
         * \param titr
         * \param act
         * \param stat
         * \param prio
         * \param d
         * surcharge constructeur
         */
        Tache(const QString i, const QString titr, const QString act, const QString stat, const QString prio, const QDate& d) : Notes(i,titr), action(act), statut(stat), priorite(prio), dateEcheance(d){}

        /*!
         * \brief Tache
         * \param i
         * \param titr
         * \param act
         * \param stat
         * \param prio
         * \param d
         * \param dateCrea
         * \param dateModif
         * surcharge constructeur
         */
        Tache(const QString i, const QString titr, const QString act, const QString stat, const QString prio, const QDate& d, QDate dateCrea, QDate dateModif) : Notes(i,titr,dateCrea,dateModif), action(act), statut(stat), priorite(prio), dateEcheance(d){}

        /*!
         * \brief afficher
         */
        void afficher();

};

//gérer multimedia, rajouter le 13/06 à 17h27, si on doit changer le git à la main il faudra juste rajouter ce qu'il y a en dessous pour ce fichier
class Multimedia : public Notes {
    private :
        QString description;
        QString fichier;
        QString type;

    public :
        /*!
         * \brief getDesc
         * \return
         */
        const QString& getDesc() const { return description; }
        /*!
         * \brief getFichier
         * \return
         */
        const QString& getFichier() const { return fichier; }
        /*!
         * \brief getType
         * \return
         */
        const QString& getType() const { return type; }

        /*!
         * \brief setDesc
         * \param s
         */
        void setDesc(const QString& s ) { description=s;}
        /*!
         * \brief setFichier
         * \param s
         */
        void setFichier(const QString& s ) { fichier=s;}
        /*!
         * \brief setType
         * \param t
         */
        void setType(const QString& t ) { type=t;}


        virtual ~Multimedia() {};
        /*!
         * \brief Multimedia
         * \param i
         * \param titr
         * \param desc
         * \param fich
         * \param typ
         * constructeur
         */
        Multimedia(const QString i, const QString titr, const QString desc, const QString fich, const QString typ) : Notes(i,titr), description(desc), fichier(fich), type(typ)  {}

        /*!
         * \brief Multimedia
         * \param i
         * \param titr
         * \param desc
         * \param fich
         * \param typ
         * \param dateCrea
         * \param dateModif
         * surcharge du constructeur
         */
        Multimedia(const QString i, const QString titr, const QString desc, const QString fich, const QString typ, QDate dateCrea, QDate dateModif) : Notes(i,titr,dateCrea,dateModif), description(desc), fichier(fich), type(typ) {}


        /*!
         * \brief afficher
         */
        void afficher();



};


#endif // NOTES_H
