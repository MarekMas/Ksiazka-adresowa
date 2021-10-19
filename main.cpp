#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <cstdlib>

using namespace std;

struct Uzytkownik {
    int id;
    string nazwa, haslo;
};

struct Adresat {
    int id = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

char wybierzOpcjeZMenu(int idZalogowanegoUzytkownika);
Uzytkownik rejestracja(vector <Uzytkownik> uzytkownicy);
int logowanie(vector <Uzytkownik> uzytkownicy);
string wyodrebnijPoleWPobranejLinii(string &linia);
string sprawdzPoleWPobranejLinii(string linia, int nrPola);
void usunAdresataZPliku(Adresat adresat);
void dodajAdresataDoPliku(Adresat adresat, int idZalogowanegoUzytkownika);
void zmienDaneAdresataWPliku(Adresat adresat, int idZalogowanegoUzytkownika);
void zapiszUzytkownicyDoPliku(vector<Uzytkownik> uzytkownicy);
int znajdzidOstatniegoAdresata(string linia);
int pobierzAdresatowZPliku(vector<Adresat>& adresaci, int idZalogowanegoUzytkownika);
void pobierzUzytkownikowZPliku(vector<Uzytkownik>& uzytkownicy);
void dodajAdresata(vector<Adresat>& adresaci, int idOstatniegoAdresata, int idZalogowanegoUzytkownika);
void wyswietlTegoAdresata (Adresat tenAdresat);
void wyswietlWszystkichAdresatow(vector<Adresat> adresaci);
void wyswietlAdresataImie(vector<Adresat> adresaci);
void wyswietlAdresataNazwisko(vector<Adresat> adresaci);
int znajdzAdresataPoID(vector<Adresat> adresaci, int numerID);
void usunAdresata(vector<Adresat>& adresaci);
void edytujAdresata(vector<Adresat>& adresaci, int idZalogowanegoUzytkownika);
void zmianaHasla(vector<Uzytkownik>& uzytkownicy, int idZalogowanegoUzytkownika);

int main() {
    vector <Uzytkownik> uzytkownicy;
    vector<Adresat> adresaci;
    int idZalogowanegoUzytkownika = 0;
    int idOstatniegoAdresata;
    pobierzUzytkownikowZPliku(uzytkownicy);
    while(true) {
        if(idZalogowanegoUzytkownika == 0) {
            switch  (wybierzOpcjeZMenu(idZalogowanegoUzytkownika)) {
            case '1':
                uzytkownicy.push_back(rejestracja(uzytkownicy));
                zapiszUzytkownicyDoPliku(uzytkownicy);
                break;
            case '2':
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
                idOstatniegoAdresata = pobierzAdresatowZPliku(adresaci, idZalogowanegoUzytkownika);
                break;
            case '9':
                exit(0);
            }
        } else {
            switch (wybierzOpcjeZMenu(idZalogowanegoUzytkownika)) {
            case '1':
                dodajAdresata(adresaci, idOstatniegoAdresata, idZalogowanegoUzytkownika);
                idOstatniegoAdresata++;
                break;
            case '2':
                wyswietlAdresataImie(adresaci);
                break;
            case '3':
                wyswietlAdresataNazwisko(adresaci);
                break;
            case '4':
                wyswietlWszystkichAdresatow(adresaci);
                cout << "\n\n\nAby wyj˜† naci˜nij Enter";
                getchar();
                getchar();
                break;
            case '5':
                usunAdresata(adresaci);
                break;
            case '6':
                edytujAdresata(adresaci, idZalogowanegoUzytkownika);
                break;
            case '7':
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
                zapiszUzytkownicyDoPliku(uzytkownicy);
                break;
            case '9':
                adresaci.clear();
                idZalogowanegoUzytkownika = 0;
                break;
            }
        }
    }
    return 0;
}

char wybierzOpcjeZMenu(int idZalogowanegoUzytkownika) {
    system("cls");
    char n;
    cout << "KSIAZKA ADRESOWA" << endl;
    cout << "================" << endl;
    if (idZalogowanegoUzytkownika ==0) {
        cout << "1. Rejestracja\n2. Logowanie\n9. Zakoäcz program.\n";
    } else {
        cout << "1. Dodaj adresata\n2. Wyszukaj po imieniu\n3. Wyszukaj po nazwisku\n4. Wy˜wietl wszystkich adresat¢w\n";
        cout << "5. Usuä adresata\n6. Edytuj adresata\n7. Zmieä hasˆo\n9. Wyloguj si©\n";
    }
    cout << "Tw¢j wyb¢r: ";
    cin >> n;
    return n;
}

Uzytkownik rejestracja(vector <Uzytkownik> uzytkownicy) {
    system("cls");
    string nazwa, haslo;
    int iloscUzytkownikow = uzytkownicy.size();

    cout << "REJESTRACJA" << endl;
    cout << "===========" << endl;

    cout << "Podaj nazw© u¾ytkownika: ";
    cin >> nazwa;
    int i = 0;

    while(i < iloscUzytkownikow) {
        if(uzytkownicy[i].nazwa == nazwa) {
            cout << "Taki u¾ytkownik istnieje. Wpisz inn¥ nazw© u¾ytkownika: ";
            cin >> nazwa;
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj hasˆo: ";
    cin >> haslo;
    Uzytkownik nowyUzytkownik;
    nowyUzytkownik.nazwa = nazwa;
    nowyUzytkownik.haslo = haslo;
    if(iloscUzytkownikow == 0)
        nowyUzytkownik.id = 1;
    else
        nowyUzytkownik.id = uzytkownicy[iloscUzytkownikow-1].id + 1;
    cout << "Konto zaˆo¾one" << endl;
    Sleep(1000);
    return nowyUzytkownik;
}

int logowanie(vector <Uzytkownik> uzytkownicy) {
    system("cls");
    string nazwa, haslo;
    int iloscUzytkownikow = uzytkownicy.size();

    cout << "LOGOWANIE" << endl;
    cout << "=========" << endl;

    cout << "Podaj login :";
    cin >> nazwa;
    int i = 0;

    while(i < iloscUzytkownikow) {

        if(uzytkownicy[i].nazwa == nazwa) {

            for(int j = 0; j<3; j++) {
                cout << "Podaj hasˆo. Pozostaˆo pr¢b " << 3 - j << ":";
                cin >> haslo;
                if(uzytkownicy[i].haslo == haslo) {

                    cout << "Zalogowaˆe˜ si©." <<endl;;
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
            }
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma u¾ytkownika z takim loginem" << endl;
    Sleep(1000);
    return 0;
}

string wyodrebnijPoleWPobranejLinii(string &linia) {
    int pozycjaZnakuSeperacji = linia.find("|");
    string pole = "";

    if(pozycjaZnakuSeperacji != string::npos) {
        for(int i = 0; i< pozycjaZnakuSeperacji; i++)
            pole += linia[i];

        linia.erase(0,pozycjaZnakuSeperacji+1);
        return pole;
    } else
        return linia;

}

string sprawdzPoleWPobranejLinii(string linia, int nrPola) {
    string pole = "";
    for(int i = 0; i< nrPola; i++) {
        pole =  wyodrebnijPoleWPobranejLinii(linia);
    }

    return pole;
}

void zapiszAdresaciDoPliku(vector<Adresat>& adresaci, int idZalogowanegoUzytkownika) {
    fstream plik;
    fstream plikTymczasowy;
    string linia = "";
    int idAdresata;
    int idUzytkownika;

    plik.open("lista_adresow.txt", ios::in);
    if(plik.good() == false) {
        cout << "Nie udaˆo sie otworzy† pliku i zapisa† w nim danych." << endl;
        Sleep(2000);
        exit(0);
    }
    plikTymczasowy.open("tymczasowa_lista_adresow.txt", ios::out);

    while(getline(plik,linia)) {
        idAdresata = atoi(sprawdzPoleWPobranejLinii(linia,1).c_str());
        idUzytkownika = atoi(sprawdzPoleWPobranejLinii(linia,2).c_str());


        if(adresaci.size() > 0 && idAdresata == adresaci[0].id) {
            plikTymczasowy << adresaci[0].id << "|" << idZalogowanegoUzytkownika << "|" << adresaci[0].imie << "|";
            plikTymczasowy << adresaci[0].nazwisko << "|" << adresaci[0].numerTelefonu <<"|";
            plikTymczasowy << adresaci[0].email << "|" << adresaci[0].adres << endl;
            adresaci.erase(adresaci.begin());
        } else if (idUzytkownika != idZalogowanegoUzytkownika) {
            plikTymczasowy << linia << endl;
        }
    }
    for(int index = 0; index < adresaci.size(); index ++) {
        plikTymczasowy << adresaci[index].id << "|" << idZalogowanegoUzytkownika << "|" << adresaci[index].imie << "|";
        plikTymczasowy << adresaci[index].nazwisko << "|" << adresaci[index].numerTelefonu <<"|";
        plikTymczasowy << adresaci[index].email << "|" << adresaci[index].adres << endl;
    }


    plik.close();
    plikTymczasowy.close();

    remove("lista_adresow.txt");
    rename( "tymczasowa_lista_adresow.txt", "lista_adresow.txt" );

}

void usunAdresataZPliku(Adresat adresat) {
    fstream plik;
    fstream plikTymczasowy;
    string linia = "";
    int idAdresata = 0;
    plik.open("lista_adresow.txt", ios::in);
    if(plik.good() == false) {
        cout << "Nie udaˆo si© otworzy† pliku i zapisa† w nim danych." << endl;
        Sleep(2000);
        exit(0);
    }
    plikTymczasowy.open("tymczasowa_lista_adresow.txt", ios::out);

    while(getline(plik,linia)) {
        idAdresata = atoi(sprawdzPoleWPobranejLinii(linia,1).c_str());

        if(idAdresata != adresat.id) {
            plikTymczasowy << linia << endl;
        }
    }
    plik.close();
    plikTymczasowy.close();

    remove("lista_adresow.txt");
    rename( "tymczasowa_lista_adresow.txt", "lista_adresow.txt" );
}

void dodajAdresataDoPliku(Adresat adresat, int idZalogowanegoUzytkownika) {

    fstream plik;
    plik.open("lista_adresow.txt", ios::out | ios::app);

    plik << adresat.id << "|" << idZalogowanegoUzytkownika << "|" << adresat.imie << "|";
    plik << adresat.nazwisko << "|" << adresat.numerTelefonu <<"|";
    plik << adresat.email << "|" << adresat.adres << endl;

    plik.close();
}

void zmienDaneAdresataWPliku(Adresat adresat, int idZalogowanegoUzytkownika) {
    fstream plik;
    fstream plikTymczasowy;
    string linia = "";
    int idAdresata = 0;

    plik.open("lista_adresow.txt", ios::in);
    if(plik.good() == false) {
        cout << "Nie udaˆo si© otworzy† pliku i zapisa† w nim danych." << endl;
        Sleep(2000);
        exit(0);
    }
    plikTymczasowy.open("tymczasowa_lista_adresow.txt", ios::out);

    while(getline(plik,linia)) {
        idAdresata = atoi(sprawdzPoleWPobranejLinii(linia,1).c_str());

        if(idAdresata == adresat.id) {

            plikTymczasowy << adresat.id << "|" << idZalogowanegoUzytkownika << "|" << adresat.imie << "|";
            plikTymczasowy << adresat.nazwisko << "|" << adresat.numerTelefonu <<"|";
            plikTymczasowy << adresat.email << "|" << adresat.adres << endl;
        } else {
            plikTymczasowy << linia << endl;
        }
    }
    plik.close();
    plikTymczasowy.close();

    remove("lista_adresow.txt");
    rename( "tymczasowa_lista_adresow.txt", "lista_adresow.txt" );
}

void zapiszUzytkownicyDoPliku(vector<Uzytkownik> uzytkownicy) {
    fstream plik;

    plik.open("Uzytkownicy.txt", ios::out);
    for(int index = 0; index < uzytkownicy.size(); index ++) {
        plik << uzytkownicy[index].id << "|" << uzytkownicy[index].nazwa << "|" << uzytkownicy[index].haslo << endl;
    }
    plik.close();
}

int znajdzidOstatniegoAdresata(string linia) {
    return atoi(wyodrebnijPoleWPobranejLinii(linia).c_str());
}

int pobierzAdresatowZPliku(vector<Adresat>& adresaci, int idZalogowanegoUzytkownika) {
    int idOstatniegoAdresata = 0;
    int idUzytkownika = 0;
    if(idZalogowanegoUzytkownika != 0) {

        fstream plik;
        plik.open("lista_adresow.txt", ios::in);
        if(plik.good() == false) {
            cout << "Nie udaˆo si© pobra† danych dla ksi¥¾ki adresowej." << endl;
            Sleep(2000);
            exit(0);
        }
        string linia;
        while(getline(plik,linia)) {
            idOstatniegoAdresata = znajdzidOstatniegoAdresata(linia);
            idUzytkownika = atoi(sprawdzPoleWPobranejLinii(linia, 2).c_str());

            if (idUzytkownika == idZalogowanegoUzytkownika) {
                int index = adresaci.size();
                adresaci.push_back(Adresat());
                adresaci[index].id = atoi(wyodrebnijPoleWPobranejLinii(linia).c_str());
                wyodrebnijPoleWPobranejLinii(linia);
                adresaci[index].imie = wyodrebnijPoleWPobranejLinii(linia);
                adresaci[index].nazwisko = wyodrebnijPoleWPobranejLinii(linia);
                adresaci[index].numerTelefonu = wyodrebnijPoleWPobranejLinii(linia);
                adresaci[index].email = wyodrebnijPoleWPobranejLinii(linia);
                adresaci[index].adres = wyodrebnijPoleWPobranejLinii(linia);
            }
        }
        plik.close();
    }
    return idOstatniegoAdresata;
}

void pobierzUzytkownikowZPliku(vector<Uzytkownik>& uzytkownicy) {
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);
    if(plik.good() == false) {
        cout << "Problem z wczytaniem bazy u¾ytkownik¢w." << endl;
        Sleep(2000);
        exit(0);
    }
    string linia;
    while(getline(plik,linia)) {
        int index = uzytkownicy.size();
        uzytkownicy.push_back(Uzytkownik());
        uzytkownicy[index].id = atoi(wyodrebnijPoleWPobranejLinii(linia).c_str());
        uzytkownicy[index].nazwa = wyodrebnijPoleWPobranejLinii(linia);
        uzytkownicy[index].haslo = wyodrebnijPoleWPobranejLinii(linia);
    }
    plik.close();
}

void dodajAdresata(vector<Adresat>& adresaci, int idOstatniegoAdresata, int idZalogowanegoUzytkownika) {
    system("cls");
    int index = adresaci.size();
    adresaci.push_back(Adresat());

    adresaci[index].id = idOstatniegoAdresata + 1;

    cout << "DODAWANIE NOWEJ OSOBY" << endl;
    cout << "=====================" << endl;

    cout << "Podaj imi©: ";
    cin >> adresaci[index].imie;

    cout << "Podaj nazwisko: ";
    cin >> adresaci[index].nazwisko;

    cout << "Podaj numer telefonu: ";
    cin >> adresaci[index].numerTelefonu;

    cin.clear();
    cin.sync();

    cout << "Podaj adres zamieszkania: ";
    getline(cin, adresaci[index].adres);

    cout << "Podaj adres e-mail: ";
    cin >> adresaci[index].email;

    dodajAdresataDoPliku(adresaci[index], idZalogowanegoUzytkownika);

    system("cls");
    cout << "Dodano now¥ osob©";
    Sleep(2000);
}

void wyswietlTegoAdresata (Adresat tenAdresat) {

    cout << "ID:                  " << tenAdresat.id << endl;
    cout << "Imie:                " << tenAdresat.imie << endl;
    cout << "Nazwisko:            " << tenAdresat.nazwisko << endl;
    cout << "Telefon:             " << tenAdresat.numerTelefonu << endl;
    cout << "Adres zamieszkania:  " << tenAdresat.adres << endl;
    cout << "Adres e-mail:        " << tenAdresat.email << endl;
    cout << endl;
}

void wyswietlWszystkichAdresatow(vector<Adresat> adresaci) {
    system("cls");
    cout << "LISTA ADRESATàW" << endl;
    cout << "===============" << endl;

    for(int i = 0; i<adresaci.size(); i ++)
        wyswietlTegoAdresata(adresaci[i]);



}

void wyswietlAdresataImie(vector<Adresat> adresaci) {
    string imie;
    bool znacznikZnalezienia = false;

    system("cls");
    cout << "Szukaj po imieniu" << endl;
    cout << "=================" << endl;
    cout << "Podaj imi©" << endl;

    cin >> imie;

    system("cls");

    cout << "Wynik wyszukiwania" << endl;
    cout << "==================" << endl;

    for(int i = 0; i<adresaci.size(); i ++) {
        if(adresaci[i].imie == imie) {
            znacznikZnalezienia = true;
            wyswietlTegoAdresata(adresaci[i]);
        }
    }
    if(znacznikZnalezienia == false)
        cout << "Takiej osoby nie ma w twojej ksi¥¾ce";

    cout << "\n\n\nAby wyj˜† naci˜nij Enter";

    getchar();
    getchar();
}

void wyswietlAdresataNazwisko(vector<Adresat> adresaci) {
    string nazwisko;
    bool znacznikZnalezienia = false;

    system("cls");

    cout << "Szukaj po nazwisku" << endl;
    cout << "=================" << endl;
    cout << "Podaj nazwisko" << endl;

    cin >> nazwisko;

    system("cls");

    cout << "Wynik wyszukiwania" << endl;
    cout << "==================" << endl;

    for(int i = 0; i<adresaci.size(); i ++) {
        if(adresaci[i].nazwisko == nazwisko) {
            znacznikZnalezienia = true;
            wyswietlTegoAdresata(adresaci[i]);
        }
    }
    if(znacznikZnalezienia == false)
        cout << "Takiej osoby nie ma w twojej ksi¥¾ce";

    cout << "\n\n\nAby wyjsc nacisnij Enter";

    getchar();
    getchar();
}

int znajdzAdresataPoID(vector<Adresat> adresaci, int numerID) {

    for(int i = 0; i<adresaci.size(); i ++) {
        if(adresaci[i].id == numerID) {
            return i;
        }
    }
    system("cls");
    cout << "Bˆ©dne ID. Spr¢buj ponownie";
    Sleep(2000);
    return -1;
}

void usunAdresata(vector<Adresat>& adresaci) {
    int indexAdresata = -1;
    int adresatID;
    char potwierdzenie;
    while(indexAdresata == -1) {
        wyswietlWszystkichAdresatow(adresaci);
        cout << endl << "Podaj numer ID adresata: ";
        cin >> adresatID;
        indexAdresata = znajdzAdresataPoID(adresaci, adresatID);
    }
    system("cls");
    cout << "USUWANIE ADRESATA" << endl;
    cout << "=================" << endl << endl;
    wyswietlTegoAdresata(adresaci[indexAdresata]);
    while(true) {
        cout << endl << "Czy napewno chcesz go usun¥†? [t/n] ";
        cin >> potwierdzenie;
        if(potwierdzenie == 't') {
            usunAdresataZPliku(adresaci[indexAdresata]);
            adresaci.erase(adresaci.begin() + indexAdresata);
            system("cls");
            cout << "Usuni©to";
            Sleep(2000);
            break;
        } else if(potwierdzenie == 'n')
            break;
    }
}

void edytujAdresata(vector<Adresat>& adresaci, int idZalogowanegoUzytkownika) {
    int adresatID;
    char numerPola = '0';
    int indexAdresata = -1;
    string nowePole;

    while(indexAdresata == -1) {
        wyswietlWszystkichAdresatow(adresaci);
        cout << endl << "Podaj numer ID adresata: ";
        cin >> adresatID;
        indexAdresata = znajdzAdresataPoID(adresaci, adresatID);
    }
    while(numerPola != '9') {
        system("cls");
        cout << "EDYCJA" << endl;
        cout << "======" << endl << endl;
        wyswietlTegoAdresata(adresaci[indexAdresata]);
        cout << "\n\n1. Edytuj Imi©\n2. Edytuj nazwisko\n3. Edytuj numer telefonu\n";
        cout << "4. Edytuj adres\n5. Edytuj email\n9. Powr¢t do menu\n";
        cout << "Tw¢j wyb¢r: ";
        cin >> numerPola;
        cin.clear();
        cin.sync();

        switch(numerPola) {
        case '1':
            cout << "Podaj nowe imie: ";
            getline(cin, nowePole);
            adresaci[indexAdresata].imie = nowePole;
            break;
        case '2':
            cout << "Podaj nowe nazwisko: ";
            getline(cin, nowePole);
            adresaci[indexAdresata].nazwisko = nowePole;
            break;
        case '3':
            cout << "Podaj nowy numer telefonu: ";
            getline(cin, nowePole);
            adresaci[indexAdresata].numerTelefonu = nowePole;
            break;
        case '4':
            cout << "Podaj nowy adres: ";
            getline(cin, nowePole);
            adresaci[indexAdresata].adres = nowePole;
            break;
        case '5':
            cout << "Podaj nowy email: ";
            getline(cin, nowePole);
            adresaci[indexAdresata].email = nowePole;
            break;
        }
    }
    zmienDaneAdresataWPliku(adresaci[indexAdresata], idZalogowanegoUzytkownika);

}

void zmianaHasla(vector<Uzytkownik>& uzytkownicy, int idZalogowanegoUzytkownika) {

    string nowehaslo;
    int iloscUzytkownikow = uzytkownicy.size();

    for(int i = 0; i< iloscUzytkownikow; i++) {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika) {
            cout << "Podaj nowe hasˆo: ";
            cin >> nowehaslo;
            uzytkownicy[i].haslo = nowehaslo;
            cout << endl << "Hasˆo zostaˆo zmienione" << endl;
            Sleep(1000);
            break;
        }
    }
}
