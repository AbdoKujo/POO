#include<iostream>

using namespace std;

int main(){
    int* T=new int[10];int* i;
	cout<<"Taper 10 entier "<<endl;
	for( i = T ; i< T+10 ; i++){
		cin>>*i;
	}
	bool echange;int c=0;
	do{
		echange=false;
		for( i=T ; i<T+9; i++){
			if(*i > *(i+1)){
				int temp= *i;
				*i= *(i+1);
				*(i+1)=temp;
				echange = true;
				c++;
			}
		}
		cout<<"parcour "<<c<<" : ";
		for(i=T ; i<T+10 ; i++){
			cout<<*i<<" "; // Afficher chaque element avec un pointeur
		}
		cout<<endl;
	}while(echange); // repeter tant qu'il ya des échange
	
//Affichage du tableau trié
    cout<<" "<<c<<" nombre d echange"<<"\nTableau trie : ";
    for(i=T ; i<T+10 ; i++) cout<<*i<<" ";
    cout<<endl;
    delete[] T;
    return 0;
}