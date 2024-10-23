#ifndef VOITURE_H
#define VOITURE_H
#include<iostream>
#include<string>
using namespace std;

class Voiture
{
	private:
		string marque;
		string modele;
		int annee;
		float km;//kilometrage
		float V;//vitesse
	public:
		//Constructeur par defaut 
	Voiture();
	    //Constructeur avec parametres
	Voiture(string ma , string mo , int a , float k , float v);
	    //autre Methode
	void accelerer(float v); 
	void freiner(float v);
	void afficherInfo() const ;
	void avancer(float distance);
	    // Destructeur
	~Voiture();  
};

#endif
#ifndef VOITURE_H
#define VOITURE_H

class Voiture
{
	public:
	protected:
};

#endif
