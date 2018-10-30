#include <iostream>
#include <string.h>
using namespace std;

class Data
{
    int zi;
    char luna[20];
    int an;

public:
    Data() {};
    ~Data(){};
    Data(int _zi, const char _luna[], int _an);
    Data(Data& data);

    friend ostream& operator << (ostream& out, Data& data)
    {
        out << "\n Ziua: " << data.zi << "\t";
        out << "Luna: " << data.luna << "\t";
        out << "Anul: " << data.an << "\n";
        return out;
    }

    friend istream& operator >> (istream& in, Data& data)
    {
        cout << "\n Introduceti ziua: ";
        in >> data.zi;
        cout << "\t Introduceti luna: ";
        in >> data.luna;
        cout << "\t Introduceti anul: ";
        in >> data.an;
        return in;
    }

    Data& operator = (const Data& data)
    {
        zi = data.zi;
        strcpy(luna, data.luna);
        an = data.an;
        return *this;
    }

    bool operator < (Data& data)
    {
        if (an == data.an)
            if (strcmp(luna, data.luna) == 0)
            {
                if (zi < data.zi)
                    return(true);
            }
        return (an < data.an);
    }

};

Data::Data(int _zi, const char _luna[], int _an)
{
    zi = _zi;
    strcpy(luna, _luna);
    an = _an;
}

Data::Data(Data &data)
{
    zi = data.zi;
    strcpy(luna, data.luna);
    an = data.an;
}

class Medicament
{
    char* denumire;
    float pret;
    Data fabricat;

public:
    Medicament()
    {
        denumire = new char[strlen("nedefinit")];
        strcpy(denumire, "nedefinit");
        pret = 0;
        Data _fabricat(0, "nedefinit", 0);
        fabricat = _fabricat;
    };

    ~Medicament(){};
    Medicament(const char _denumire[], float _pret, int _zi, const char _luna[], int _an);
    Medicament(const char _denumire[], Data _fabricat);

    friend ostream& operator << (ostream& out, Medicament& medicament)
    {
        out << "\n Denumire: " << medicament.denumire << "\t";
        if ( medicament.pret != 0)
            out << "Pret: " << medicament.pret << "\t";
        out << "Fabricat la: " << medicament.fabricat << "\t";
        return out;
    }

    friend istream& operator >> (istream& in, Medicament& medicament)
    {
        char _denumire[200];
        cout << "\n Introduceti denumirea medicamentului: ";
        in.getline(_denumire, 200);
        medicament.denumire = new char[strlen(_denumire)];
        strcpy(medicament.denumire, _denumire);
        cout << "\t Introduceti pretul: ";
        in >> medicament.pret;
        cout << "\t Introduceti data de fabricatie: ";
        in >> medicament.fabricat;

        return in;
    }

    bool operator < (Medicament& medicament)
    {
        return (fabricat < medicament.fabricat);
    }

    Medicament& operator = (const Medicament& medicament)
    {
        denumire = new char[strlen(medicament.denumire)];
        strcpy(denumire, medicament.denumire);
        pret = medicament.pret;
        fabricat = medicament.fabricat;
        return *this;
    }
};

Medicament::Medicament(const char _denumire[], float _pret, int _zi, const char _luna[], int _an)
{
    denumire = new char[strlen(_denumire)];
    strcpy(denumire, _denumire);
    pret = _pret;
    Data _data(_zi, _luna, _an);
    fabricat = _data;
}

Medicament::Medicament(const char _denumire[], Data _fabricat)
{
    denumire = new char[strlen(_denumire)];
    strcpy(denumire, _denumire);
    pret = 0;
    fabricat = _fabricat;
}

class Farmacie
{
    char denumire[50];
    int nrMedicamente;
    Medicament* Med;

public:
    Farmacie()
    {
      strcpy(denumire, "nedefinit");
        nrMedicamente=0;
    };

    ~Farmacie(){};
    Farmacie(const char denumire[]);

    friend ostream& operator << (ostream& out, Farmacie& farmacie)
    {
        out << "\nDenumirea Farmaciei: " << farmacie.denumire;
        out << "\t Numar medicamente: " << farmacie.nrMedicamente;
        if ( farmacie.nrMedicamente > 0)
        {
            out << "\t Medicamente: ";
            for (int i=0; i < farmacie.nrMedicamente; i++)
                out << " " << farmacie.Med[i];
        }
    }

    void operator += (Medicament& medicament)
    {
        Medicament _TempMed[nrMedicamente];
        for (int i=0; i < nrMedicamente; i++)
        {
            _TempMed[i]=Med[i];
        }
        nrMedicamente=nrMedicamente+1;
        delete(Med);
        Med = new Medicament[nrMedicamente];
        for (int i=0; i < nrMedicamente; i++)
            if ( i < nrMedicamente-1)
                Med[i]=_TempMed[i];
            else Med[i]=medicament;
    };

    friend Farmacie operator + (const Medicament& medicament, const Farmacie& farmacie)
    {
        Farmacie Tmp;
        Tmp = farmacie;
        Medicament _TempMed[Tmp.nrMedicamente];
        for (int i=0; i < Tmp.nrMedicamente; i++)
        {
            _TempMed[i]=Tmp.Med[i];
        }
        Tmp.nrMedicamente=Tmp.nrMedicamente+1;
        delete(Tmp.Med);
        Tmp.Med = new Medicament[Tmp.nrMedicamente];
        for (int i=0; i < Tmp.nrMedicamente; i++)
            if ( i < Tmp.nrMedicamente-1)
                Tmp.Med[i]=_TempMed[i];
            else Tmp.Med[i]=medicament;
        return Tmp;
    }

   Farmacie& operator = (const Farmacie& farmacie)
    {
        strcpy(denumire, farmacie.denumire);
        nrMedicamente = farmacie.nrMedicamente;
        Med = new Medicament[nrMedicamente];
        for (int i=0; i < nrMedicamente; i++)
            Med[i] = farmacie.Med[i];
        return *this;
    }
};

Farmacie::Farmacie(const char *_denumire)
{
    strcpy(denumire, _denumire);
    nrMedicamente=0;
}

int main()
{
    Data d(1,"ianuarie",2018);
   // cout << d;
    Medicament m1("Parasinus",9.5, 10, "ianuarie", 2030), m2("Aspirina", d), m3;
    cout << m1 << "\n" << m2 << "\n";
    cin>>m3;
    cout<<m1 <<m3;
    if (m1<m3) cout<<"m1 este fabricat inaintea m3";
    else cout<<"m3 este fabricat inaintea m1";
    Farmacie f1("Farmac");
    f1 += m1; //adaugare medicament m1 in lista de medicamente a farmaciei
    f1 = m2 + f1; //adaugare medicament m2 in lista de medicamente a farmaciei
    cout << f1;
     Farmacie f2 = f1;
   cout<<f2; //afisarea tuturor medicamentelor
    return 0;
    
}