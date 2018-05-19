#include <iostream>
#include <fstream>
#include <vector>
#include "ColaPrior.h"
#include "mini_test.h"

using namespace std;
using namespace aed2;

/*
 * 20/11/2016 - 16:10
 * Pasa todos los tests que puse.
 * No pierde memoria.
 * 
 * --Nico
 *
 * 
 * 25/11/2016 - 17:32
 * Pasa los tests que había más
 * los que puse para eliminar elementos
 * intermedios
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
{ os << '\n' << '<' << t.first() << ',' << t.second() << '>' << '\n'; return os; }



void test_constructor()
{
    ColaPrior<int> cola();
    ColaPrior<TuplaReLoca> otra_cola();
}


void test_encolar()
{
    ColaPrior<int> c1;

    c1.encolar(9);
    c1.encolar(4);
    c1.encolar(1);
    c1.encolar(6);
    c1.encolar(7);
    c1.encolar(3);
    c1.encolar(5);
}


void test_desencolar()
{
    ColaPrior<int> c1;

    c1.encolar(9);
    c1.encolar(4);
    c1.encolar(1);
    c1.encolar(6);
    c1.encolar(7);
    c1.encolar(3);
    c1.encolar(5);

    c1.desencolar();
    c1.desencolar();
    c1.desencolar();
}


void test_esVacia()
{
    TuplaReLoca t1(1, 2);

    ColaPrior<TuplaReLoca> cola;
    ColaPrior<TuplaReLoca> otra_cola;

    cola.encolar(t1);

    ASSERT(!cola.esVacia());
    ASSERT(otra_cola.esVacia());
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

    cout << '\n' << '\n' << "======================== TEST PROXIMO =======================" << '\n';

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

    cout << '\n' << "====================== fin TEST PROXIMO =====================" << '\n';
}


void test_borrar_elem_intermedio()
{
    ColaPrior<int> c1;

    c1.encolar(9);
    c1.encolar(4);
    c1.encolar(1);
    ColaPrior<int>::ItColaPrior it = c1.encolar(6);
    c1.encolar(7);
    ColaPrior<int>::ItColaPrior it2 = c1.encolar(3);
    c1.encolar(5);
    c1.encolar(8);

    cout << '\n' << "Estado inicial: " << c1 << '\n';
    
    it.eliminarSiguiente();
    cout << "Borro el 6: " << c1 << '\n';

    it2.eliminarSiguiente();
    cout << "Borro el 3: " << c1 << '\n';

}


void test_borrar_elem_intermedio_2()
{
    cout << '\n' << '\n' << "=============== TEST BORRAR_ELEM_INTERMEDIO_2 ===============" << '\n';

    ColaPrior<int> c1;

    ColaPrior<int>::ItColaPrior it1 = c1.encolar(9);
    cout << '\n' << "Encolo el 9 y lo apunto con it1" << '\n';

    ColaPrior<int>::ItColaPrior it2 = c1.encolar(4);
    cout << "Encolo el 4 y lo apunto con it2" << '\n';

    ColaPrior<int>::ItColaPrior it3 = c1.encolar(1);
    cout << "Encolo el 1 y lo apunto con it3" << '\n';

    ColaPrior<int>::ItColaPrior it4 = c1.encolar(6);
    cout << "Encolo el 6 y lo apunto con it4" << '\n';

    ColaPrior<int>::ItColaPrior it5 = c1.encolar(7);
    cout << "Encolo el 7 y lo apunto con it5" << '\n';

    ColaPrior<int>::ItColaPrior it6 = c1.encolar(3);
    cout << "Encolo el 3 y lo apunto con it6" << '\n';

    ColaPrior<int>::ItColaPrior it7 = c1.encolar(5);
    cout << "Encolo el 5 y lo apunto con it7" << '\n';

    ColaPrior<int>::ItColaPrior it8 = c1.encolar(8);
    cout << "Encolo el 8 y lo apunto con it8" << '\n';


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
    cout << "El siguiente de it2 es: " << it2.siguiente() << '\n';
    cout << "El siguiente de it3 es: " << it3.siguiente() << '\n';
    cout << "El siguiente de it4 es: " << it4.siguiente() << '\n';
    cout << "El siguiente de it5 es: " << it5.siguiente() << '\n';
    cout << "El siguiente de it6 es: " << it6.siguiente() << '\n';
    cout << "El siguiente de it7 es: " << it7.siguiente() << '\n';
    cout << "El siguiente de it8 es: " << it8.siguiente() << '\n';

    it4.eliminarSiguiente();

    cout << '\n' << "Borro el 6: " << c1 << '\n';


    // Chequeo que no se modifiquen los valores a los que apuntan los iteradores

    ASSERT_EQ(it1.siguiente(), 9);
    ASSERT_EQ(it2.siguiente(), 4);
    ASSERT_EQ(it3.siguiente(), 1);
    ASSERT_EQ(it5.siguiente(), 7);
    ASSERT_EQ(it6.siguiente(), 3);
    ASSERT_EQ(it7.siguiente(), 5);
    ASSERT_EQ(it8.siguiente(), 8);

    cout << "El siguiente de it1 es: " << it1.siguiente() << '\n';
    cout << "El siguiente de it2 es: " << it2.siguiente() << '\n';
    cout << "El siguiente de it3 es: " << it3.siguiente() << '\n';
    cout << "El siguiente de it5 es: " << it5.siguiente() << '\n';
    cout << "El siguiente de it6 es: " << it6.siguiente() << '\n';
    cout << "El siguiente de it7 es: " << it7.siguiente() << '\n';
    cout << "El siguiente de it8 es: " << it8.siguiente() << '\n';

    it6.eliminarSiguiente();

    cout << '\n' << "Borro el 3: " << c1 << '\n';

    it8.eliminarSiguiente();

    cout << "Borro el 8: " << c1 << '\n';

    it3.eliminarSiguiente();

    cout << "Borro el 1: " << c1 << '\n';

    cout << '\n' << "============= fin TEST BORRAR_ELEM_INTERMEDIO_2 =============" << '\n';
}


void test_modificar_elem_intermedio()
{
	ColaPrior<int> c1;

	c1.encolar(9);
	c1.encolar(4);
	c1.encolar(1);
	ColaPrior<int>::ItColaPrior it = c1.encolar(6);
	c1.encolar(7);
	ColaPrior<int>::ItColaPrior it2 = c1.encolar(3);
	c1.encolar(5);
	c1.encolar(8);

	cout << '\n' << "Estado inicial: " << c1 << '\n';
	
	it.modificarSiguiente(0);
	cout << "Cambio el 6 por un 10: " << c1 << '\n';
	ASSERT_EQ(c1.proximo(), 0);

	it2.modificarSiguiente(-1);
	cout << "Cambio el 3 por un -1: " << c1 << '\n';
	ASSERT_EQ(c1.proximo(), -1);

	it2.modificarSiguiente(5);
	cout << "Cambio el -1 por un 5: " << c1 << '\n';
	ASSERT_EQ(c1.proximo(), 0);
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
	RUN_TEST(test_borrar_elem_intermedio_2);
	RUN_TEST(test_modificar_elem_intermedio);

	return 0;
}