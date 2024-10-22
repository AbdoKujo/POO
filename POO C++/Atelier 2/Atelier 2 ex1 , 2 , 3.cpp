#include <iostream>

using namespace std;
//Exercice 1
int i=0;
void Nappele(){
	i++;
	cout<<"appel numero " <<i<<endl;
}
//Exercice 2
int M2(int x){
	return (x%2==0) ? 2 : 0;
}
int M3(int x){
	return (x%3==0) ? 3 : 0;
}
int main(){
	int n;
	cout<<"entrer un nombre"<<endl;
	cin>>n;
	if(M2(n)==2) cout<<"il est paire"<<endl;
	else cout<<"il est impaire"<<endl;
	if(M3(n)==3){
	cout<<"il est multiple de 3"<<endl;
	if(n%6==0) cout<<"il est multiple de 6"<<endl;
	}
//Exercice 3

//en utilisant uniquement le « formalisme tableau »
    int T[10];
    cout<<"entrez 10 nombres entiers "<<endl;
    for(i=0;i<10;i++){
    	cin>>T[i];
	}
	int max=T[0],min=T[0];
	for(int i=1;i<10;i++){
    	if(T[i]<min) min=T[i];
    	if(T[i]>max) max=T[i];	
	}
	cout<<"le plus grand est : "<<max<<endl<<"le plus petit est : "<<min<<endl;
//en utilisant le « formalisme pointeur »
    int *Td ;
    int *j;
    Td=new int [10];
	cout<<"entrez 10 nombres entiers"<<endl;
    for(j= Td ;j<Td+10;j++){
    	cin>> *j;
	}
	max=min= *T;
	for( j=Td+1;j<Td+10;j++){
    	if(*j <min) min= *j;
    	if(*j >max) max= *j;	
	}
	cout<<"le plus grand est : "<<max<<endl<<"le plus petit est : "<<min<<endl;
	delete[] Td;
	return 0;
}