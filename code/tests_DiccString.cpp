#include <iostream>
#include "mini_test.h"
#include "DiccString.h"

using namespace aed2;


/*
 * 13/11/2016 23:27
 *
 * Esto pasa todos los tests que se agregaron hasta el momento.
 * Es el mismo archivo del taller 4, así que no debería hacer
 * falta agregar más casos de prueba.
 *
 * --Nico
 */


//Chequea que el diccionario vacio no tenga claves
void test_claves_dicc_vacio() 
{
	DiccString<int> d;
	ASSERT(d.Claves().Cardinal() == 0);
	ASSERT(!NULL);
}


//Chequea el definir y definido
void test_definir_definido() 
{
	DiccString<int> d;
	d.Definir("hola",42);
	ASSERT( d.Definido("hola") );
	ASSERT( !d.Definido("casona") );
	ASSERT( !d.Definido("casa") );

	d.Definir("casona",13);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casona") );
	ASSERT( !d.Definido("casa") );

	d.Definir("casa",6);
	d.Definir("",0);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casona") );
	ASSERT( d.Definido("casa") );
	ASSERT( !d.Definido("cas") );
	ASSERT( !d.Definido("") );
}


//chequea el obtener
void test_obtener() 
{
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("casa",22);

	ASSERT( d.Obtener("hola") == 42 );
	ASSERT( d.Obtener("casa") == 22 );

	d.Definir("casa", 33);

	ASSERT( d.Obtener("casa") == 33 );
}


//chequea el borrar
void test_borrar() 
{
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("holanda",43);
	d.Definir("casa",22);
	d.Definir("colegio",12);
	d.Definir("cola",14);
	d.Definir("casona",21);

	ASSERT(d.Definido("hola"));
	ASSERT(d.Definido("casa"));
	ASSERT(d.Definido("casona"));
	ASSERT(d.Definido("cola"));
	ASSERT(d.Definido("colegio"));
	ASSERT(d.Definido("holanda"));

	ASSERT( d.Obtener("hola") == 42 );
	ASSERT( d.Obtener("casa") == 22 );
	ASSERT( d.Obtener("holanda") == 43 );
	ASSERT( d.Obtener("colegio") == 12 );
	ASSERT( d.Obtener("cola") == 14 );
	ASSERT( d.Obtener("casona") == 21 );

	d.Borrar("casona");

	ASSERT(d.Definido("hola"));
	ASSERT(d.Definido("casa"));
	ASSERT(!d.Definido("casona"));
	ASSERT(d.Definido("cola"));
	ASSERT(d.Definido("colegio"));
	ASSERT(d.Definido("holanda"));

	ASSERT( d.Obtener("hola") == 42 );
	ASSERT( d.Obtener("casa") == 22 );
	ASSERT( d.Obtener("holanda") == 43 );
	ASSERT( d.Obtener("colegio") == 12 );
	ASSERT( d.Obtener("cola") == 14 );

	d.Borrar("colegio");

	ASSERT(d.Definido("hola"));
	ASSERT(d.Definido("casa"));
	ASSERT(!d.Definido("casona"));
	ASSERT(d.Definido("cola"));
	ASSERT(!d.Definido("colegio"));
	ASSERT(d.Definido("holanda"));

	ASSERT( d.Obtener("hola") == 42 );
	ASSERT( d.Obtener("casa") == 22 );
	ASSERT( d.Obtener("holanda") == 43 );
	ASSERT( d.Obtener("cola") == 14 );

	d.Borrar("hola");

	ASSERT(!d.Definido("hola"));
	ASSERT(d.Definido("casa"));
	ASSERT(!d.Definido("casona"));
	ASSERT(d.Definido("cola"));
	ASSERT(!d.Definido("colegio"));
	ASSERT(d.Definido("holanda"));

	ASSERT( d.Obtener("casa") == 22 );
	ASSERT( d.Obtener("holanda") == 43 );
	ASSERT( d.Obtener("cola") == 14 );

	d.Borrar("casa");

	ASSERT(!d.Definido("hola"));
	ASSERT(!d.Definido("casa"));
	ASSERT(!d.Definido("casona"));
	ASSERT(d.Definido("cola"));
	ASSERT(!d.Definido("colegio"));
	ASSERT(d.Definido("holanda"));

	ASSERT( d.Obtener("holanda") == 43 );
	ASSERT( d.Obtener("cola") == 14 );

	d.Borrar("holanda");

	ASSERT(!d.Definido("hola"));
	ASSERT(!d.Definido("casa"));
	ASSERT(!d.Definido("casona"));
	ASSERT(d.Definido("cola"));
	ASSERT(!d.Definido("colegio"));
	ASSERT(!d.Definido("holanda"));

	ASSERT( d.Obtener("cola") == 14 );

	d.Borrar("cola");

	ASSERT(!d.Definido("hola"));
	ASSERT(!d.Definido("casa"));
	ASSERT(!d.Definido("casona"));
	ASSERT(!d.Definido("cola"));
	ASSERT(!d.Definido("colegio"));
	ASSERT(!d.Definido("holanda"));

	DiccString<int> e;
	e.Definir("oceano",2);
	e.Borrar("oceano");

}

void test_constructor_por_copia()
{
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("holanda",43);
	d.Definir("casa",22);
	d.Definir("colegio",12);
	d.Definir("cola",14);
	d.Definir("casona",21);

	DiccString<int> e(d);
	e.Definir("fruta",15);

	ASSERT(e.Definido("fruta"));
	ASSERT(!d.Definido("fruta"));
}

void test_borrar2()
{
	DiccString<int> e;
	e.Definir("oceano",2);

	ASSERT(e.Definido("oceano"));

	e.Borrar("oceano");

	ASSERT(!e.Definido("oceano"));

	e.Definir("oceano",3);
	

	DiccString<int> f(e);

	ASSERT(f.Definido("oceano"));

	f.Borrar("oceano");

	ASSERT(e.Definido("oceano"));
	ASSERT(!f.Definido("oceano"));
}

void test_borrar3()
{
	DiccString<int> d;
	d.Definir("hola", 1);
	d.Definir("holanda", 2);

	d.Borrar("hola");

	ASSERT(!d.Definido("hola"));
	ASSERT(d.Definido("holanda"));

	d.Borrar("holanda");

	ASSERT(!d.Definido("holanda"));
	ASSERT(!d.Definido("hola"));

	d.Definir("superagente", 86);

	DiccString<int> e;
	e.Definir("hola", 1);
	e.Definir("holanda", 2);

	e.Borrar("holanda");

	ASSERT(!e.Definido("holanda"));
	ASSERT(e.Definido("hola"));

	e.Borrar("hola");

	ASSERT(!e.Definido("holanda"));
	ASSERT(!e.Definido("hola"));

	e.Definir("superagente", 86);
}


int main() {
	RUN_TEST(test_claves_dicc_vacio);
	RUN_TEST(test_definir_definido);
	RUN_TEST(test_obtener);
	RUN_TEST(test_borrar);
	RUN_TEST(test_constructor_por_copia);
	RUN_TEST(test_borrar2);
	RUN_TEST(test_borrar3);
	
	return 0;

}
