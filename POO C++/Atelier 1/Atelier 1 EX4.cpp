#include<iostream>
//EXERCICE 4
//Q1
#include <cstdlib>
#include <ctime>
using namespace std;
//Q2
int throwDice() {
    return rand() % 6 + 1;
	}
//Q3
int playerTurn() {
    int choix, score = 0;
    do {
        cout << "Voulez-vous lancer 1 ou 2 des ? " << endl;
        cin >> choix;
    } while (choix != 1 && choix != 2); 
    if (choix == 1) {
        score += throwDice();
    } else {
        int de1 = throwDice() , de2 = throwDice();
        if (de1 == de2) {
            score -= (de1 + de2); 
        } else {
            score += de1 + de2;
        }
    }
    return score;
}
//UNE fonction qui determine The winner
int winner(int a, int b) {
    if (a < b) return 1;
    else return 2;
}
//Q4
int main() {
    srand(time(0));  
    int i = 1, score1 = 0, score2 = 0;
    while (score1 < 30 && score2 < 30) {
        cout << "\nRound : " << i << endl;
        cout << "Player 1 Turn : "; score1 += playerTurn(); 
        cout << "Player 2 Turn : "; score2 += playerTurn();
        cout << "Score1 = " << score1 << "  Score2 = " << score2 << endl;
        i++;
    }
    if (score1 >= 30 && score2 >= 30) {
        cout << "There is no winner" << endl;
        return 0;
    }
    cout << "The winner is Player " << winner(score1, score2) << endl;
    return 0;
}