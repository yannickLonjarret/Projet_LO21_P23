#pragma once
#include "Carte.h"
#ifndef CARTES_T_H
#define CARTES_T_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "Combinaison.h"
#include "Carte_c.h"

/// @brief Enumeration of the different types of tactical cards
enum types {elite, combat, ruse};

/// @brief This class represents errors due to a misuse of a function of Carte_t class
class Carte_tException {
	/// Error raised
	string info;
public:
	/// @brief Contructor initializes the string 'info'
	/// @param str : the message returned for this error
	Carte_tException(const string str) { info = str; }

	/// @brief Allows the user to access the message associated to the error
	/// @return The message associated to the error raised
	const string getInfo() const { return info; }
};

/// @brief Carte_t represents tactical cards
class Carte_t : public Carte
{
protected:
    /// @brief The type of the card
    types type;

    /// @brief The name of the card
    string nom;
public:
    /// @brief Constructor which initializes a Carte_t object
    /// @param t : type of the card
    /// @param n : name of the card
    Carte_t(types t, string n):type(t), nom(n){}

    /// @brief Default destructor
    ~Carte_t() = default;

    /// @brief Allows the user to get the type of the card
    /// @return the type of the card
    types getType() const {return type;}

    /// @brief Allows the user to get the name of the card
    /// @return the name of the card
    string getNom() const {return nom;}

    /// @brief Allows the user to change the type of the card
    /// @param valeur : the desired type of the card
    void setType(types valeur){type = valeur;}

    /// @brief Allows the user to change the name of the card
    /// @param name : the desired name of the card
    void setNom(string name){nom = name;}
};

/// @brief TroupeElite represents cards which correspond to Troupe d'Elite cards (playable as clan cards)
class TroupeElite : public Carte_t, public Carte_c
{
private:
    /// @brief The minimum value this card is allowed to take
    int val_deb;

    /// @brief The maximum value this card is allowed to take
    int val_fin;
public:
    /// @brief Constructor of a TroupeElite card
    /// @param t : type of the card
    /// @param n : name of the card
    /// @param v : value of the card
    /// @param c : color of the card
    /// @param vd : minimum value
    /// @param vf : maximum value
    TroupeElite(types t, string n, int v, const string& c, int vd, int vf):Carte_t(t, n), Carte_c(v, c), val_deb(vd), val_fin(vf){}
    
    /// @brief Default destructor
    ~TroupeElite() = default;
    
    /// @brief Allows the user to get the minimum value the card can take
    /// @return the minimum value
    int getDebut() const {return val_deb;}
    
    /// @brief Allows the user to get the maximum value the card can take
    /// @return the maximum value
    int getFin() const {return val_fin;}
    
    /// @brief Allows the user to change the minimum value takeable
    /// @param v : the desired minimum value
    void setDebut(int v){val_deb = v;}
    
    /// @brief Allows the user to change the maximum value takeable
    /// @param v : the desired maximum value
    void setFin(int v){val_fin = v;}
    
    /// @brief Allows the user to change both the minimum and the maximum values takeable
    /// @param vd : minimum value
    /// @param vf : maximum value
    void setAll(int vd, int vf){val_deb = vd; val_fin = vf;}
    
    /// @brief Allows the user to define the TroupeElite card to a Carte_c card (to claim)
    /// @param v : the value the card has to take
    /// @param c : the color the card has to take
    /// @return a Carte_c object reference
    Carte_c& definir_carte(int v, const string& c);
};

/// @brief Print operator overload to display the card
/// @param f : the output stream
/// @param c : the card to display
/// @return the output stream with the card displayed
ostream& operator<<(ostream& f, const TroupeElite& c);

/// @brief ModeCombat represents cards 'Mode de Combat' (playable on a Tuile)
class ModeCombat : public Carte_t
{
private:
    /// @brief The number of cards to be able to claim the Tuile object where the card will be played
    int nb_cartes;

	/// @brief The vector of the different combinations accepted for the Tuile object where the card will be played
	vector<Combinaison*> victoirePossible;

public:
    /// @brief Constructor of a ModeCombat card
    /// @param t : the type of the card
    /// @param n : the name of the card
    /// @param nb : the number of cards (in order to claim the Tuile object)
    /// @param combi : the vector of Combinaison objects accepted (in order to claim the Tuile object)
    ModeCombat(types t, string n, int nb, vector<Combinaison*> combi) : Carte_t(t, n), nb_cartes(nb), victoirePossible(combi){}
    
    /// @brief Default destructor
    ~ModeCombat() = default;
    
    /// @brief Allows the user to get the number of cards
    /// @return the number of card 
    int getNbCartes() const {
        return nb_cartes;
    }
    
    /// @brief Allows the user to get the Combinaison vector
    /// @return a reference on the Combinaison objects vector
    const vector<Combinaison*>& getCombinaison() const {
        return victoirePossible;
    }
};

/// @brief Ruse represents cards Ruses (which add different actions to the player's turn)
class Ruse : Carte_t
{
private:
    /// @brief Represents a vector which contains all the permitted actions of the card
    vector<int> actions;
public:
    /// @brief Constructor of a Ruse card
    /// @param t : the type of the card
    /// @param n : the name of the card
    /// @param suite_actions : a vector of the different actions permitted by this card
    Ruse(types t, string n, vector<int> suite_actions) : Carte_t(t, n), actions(suite_actions){}
    
    /// @brief Default destructor
    ~Ruse() = default;
    
    /// @brief Allows the user to get the actions of the card
    /// @return the vector of the different actions
    const vector<int>& getActions() const{
        return actions;
    }

    /// @brief Allows the user to add an action in the vector actions
    /// @param a : the action to add
    void addAction(int a){
        actions.push_back(a);
    }
};

#endif // !CARTES_T_H



