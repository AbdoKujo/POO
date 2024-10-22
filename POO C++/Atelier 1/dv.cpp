#include <iostream>
#include <vector>
#include <stdexcept> // pour bad_alloc

using namespace std;

// Fonction qui simule le passage de plusieurs paramètres
void test(const vector<int>& params) {
    cout << "Fonction appelee avec " << params.size() << " parametres." << endl;
}

int main() {
    try {
        size_t i = 1;  // Départ avec 1 paramètre
        size_t step = 100000;  // Augmentation progressive des paramètres (par 100 000)

        // Boucle qui ajoute progressivement des paramètres
        while (true) {
            vector<int> params(i, 1);  // Créer un vecteur avec 'i' paramètres
            test(params);  // Appeler la fonction avec ces paramètres

            i += step;  // Augmenter le nombre de paramètres à chaque itération
        }
    } catch (const bad_alloc& e) {
        // Exception attrapée lorsque la mémoire allouée est insuffisante
        cout << "Erreur d'allocation memoire : " << e.what() << endl;
        cout << "Limite atteinte lors de la tentative avec trop de parametres." << endl;
    }

    return 0;
}