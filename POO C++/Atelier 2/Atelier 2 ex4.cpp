#include<iostream>

using namespace std;

int main(){
	int n,i ;
	cout<<"entrez la taille de tableau "<<endl;
	cin>>n;
	int *T=new int[n];
	cout<<"remplir le tableau : "<<endl;
	for( i=0;i<n;i++) cin>>T[i];
	int *T2=new int[n];
	for(i=0;i<n;i++) T2[i]=T[i] * T[i];
	delete[] T;
	for(i=0 ; i<n; i++) cout<<"T carre ["<<i<<"] = "<<T2[i]<<endl;
	delete[] T2;	
}