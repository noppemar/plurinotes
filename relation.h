#ifndef RELATION_H
#define RELATION_H
#include "notes.h"
//#include "histonotes.h"

/*!
 * \brief The RelationException class
 * gère les erreurs de la classe Relation
 */
class RelationException{
public:
    /*!
     * \brief RelationException
     * \param message
     */
    RelationException(const QString& message):info(message){}
    /*!
     * \brief getInfo
     * \return message erreur
     */
    QString getInfo() const { return info; }
private:
    QString info;
};


/*!
 * \brief The Couple class
 * contient un couple de 2 notes
 */
class Couple
{
private:
    Notes& note1;
    Notes& note2;
    QString label;

public:
    /*!
     * \brief Couple
     * \param a
     * \param b
     * \param l
     */
    Couple(Notes& a, Notes& b, QString l=""):note1(a),note2(b),label(l){}  
    /*!
     * \brief getNote1
     * \return la premiere note
     */
    Notes& getNote1() const {return note1;}
    /*!
     * \brief getNote2
     * \return la deuxieme note
     */
    Notes& getNote2() const {return note2;}
    /*!
     * \brief getLabel
     * \return le label
     */
    const QString& getLabel() const {return label;}

    /*!
     * \brief setLabel
     * \param newL
     * accesseur en ecriture
     */
    void setLabel(const QString& newL){label=newL;}
    
    /*!
     * \brief operator ==
     * \param c
     * \return bool
     * surcharge operateur ==
     */
    bool operator ==(const Couple& c); // OK
    ~Couple(){}
};

/*!
 * \brief The Relation class
 * Classe abstraite
 */
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
    /*!
     * \brief Relation
     * \param id
     * \param titr
     * \param desc
     * \param orie
     * constructeur
     */
    Relation(const QString& id, const QString& titr, const QString& desc, bool orie=true):
          nbCouples(0), nbMaxCouples(10),id (id), titre(titr), description(desc), orientation(orie) {}
    /*!
     * \brief addCouple
     * \param newCouple
     * ajoute un couple au tableau couples
     */
    void addCouple(Couple* newCouple);
    /*!
     * \brief addCouple
     * \param n1
     * \param n2
     * \param l
     * crée à partir de 2 notes et ajoute le couple au tableau couples
     */
    void addCouple(Notes& n1, Notes& n2, QString l="");

    /*!
     * \brief getId
     * \return 
     */
    const QString& getId() const {return id;}
    /*!
     * \brief getTitre
     * \return 
     */
    const QString& getTitre() const {return titre;}
    /*!
     * \brief getDescription
     * \return 
     */
    const QString& getDescription() const {return description;}
    /*!
     * \brief getOrientation
     * \return 
     */
    bool getOrientation() const {return orientation;}

    /*!
     * \brief setTitre
     * \param newTitre
     * methode virtuelle pure
     */
    virtual void setTitre(const QString& newTitre) = 0;     
    /*!
     * \brief setDescription
     * \param newDescription
     * methode virtuelle pure
     */
    virtual void setDescription(const QString& newDescription) = 0;   
    /*!
     * \brief setOrientation
     * \param boolVal
     * methode virtuelle pure
     */
    virtual void setOrientation(bool boolVal) = 0;                            
    
    /*!
     * \brief ~Relation
     * gère la destruction des couples qui compose la relation
     */
    virtual ~Relation(){
           for (unsigned int i=0; i < nbCouples; i++) delete couples[i];
           delete[] couples;
       }
    /*!
     * \brief The iterator class
     * pour parcourir les couples d'une relation
     */
    class iterator{
        Couple** current;
        iterator(Couple **a):current(a){}

        friend class Relation;

    public:
        /*!
         * \brief iterator
         */
        iterator():current(0){}
        /*!
         * \brief getCurrent
         * \return 
         */
        Couple* getCurrent(){return *current;}
        /*!
         * \brief operator *
         * \return 
         */
        Couple& operator*(){ //pour avoir contenu du double pointeur avec 1 seul *
            return **current;
        }
        /*!
         * \brief operator ++
         * \return 
         */
        iterator &operator++(){
            ++current;
            return *this;
        }

        /*!
         * \brief operator !=
         * \param it
         * \return 
         */
        bool operator!=(iterator it) const{
            return current != it.current;
        }
    };
    /*!
     * \brief begin_relationr
     * \return 
     */
    iterator begin_relationr(){ //1ère case du tableau relation
        return iterator(couples);
    }
    /*!
     * \brief end_relation
     * \return 
     */
    iterator end_relation(){ //case juste après dernière case du tableau relation (condition boucle for : !=m.end)
        return iterator(couples + nbCouples);
    }

};

/*!
 * \brief The RelationNormale class
 * toutes les relations autre que les references
 * hérite de la classe Relation
 */
class RelationNormale: public Relation{  //OK
public:
    /*!
     * \brief RelationNormale
     * \param id
     * \param titr
     * \param desc
     * \param orie
     */
    RelationNormale(const QString& id, const QString& titr, const QString& desc, bool orie=true): Relation(id, titr, desc, orie){}

