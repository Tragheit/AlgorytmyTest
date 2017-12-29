#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

int const N = 1000001;
int los[N];
int uporz[N];
int odwr[N];
int a[N]; //a na której dzialaja algorytmy
int rozmiar = 0;


void wstawianie();

void wybieranie();

void babelkowe();

void sps(int l, int p);

void szybkie(int l, int p);

void sprawdz(const int tablica[], int rozmiar);

void przypisz(int tablicawynikowa[], const int tablica[], int rozmiar);

typedef void (*wskaznikNaFunkcjeBezArgumentow)();

typedef void (*wskaznikNaFunkcjeDwuargumentowe)(int, int);

void sortuj(wskaznikNaFunkcjeBezArgumentow wskaznik);

void sortuj(int i, int j, wskaznikNaFunkcjeDwuargumentowe wskaznik);

void dzialamy(int rozmiarTablicy);

int main() {
    //generator liczb losowych

    int Tablice[5]{10,100,1000,10000,100000};

    for (int i : Tablice){
        rozmiar = i;
        dzialamy(rozmiar);
    }
}

void sprawdz(const int tablica[], int rozmiar) {
    for (int i = 0; i < rozmiar; i++) {
        cout << tablica[i] << " ";
    }
    cout << endl;
}

void przypisz(int tablicawynikowa[], const int tablica[], int rozmiar) {
    for (int i = 0; i < rozmiar; i++) {
        tablicawynikowa[i] = tablica[i];
    }
}

void wstawianie() {
    int i, j, v;
    for (i = 1; i < rozmiar; i++) {
        j = i;
        v = a[i];
        while ((j > 0) && (a[j - 1] > v)) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = v;
    }
}

void wybieranie() {
    int max, pomoc;
    for (int i = 0; i < rozmiar; i++) {
        max = i;
        for (int j = i + 1; j < rozmiar; j++) {
            if (a[j] < a[max])
                max = j;
        }
        pomoc = a[max];
        a[max] = a[i];
        a[i] = pomoc;
    }
}

void babelkowe() {
    int zamiana, schowek;
    do {
        zamiana = 0;//przed każdym "przejazdem" pętli for zmienna zamiana jest zerowana
        for (int i = 0; i < 5; i++) {
            if (a[i] > a[i + 1])// jeśli element tablicy jest większy od następnego elementu
            {
                zamiana = zamiana + 1; //jeśli jest jakaś zmiana, to zmienne zamiana powiększa swoją wartość
                schowek = a[i];//wartość t[i] jest kopiowana do schowka
                a[i] = a[i + 1];//t[i] przyjmuje wartość następnego elementu, gdyż jest on mniejszy
                a[i +
                  1] = schowek;//kolejny element tablicy przejmuje wcześniejszą wartość poprzedniego elementu, gdyż jest on większy
            }
        }
    } while (zamiana != 0);
}

void sps(int l, int p) {
    int pom[rozmiar];
    int i_s, i1, i2, i;

    i_s = (l + p + 1) / 2;
    if (i_s - l > 1) sps(l, i_s - 1);

    if (p - i_s > 0) sps(i_s, p);

    i1 = l;
    i2 = i_s;
    for (i = l; i <= p; i++)
        pom[i] = ((i1 == i_s) || ((i2 <= p) && (a[i1] > a[i2]))) ? a[i2++]
                                                                 : a[i1++];

    for (i = l; i <= p; i++) a[i] = pom[i];

}

void szybkie(int l, int p) {
    int i, j, v, temp;
    i = l;
    j = p;
    v = a[div(l + p, 2).quot];
    do {
        while (a[i] < v) i++;
        while (v < a[j]) j--;
        if (i <= j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);
    if (l < j) szybkie(l, j);
    if (i < p) szybkie(i, p);
}

void sortuj(int i, int j, wskaznikNaFunkcjeDwuargumentowe wskaznik) {
    przypisz(a, los, rozmiar);
    wskaznik(i, j);

    przypisz(a, uporz, rozmiar);
    wskaznik(i, j);

    przypisz(a, odwr, rozmiar);
    wskaznik(i, j);
}

void sortuj(wskaznikNaFunkcjeBezArgumentow wskaznik) {
    przypisz(a, los, rozmiar);
    wskaznik();

    przypisz(a, uporz, rozmiar);
    wskaznik();

    przypisz(a, odwr, rozmiar);
    wskaznik();
}

void dzialamy (int rozmiarTablicy){
    mt19937 uni;
    uni.seed(unsigned(nullptr));
    uniform_int_distribution<int> rand(0, 100);
    // generowanie zawartosci tablicy
    for (int i = 0; i < rozmiar; i++) {
        los[i] = rand(uni);
    }

    //pierwsza i ostatnia komorka tablicy
    int l = 0;
    int p = rozmiar - 1;

    //przepisywanie losowych danych do tablicy a
    przypisz(a, los, rozmiar);

    // sortowanie rosnaco
    sort(a, a + rozmiar);
    przypisz(uporz, a, rozmiar);

    //sortowanie malejaco
    sort(a, a + rozmiar, greater<int>());
    przypisz(odwr, a, rozmiar);

    /*
    //sprawdzanie wartosci tablic
    cout << "\nsprawdzanie koncowe\n\n";
    cout << "wartosci nieposortowane\n";
    sprawdz(los, n);
    cout << "wartosci posortowane rosnaco\n";
    sprawdz(uporz, n);
    cout << "wartosci posortowane malejaco\n";
    sprawdz(odwr, n);
*/

    //obliczanie czasow wykonania algorytmu

    cout << "wstawianie\n";
    sortuj(wstawianie);
    cout << "wybieranie\n";
    sortuj(wybieranie);
    cout << "babelkowe\n";
    sortuj(babelkowe);
    cout << "sps\n";
    sortuj(l, p, sps);
    cout << "szybkie\n";
    sortuj(l, p, szybkie);

}