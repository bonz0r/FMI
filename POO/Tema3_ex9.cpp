#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

class Produs
{
public:
    virtual float CalculPret()const = 0;
    virtual void Afisare() const = 0;
};

class Ingredient
{
    char* denumire;
    int cantitate;
    float pret_unitar;

public:
    Ingredient()
    {
        denumire = new char[strlen("nedefinit")];
        strcpy(denumire, "nedefinit");
        cantitate = 0;
        pret_unitar = 0;
    };
    ~Ingredient()
    {
        delete denumire;
    };
    Ingredient(const char* _denumire, int _cantitate, float _pret_unitar)
    {
        denumire = new char[strlen(_denumire)];
        strcpy(denumire, _denumire);
        cantitate = _cantitate;
        pret_unitar = _pret_unitar;
        cout << "Constructor pentru ingredient";
    }

    Ingredient (const Ingredient& ingredient)
    {
        denumire = new char[strlen(ingredient.denumire)];
        strcpy(denumire, ingredient.denumire);
        cantitate =  ingredient.cantitate;
        pret_unitar = ingredient.pret_unitar;
        cout << "Constructor de copiere pentru ingredient";
    }

    Ingredient& operator = (const Ingredient& ingredient);
    friend ostream& operator << (ostream& out, Ingredient& ingredient);
    friend istream& operator >> (istream& in, Ingredient& ingredient);

    float Pret();

    char *getDenumire() const;

    int getCantitate() const;

    float getPret_unitar() const;
};

Ingredient &Ingredient::operator=(const Ingredient &ingredient)
{
    denumire = new char[strlen(ingredient.denumire)];
    strcpy(denumire, ingredient.denumire);
    cantitate =  ingredient.cantitate;
    pret_unitar = ingredient.pret_unitar;

    return *this;
}

ostream &operator << (ostream &out, Ingredient &ingredient)
{
    out << "\n\tDenumire ingredient: " << ingredient.denumire;
    out << "\n\tCantitate ingredient: " << ingredient.cantitate;
    out << "\n\tPret unitar ingredient: " << ingredient.pret_unitar;
    out << "\n\tPret total: " << ingredient.pret_unitar * ingredient.cantitate;
    return out;
}

istream &operator >> (istream &in, Ingredient &ingredient)
{
    char _denumire[500];
    cout << "\nIntroduceti denumirea ingredientului: ";
    in.getline(_denumire, 500);
    ingredient.denumire = new char[strlen(_denumire)];
    strcpy(ingredient.denumire, _denumire);
    cout << "\nIntroduceti cantitatea: ";
    in >> ingredient.cantitate;
    cout << "\nIntroduceti pretul unitar: ";
    in >> ingredient.pret_unitar;

    return in;
}

float Ingredient::Pret()
{
    return (pret_unitar*cantitate);
}

char *Ingredient::getDenumire() const
{
    return denumire;
}

int Ingredient::getCantitate() const
{
    return cantitate;
}

float Ingredient::getPret_unitar() const
{
    return pret_unitar;
}

class Pizza: public Produs
{
    Ingredient* ingrediente;
    int nrIngrediente;
    char* denPizza;
    float pret_total, manopera;
public:
    Pizza()
    {
        ingrediente = nullptr;
        nrIngrediente = 0;
        denPizza = new char[strlen("nedefinit")];
        strcpy(denPizza, "nedefinit");
        pret_total = 0;
        manopera = 0;
    }

    ~Pizza(){delete ingrediente;}

    Pizza(Ingredient* _ingrediente, int _nrIngrediente, const char* _denPizza, float _manopera)
    {
        nrIngrediente = _nrIngrediente;
        if (nrIngrediente > 0)
        {
            ingrediente = new Ingredient[nrIngrediente];
            for (int i =0; i < nrIngrediente; i++)
                ingrediente[i] = _ingrediente[i];
        }
        denPizza = new char[strlen(_denPizza)];
        strcpy(denPizza, _denPizza);
        pret_total = 0;
        manopera = _manopera;
    }

