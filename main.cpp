#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Student {
    vector <string> vardai, pavardes;
    vector <int> pazymiai;
    vector <double> galutiniaiVid, galutiniaiMed;
};

int main() {
    Student S;

    meniu:
    cout<<"Pasirinkite ivedimo rezima:"<<endl;
    cout<<"1. Ivedimas ranka;"<<endl;
    cout<<"2. Generuoti pazymius;"<<endl;
    cout<<"3. Generuoti pazymius, vardus, pavardes;"<<endl;
    cout<<"4. Baigti darba."<<endl;

    char pasirinkimas;
    cin>>pasirinkimas;

    switch(pasirinkimas){
    case '1':
        cout<<"Tu pasirinkai pirma varianta."<<endl;
        break;
    case '2':
        cout<<"Tu pasirinkai antra varianta."<<endl;
        break;
    case '3':
        cout<<"Tu pasirinkai trecia varianta."<<endl;
        break;
    case '4':
        cout<<"Tu pasirinkai ketvirta varianta."<<endl;
        break;
    default:
        cout<<"Tokio varianto nera."<<endl;
        goto meniu;
    }



    int studentu_kiekis = 1;      //nuo 1, nes klausiant studento vardo butu numeruojama nuo 1;

    //Ivedinejame studentu vardus ir pavardes tol kol ivedamas NE.
    while (true) {
        cout << "Iveskite " << studentu_kiekis << "-o studento varda ir pavarde arba 'NE' jeigu nebera daugiau studentu." << endl;
        string vardas, pavarde;
        cin >> vardas;

        if (vardas == "NE") {
            break;
        }

        cin >> pavarde;

        if (pavarde == "NE") {
            break;
        }

        S.vardai.push_back(vardas);
        S.pavardes.push_back(pavarde);

        studentu_kiekis++;

        //--------------------------------------------------------------------------------
        //Ivedinejame pazymius
        S.pazymiai.clear();
        cout << "Iveskite studento namu darbu pazymius. Pabaigus juos vardyt, parasykite '-1'." << endl;
        int pazymys, suma = 0, pazymiu_kiekis = 0;
        while (true) {
            cin >> pazymys;
            if (pazymys == -1) {
                break;
            }
            suma += pazymys;
            S.pazymiai.push_back(pazymys);
            pazymiu_kiekis++;
        }

        //----------------------------------------------
        //Ivedamas studento egzamino rezultatas
        int egzas;
        cout << "Iveskite studento egzamino pazymi." << endl;
        cin >> egzas;

        //----------------------------------------------
        //Skaiciujami galutiniai rezultatai
        double galutinisVid;
        galutinisVid = (double(suma) / double(pazymiu_kiekis)) * 0.4 + egzas * 0.6;
        S.galutiniaiVid.push_back(galutinisVid);

        double galutinisMed, mediana;
        sort(S.pazymiai.begin(), S.pazymiai.end());
        if(pazymiu_kiekis % 2 == 0){
            mediana = (S.pazymiai[pazymiu_kiekis / 2] + S.pazymiai [pazymiu_kiekis / 2 - 1]) / 2.0;
        }


        else mediana = S.pazymiai[pazymiu_kiekis / 2];
        galutinisMed = mediana * 0.4 + egzas * 0.6;
        S.galutiniaiMed.push_back(galutinisMed);
        cout << endl;

    }
    cout << endl;

    int t;
    cout << "Jei lenteleje norite galutinio vidurkio spauskite 0, jei medianos - 1" << endl;
    cin >> t;
    cout << endl;

    if(t == 0)
        cout << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << endl;
    else
        cout << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Med.)" << endl;

    for(int i = 0; i < 20 * 3; i++){        //pridetu pakankamai "-", kad gerai atrodytu lentele;
        cout<<"-";
    }
    cout << endl;

    for(int i = 0; i < studentu_kiekis-1; i++){
        if(t == 0)
            cout << left << setw(20) << S.pavardes[i] << setw(20) << S.vardai[i] << setw(20) << fixed <<setprecision(2) << S.galutiniaiVid[i] << endl;
        else
            cout << left << setw(20) << S.pavardes[i] << setw(20) << S.vardai[i] << setw(20) << fixed <<setprecision(2) << S.galutiniaiMed[i] << endl;
    }

    return 0;
}




