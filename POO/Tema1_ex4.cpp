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
        zi = 0;
        strcpy(luna, "nedefinit");
        an = 0;
    }
    ~Data(){};
    Data(int _zi, const char _luna[], int _an);

    Data& operator = (const Data& _data)
    {
        zi = _data.zi;
        strcpy(luna, _data.luna);
        an = _data.an;
        return *this;
    }

    friend ostream& operator << (ostream& out, Data& _data)
    {
        out << "\n\tZiua: " << _data.zi;
        out << "\n\tLuna: " << _data.luna;
        out << "\n\tAnul: " << _data.an;
        return out;
    }
};

Data::Data(int _zi, const char *_luna, int _an)
{
    zi = _zi;
    strcpy(luna, _luna);
    an = _an;
}

class Actor
{
    char* nume;
    Data data_nasterii;

public:
    Actor()
    {
        nume = new char[strlen("nedefinit")];
        strcpy (nume, "nedefinit");
        data_nasterii= Data (0, "nedefinit", 0);
    }
    ~Actor(){};
    Actor(const char _nume[], Data _data);
    Actor(const char _nume[], int _zi, const char _luna[], int _an);

    friend ostream& operator << (ostream& out, Actor& actor)
    {
        out<< "\n\tNumele actorului: "<< actor.nume;
        out << "\n\t Data nasterii: "<< actor.data_nasterii;
        return out;
    }
};

Actor::Actor(const char _nume[], Data _data)
{
    nume = new char[strlen(_nume)];
    strcpy(nume, _nume);
    data_nasterii = _data;
}

Actor::Actor(const char *_nume, int _zi, const char _luna[], int _an)
{
    nume = new char[strlen(_nume)];
    strcpy(nume, _nume);
    data_nasterii = Data (_zi, _luna, _an);
}

class Film
{
    char titlu[50];
    int nrActori;
    Actor* Act;

public:
    Film()
    {
        strcpy(titlu, "nedefinit");
        nrActori=0;
    }
    ~Film(){};
    Film(const char _titlu[]);

    friend ostream& operator << (ostream& out, Film& film)
    {
        out << "\nTitlu: "<< film.titlu;
        out << "\nNumar actori: "<< film.nrActori;
        if ((film.nrActori > 0)&&(film.Act != nullptr))
        {
            out << "\nActori:";
            for (int i=0; i < film.nrActori; i++)
                out << "\n\tActor "<< i <<" :"<<film.Act[i];
        }
        return out;
    }

    void operator += (const Actor& actor)
    {
            Actor Temp[nrActori];
            for (int i=0; i< nrActori; i++)
                Temp[i]=Act[i];
            delete(Act);
            nrActori = nrActori+1;
            Act = new Actor[nrActori];
            for (int i=0; i < nrActori; i++)
                if (i < nrActori-1)
                    Act[i]=Temp[i];
                else
                    Act[i]=actor;
    }

    Film& operator = (Film& film)
    {

    }

};

Film::Film(const char _titlu[])
{
    strcpy(titlu, _titlu);
    nrActori=0;
    Act= nullptr;
}

int main()
{
    Data d1(15,"iulie",1975), d2=d1;
    //cout<< d1 << d2;
    Actor a1("Ionescu",d1), a2("Popescu",2,"ianuarie",1980);
    //cout << a1;
    //cout << a2;
    Film f1("Matrix"), f2, f3;
    f1+=a1; // adauga actorul a1 in lista filmului f1
    f1+=a2; // adauga actorul a2 in lista filmului f1
    cout<<f1;
    cin>>f2;
    f3 = f2;
    cout<<f3;
    return 0;
}