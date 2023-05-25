#include "Joueur.h"

void Poser_carte_c(Carte_c c,id_joueur id, Jeu& jeu){
    //Logique de pose d'une carte classique sur le plateau
    bool carteTrouvee = false;
    for (auto it = cartes_c.begin(); it != cartes_c.end();++it){
        if (it == c){
            carteTrouvee = true;
            cartes_c.erase(it);
            setNb_cartes();
            break;
        }
    }
    if (carteTrouve){
        //jeu.Poser_carte_c(c,id);
    }else {
        std::cout << "La carte n'appartient pas à la main du joueur !" << std::endl;
    }
}


void Poser_carte_t(Carte_t c, id_joueur id, Jeu& jeu) {
    //Logique de pose d'une carte tactique sur le plateau
    bool carteTrouvee = false;
    for (auto it = cartes_t.begin(); it != cartes_t.end(); ++it) {
        if (it == c) {
            carteTrouvee = true;
            cartes_t.erase(it);
            setNb_cartes();
            break;
        }
    }
    if (carteTrouve) {
        //jeu.Poser_carte_t(c, id);
    }
    else {
        std::cout << "La carte n'appartient pas à la main du joueur !" << std::endl;
    }
}

Carte_c Pioche_c(Jeu& jeu){
    //Logique de la pioche d'une carte classique
    Carte_c carte;
    /*if (!jeu.getPioche_c().estVide()) {
        carte = jeu.getPioche_c().piocher();
        cartes_c.push_back(carte);
        setNb_cartes();
    }*/
    return carte;
}

Carte_t Pioche_t(Jeu& jeu) {
    //Logique de la pioche d'une carte classique
    Carte_t carte;
    /*if (!jeu.getPioche_t().estVide()) {
        carte = jeu.getPioche_t().piocher();
        cartes_t.push_back(carte);
        setNb_cartes();
    }
    */
    return carte;
}