    Pizza (Pizza& pizza)
    {
        nrIngrediente = pizza.nrIngrediente;
        if (nrIngrediente > 0)
        {
            ingrediente = new Ingredient[nrIngrediente];
            for (int i =0; i < nrIngrediente; i++)
                ingrediente[i] = pizza.ingrediente[i];
        }
        denPizza = new char[strlen(pizza.denPizza)];
        strcpy(denPizza, pizza.denPizza);
        pret_total = pizza.pret_total;
        manopera = pizza.manopera;
    }

    Pizza& operator = (const Pizza& pizza)
    {
        nrIngrediente = pizza.nrIngrediente;
        if (nrIngrediente > 0)
        {
            ingrediente = new Ingredient[nrIngrediente];
            for (int i =0; i < nrIngrediente; i++)
                ingrediente[i] = pizza.ingrediente[i];
        }
        denPizza = new char[strlen(pizza.denPizza)];
        strcpy(denPizza, pizza.denPizza);
        pret_total = pizza.pret_total;
        manopera = pizza.manopera;

        return *this;
    }

    friend ostream& operator << (ostream& out, const Pizza& pizza)
    {
        out << "Denumire Pizza: " << pizza.denPizza;
        out << "\nNumar Ingrediente: " << pizza.nrIngrediente;
        if (pizza.nrIngrediente > 0)
        {
            out << "\nIngrediente: ";
            for (int i = 0; i < pizza.nrIngrediente; i++)
                out << "\n\t" << pizza.ingrediente[i];
        }
        return out;
    }

    friend istream& operator >> (istream& in, Pizza& pizza)
    {
        char _denPizza[500],str[1];
        cout << "\nIntroduceti numele pizzei: ";
        in.getline(_denPizza,500);
        pizza.denPizza = new char[ strlen(_denPizza) ];
        strcpy(pizza.denPizza, _denPizza);
        cout << "\nIntroduceti nr ingrediente: ";
        in >> pizza.nrIngrediente;

        if(pizza.nrIngrediente > 0)
        {
            pizza.ingrediente = new Ingredient[pizza.nrIngrediente];
            cout << "\nIntroduceti ingredientele ";
            for (int i = 0; i < pizza.nrIngrediente; ++i)
            {
                cout << '\n';
                in.getline(str, 1);
                in >> pizza.ingrediente[i];
            }
        }
        cout << "\nIntroduceti costul manoperei: ";
        in >> pizza.manopera;
        pizza.pret_total = 0;
        return in;
    }

    void setPret_total(float pret_total)
    {
        Pizza::pret_total = pret_total;
    }


    float CalculPret() const override
    {
        float s = 0;
        for (int i = 0; i < nrIngrediente; i++)
        {
            s = s + ingrediente[i].Pret();
        }
        s = s + manopera;

        return s;
    }

    void Afisare() const override
    {
        cout << *this;
        cout << "\nPretul este: "<< this->CalculPret();
    }

    Ingredient *getIngrediente() const;

    int getNrIngrediente() const;

    char *getDenPizza() const;
};

Ingredient *Pizza::getIngrediente() const
{
    return ingrediente;
}

int Pizza::getNrIngrediente() const
{
    return nrIngrediente;
}

char *Pizza::getDenPizza() const
{
    return denPizza;
}

class OnLinePizza: public Pizza
{
    int distanta;

public:
    OnLinePizza(): Pizza()
    {
        distanta = 0;
    };

    ~OnLinePizza(){};
    OnLinePizza(int _distanta, Ingredient* _ingrediente, int _nrIngrediente, const char* _denPizza, float _manopera): Pizza( _ingrediente, _nrIngrediente, _denPizza, _manopera)
    {
        distanta = _distanta;
    };

    OnLinePizza (OnLinePizza& online): Pizza(static_cast<Pizza&>(online))
    {
        distanta = online.distanta;
    }

    friend ostream& operator << (ostream& out, OnLinePizza& oPizza)
    {
        out << static_cast<Pizza&>(oPizza);
        try
        {
            out << "\nDistanta: " << oPizza.distanta;
            if(oPizza.distanta < 0)
                throw 1;
        }catch (int x){
            if(x == 1)
                cout << "\nNu puteti introduce o distanta negativa";
        }
        return out;
    }

    void setDistanta(int distanta)
    {
        OnLinePizza::distanta = distanta;
    }

