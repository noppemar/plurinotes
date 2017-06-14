#ifndef RELATION_H
#define RELATION_H
#include "notes.h"
//#include "histonotes.h"

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

    bool operator ==(const Couple& c); // OK
    ~Couple(){}
};


class Relation
{
private:
    Couple** couples;
    unsigned int nbCouples;
    unsigned int nbMaxCouples;
protected:
    QString id;
    QString titre;
    QString description;
    bool orientation;
public:
    Relation(const QString& id, const QString& titr, const QString& desc, bool orie=true):
          nbCouples(0), nbMaxCouples(10),id (id), titre(titr), description(desc), orientation(orie) {}

    void addCouple(Couple* newCouple);
    void addCouple(Notes& n1, Notes& n2, QString l="");
    //void deleteCouple(Couple& c);


    const QString& getId() const {return id;}
    const QString& getTitre() const {return titre;}
    const QString& getDescription() const {return description;}
    bool getOrientation() const {return orientation;}


    virtual void setTitre(const QString& newTitre) = 0;                     //pure
    virtual void setDescription(const QString& newDescription) = 0;         //pure
    virtual void setOrientation(bool boolVal) = 0;                             //pure

    void ajouterCouple(Couple* newCouple);
    //void supprimerCouple(Couple* supCouple);

       virtual ~Relation(){
           for (unsigned int i=0; i < nbCouples; i++) delete couples[i];
           delete[] couples;
       }

    class iterator{
        Couple** current;
        iterator(Couple **a):current(a){}

        friend class Relation;

    public:
        iterator():current(0){}
        Couple* getCurrent(){return *current;}
        Couple& operator*(){ //pour avoir contenu du double pointeur avec 1 seul *
            return **current;
        }

        iterator &operator++(){
            ++current;
            return *this;
        }

        bool operator!=(iterator it) const{
            return current != it.current;
        }
    };

    iterator begin_relationr(){ //1ère case du tableau relation
        return iterator(couples);
    }

    iterator end_relation(){ //case juste après dernière case du tableau relation (condition boucle for : !=m.end)
        return iterator(couples + nbCouples);
    }

};


class RelationNormale: public Relation{  //OK
public:
    RelationNormale(const QString& id, const QString& titr, const QString& desc, bool orie=true): Relation(id, titr, desc, orie){}

    void setTitre(const QString& newTitre) {titre = newTitre;}
    void setDescription(const QString& newDescription){description = newDescription;}
    void setOrientation(bool boolVal){orientation = boolVal;}
};




class RelationPreexistente: public Relation{
    void setTitre(const QString&){}   //Ne fait rien car tout se fait dans le constructeur.
    void setDescription(const QString&){} //Ne fait rien car tout se fait dans le constructeur.
    void setOrientation(bool){} //Ne fait rien car tout se fait dans le constructeur.

    static RelationPreexistente* instance_RelationPreexistente;
    RelationPreexistente(const RelationPreexistente& r);
    ~RelationPreexistente(){}
    RelationPreexistente& operator=(const RelationPreexistente&);
    RelationPreexistente(): Relation("Ref","references", "preexistente"){}  //Construit avec titre et description fixe

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
    RelationNormale** relations; //tableau des relations normales
    unsigned int nbRelations;
    unsigned int nbMaxRelations;
    RelationPreexistente* reference;
    static RelationManager* instance;
    friend class HistoNoteManager;
    RelationManager(const RelationManager&){}
    RelationManager(){
        relations = new RelationNormale*[nbMaxRelations+10];
        nbMaxRelations += 10;
        RelationPreexistente* RP = RelationPreexistente::getRelationPreexistente();
        reference = RP;
    }
    RelationManager& operator=(const RelationManager&);
    ~RelationManager();

public:
    static RelationManager& getInstance(); //DP singleton
    static void libererInstance(); //DP singleton


    const QString makeRelationId();

     RelationNormale* getRelationNormal(const QString &id);
     RelationPreexistente* getRelationRef() {return reference;}

     void addRelation(RelationNormale* r);
     void addRelation(QString id, QString titre, QString desc, bool orientation);

    // void addRelationRef(RelationPreexistente* rP);
    //void addRelationRef(QString id="Ref", QString titre="references", QString desc="preexistente");
    //Plus besoin d'en ajouter, on les stocke dans relations[0]




    class iterator{
        RelationNormale** current;
        iterator(RelationNormale **a):current(a){}

        friend class RelationManager;

    public:
        iterator():current(0){}
        RelationNormale* getCurrent(){return *current;}
        RelationNormale& operator*(){ //pour avoir contenu du double pointeur avec 1 seul *
            return **current;
        }

        iterator &operator++(){
            ++current;
            return *this;
        }

        bool operator!=(iterator it) const{
            return current != it.current;
        }
    };
    iterator begin_relationManager(){ //1ère case du tableau relation
        return iterator(relations);
    }

    iterator end_relationManager(){ //case juste après dernière case du tableau relation (condition boucle for : !=m.end)
        return iterator(relations + nbRelations);
    }

};

#endif // RELATION_H
