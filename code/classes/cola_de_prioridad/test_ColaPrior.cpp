#include <iostream>
#include <fstream>
#include "ColaPrior.h"
#include "ColaPrior.cpp"
#include "../../mini_test.h"

using namespace std;
using namespace aed2;

/*
 * 20/11/2016 - 16:10
 * Pasa todos los tests que puse.
 * No pierde memoria.
 * 
 * --Nico
 */



/*
 * Esto es una una tupla de dos Nat que puse sólo para los casos de test. Tiene un constructor con parámetros
 * y un constructor por copia para poder usarlo en la cola de prioridad (recordar que los elementos se agregan por 
 * copia).
 * Habría que ver si en el caso más general no hace falta definir la clase por separado.
 *
 * --Nico
 */
struct TuplaReLoca
{
    TuplaReLoca(const Nat& p, const Nat& s) : fst_(p), snd_(s) {}
    TuplaReLoca(const TuplaReLoca& otra) { fst_ = otra.fst_, snd_ = otra.snd_; }

    const Nat& first() const { return fst_; }
    const Nat& second() const { return snd_; }

    bool operator<(const TuplaReLoca& otra) const { return fst_ < otra.fst_ || snd_ < otra.snd_; }

    bool operator==(const TuplaReLoca& otra) const { return fst_ == otra.fst_ && snd_ == otra.snd_; }

    Nat fst_;
    Nat snd_;
};

// Para mostrar las tuplas por pantalla
std::ostream& operator<<(std::ostream& os, const TuplaReLoca& t) 
{ os << '\n' << '<' << t.first() << ',' << t.second() << '>' << '\n'; }



void test_constructor()
{
    ColaPrior<int> cola();
    ColaPrior<TuplaReLoca> otra_cola();
}


void test_encolar()
{
    ColaPrior<int> cola;

    cola.encolar(3);
    cola.encolar(4);
    cola.encolar(6);
    cola.encolar(5);
}


void test_desencolar()
{
    ColaPrior<int> cola;

    ASSERT_EQ(cola.tamanio(), 0);
    cola.encolar(3);
    cola.encolar(4);
    cola.encolar(6);
    cola.encolar(5);


    cola.desencolar();
    cola.desencolar();
    cola.desencolar();
    cola.desencolar();
}


void test_esVacia()
{
    TuplaReLoca t1(1, 2);
    // cout << t1 << endl;
    ColaPrior<TuplaReLoca> cola;
    ColaPrior<TuplaReLoca> otra_cola;

    cola.encolar(t1);

    ASSERT(!cola.esVacia());
    ASSERT(otra_cola.esVacia());
    // cout << "Llegué hasta acá" << endl;
}


void test_tamanio()
{
    ColaPrior<int> c1;
    ColaPrior<int> c2;

    c2.encolar(1);

    ASSERT_EQ(c1.tamanio(), 0);
    ASSERT_EQ(c2.tamanio(), 1);

    c2.desencolar();

    ASSERT_EQ(c2.tamanio(), 0);
}


void test_proximo()
{
    ColaPrior<int> c1;

    c1.encolar(9);
    c1.encolar(4);
    c1.encolar(1);
    c1.encolar(6);
    c1.encolar(7);
    c1.encolar(3);
    c1.encolar(5);
    c1.encolar(8);

    cout << '\n' << "Estado inicial: " << c1 << '\n';

    ASSERT_EQ(c1.proximo(), 1);

    c1.desencolar();

    cout << "Desencolo por 1ra vez: " << c1 << '\n';

    ASSERT_EQ(c1.proximo(), 3);

    c1.desencolar();

    cout << "Desencolo por 2da vez: " << c1 << '\n';

    ASSERT_EQ(c1.proximo(), 4);

    c1.desencolar();

    cout << "Desencolo por 3ra vez: " << c1 << '\n';

    ASSERT_EQ(c1.proximo(), 5);

    c1.desencolar();

    cout << "Desencolo por 4ta vez: " << c1 << '\n';

    ASSERT_EQ(c1.proximo(), 6);

    c1.desencolar();

    cout << "Desencolo por 5ta vez: " << c1 << '\n';

    ASSERT_EQ(c1.proximo(), 7);

    c1.desencolar();

    cout << "Desencolo por 6ta vez: " << c1 << '\n';

    ASSERT_EQ(c1.proximo(), 8);

    c1.desencolar();

    cout << "Desencolo por 7ma vez: " << c1 << '\n';

    ASSERT_EQ(c1.proximo(), 9);

    c1.desencolar();

    cout << "Desencolo por 8va vez: " << c1 << '\n';

    ASSERT(c1.esVacia());
}


