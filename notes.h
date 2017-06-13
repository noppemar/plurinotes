#ifndef NOTES_H
#define NOTES_H


#include <QString>
#include <QDateTime>
#include <QDate>
#include <iostream>
#include <QTextStream>



class Notes
{
private :
    QString id;
    QString titre;
    QDateTime dateModif;
    QDateTime dateCrea;
public:

    Notes(const QString i, const QString t) : id(i), titre(t) {
        dateModif=QDateTime::currentDateTime();
        dateCrea=QDateTime::currentDateTime();
    }



    virtual ~Notes(){};
    virtual void afficher()=0;


    const QString& getId() const { return id; }
    const QString& getTitre() const { return titre; }
    const QDateTime& getModif() const { return dateModif; }
    const QDateTime& getCrea() const { return dateCrea; }
    void setTitre(const QString& s ) { titre=s;}
    void setModif(const QDateTime& d) { dateModif=d;}
    void setCrea(const QDateTime& d ) { dateCrea=d;}
    bool operator==(const Notes& n);


};

class Article : public Notes {
    private :
        QString texte;

    public :
        const QString& getText() const { return texte; }
        void setTexte(const QString& s ) { texte=s;}
        virtual ~Article() {};
        Article(const QString i, const QString titr, const QString text) : Notes(i,titr), texte(text)  {}

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
        const QString& getAction() const { return action; }
        void setAction(const QString& a ) { action=a;}

        const QString& getPriorite() const { return priorite; }
        void setPrio(const int p ) { priorite=p;}

        const QDate& getEcheance() const { return dateEcheance; }
        void setEcheance(const QDate& d ) { dateEcheance=d;}

        const QString& getStatut() const { return statut; }
        void setStatut(const QString& s ) { statut=s;}


        Tache(const QString i, const QString titr, const QString act, const QString stat) : Notes(i,titr), action(act), statut(stat){}
        Tache(const QString i, const QString titr, const QString act, const QString stat, const QString prio) : Notes(i,titr), action(act), statut(stat), priorite(prio){}
        Tache(const QString i, const QString titr, const QString act, const QString stat, const QDate& d) : Notes(i,titr), action(act), statut(stat), dateEcheance(d){}

        Tache(const QString i, const QString titr, const QString act, const QString stat, const QString prio, const QDate& d) : Notes(i,titr), action(act), statut(stat), priorite(prio), dateEcheance(d){}


        void afficher();
};

//gérer multimedia, rajouter le 13/06 à 17h27, si on doit changer le git à la main il faudra juste rajouter ce qu'il y a en dessous pour ce fichier
class Multimedia : public Notes {
    private :
        QString description;
        QString fichier;
        QString type;

    public :
        const QString& getDesc() const { return description; }
        const QString& getFichier() const { return fichier; }
        void setDesc(const QString& s ) { description=s;}
         void setFichier(const QString& s ) { fichier=s;}
        virtual ~Multimedia() {};
        Multimedia(const QString i, const QString titr, const QString desc, const QString fich, const QString typ) : Notes(i,titr), description(desc), fichier(fich), type(typ)  {}

        void afficher();


};


#endif // NOTES_H
