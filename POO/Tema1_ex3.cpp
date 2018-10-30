#include <iostream>
#include <string.h>
using namespace std;

class Data
{
    int zi;
    char luna[20];
    int an;

public:
    Data()
    {
        zi=0;
        strcpy(luna, "nedefinit");
        an=0;
    };
    ~Data(){};
    Data(int _zi, const char _luna[], int _an);

    Data& operator = (Data& data)
    {
        zi = data.zi;
        strcpy(luna, data.luna);
        an = data.an;

        return *this;
    }

    friend ostream& operator << (ostream& out, Data& data)
    {
        out << "Ziua: " << data.zi << ' ';
        out << "Luna: " << data.luna << ' ';
        out << "Anul: " << data.an << '\n';
        return out;
    }

    friend istream& operator >> (istream& in, Data& data)
    {
        cout << "Introduceti Ziua: ";
        in >> data.zi;
        cout << "\tIntroduceti luna: ";
        in >> data.luna;
        cout << "\tIntroduceti anul: ";
        in >> data.an;

        return in;
    }
};

Data::Data(int _zi, const char *_luna, int _an)
{
    zi = _zi;
    strcpy (luna, _luna);
    an = _an;
}

class Proprietar
{
    char* nume;
    Data data_nasterii;

public:
    Proprietar() {};
    ~Proprietar() {};
    Proprietar (const char _nume[], Data _data_nasterii);
    Proprietar (const char _nume[], int _zi, const char _luna[], int _an);

    friend ostream& operator << (ostream& out, Proprietar& proprietar)
    {
        out << "Nume proprietar: " << proprietar.nume << "\n";
        out << "\tData nasterii: " << proprietar.data_nasterii << "\n";
        return out;
    }

    friend istream& operator >> (istream& in, Proprietar& proprietar)
    {
        char _nume[500], str[1];
        in.getline(str, 1);
        cout << "Introduceti nume proprietar: ";
        in.getline(_nume, 500);
        proprietar.nume = new char[strlen(_nume)];
        strcpy(proprietar.nume, _nume);
        cout << "\t" << "introduceti data nasterii: ";
        in >> proprietar.data_nasterii;
        return in;
    }
};

Proprietar::Proprietar(const char *_nume, Data _data_nasterii)
{
    nume = new char[strlen(_nume)];
    strcpy(nume, _nume);
    data_nasterii = _data_nasterii;
}

Proprietar::Proprietar(const char *_nume, int _zi, const char *_luna, int _an)
{
    nume = new char[strlen(_nume)];
    strcpy(nume, _nume);
    Data _data(_zi, _luna, _an);
    data_nasterii = _data;
}

class Casa
{
    char oras[50];
    int nrProprietari;
    Proprietar* Prop;

public:
    Casa()
    {
        strcpy(oras, "nedefinit");
        nrProprietari = 0;
    };
    ~Casa() {};
    Casa(const char _oras[]);

    friend ostream& operator << (ostream& out, Casa& casa)
    {
        out << "Denumire oras: " << casa.oras << ' ';
        out << "Numar proprietari: " << casa.nrProprietari << "\n";
        if (casa.nrProprietari > 0)
        {
            out << "Proprietari:\n";
            for (int i=0; i < casa.nrProprietari; i++ )
            {
                out << "\tProprietar " << i << ":\t" << casa.Prop[i];
                out << "\n";
            }
        }
        return out;
    }

    friend istream& operator >> (istream& in, Casa& casa)
    {
        cout << "Introduceti Orasul: ";
        in >> casa.oras;
        cout << '\n';
        cout << "Introduceti Numar Proprietari: ";
        in >> casa.nrProprietari;
        casa.Prop = new Proprietar[casa.nrProprietari];
        for (int i=0; i < casa.nrProprietari; i++)
        {
            cout << "Proprietar " << i <<"\t";
            in >> casa.Prop[i];
        }
            return in;
    }

    void operator += (Proprietar& _proprietar)
    {
        Proprietar* _TempProp = new Proprietar[nrProprietari];
        for (int i = 0; i < nrProprietari; ++i)
        {
            _TempProp[i] = Prop[i];
        }
        delete Prop;
        nrProprietari = nrProprietari+1;
        Prop = new Proprietar[nrProprietari];
        for (int i=0; i< nrProprietari; i++)
        {
            if ( i != nrProprietari-1 )
                Prop[i] = _TempProp[i];
            else Prop[i] = _proprietar;
        }
    }

    //Remove a certain "propietar" from the array
    void operator -=(Proprietar& _proprietar){
        for(int i = 0; i < nrProprietari; ++i){
            if(Prop[i] == _proprietar){
                for (int j = i; j < nrProprietari - 1; ++j)
                {
                    Prop[j] = Prop[j+1]
                }
            }
            break;
        }
    }

    Casa& operator = (Casa& casa)
    {
        strcpy(oras, casa.oras);
        nrProprietari = casa.nrProprietari;
        Prop = new Proprietar[nrProprietari];
        for (int i=0; i< nrProprietari; i++)
            Prop[i] = casa.Prop[i];
        return *this;
    }
};

Casa::Casa(const char *_oras)
{
    strcpy(oras, _oras);
    nrProprietari = 0;
}

int main()
{
    Data d1(15,"iulie",1975), d2=d1;
    //cout << d2;
    Proprietar p1("Ionescu",d1), p2("Popescu",2,"ianuarie",1980);
    cout << p2;
    Casa c1("Bucuresti"), c2, c3;

    c1+=p1; // adauga proprietarul p1 in lista de proprietari din casa c1
    c1+=p2; // adauga proprietarul p2 in lista de proprietari din casa c1
    cout<<c1;
    cin>>c2;
    c3 = c2;
    cout<<c3;
    return 0;
}