#include <iostream>
#include <string.h>
using namespace std;

class Caracteristica
{
    char functie[20];
    int vechime;
public:
    void setVechime(int vechime);

public:
    int getVechime();

public:
    Caracteristica()
    {
        strcpy(functie, "nedefinit");
        vechime = -1;
    };
    ~Caracteristica(){};
    Caracteristica (const char _functie[]);
    Caracteristica(const char _functie[], int _vechime);
    Caracteristica (Caracteristica& caracteristica);

    friend ostream& operator << (ostream& out, Caracteristica& caracteristica)
    {
        if (caracteristica.vechime > -1)
        {
            out << "Functia este: "<< caracteristica.functie;
            out << "\t Vechimea este: "<< caracteristica.vechime << "\n";
        }
        return out;
    }

    friend istream& operator >> (istream& in, Caracteristica& caracteristica)
    {
        cout << "Introduceti functia: ";
        in >> caracteristica.functie;
        cout << "\t Introduceti vechimea: ";
        in >> caracteristica.vechime;
        return in;

    }

    Caracteristica& operator = (const Caracteristica& caracteristica)
    {
        strcpy(functie, caracteristica.functie);
        vechime =  caracteristica.vechime;
        return *this;
    }

    friend Caracteristica operator + (const int _vechime_add, const Caracteristica& caracteristica)
    {
        Caracteristica Tmp;
        Tmp = caracteristica;
        Tmp.vechime += _vechime_add;
        return Tmp;
    }
};

Caracteristica::Caracteristica(const char _functie[], int _vechime)
{
    strcpy(functie, _functie);
    vechime = _vechime;
}

Caracteristica::Caracteristica(const char *_functie)
{
    strcpy(functie, _functie);
    vechime = 0;
}

Caracteristica::Caracteristica(Caracteristica &caracteristica)
{
    strcpy(functie, caracteristica.functie);
    vechime =  caracteristica.vechime;
}

int Caracteristica::getVechime()
{
    return vechime;
}

void Caracteristica::setVechime(int vechime)
{
    Caracteristica::vechime = vechime;
}

class Angajat
{
    int id;
public:
    int getId();

private:
    char nume[50];
    Caracteristica car;
public:
    Caracteristica &getCar();

public:
    Angajat()
    {
        id=-1;
        strcpy(nume, "nedefinit");
    };
    ~Angajat(){};
    Angajat(int _id, const char _nume[], Caracteristica _car);
    Angajat(int _id, const char _nume[], const char _functie[], int _vechime);
    Angajat(Angajat& angajat);

    Angajat& operator = (const Angajat& angajat)
    {
        id = angajat.id;
        strcpy(nume, angajat.nume);
        car = angajat.car;
        return *this;
    }

    friend ostream& operator << (ostream& out, Angajat& angajat)
    {
        if (angajat.id > -1){
            out << "Id-ul angajatului este: "<< angajat.id;
            out << "\t Numele angajatului: "<< angajat.nume;
            out << "\n Caracteristica angajat: "<< angajat.car << "\n";
        }
    return out;
    }

    friend istream& operator >> (istream& in, Angajat& angajat)
    {
        cout << "Introduceti id-ul angajatului: ";
        in >> angajat.id;
        cout << "\nIntroduceti numele angajatului: ";
        in >> angajat.nume;
        cout <<"\n Introduceti caracteristica angajatului: ";
        in >>angajat.car;
        return in;
    }

};

Angajat::Angajat(int _id, const char *_nume, Caracteristica _car)
{
    id = _id;
    strcpy(nume, _nume);
    car = _car;
}

Angajat::Angajat(int _id, const char *_nume, const char _functie[], int _vechime)
{
    id = _id;
    strcpy(nume, _nume);
    Caracteristica _car(_functie, _vechime);
    car = _car;
}

Angajat::Angajat(Angajat &angajat)
{
    id = angajat.id;
    strcpy(nume, angajat.nume);
    car = angajat.car;
}

