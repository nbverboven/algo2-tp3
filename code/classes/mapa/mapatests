#include <iostream>
#include <fstream>
#include "Mapa.h"
#include "../../mini_test.h"


void test_MapaVacio() {
	Mapa m;
	ASSERT_EQ(m.Coordenadas().EsVacio(),true);
	ASSERT_EQ(m.MaxLongitud(),0);
	ASSERT_EQ(m.MaxLatitud(),0)
}

void test_agregarCoordenada() {
	Mapa m;
	Coordenada a(1,1);
	Coordenada b(1,2);
	Coordenada c(1,3);
	Coordenada e(1,10);
	Coordenada d(2,2);
	Coordenada f(20,2);
	
	m.AgregarCoordenada(a);
	m.AgregarCoordenada(b);
	m.AgregarCoordenada(c);
	m.AgregarCoordenada(d);
	m.AgregarCoordenada(e);
	ASSERT_EQ(m.PosicionExistente(a),true);
	ASSERT_EQ(m.PosicionExistente(f),false);
	}

void test_Coordenadas() {
	Mapa m;
	Coordenada a(13,1);
	Coordenada b(11,24);
	Coordenada c(10,3);
	Coordenada e(7,10);
	Coordenada d(2,2);
	Coordenada f(20,2);
	m.AgregarCoordenada(a);
	m.AgregarCoordenada(b);
	m.AgregarCoordenada(c);
	m.AgregarCoordenada(d);
	m.AgregarCoordenada(e);
	m.AgregarCoordenada(f);
	m.AgregarCoordenada(d);
	m.AgregarCoordenada(e);
	m.AgregarCoordenada(f);
	ASSERT_EQ(m.Coordenadas().Cardinal(),6)
}

void test_posicionExistente() {
	Mapa m;
	Coordenada a(13,1);
	Coordenada b(11,24);
	Coordenada c(10,3);
	Coordenada e(7,10);
	Coordenada d(2,2);
	Coordenada f(20,2);
	m.AgregarCoordenada(a);
	m.AgregarCoordenada(b);
	m.AgregarCoordenada(c);
	m.AgregarCoordenada(e);
	m.AgregarCoordenada(a);
	m.AgregarCoordenada(b);
	ASSERT_EQ(m.PosicionExistente(a),true);
	ASSERT_EQ(m.PosicionExistente(b),true);
	ASSERT_EQ(m.PosicionExistente(c),true);
	ASSERT_EQ(m.PosicionExistente(d),false);
	ASSERT_EQ(m.PosicionExistente(e),true);
	ASSERT_EQ(m.PosicionExistente(f),false);
}
void test_HayCamino(){
	Mapa m;
	Coordenada a(13,1);
	Coordenada b(11,24);
	Coordenada c(10,3);
	Coordenada e(7,10);
	Coordenada d(2,2);
	Coordenada f(20,2);
	Coordenada g(1,1);
	Coordenada h(1,2);
	Coordenada i(1,3);
	Coordenada j(1,10);
	Coordenada k(2,2);
	Coordenada l(20,2);
	m.AgregarCoordenada(a);
	m.AgregarCoordenada(b);
	m.AgregarCoordenada(c);
	m.AgregarCoordenada(d);
	m.AgregarCoordenada(e);
	m.AgregarCoordenada(f);
	m.AgregarCoordenada(g);
	m.AgregarCoordenada(h);
	m.AgregarCoordenada(i);
	m.AgregarCoordenada(j);
	m.AgregarCoordenada(k);
	m.AgregarCoordenada(l);
	Mapa z;
	z=m;
	ASSERT_EQ(z.HayCamino(a,b),false);
	ASSERT_EQ(z.HayCamino(g,h),true);
	ASSERT_EQ(z.HayCamino(g,i),true);
	ASSERT_EQ(z.HayCamino(g,k),true);
	ASSERT_EQ(z.HayCamino(a,l),false);
	

}


int main()
{
    RUN_TEST(test_MapaVacio);
    RUN_TEST(test_agregarCoordenada);
    RUN_TEST(test_Coordenadas);
    RUN_TEST(test_posicionExistente);
    RUN_TEST(test_HayCamino);
    

    return 0;
}