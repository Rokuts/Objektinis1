#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>  //random
#include <cctype> // darbas su simboliais

using namespace std;

struct Studentas {
    string vardas, pavarde;
    int* pazymiai;
    int pazymiu_kiekis;
    double galutiniaiVid, galutiniaiMed;
};

struct Universitetas{
    Studentas* studentai;
    int studentu_kiekis;
};

void add_student_uni(Universitetas& uni, Studentas& stud){
    uni.studentu_kiekis++;
    Studentas* new_studentai= new Studentas[uni.studentu_kiekis];       //susikurem nauja masyva, kuris yra seno dydis+1;

    for(int i=0;i<uni.studentu_kiekis-1;i++){           //perkeliame is seno masyvo i nauja, jau esamus studentus (kas nepasimestu duomenys);
        new_studentai[i]=uni.studentai[i];
    }

    new_studentai[uni.studentu_kiekis-1]=stud;          //itraukiamas naujas studentas i masyvo gala;

    if(uni.studentai!=nullptr){                         //atlaisviname vieta atmintyje;
        delete[] uni.studentai;
    } 
    uni.studentai=new_studentai;                        //priskiriame nauja masyva kaip pagrindini universiteto masyva su visais pries tai itrauktais duomenimis;
}

void add_mark_stud(Studentas& stud, int& pazymys){
    stud.pazymiu_kiekis++;
    int* new_pazymiai = new int[stud.pazymiu_kiekis];       //susikurem nauja masyva, kuris yra seno dydis+1;

    for(int i=0;i<stud.pazymiu_kiekis-1;i++){           //perkeliame is seno masyvo i nauja, jau esamus pazymius (kas nepasimestu duomenys);
        new_pazymiai[i]=stud.pazymiai[i];
    }

    new_pazymiai[stud.pazymiu_kiekis-1]=pazymys;          //itraukiamas naujas pazymys i masyvo gala;

    if(stud.pazymiai!=nullptr){                         //atlaisviname vieta atmintyje;
        delete[] stud.pazymiai;
    } 
    stud.pazymiai=new_pazymiai;                        //priskiriame nauja masyva kaip pagrindini studento masyva su visais pries tai itrauktais duomenimis;
}

bool ar_tik_raides(const string& zodis) {
    for (char simbolis : zodis) {
        if (!isalpha(simbolis)) {
            return false;
        }
    }
    return true;
}

const int vardai_kiekis=15;
const int pavardes_kiekis=20;

static const string vardai[] = {

    "Dominykas", "Deividas", "Matas", "Lukas", "Nojus",
    "Erikas", "Danielis", "Tomas", "Mindaugas", "Edvinas",
    "Gabrielius", "Martynas", "Mantas", "Azuolas", "Benas"
};

static const string pavardes[] = {

    "Kazlauskas", "Petrauskas", "Jankauskas", "Antanaitis", "Baksys",
    "Balciunas", "Baranauskas", "Bartkus", "Dambrauskas", "Gudauskas",
    "Kavaliauskas", "Kazakevicius", "Lukauskas", "Maciulis", "Navickas",
    "Paulauskas", "Rutkauskas", "Simkus", "Urbonas", "Valentukevicius"
};

int atsitiktinis_skaicius(int min, int max) {

    // Apskaiciujam intervala;
    int range = max - min + 1;
    int random_num;

    random_num = rand() % range;

    return min + random_num;
}

int atsitiktinis_pazymys() {

    // Diapazonas yra 10 (nuo 1 iki 10 imtinai)
    int range = 10 - 1 + 1;

    // Deklaruojame kintamąjį saugoti atsitiktiniam skaičiui
    int atsitiktinis_skaicius;

    // Paemam random skaiciu
    atsitiktinis_skaicius = rand() % range;

    // Grąžinkite atsitiktinį skaičių tarp 1 ir 10 imtinai
    return 1 + atsitiktinis_skaicius;
}



