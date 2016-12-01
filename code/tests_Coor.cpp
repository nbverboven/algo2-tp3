#include <iostream>
#include <fstream>
#include "Coordenada.h"
#include "mini_test.h"

using namespace std;
using namespace aed2;

/* 
 * 23/11/2016 -- 15:38 
 * Esto pasa todos los tests que agregué yo.
 *
 * --Nico
 */


void test_constructor()
{
	Coordenada c1(0, 0);
	Coordenada c2(1, 2);

	ASSERT_EQ(c1.Latitud(), 0);
	ASSERT_EQ(c1.Longitud(), 0);

	ASSERT_EQ(c2.Latitud(), 1);
	ASSERT_EQ(c2.Longitud(), 2);
}

void test_cambiar_Coordenada()
{
	Coordenada c1 = Coordenada(5, 10);

	Coordenada c2 = c1.CoordenadaArriba();

	ASSERT_EQ( c1.Latitud(), 5 );
	ASSERT_EQ( c1.Longitud(), 10 );

	Coordenada c3 = c1.CoordenadaAbajo();

	ASSERT_EQ( c1.Latitud(), 5 );
	ASSERT_EQ( c1.Longitud(), 10 );

	Coordenada c4 = c1.CoordenadaALaIzquierda();

	ASSERT_EQ( c1.Latitud(), 5 );
	ASSERT_EQ( c1.Longitud(), 10 );

	Coordenada c5 = c1.CoordenadaALaDerecha();

	ASSERT_EQ( c1.Latitud(), 5 );
	ASSERT_EQ( c1.Longitud(), 10 );

	ASSERT_EQ( c2.Latitud(), 6 );
	ASSERT_EQ( c2.Longitud(), 10 );

	ASSERT_EQ( c3.Latitud(), 4 );
	ASSERT_EQ( c3.Longitud(), 10 );

	ASSERT_EQ( c4.Latitud(), 5 );
	ASSERT_EQ( c4.Longitud(), 9 );

	ASSERT_EQ( c5.Latitud(), 5 );
	ASSERT_EQ( c5.Longitud(), 11 );
}

void test_ditEuclidea()
{
	Coordenada c1(5, 10);
	Coordenada c2(10, 5);
	Coordenada c3(1, 1);
	Coordenada c4(0, 0);

	ASSERT_EQ( Coordenada::distEuclidea(c3, c4), 2 )
	ASSERT_EQ( Coordenada::distEuclidea(c1, c2), 50 );
}

void test_asignacion()
{
	Coordenada c1 = Coordenada(1, 2);
	Coordenada c2 = Coordenada(2, 3);

	ASSERT_EQ( c1.Latitud(), 1 );
	ASSERT_EQ( c1.Longitud(), 2 );

	ASSERT_EQ( c2.Latitud(), 2 );
	ASSERT_EQ( c2.Longitud(), 3 );

	c1 = c2;

	ASSERT_EQ( c1.Latitud(), 2 );
	ASSERT_EQ( c1.Longitud(), 3 );

	ASSERT_EQ( c2.Latitud(), 2 );
	ASSERT_EQ( c2.Longitud(), 3 );

	c2 = c2.CoordenadaALaDerecha();

	ASSERT_EQ( c1.Latitud(), 2 );
	ASSERT_EQ( c1.Longitud(), 3 );

	ASSERT_EQ( c2.Latitud(), 2 );
	ASSERT_EQ( c2.Longitud(), 4 );

	c2 = c2.CoordenadaALaIzquierda();

	ASSERT_EQ( c1.Latitud(), 2 );
	ASSERT_EQ( c1.Longitud(), 3 );

	ASSERT_EQ( c2.Latitud(), 2 );
	ASSERT_EQ( c2.Longitud(), 3 );

	c2 = c2.CoordenadaArriba();

	ASSERT_EQ( c1.Latitud(), 2 );
	ASSERT_EQ( c1.Longitud(), 3 );

	ASSERT_EQ( c2.Latitud(), 3 );
	ASSERT_EQ( c2.Longitud(), 3 );

	c2 = c2.CoordenadaAbajo();

	ASSERT_EQ( c1.Latitud(), 2 );
	ASSERT_EQ( c1.Longitud(), 3 );

	ASSERT_EQ( c2.Latitud(), 2 );
	ASSERT_EQ( c2.Longitud(), 3 );
}


int main()
{
	RUN_TEST(test_constructor);
	RUN_TEST(test_cambiar_Coordenada);
	RUN_TEST(test_ditEuclidea);
	RUN_TEST(test_asignacion);
	return 0;
}