    float CalculPret() const override
    {
        float pret_dist;
        int dist;
        dist = distanta/10;
        float proc;
        proc = Pizza::CalculPret() * 0.05;
        float pret_pizz = Pizza::CalculPret();
        pret_dist = proc * dist + pret_pizz;
        return pret_dist;
    }

    int getDistanta() const;
};

int OnLinePizza::getDistanta() const
{
    return distanta;
}

template <class T>
class Meniu
{
    Pizza** pizze;
    static int index;

public:
    Pizza **getPizze() const;

    static int getIndex();

    Meniu()
    {
        pizze = nullptr;
    }
    ~Meniu(){delete pizze};

    Meniu& operator = (Meniu& menu)
    {
        pizze = new Pizza*[menu.index];
        for (int i=0; i< menu.index; i++)
            pizze[i] = menu.pizze[i];
        return *this;
    }

    void operator += (Pizza *pizza)
    {
            Pizza **temp;
            temp = new Pizza *[index];
            for (int i = 0; i < index; i++)
                temp[i] = pizze[i];
            delete (pizze);
            index++;
            pizze = new Pizza*[index];
            for (int i = 0; i< index; i++)
                if (i < index - 1)
                    pizze[i] = temp[i];
                else
                    pizze[i] =  pizza;
    }

    friend ostream& operator << (ostream& out, Meniu& meniu)
    {
        out << "\n\nMeniu Pizzeria X: ";
        out << "\nNumar tipuri Pizza: "<< meniu.index;
        if (meniu.index > 0)
        {
            out << "\nPizza: ";
            for (int i = 0; i < meniu.index; i++)
            {
                out << "\n\n" << i << ": \n"<< *meniu.pizze[i];
            }
        }
        return out;
    }

    void vegetariana()
    {
        float pret_total_veg = 0;
        bool ok;
        int index_veg = 0;
        for (int i=0; i< index; i++)
        {
            ok = false;
            if ((strcmp(pizze[i]->getDenPizza(), "vegetariana")==0)
                ||(strcmp(pizze[i]->getDenPizza(), "Vegetariana")==0))
                ok = true;
            ok = true;
            for (int j=0; j < pizze[i]->getNrIngrediente(); j++)
            {
                if ((strcmp(pizze[i]->getIngrediente()[j].getDenumire(), "carne") == 0)
                    || (strcmp(pizze[i]->getIngrediente()[j].getDenumire(), "carnati")== 0)
                    || (strcmp(pizze[i]->getIngrediente()[j].getDenumire(), "salam")== 0)
                    || (strcmp(pizze[i]->getIngrediente()[j].getDenumire(), "pui")== 0))
                    ok = false;
            }

            if (ok)
            {

                pret_total_veg = pret_total_veg + pizze[i]->CalculPret();

                index_veg++;
            }
        }
        ofstream contabil("Pret_Vegetariana.out");
        contabil << "Pretul pizza vegetariana per comanda este: " << pret_total_veg;
        contabil << "\nS-au vandut " << index_veg << " pizza vegetariene";
        contabil.close();
    }

    void verifica_exceptie();
};

template<>
void Meniu<int>::verifica_exceptie()
{
    for (int i = 0; i < index; i++)
        try
        {
            if (pizze[i]->getNrIngrediente() < 0)
                throw 1;
            for (int j=0; j < pizze[i]->getNrIngrediente(); j++)
            {
                if (pizze[i]->getIngrediente()[j].getCantitate() < 0)
                    throw 2;
                if (pizze[i]->getIngrediente()[j].getPret_unitar() < 0)
                    throw 3;
            }

        }catch(int valoare)
        {
            switch(valoare)
            {
                case 1:
                    cout << "\nNu puteti introduce numar negativ de ingrediente";
                    break;
                case 2:
                    cout << "\nNu puteti introduce o cantitate negativa de ingrediente";
                    break;
                case 3:
                    cout << "\nNu puteti introduce un pret negativ";
                    break;
                default:
                    cout << "\nEroare necunoscuta";
            }
            exit(-1);
        }
};

template <class T>
int Meniu <T> ::index = 0;

template<class T>
Pizza **Meniu<T>::getPizze() const
{
    return pizze;
}

