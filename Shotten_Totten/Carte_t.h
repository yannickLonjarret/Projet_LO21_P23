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

enum types {elite, combat, ruse};

class Carte_tException {
	string info;
public:
	Carte_tException(const string str) { info = str; }
	const string getInfo() const { return info; }
};


class Carte_t : public Carte
{
protected:
    types type;
    string nom;
public:
    Carte_t(types t, string n):type(t), nom(n){}
    ~Carte_t() = default;
    types getType() const {return type;}
    string getNom() const {return nom;}
    void setType(types valeur){type = valeur;}
    void setNom(string name){nom = name;}
};

class TroupeElite : public Carte_t
{
private:
    int val_deb;
    int val_fin;
public:
    TroupeElite(types t, string n, int vd, int vf):Carte_t(t, n), val_deb(vd), val_fin(vf){}
    ~TroupeElite() = default;
    int getDebut() const {return val_deb;}
    int getFin() const {return val_fin;}
    void setDebut(int v){val_deb = v;}
    void setFin(int v){val_fin = v;}
    void setAll(int vd, int vf){val_deb = vd; val_fin = vf;}
    Carte_c& definir_carte(int v, const string& c);
}

ostream& operator<<(ostream& f, const TroupeElite& c);

class ModeCombat : public Carte_t
{
private:
    int nb_cartes;
	vector<Combinaison*> victoirePossible;

public:
    ModeCombat(types t, string n, int nb, vector<Combinaison*> combi) : Carte_t(t, n), nb_cartes(nb), victoirePossible(combi){}
    ~ModeCombat() = default;
    int getNbCartes() const {
        return nb_cartes;
    }
    const vector<Combinaison*>& getCombinaison() const {
        return victoirePossible;
    }
};

class Ruse : Carte_t
{
private:
    vector<int> actions;
public:
    Ruse(types t, string n, vector<int> suite_actions) : Carte_t(t, n), actions(suite_actions){}
    ~Ruse() = default;
    const vector<int>& getActions() const{
        return actions;
    }
    void addAction(int a){
        actions.push_back(a);
    }
};

#endif // !CARTES_T_H



