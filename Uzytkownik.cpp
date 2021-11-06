#include "Uzytkownik.h"
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;
Uzytkownik::Uzytkownik()
{
}
Uzytkownik::~Uzytkownik()
{
}
void Uzytkownik::rejestracja(vector <Uzytkownik> uzytkownicy)
{
    system("cls");
    int iloscUzytkownikw = uzytkownicy.size();

    cout << "REJESTRACJA" << endl;
    cout << "===========" << endl;

    cout << "Podaj nazw© u¾ytkownika: ";
    cin >> nazwa;
    int i = 0;

    while(i < iloscUzytkownikw) {
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
    if(iloscUzytkownikw == 0)
        id = 1;
    else
        id = uzytkownicy[iloscUzytkownikw-1].id + 1;
    cout << "Konto zaˆo¾one" << endl;
    Sleep(1000);
}
