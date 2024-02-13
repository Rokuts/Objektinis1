#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct studentas{
    string vardas, pavarde;
    int egzas, suma=0;
    double n[10];
    double galutinisVid, galutinisMed;

};

int main()
{

    studentas S[10];
    int n,x,y,*dydis;

    cout<<"Kiek yra studentu (max 10)?"<<endl;
    cin>>y;
    cout<<endl;

    cout<<"Kiek buvo namu darbu? (max 10)"<<endl;
    cin>>x;
    cout<<endl;

    dydis=new int [y];      //Vardo/Pavardes ilgio masyvas

    int a,b;
    for(int i=0;i<y;i++){
        cout<<"Koks "<<i+1<<"-o studento vardas ir pavarde?"<<endl;
        cin>>S[i].vardas>>S[i].pavarde;
        a=(S[i].vardas).size();     //Vardo ilgis
        b=(S[i].pavarde).size();    //Pavardes ilgis
        if(a>b) dydis[i]=a;
        else dydis[i]=b;

        cout<<"Iveskite visus sio studento tarpinius rezultatus."<<endl;
        for(int j=0;j<x;j++){
            cin>>S[i].n[j];
            S[i].suma+=S[i].n[j];
        }

        cout<<"Koks sio studento egzamino rezultatas?"<<endl;
        cin>>S[i].egzas;
        cout<<endl;
    }

    sort(dydis,dydis+y);    //susortinam masyva kad galetyme paimti didziausia skaiciu;

    double mediana;
    for(int i=0;i<y;i++){
        sort(S[i].n,S[i].n+x);
        S[i].galutinisVid=(double(S[i].suma)/double(x))*0.4+(S[i].egzas*0.6);
        if(x%2==0)
            mediana=(S[i].n[x/2]+S[i].n[x/2-1])/2;
        else mediana=S[i].n[x/2];
        S[i].galutinisMed=mediana*0.4+(S[i].egzas*0.6);
    }

    int t;
    cout<<"Jei lenteleje norite galutinio vidurkio spauskite 0, jei medianos - 1"<<endl;
    cin>>t;
    cout<<endl;

    if(t==0) cout<<left<<setw(dydis[y-1]+3)<<"Pavarde"<<setw(dydis[y-1]+3)<<"Vardas"<<setw(dydis[y-1]+3)<<"Galutinis (Vid.)"<<endl;
    else cout<<left<<setw(dydis[y-1]+3)<<"Pavarde"<<setw(dydis[y-1]+3)<<"Vardas"<<setw(dydis[y-1]+3)<<"Galutinis (Med.)"<<endl;

    for(int i=0;i<(dydis[y-1]+3)*3;i++){
        cout<<"-";
    }
    cout<<endl;

    for(int i=0;i<y;i++){
        if(t==0) cout<<left<<setw(dydis[y-1]+3)<<S[i].pavarde<<setw(dydis[y-1]+3)<<S[i].vardas<<setw(dydis[y-1]+3)<<S[i].galutinisVid<<endl;
        else cout<<left<<setw(dydis[y-1]+3)<<S[i].pavarde<<setw(dydis[y-1]+3)<<S[i].vardas<<setw(dydis[y-1]+3)<<S[i].galutinisMed<<endl;
    }


    return 0;
}