void test_borrar_elem_intermedio()
{
    ColaPrior<int> c1;

    c1.encolar(9);
    c1.encolar(4);
    c1.encolar(1);
    ColaPrior<int>::ItColaPrior it = c1.encolar(6);
    c1.encolar(7);
    c1.encolar(3);
    c1.encolar(5);
    c1.encolar(8);

    cout << '\n' << "Estado inicial: " << c1 << '\n';
    
    ASSERT_EQ(c1.tamanio(), 8);

    it.eliminarSiguiente();

    cout << "Borro el 6: " << c1 << '\n';

    ASSERT_EQ(c1.tamanio(), 7);
}


void test_borrar_elem_intermedio_2()
{
    ColaPrior<int> c1;

    ColaPrior<int>::const_ItColaPrior it1 = c1.encolar(9);
    ColaPrior<int>::const_ItColaPrior it2 = c1.encolar(4);
    ColaPrior<int>::const_ItColaPrior it3 = c1.encolar(1);
    ColaPrior<int>::ItColaPrior it4 = c1.encolar(6);
    ColaPrior<int>::const_ItColaPrior it5 = c1.encolar(7);
    ColaPrior<int>::const_ItColaPrior it6 = c1.encolar(3);
    ColaPrior<int>::const_ItColaPrior it7 = c1.encolar(5);
    ColaPrior<int>::const_ItColaPrior it8 = c1.encolar(8);

    cout << '\n' << "Estado inicial: " << c1 << '\n';

    ASSERT_EQ(it1.siguiente(), 9);
    ASSERT_EQ(it2.siguiente(), 4);
    ASSERT_EQ(it3.siguiente(), 1);
    ASSERT_EQ(it4.siguiente(), 6);
    ASSERT_EQ(it5.siguiente(), 7);
    ASSERT_EQ(it6.siguiente(), 3);
    ASSERT_EQ(it7.siguiente(), 5);
    ASSERT_EQ(it8.siguiente(), 8);

    cout << "El siguiente de it1 es: " << it1.siguiente() << '\n';
    cout << "El siguiente de it2 es: " << it1.siguiente() << '\n';
    cout << "El siguiente de it3 es: " << it1.siguiente() << '\n';
    cout << "El siguiente de it4 es: " << it1.siguiente() << '\n';
    cout << "El siguiente de it5 es: " << it1.siguiente() << '\n';
    cout << "El siguiente de it6 es: " << it1.siguiente() << '\n';
    cout << "El siguiente de it7 es: " << it1.siguiente() << '\n';
    cout << "El siguiente de it8 es: " << it1.siguiente() << '\n';

    cout << "Borro el 6: " << c1 << '\n';

    // Chequeo que no se modifiquen los valores a los que apuntan los iteradores

    ASSERT_EQ(it1.siguiente(), 9);
    ASSERT_EQ(it2.siguiente(), 4);
    ASSERT_EQ(it3.siguiente(), 1);
    ASSERT_EQ(it5.siguiente(), 7);
    ASSERT_EQ(it6.siguiente(), 3);
    ASSERT_EQ(it7.siguiente(), 5);
    ASSERT_EQ(it8.siguiente(), 8);

    cout << "El siguiente de it1 es: " << it1.siguiente() << '\n';
    cout << "El siguiente de it2 es: " << it1.siguiente() << '\n';
    cout << "El siguiente de it3 es: " << it1.siguiente() << '\n';
    cout << "El siguiente de it5 es: " << it1.siguiente() << '\n';
    cout << "El siguiente de it6 es: " << it1.siguiente() << '\n';
    cout << "El siguiente de it7 es: " << it1.siguiente() << '\n';
    cout << "El siguiente de it8 es: " << it1.siguiente() << '\n';
}


int main()
{
    RUN_TEST(test_constructor);
    RUN_TEST(test_encolar);
    RUN_TEST(test_desencolar);
    RUN_TEST(test_esVacia);
    RUN_TEST(test_tamanio);
    RUN_TEST(test_proximo);
    RUN_TEST(test_borrar_elem_intermedio);

    return 0;
}