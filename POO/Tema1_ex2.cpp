#include <iostream>
#include <string.h>
using namespace std;

//class Pizza;

class Ingredient
{
    char* nume;
    float pret;
    int cantitate;
    float profitabilitate;
public:
    Ingredient();
    ~Ingredient();
    Ingredient(const char _nume[], float _pret, int _cantitate);
    Ingredient ( Ingredient &ingredient);

    friend ostream& operator << (ostream& out, Ingredient &ingredient)
    {
        out << ingredient.nume << ", ";
        out << ingredient.pret << ", ";
        out << ingredient.cantitate << ", ";
        out << ingredient.profitabilitate << "\n"; 
        return out;
    }

    // Vrem sa putem citi direct ingredientele pentru simplitate
    friend istream& operator >> (istream& in, Ingredient& ingredient)
    {
        char _nume[250];
        float _pret;
        int _cantitate;
        float _profitabilitate;
        cout << "Nume ingredient:";
        in.getline(_nume, 250);
        ingredient.nume = new char[strlen(_nume)];
        strcpy(ingredient.nume, _nume);
        cout << "\nPret ingredient:";
        in >> _pret;
        ingredient.pret = _pret;
        cout << "\nCantitate:";
        in >> _cantitate;
        ingredient.cantitate = _cantitate;
        in >> _profitabilitate;
        ingredient.profitabilitate = _profitabilitate;
        return in;
    }

    void operator += (int _cantitate)
    {
        cantitate = cantitate + _cantitate;
    }

    Ingredient& operator = (const Ingredient& ingredient)
    {
        nume = new char[strlen(ingredient.nume)];
        strcpy (nume, ingredient.nume);
        pret = ingredient.pret;
        cantitate =  ingredient.cantitate;
    }



};

Ingredient::Ingredient()
{

}

Ingredient::~Ingredient()
{

}

Ingredient::Ingredient(const char *_nume, float _pret, int _cantitate)
{
    nume= new char[strlen(_nume)];
    strcpy(nume, _nume);
    pret = _pret;
    cantitate = _cantitate;
}

Ingredient::Ingredient(Ingredient &ingredient)
{
    nume = new char[strlen(ingredient.nume)];
    strcpy (nume, ingredient.nume);
    pret = ingredient.pret;
    cantitate =  ingredient.cantitate;
}

class Pizza
{
    char denumire[50];
    int nrIngrediente;
public:
    void setNrIngrediente(int nrIngrediente);

    void setIngr(Ingredient *Ingr);

private:
    Ingredient* Ingr;
public:
    const char *getDenumire() const;

    int getNrIngrediente() const;

    Ingredient *getIngr() const;

public:
    Pizza();
    ~Pizza(){};
    Pizza(const char _denumire[]);

    Pizza& operator = (const Pizza& pizza)
    {
        strcpy(denumire, pizza.denumire);
        nrIngrediente = pizza.nrIngrediente;
        Ingr = new Ingredient[nrIngrediente];
        for (int i=0; i < nrIngrediente; i++)
            Ingr[i] = pizza.Ingr[i];

        return *this;
    }

    friend ostream& operator << (ostream& out, Pizza& pizza)
    {
        out << "denumire: ";
        out << pizza.denumire << "\n";
        out << "Numar Ingrediente: ";
        out << pizza.nrIngrediente << "\n";
        if ( pizza.nrIngrediente > 0)
        {
            out << "Ingrediente: ";
            for (int i=0; i < pizza.nrIngrediente; i++)
            {
                out << pizza.Ingr[i]<< ' ';
            };
        }

        return out;
    }

    friend istream& operator >> (istream& in, Pizza &pizza)
    {
        cout << "Introduceti denumirea pizzei: ";
        in >> pizza.denumire;
        cout << "\n";
        cout << "Introduceti numarul de ingrediente: ";
        in >> pizza.nrIngrediente;
        if (pizza.nrIngrediente > 0 )
        {
            cout << "Introduceti ingredientele pentru pizza: \n";
            pizza.Ingr = new Ingredient[pizza.nrIngrediente];
            for (int i=0; i < pizza.nrIngrediente; i++)
            {
                char str[1];
                cout << "Indredientul " << i << ' ';
                in.getline(str, 1);
                in >> pizza.Ingr[i];
                cout << ' ';
            }
        }

        return in;
    }

    friend Pizza operator + (Ingredient& ingredient, Pizza& _pizza)
    {
        // i1.operator+( pizza1 ) //adauga i1 la pizza1
        Ingredient ingrTmp[_pizza.getNrIngrediente()];
        for (int i = 0; i < _pizza.getNrIngrediente(); ++i)
        {
            ingrTmp[i] = _pizza.getIngr()[i];
        }
        delete _pizza.getIngr();
        _pizza.setIngr(new Ingredient[_pizza.getNrIngrediente()+1]);
        _pizza.setNrIngrediente(_pizza.getNrIngrediente()+1);
        for (int i=0; i < _pizza.getNrIngrediente(); i++)
            if (i == _pizza.getNrIngrediente()-1)
                _pizza.getIngr()[i] = ingredient;
            else
                _pizza.getIngr()[i] = ingrTmp[i];
        return _pizza;
    };

    bool operator > (Pizza& pizza)
    {
        return(nrIngrediente > pizza.nrIngrediente);
    }
};


Pizza::Pizza()
{
    strcpy(denumire,"Nedenumit");
    nrIngrediente = 0;
}

Pizza::Pizza(const char *_denumire)
{
    strcpy(denumire, _denumire);
    nrIngrediente = 0;
}

const char *Pizza::getDenumire() const
{
    return denumire;
}

int Pizza::getNrIngrediente() const
{
    return nrIngrediente;
}

Ingredient *Pizza::getIngr() const
{
    return Ingr;
}

void Pizza::setNrIngrediente(int nrIngrediente)
{
    Pizza::nrIngrediente = nrIngrediente;
}

void Pizza::setIngr(Ingredient *Ingr)
{
    Pizza::Ingr = Ingr;
}


int main()
{
    Ingredient i1("Piper",0.5, 10), i2("Nimic", 0.0, 0);
    cout<<i1;
    cin>>i2;
    cout << i2;
    i1 += 500; // aduna o valoare la cantitatea disponibila
    Ingredient i3 = i1, i4, i5(i1);
    i4 = i1;
    Pizza pizza1("Clasic"), pizza2;
    pizza1 = i1 + pizza1; // adaugare ingredient 1 in pizza 1
    pizza1 = i2 + pizza1;

    cout << pizza1;
    cin>>pizza2;
    cout << pizza2;
    cout<<pizza1<<pizza2;
    if (pizza1 > pizza2) cout<<"pizza1 are mai multe ingrediente decat pizza2";
    else cout<<"pizza2 are mai multe ingrediente decat pizza1";

    return 0;
}