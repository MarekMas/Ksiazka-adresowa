#include <iostream>
#include <vector>


class Uzytkownik
{
    int id;
    std::string nazwa, haslo;
    public:
        friend void pobierzUzytkownikwZPliku(std::vector<Uzytkownik>& uzytkownicy);
        friend int logowanie(std::vector <Uzytkownik> uzytkownicy);
        friend void zapiszUzytkownicyDoPliku(std::vector<Uzytkownik> uzytkownicy);
        friend void zmianaHasla(std::vector<Uzytkownik>& uzytkownicy, int idZalogowanegoUzytkownika);
    Uzytkownik();
    ~Uzytkownik();
    void rejestracja(std::vector <Uzytkownik> uzytkownicy);
};