int Angajat::getId()
{
    return id;
}

Caracteristica &Angajat::getCar()
{
    return car;
}


class Banca
{
    char denumire[50];
    int nrAngajati;
    Angajat* Ang;

public:
    Banca()
    {
        strcpy(denumire, "nedefinit");
        nrAngajati=0;
    };
    ~Banca(){};
    Banca(const char _denumire[], int _nrAngajati);
    Banca(const char _denumire[], int _nrAngajati, Angajat _ang[]);
    Banca(Banca& banca);

    Banca& operator = (const Banca& banca)
    {
        strcpy(denumire, banca.denumire);
        nrAngajati = banca.nrAngajati;
        Ang = new Angajat[banca.nrAngajati];
        if ((banca.nrAngajati > 0)&&(banca.Ang!=NULL))
            for (int i=0; i < banca.nrAngajati; i++)
              Ang[i] = banca.Ang[i];
        return *this;
    }

    friend ostream& operator << (ostream& out, Banca& banca)
    {
        out << "\n Denumire banca: "<< banca.denumire;
        out << "\t Numar angajati: "<< banca.nrAngajati;
        if ((banca.nrAngajati > 0) && (banca.Ang!= NULL))
        {
            out << "\n Angajati: \n";
            for (int i = 0; i < banca.nrAngajati; i++)
                if (banca.Ang[i].getId() > -1)
                    out << i << ":" << banca.Ang[i] << "\n";

        }
        return out;
    }

    void operator += (const Angajat& _a)
    {
        Angajat Tmp[nrAngajati];
        for (int i=0; i < nrAngajati; i++)
                    Tmp[i]=Ang[i];
        nrAngajati = nrAngajati+1;
        delete(Ang);
        Ang = new Angajat[nrAngajati];
        for (int i=0; i < nrAngajati; i++)
            if (i < nrAngajati-1)
                Ang[i] = Tmp[i];
            else Ang[i] = _a;
    }

    void modificare (int _i, int _vechime_subst)
    {
                if ((_i < nrAngajati)&&(Ang[_i].getId() > -1))
                    Ang[_i].getCar().setVechime(Ang[_i].getCar().getVechime()+ _vechime_subst);
    }
};

Banca::Banca(const char *_denumire, int _nrAngajati)
{
    strcpy(denumire, _denumire);
    nrAngajati = _nrAngajati;
}

Banca::Banca(const char *_denumire, int _nrAngajati, Angajat _ang[])
{
    strcpy(denumire, _denumire);
    nrAngajati = _nrAngajati;
    Ang = _ang;
}

Banca::Banca(Banca &banca)
{
    strcpy(denumire, banca.denumire);
    nrAngajati = banca.nrAngajati;
    Ang = new Angajat[banca.nrAngajati];
    if ((banca.nrAngajati > 0)&&(banca.Ang!=NULL))
        for (int i=0; i < banca.nrAngajati; i++)
            Ang[i] = banca.Ang[i];
}

int main()
{
    Caracteristica c1("Director",10), c2("Casier"), c3 = c1;
    c3 = 12 + c3; // actualizeaza vechimea adaugand 12 ani
    cout << c3;
    Angajat a1(1,"Ionescu",c1), a2(2,"Popescu","Functionar",25), a3(a1), a4,a5[2];
    cout << a1;
    for (int i=0;i<2;i++) cin>>a5[i];
    cout<<a5[1];
    Banca b1("Bank",50), b3, b4, b5("Bank2",3,a5);
    cout << b1;
    b4 = b3 = b1;
    cout << b4;
    for (int i=0;i<2;i++) b3 += a5[i]; // se adauga angajatii din vectorul a5 listei de angajati ai bancii b3
    cout << b3;
    Banca b2(b3);
    b2.modificare(50,-5); // scade vechimea celui de-al doilea angajat cu 5 ani
    cout<<b2;
    return 0;
}