#ifndef RELATION_H
#define RELATION_H
#include "notes.h"

class RelationException{
public:
    RelationException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};



class Couple
{
private:
    Notes& note1;
    Notes& note2;
    QString label;

public:
    Couple(Notes& a, Notes& b, QString l=""):note1(a),note2(b),label(l){}  //constructeur
   //Accesseur en lecture
    Notes& getNote1() const {return note1;}
    Notes& getNote2() const {return note2;}
    const QString& getLabel() const {return label;}

    //Accesseur en écriture
    void setLabel(const QString& newL){label=newL;}

    bool operator ==(const Couple& c);
    ~Couple(){}
};


class Relation
{
private:
    Couple** couples;
    unsigned int nbCouples;
    unsigned int nbMaxCouples;
protected:
    QString titre;
    QString description;
    bool orientation;
public:
    Relation(const QString& titr, const QString& desc, bool orie=true):
          titre(titr), description(desc), orientation(orie), nbCouples(0), nbMaxCouples(10) {}

    void addCouple(Couple* newCouple);
    void addCouple(Notes& n1, Notes& n2, QString l="");
    //void deleteCouple(Couple& c);

    const QString& getTitre() const {return titre;}
    const QString& getDescription() const {return description;}
    bool getOrientation() const {return orientation;}

    virtual void setTitre(const QString& newTitre) = 0;                     //pure
    virtual void setDescription(const QString& newDescription) = 0;         //pure
    virtual void setOrientation(bool boolVal) = 0;                             //pure

    void ajouterCouple(Couple* newCouple);
    void supprimerCouple(Couple* supCouple);

       virtual ~Relation(){
           for (unsigned int i=0; i < nbCouples; i++) delete couples[i];
           delete[] couples;
       }

};


class RelationNormale: public Relation{
public:
    RelationNormale(const QString& titr, const QString& desc, bool orie=true): Relation(titr, desc, orie){}

    void setTitre(const QString& newTitre) {titre = newTitre;}
    void setDescription(const QString& newDescription){description = newDescription;}
    void setOrientation(bool boolVal){orientation = boolVal;}
};




class RelationPreexistente: public Relation{
    void setTitre(const QString&){}
    void setDescription(const QString&){}
    void setOrientation(bool){}

    static RelationPreexistente* instance_RelationPreexistente;
    RelationPreexistente(const RelationPreexistente& r);
    ~RelationPreexistente(){}
    RelationPreexistente& operator=(const RelationPreexistente&);
    RelationPreexistente(): Relation("references", "preexistente"){}

public:
    static RelationPreexistente* getRelationPreexistente(){
        if (!instance_RelationPreexistente) instance_RelationPreexistente = new RelationPreexistente;
            return instance_RelationPreexistente;
    }
    static void libererRelationPreexistente(){
        if (instance_RelationPreexistente){
            delete instance_RelationPreexistente;
            instance_RelationPreexistente = 0;
        }
    }
};






class RelationManager{
    Relation** relations;
    unsigned int nbRelations;
    unsigned int nbMaxRelations;

    static RelationManager *instance;
    RelationManager();
    ~RelationManager();
    RelationManager(const RelationManager& r){}
    RelationManager& operator=(const RelationManager&);





};

#endif // RELATION_H
