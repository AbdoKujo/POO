#include "Voiture.h"
#include<iostream>

using namespace std;

	//Constructeur par defaut 
	
	Voiture::Voiture() : marque(" Inconnue ") , modele("Inconnu"), annee(0) ,km(0.00),V(0.00){
		cout<<"Tous les attributs sont initialise par defaut"<<endl;	} 
	
	//Constructeur avec parametres
	
	Voiture::Voiture(string ma , string mo , int a , float km , float V){
		this->marque=ma;
		this->modele=mo;
		this->annee=a;
		this->km=km;
		this->V=V;
		cout<<"initialiser la voiture avec des parametre . "<<endl;
	}
	//autre Methode
	void Voiture::accelerer(float V){
		this->V += V;
		cout << "La voiture accelere. Vitesse actuelle : " << this->V << " km/h." << endl;
	}
	void Voiture::freiner(float V){
		this->V -= V;
		if(this->V <= 0.0){
			this->V=0.0;
		}
		cout<<" vitesse a diminue vers  : "<< this->V << " km/h." << endl;
	}
	void Voiture::afficherInfo() const{
		cout<<"Voila les informations sur la voiture : "<<endl;
		cout<<" Marque : "<<marque<<endl;
		cout<<" Modele : "<<modele<<endl;
		cout<<" Annee  : "<<annee<<endl;
		cout<<"Kilometrage : "<<km<<" km"<<endl;
		cout<<"Vitesse actuelle : "<<V<<" km"<<endl;
	}
	void Voiture::avancer(float distance){
		this->km += distance;
		cout<<" la voiture a avance de "<<distance<<" km . Kilometrage actuel : "<<km<<" km"<<endl;
	}
	    // Destructeur
	Voiture::~Voiture(){
		cout<<"La voiture "<<marque<<" "<<modele<<" est detruite."<<endl;
	}