int main() {
    srand(static_cast<unsigned int>(time(0)));     //Kiekvienu random generuojami skaiciai yra kitokie;

    Universitetas Uni={nullptr,0};      //del saugumo, kad tuscias universitetas(struktura);

    meniu:
    cout<<"Pasirinkite ivedimo rezima:"<<endl;
    cout<<"1. Ivedimas ranka;"<<endl;
    cout<<"2. Generuoti pazymius;"<<endl;
    cout<<"3. Generuoti pazymius, vardus, pavardes;"<<endl;
    cout<<"4. Baigti darba."<<endl;

    char pasirinkimas;
    cin>>pasirinkimas;

    switch(pasirinkimas){
    //----------------------------------------------------------------------------------
    case '1':
        {
        cout<<"Tu pasirinkai pirma varianta."<<endl;

        int studentu_kiekis = 1;      //nuo 1, nes klausiant studento vardo butu numeruojama nuo 1;

        //Ivedinejame studentu vardus ir pavardes tol kol ivedamas NE.
        while (true) {
            cout << "Iveskite " << studentu_kiekis << "-o studento duomenis. Jei norite nutraukti parasykite 'NE'." << endl;
            string vardas, pavarde;

            while(true){
                cout<<"Iveskite studento varda: ";
                cin>>vardas;
                if(ar_tik_raides(vardas))
                    break;
                cout<<"!!!Rasta klaida!!! Bandykite dar karta."<<endl;
            }

            if (vardas == "NE") {
                break;
            }

            while(true){
                cout<<"Iveskite studento pavarde: ";
                cin>>pavarde;
                if(ar_tik_raides(pavarde))
                    break;
                cout<<"!!!Rasta klaida!!! Bandykite dar karta."<<endl;
            }

            if (pavarde == "NE") {
                break;
            }


            Studentas stud={vardas,pavarde,nullptr,0,0,0};        //vardas ir pavarde egzistuoja, o pazymiai(nullptr), pazymiu kiekis, mediana, vidurki nunulinam;

            studentu_kiekis++;

            //--------------------------------------------------------------------------------
            //Ivedinejame pazymius

            ivesti_pazymius:

            cout << "Iveskite studento namu darbu pazymius. Pabaigus juos vardyt, parasykite '-1'." << endl;
            int pazymys, suma = 0, pazymiu_kiekis = 0;
            while (true) {
                cin >> pazymys;

                if(cin.fail()){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');    //isvalome is atminties likusia vartotojo ivesti;
                    cout<<"!!!Klaida. Netinkama skaiciaus ivestis!!!"<<endl;
                    goto ivesti_pazymius;
                }

                if (pazymys == -1) {
                    break;
                }
                suma += pazymys;
                add_mark_stud(stud,pazymys);
                
                pazymiu_kiekis++;
                if(pazymys>10||pazymys<0){
                    cout<<"!!!Klaida, pazymiu intervalas 1-10!!!"<<endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');    //isvalome is atminties likusia vartotojo ivesti;
                    goto ivesti_pazymius;
                }

            }
            if(pazymiu_kiekis==0){
                cout<<"Pamirsote ivesti pazymius."<<endl;
                goto ivesti_pazymius;
            }



            //----------------------------------------------
            //Ivedamas studento egzamino rezultatas
            ivesti_egza:
            int egzas;
            cout << "Iveskite studento egzamino pazymi." << endl;
            cin >> egzas;
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');    //isvalome is atminties likusia vartotojo ivesti;
                cout<<"!!!Klaida. Netinkama skaiciaus ivestis!!!"<<endl;
                goto ivesti_egza;
            }

            if(egzas>10||egzas<0){
                cout<<"!!!Klaida, pazymiu intervalas 1-10!!!"<<endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');    //isvalome is atminties likusia vartotojo ivesti;
                goto ivesti_egza;
            }

            //----------------------------------------------
            //Skaiciujami galutiniai rezultatai
            double galutinisVid;
            galutinisVid = (double(suma) / double(pazymiu_kiekis)) * 0.4 + egzas * 0.6;
            stud.galutiniaiVid=galutinisVid;

            double galutinisMed, mediana;
            sort(stud.pazymiai, stud.pazymiai+stud.pazymiu_kiekis);
            if(pazymiu_kiekis % 2 == 0){
                mediana = (stud.pazymiai[pazymiu_kiekis / 2] + stud.pazymiai[pazymiu_kiekis / 2 - 1]) / 2.0;
            }


            else mediana = stud.pazymiai[pazymiu_kiekis / 2];
            galutinisMed = mediana * 0.4 + egzas * 0.6;
            stud.galutiniaiMed=galutinisMed;
            cout << endl;

            add_student_uni(Uni,stud);

        }
        cout << endl;
        goto meniu;
        break;
        }
    //-------------------------------------------------------------------------------------------------------
    case '2':
        {
        cout<<"Tu pasirinkai antra varianta."<<endl;

        int studentu_kiekis = 1;      //nuo 1, nes klausiant studento vardo butu numeruojama nuo 1;

        //Ivedinejame studentu vardus ir pavardes tol kol ivedamas NE.
        while (true) {
            cout << "Iveskite " << studentu_kiekis << "-o studento duomenis. Jei norite nutraukti parasykite 'NE'." << endl;
            string vardas, pavarde;

            while(true){
                cout<<"Iveskite studento varda: ";
                cin>>vardas;
                if(ar_tik_raides(vardas))
                    break;
                cout<<"!!!Rasta klaida!!! Bandykite dar karta."<<endl;
            }

            if (vardas == "NE") {
                break;
            }

            while(true){
                cout<<"Iveskite studento pavarde: ";
                cin>>pavarde;
                if(ar_tik_raides(pavarde))
                    break;
                cout<<"!!!Rasta klaida!!! Bandykite dar karta."<<endl;
            }

            if (pavarde == "NE") {
                break;
            }

            Studentas stud={vardas,pavarde,nullptr,0,0,0};

            studentu_kiekis++;

            //--------------------------------------------------------------------------------
            //Ivedinejame pazymius
            kiekis_pazimiu:
            int pazymiu_kiekis;
            cout<<"Kiek pazymiu studentui sugeneruoti?"<<endl;
            cin>>pazymiu_kiekis;

            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');    //isvalome is atminties likusia vartotojo ivesti;
                cout<<"!!!Klaida. Netinkama skaiciaus ivestis!!!"<<endl;
                goto kiekis_pazimiu;
            }

            if(pazymiu_kiekis<1){
                cout<<"!!!Klaida, pazymiu kiekis naturalus skaicius!!!"<<endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');    //isvalome is atminties likusia vartotojo ivesti;
                goto kiekis_pazimiu;
            }

            int suma=0;
            
            cout<<"Pazymiai: ";
            for(int i=0;i<pazymiu_kiekis;i++){
                int pazymys=atsitiktinis_pazymys();
                add_mark_stud(stud,pazymys);
                cout<<pazymys<<" ";
                suma+=pazymys;

            }
            cout<<endl;

            //----------------------------------------------
            //Ivedamas studento egzamino rezultatas
            int egzas=atsitiktinis_pazymys();
            cout<<"Egzamino pazymys: "<<egzas<<endl;

            //----------------------------------------------
            //Skaiciujami galutiniai rezultatai
            double galutinisVid;
            galutinisVid = (double(suma) / double(pazymiu_kiekis)) * 0.4 + egzas * 0.6;
            stud.galutiniaiVid=galutinisVid;

            double galutinisMed, mediana;
            sort(stud.pazymiai, stud.pazymiai+stud.pazymiu_kiekis);
            if(pazymiu_kiekis % 2 == 0){
                mediana = (stud.pazymiai[pazymiu_kiekis / 2] + stud.pazymiai[pazymiu_kiekis / 2 - 1]) / 2.0;
            }


            else mediana = stud.pazymiai[pazymiu_kiekis / 2];
            galutinisMed = mediana * 0.4 + egzas * 0.6;
            stud.galutiniaiMed=galutinisMed;
            cout << endl;

            add_student_uni(Uni,stud);


        }
        cout << endl;
        goto meniu;
        break;
        }
    //------------------------------------------------------------------------------------------------------------
    case '3':
        {
        cout<<"Tu pasirinkai trecia varianta."<<endl;

        kiekis_studentu:
        int studentu_kiekis;
        cout<<"Kiek yra studentu?"<<endl;
        cin>>studentu_kiekis;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    //isvalome is atminties likusia vartotojo ivesti;
            cout<<"!!!Klaida. Netinkama skaiciaus ivestis!!!"<<endl;
            goto kiekis_studentu;
        }

        if(studentu_kiekis<0){
            cout<<"!!!Klaida, studentu kiekis naturalus skaicius arba 0!!!"<<endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    //isvalome is atminties likusia vartotojo ivesti;
            goto kiekis_studentu;
        }


        for(int i=0;i<studentu_kiekis;i++){
            cout<<"Vardas, pavarde: ";
            string vardas=vardai[atsitiktinis_skaicius(0,vardai_kiekis-1)];      //vardai[atsitiktinis_skaicius(0,14)];
            string pavarde=pavardes[atsitiktinis_skaicius(0,pavardes_kiekis-1)];      //pavardes[atsitiktinis_skaicius(0,19)];
            cout<<vardas<<", "<<pavarde<<endl;
            
            Studentas stud={vardas,pavarde,nullptr,0,0,0};

            //--------------------------------------------------------------------------------
            //Ivedinejame pazymius
            int pazymiu_kiekis;
            pazkiek:
            cout<<"Kiek pazymiu studentui sugeneruoti?"<<endl;
            cin>>pazymiu_kiekis;

            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');    //isvalome is atminties likusia vartotojo ivesti;
                cout<<"!!!Klaida. Netinkama skaiciaus ivestis!!!"<<endl;
                goto pazkiek;
            }

            if(pazymiu_kiekis<1){
                cout<<"!!!Klaida, pazymiu kiekis naturalus skaicius!!!"<<endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');    //isvalome is atminties likusia vartotojo ivesti;
                goto pazkiek;
            }

            int suma=0;
            
            cout<<"Pazymiai: ";
            for(int i=0;i<pazymiu_kiekis;i++){
                int pazymys=atsitiktinis_pazymys();
                cout<<pazymys<<" ";
                add_mark_stud(stud,pazymys);
                suma+=pazymys;

            }
            cout<<endl;

            //----------------------------------------------
            //Ivedamas studento egzamino rezultatas
            int egzas=atsitiktinis_pazymys();
            cout<<"Egzamino pazymys: "<<egzas<<endl;

            //----------------------------------------------
            //Skaiciujami galutiniai rezultatai
            double galutinisVid;
            galutinisVid = (double(suma) / double(pazymiu_kiekis)) * 0.4 + egzas * 0.6;
            stud.galutiniaiVid=galutinisVid;

            double galutinisMed, mediana;
            sort(stud.pazymiai,stud.pazymiai+stud.pazymiu_kiekis);
            if(pazymiu_kiekis % 2 == 0){
                mediana = (stud.pazymiai[pazymiu_kiekis / 2] + stud.pazymiai [pazymiu_kiekis / 2 - 1]) / 2.0;
            }


            else mediana = stud.pazymiai[pazymiu_kiekis / 2];
            galutinisMed = mediana * 0.4 + egzas * 0.6;
            stud.galutiniaiMed=galutinisMed;
            cout << endl;

            add_student_uni(Uni,stud);
        }
        cout << endl;
        goto meniu;
        break;
        }
    //-------------------------------------------------------------------------------------------------------
    case '4':
        {

        cout<<"Tu pasirinkai ketvirta varianta."<<endl;

        Vidmed:
        int t;
        cout << "Jei lenteleje norite galutinio vidurkio spauskite 0, jei medianos - 1" << endl;
        cin >> t;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    //isvalome is atminties likusia vartotojo ivesti;
            cout<<"!!!Klaida. Netinkama skaiciaus ivestis!!!"<<endl;
            goto Vidmed;
        }

        if(t!=0&&t!=1){
            cout<<"!!!Klaida, iveskite 0 arba 1!!!"<<endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    //isvalome is atminties likusia vartotojo ivesti;
            goto Vidmed;
        }

        cout << endl;

        if(t == 0)
            cout << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << endl;
        else
            cout << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Med.)" << endl;

        for(int i = 0; i < 20 * 3; i++){        //pridetu pakankamai "-", kad gerai atrodytu lentele;
            cout<<"-";
        }
        cout << endl;

        for(int i = 0; i < Uni.studentu_kiekis; i++){
            if(t == 0)
                cout << left << setw(20) << Uni.studentai[i].pavarde << setw(20) << Uni.studentai[i].vardas << setw(20) << fixed <<setprecision(2) << Uni.studentai[i].galutiniaiVid << endl;
            else
                cout << left << setw(20) << Uni.studentai[i].pavarde << setw(20) << Uni.studentai[i].vardas << setw(20) << fixed <<setprecision(2) << Uni.studentai[i].galutiniaiMed << endl;
        }

        break;
        }
    //------------------------------------------------------------------------------------------------------------
    default:
        cout<<"Tokio varianto nera."<<endl;
        goto meniu;
    }

    return 0;
}




