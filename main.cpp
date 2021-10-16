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

vector<Adresat> adresaci;

int wybierzOpcjeZMenu(int idZalogowanegoUzytkownika) {
    system("cls");
    int n;
    cout << "KSIAZKA ADRESOWA" << endl;
    cout << "================" << endl;
    if (idZalogowanegoUzytkownika ==0) {
        cout << "1. Rejestracja\n2. Logowanie\n9. Zakończ program.\n";
    } else {
        cout << "1. Dodaj adresata\n2. Wyszukaj po imieniu\n3. Wyszukaj po nazwisku\n4. Wyświetl wszystkich adresatów\n";
        cout << "5. Usuń adresata\n6. Edytuj adresata\n7. Zmień hasło\n9. Wyloguj się\n";
    }
    cout << "Twój wybór: ";
    cin >> n;
    return n;
}

Uzytkownik (rejestracja(vector <Uzytkownik> uzytkownicy)) {
    string nazwa, haslo;
    int iloscUzytkownikow = uzytkownicy.size();

    cout << "Podaj nazwę użytkownika: ";
    cin >> nazwa;
    int i = 0;

    while(i < iloscUzytkownikow) {
        if(uzytkownicy[i].nazwa == nazwa) {
            cout << "Taki użytkownik istnieje. Wpisz inną nazwę użytkownika: ";
            cin >> nazwa;
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj hasło: ";
    cin >> haslo;
    Uzytkownik nowyUzytkownik;
    nowyUzytkownik.nazwa = nazwa;
    nowyUzytkownik.haslo = haslo;
    if(iloscUzytkownikow == 0)
        nowyUzytkownik.id = 1;
    else
        nowyUzytkownik.id = uzytkownicy[iloscUzytkownikow-1].id + 1;
    cout << "Konto założone" << endl;
    Sleep(1000);
    return nowyUzytkownik;
}

int logowanie(vector <Uzytkownik> uzytkownicy) {
    string nazwa, haslo;
    int iloscUzytkownikow = uzytkownicy.size();
    cout << "Podaj login :";
    cin >> nazwa;
    int i = 0;

    while(i < iloscUzytkownikow) {

        if(uzytkownicy[i].nazwa == nazwa) {

            for(int j = 0; j<3; j++) {
                cout << "Podaj hasło. Pozostało prób " << 3 - j << ":";
                cin >> haslo;
                if(uzytkownicy[i].haslo == haslo) {

                    cout << "Zalogowałeś się." <<endl;;
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
            }
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma użytkownika z takim loginem" << endl;
    Sleep(1000);
    return 0;
}

void zapiszDoPliku() {
    fstream plik;

    plik.open("lista_adresow.txt", ios::out);
    for(int index = 0; index < adresaci.size(); index ++) {
        plik << adresaci[index].id << "|" << adresaci[index].imie << "|";
        plik << adresaci[index].nazwisko << "|" << adresaci[index].numerTelefonu <<"|";
        plik << adresaci[index].email << "|" << adresaci[index].adres << endl;
    }
    plik.close();
}

string wyodrebnijPole(string &linia) {
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
void pobierzListeZPliku() {
    fstream plik;
    plik.open("lista_adresow.txt", ios::in);
    string linia;
    while(getline(plik,linia)) {
        int index = adresaci.size();
        adresaci.push_back(Adresat());
        adresaci[index].id = atoi(wyodrebnijPole(linia).c_str());
        adresaci[index].imie = wyodrebnijPole(linia);
        adresaci[index].nazwisko = wyodrebnijPole(linia);
        adresaci[index].numerTelefonu = wyodrebnijPole(linia);
        adresaci[index].email = wyodrebnijPole(linia);
        adresaci[index].adres = wyodrebnijPole(linia);
    }
    plik.close();
}
void DodajAdresata() {
    system("cls");
    int index = adresaci.size();
    adresaci.push_back(Adresat());
    if(index == 0)
        adresaci[index].id = 1;
    else
        adresaci[index].id = adresaci[index-1].id + 1;

    cout << "DODAWANIE NOWEJ OSOBY" << endl;
    cout << "=====================" << endl;

    cout << "Podaj imię: ";
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

    system("cls");
    cout << "Dodano nową osobę";
    Sleep(2000);
}
void wyswietlTegoAdresata (int index) {

    cout << "ID:                  " << adresaci[index].id << endl;
    cout << "Imie:                " << adresaci[index].imie << endl;
    cout << "Nazwisko:            " << adresaci[index].nazwisko << endl;
    cout << "Telefon:             " << adresaci[index].numerTelefonu << endl;
    cout << "Adres zamieszkania:  " << adresaci[index].adres << endl;
    cout << "Adres e-mail:        " << adresaci[index].email << endl;
    cout << endl;
}
void wyswietlWszystkichAdresatow() {
    system("cls");
    cout << "LISTA ADRESATÓW" << endl;
    cout << "===============" << endl;

    for(int i = 0; i<adresaci.size(); i ++)
        wyswietlTegoAdresata(i);



}

void wyswietlAdresataImie() {
    string imie;
    bool znacznikZnalezienia = false;

    system("cls");
    cout << "Szukaj po imieniu" << endl;
    cout << "=================" << endl;
    cout << "Podaj imię" << endl;

    cin >> imie;

    system("cls");

    cout << "Wynik wyszukiwania" << endl;
    cout << "==================" << endl;

    for(int i = 0; i<adresaci.size(); i ++) {
        if(adresaci[i].imie == imie) {
            znacznikZnalezienia = true;
            wyswietlTegoAdresata(i);
        }
    }
    if(znacznikZnalezienia == false)
        cout << "Takiej osoby nie ma w twojej książce";

    cout << "\n\n\nAby wyjść naciśnij Enter";

    getchar();
    getchar();
}

void wyswietlAdresataNazwisko() {
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
            wyswietlTegoAdresata(i);
        }
    }
    if(znacznikZnalezienia == false)
        cout << "Takiej osoby nie ma w twojej książce";

    cout << "\n\n\nAby wyjsc nacisnij Enter";

    getchar();
    getchar();
}

int znajdzAdresataPoID(int numerID) {

    for(int i = 0; i<adresaci.size(); i ++) {
        if(adresaci[i].id == numerID) {
            return i;
        }
    }
    system("cls");
    cout << "B³êdne ID. Spróbuj ponownie";
    Sleep(2000);
    return -1;
}

void usunAdresata() {
    int indexAdresata = -1;
    int adresatID;
    char potwierdzenie;
    while(indexAdresata == -1) {
        wyswietlWszystkichAdresatow();
        cout << endl << "Podaj numer ID adresata: ";
        cin >> adresatID;
        indexAdresata = znajdzAdresataPoID(adresatID);
    }
    system("cls");
    cout << "USUWANIE ADRESATA" << endl;
    cout << "=================" << endl << endl;
    wyswietlTegoAdresata(indexAdresata);
    while(true) {
        cout << endl << "Czy napewno chcesz go usunąć? [t/n] ";
        cin >> potwierdzenie;
        if(potwierdzenie == 't') {
            //vector<Adresat>::iterator index = adresaci.begin()
            adresaci.erase(adresaci.begin() + indexAdresata);
            system("cls");
            cout << "Usunięto";
            Sleep(2000);
            break;
        } else if(potwierdzenie == 'n')
            break;
    }
}

void edytujAdresata() {
    int adresatID;
    int numerPola = 0;
    int indexAdresata = -1;
    string nowePole;

    while(indexAdresata == -1) {
        wyswietlWszystkichAdresatow();
        cout << endl << "Podaj numer ID adresata: ";
        cin >> adresatID;
        indexAdresata = znajdzAdresataPoID(adresatID);
    }
    while(numerPola != 9) {
        system("cls");
        cout << "EDYCJA" << endl;
        cout << "======" << endl << endl;
        wyswietlTegoAdresata(indexAdresata);
        cout << "\n\n1. Edytuj Imię\n2. Edytuj nazwisko\n3. Edytuj numer telefonu\n";
        cout << "4. Edytuj email\n5. Edytuj adres\n9. Powrót do menu\n";
        cout << "Twój wybór: ";
        cin >> numerPola;
        switch(numerPola) {
        case 1:
            cout << "Podaj nowe imie: ";
            cin >> nowePole;
            adresaci[indexAdresata].imie = nowePole;
            break;
        case 2:
            cout << "Podaj nowe nazwisko: ";
            cin >> nowePole;
            adresaci[indexAdresata].nazwisko = nowePole;
            break;
        case 3:
            cout << "Podaj nowy numer telefonu: ";
            cin >> nowePole;
            adresaci[indexAdresata].numerTelefonu = nowePole;
            break;
        case 4:
            cout << "Podaj nowy email: ";
            cin >> nowePole;
            adresaci[indexAdresata].email = nowePole;
            break;
        case 5:
            cout << "Podaj nowy adres: ";
            cin >> nowePole;
            adresaci[indexAdresata].adres = nowePole;
            break;

        }
    }

}

void zmianaHasla(vector<Uzytkownik>& uzytkownicy, int idZalogowanegoUzytkownika) {

    string nowehaslo;
    int iloscUzytkownikow = uzytkownicy.size();

    for(int i = 0; i< iloscUzytkownikow; i++) {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika) {
            cout << "Podaj nowe hasło: ";
            cin >> nowehaslo;
            uzytkownicy[i].haslo = nowehaslo;
            cout << endl << "Hasło zostało zmienione" << endl;
            Sleep(1000);
            break;
        }
    }
}


int main() {
    vector <Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    pobierzListeZPliku();
    while(true) {
        if(idZalogowanegoUzytkownika == 0) {
            switch  (wybierzOpcjeZMenu(idZalogowanegoUzytkownika)) {
            case 1:
                uzytkownicy.push_back(rejestracja(uzytkownicy));
                break;
            case 2:
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
                break;
            case 9:
                exit(0);
            }
        } else {
            switch (wybierzOpcjeZMenu(idZalogowanegoUzytkownika)) {
            case 1:
                DodajAdresata();
                break;
            case 2:
                wyswietlAdresataImie();
                break;
            case 3:
                wyswietlAdresataNazwisko();
                break;
            case 4:
                wyswietlWszystkichAdresatow();
                cout << "\n\n\nAby wyjść naciśnij Enter";
                getchar();
                getchar();
                break;
            case 5:
                usunAdresata();
                break;
            case 6:
                edytujAdresata();
                break;
            case 7:
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
            case 9:
                zapiszDoPliku();
                idZalogowanegoUzytkownika = 0;
                break;
            }
        }
    }
    return 0;
}