    /*!
     * \brief setTitre
     * \param newTitre
     */
    void setTitre(const QString& newTitre) {titre = newTitre;}
    /*!
     * \brief setDescription
     * \param newDescription
     */
    void setDescription(const QString& newDescription){description = newDescription;}
    /*!
     * \brief setOrientation
     * \param boolVal
     */
    void setOrientation(bool boolVal){orientation = boolVal;}
};



/*!
 * \brief The RelationPreexistente class
 * gère relation preexistente (on ne la crée pas directement elle dépend du contenu des notes)
 * dans notre cas : relation reference
 * 
 * singleton car on a seulement la relation reference 
 */
class RelationPreexistente: public Relation{
    /*!
     * \brief setTitre
     */
    void setTitre(const QString&){}   
    /*!
     * \brief setDescription
     */
    void setDescription(const QString&){} 
    /*!
     * \brief setOrientation
     */
    void setOrientation(bool){} 
    

    static RelationPreexistente* instance_RelationPreexistente;
    /*!
     * \brief RelationPreexistente
     * \param r
     * recopie interdite (singleton)
     */
    RelationPreexistente(const RelationPreexistente& r);

    ~RelationPreexistente(){}
    /*!
     * \brief operator =
     * \return 
     */
    RelationPreexistente& operator=(const RelationPreexistente&);
    /*!
     * \brief RelationPreexistente
     * constructeur
     * titre et description fixe
     */
    RelationPreexistente(): Relation("Ref","references", "preexistente"){} 

public:
    /*!
     * \brief getRelationPreexistente
     * \return instance unique de RelationPreexistente
     * singleton
     */
    static RelationPreexistente* getRelationPreexistente(){
        if (!instance_RelationPreexistente) instance_RelationPreexistente = new RelationPreexistente;
            return instance_RelationPreexistente;
    }
    /*!
     * \brief libererRelationPreexistente
     * liberer instance unique
     * singleton
     */
    static void libererRelationPreexistente(){
        if (instance_RelationPreexistente){
            delete instance_RelationPreexistente;
            instance_RelationPreexistente = 0;
        }
    }
};





/*!
 * \brief The RelationManager class
 * gère l'ensemble des relations
 * singleton
 */
class RelationManager{
    /*!
     * \brief relations
     * tableau des relations normales
     */
    RelationNormale** relations; 
    unsigned int nbRelations;
    unsigned int nbMaxRelations;
    /*!
     * \brief reference
     * pointeur sur relation preexistente
     */
    RelationPreexistente* reference;
    static RelationManager *instance;
    /*!
     * \brief RelationManager
     */
    RelationManager(const RelationManager&){}
    /*!
     * \brief RelationManager
     */
    RelationManager();
    /*!
     * \brief operator =
     * \return 
     */
    RelationManager& operator=(const RelationManager&);

    ~RelationManager();

public:
    /*!
     * \brief getInstance
     * \return 
     * singleton
     */
    static RelationManager& getInstance();
    /*!
     * \brief libererInstance
     * singleton
     */
    static void libererInstance(); 

    /*!
     * \brief makeRelationId
     * \return 
     * fabrique id unique pour relation
     */
    const QString makeRelationId();
    /*!
      * \brief getRelationNormal
      * \param id
      * \return pointeur sur RelationNormale qui correspond à l'id
      */
     RelationNormale* getRelationNormal(const QString &id);
     /*!
      * \brief getRelationRef
      * \return pointeur sur attribut reference
      */
     RelationPreexistente* getRelationRef() {return reference;}


     
     /*!
      * \brief addRelation
      * \param id
      * \param titre
      * \param desc
      * \param orientation
      * crée et ajoute une relation normale au tableau relations
      */
     void addRelation(QString id, QString titre, QString desc, bool orientation);



     /*!
     * \brief The iterator class
     * iterator pour se deplacer dans les relations normales de RelationManager
     */
    class iterator{
        RelationNormale** current;
        /*!
         * \brief iterator
         * \param a
         */
        iterator(RelationNormale **a):current(a){}

        friend class RelationManager;

    public:
        /*!
         * \brief iterator
         */
        iterator():current(0){}
        /*!
         * \brief getCurrent
         * \return 
         */
        RelationNormale* getCurrent(){return *current;}
        /*!
         * \brief operator *
         * \return 
         */
        RelationNormale& operator*(){ //pour avoir contenu du double pointeur avec 1 seul *
            return **current;
        }
        /*!
         * \brief operator ++
         * \return 
         */
        iterator &operator++(){
            ++current;
            return *this;
        }
        /*!
         * \brief operator !=
         * \param it
         * \return 
         */
        bool operator!=(iterator it) const{
            return current != it.current;
        }
    };
    /*!
     * \brief begin_relationManager
     * \return 
     */
    iterator begin_relationManager(){ //1ère case du tableau relation
        return iterator(relations);
    }
    /*!
     * \brief end_relationManager
     * \return 
     */
    iterator end_relationManager(){ //case juste après dernière case du tableau relation (condition boucle for : !=m.end)
        return iterator(relations + nbRelations);
    }

};

#endif // RELATION_H