template<class T>
int Meniu<T>::getIndex()
{
    return index;
}

int main()
{
    Pizza p;
    Ingredient i1("salam", 2, 2.36), i2("cascaval", 12, 3.6), i3[2], ingr[1];
    Ingredient i4("mozzarela", 4, 1.56), i5("sunca", 3, 6.5), i6("ketchup", 1, 3.4);
    i3[0]=i1;
    i3[1]=i2;
    i3[2]=i6;
    ingr[0] = i4;
    ingr[1] = i5;
    Pizza p1(i3, 2, "Rustica", 1.23), p2 = p1, p3(&ingr[1], 3, "Clasica", 3.4);
    //cout << i1;
   // cout << p1;
    Pizza pizzaaaa(ingr, 1, "Chili", 11);
    //OnLinePizza op = static_cast<OnLinePizza&>(pizzaaaa);
    //op.setDistanta(12);
    Pizza pizzaaa(&ingr[0], 1, "Pepperoni", 12);
    //OnLinePizza op_2(24, &ingr[0], 1, "Speciala", 12.5);
    Meniu <int> meniu, menu;
   // meniu += dynamic_cast<Pizza*>(&op);
   // meniu += &op_2;
    meniu += &p1;
    meniu += &p3;
    //cout << meniu;
    meniu.verifica_exceptie();
    meniu.vegetariana();
    int ch;

    bool ok = true;
    int k = 0, k2 = 0;
    while (ok)
    {
        cout << "\n\n 1 - Afisare Meniu prestabilit";
        cout << "\n 2 - Comanda Pizza";
        cout << "\n 3 - Exit";
        cout << "\n Introduceti alegerea : ";
        cin >> ch;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            system("cls");
            cout << "Introduceti cifre din optiunile de mai sus " << endl;
            cin >> ch;
        }


        switch (ch)
        {
            case 1:
                cout << meniu;
                break;
            case 2:
                int alegere, notonline, comanda, online, _distanta;
                cout << "\nDoriti sa comandati aceste pizza online?";
                cout << "\n\t 1. Da";
                cout << "\n\t 2. Nu";
                cin >> comanda;
                switch (comanda)
                {
                    case 1:
                        cout << "\nCe tip de pizza doriti?";
                        for (int i = 0; i < meniu.getIndex(); i++)
                        {
                            cout << "\n" << i << ": \t"<< meniu.getPizze()[i]->getDenPizza() << "\t" << meniu.getPizze()[i]->CalculPret();
                        }
                        cin >> online;
                        cout << "\nIntroduceti numarul de pizza dorite: ";
                        cin >> alegere;
                        cout << "\nIntroduceti distanta la care trebuie livrata pizza: ";
                        cin >> _distanta;
                        for (int i = 0; i < meniu.getIndex(); i++)
                        {
                            if (i == online)
                            {
                                Pizza pizzaaaaa = *meniu.getPizze()[i];
                                OnLinePizza op = static_cast<OnLinePizza&>(pizzaaaaa);
                                op.setDistanta(_distanta);
                                cout << "Costul total al comenzii este: ";
                                cout << alegere * op.CalculPret();
                            }
                        }
                        break;

                    case 2:
                        cout << "\nCe tip de pizza doriti?";
                        for (int i = 0; i < meniu.getIndex(); i++)
                        {
                            cout << "\n" << i << ": \t"<< meniu.getPizze()[i]->getDenPizza() << "\t" << meniu.getPizze()[i]->CalculPret();
                        }
                        cin >> notonline;
                        cout << "\nIntroduceti numarul de pizza dorite: ";
                        cin >> alegere;
                        for (int i = 0; i < meniu.getIndex(); i++)
                        {
                            if (i == notonline)
                            {
                                cout << "Costul total al comenzii este: ";
                                cout << alegere * meniu.getPizze()[i]->CalculPret();
                            }
                        }
                        break;

                    default:
                        cout << "Introduceti 1 sau 2";
                        cin >> comanda;
                        break;
                }
                break;
            case 3:
                ok = false;
                break;
            default:
                cout << "\nAlegere gresita. Reintroduceti alegerea";
                break;
        }
    }

    return 0;
}
