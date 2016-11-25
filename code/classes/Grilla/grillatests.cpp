#include <iostream>
#include <fstream>
#include "grilla.h"
#include "../../mini_test.h"

using namespace std;
using namespace aed2;


void test_Grilla() {
	Grilla<Nat> g;
	ASSERT_EQ(g.CantFilas(),0);
	ASSERT_EQ(g.CantColumnas(),0);
	ASSERT_EQ(g.EsVacio(),true)
}

void test_constructor() {
	Grilla <Nat> g;
	g.AgregarFilas(1,1);
	Grilla <Nat> f(g);
	ASSERT_EQ(g.CantFilas(),1);
	ASSERT_EQ(g.CantColumnas(),1);
	ASSERT_EQ(f.CantFilas(),1);
	ASSERT_EQ(f.CantColumnas(),1);
	}
void test_agregarFilas() {
	Grilla <Nat> g;
	g.AgregarFilas(3,4);
	g.AgregarFilas(1,5);
	ASSERT_EQ(g.CantFilas(),4);
	ASSERT_EQ(g(3,0),5)
}

void test_agregarColumnas() {
	Grilla <Nat> g;
	g.AgregarFilas(3,4);
	g.AgregarFilas(1,5);
	g.AgregarColumnas(2,0);
	ASSERT_EQ(g.CantFilas(),4);
	ASSERT_EQ(g.CantColumnas(),3);
	Grilla <Nat> f;
	f = g;
	ASSERT_EQ(f==g,true);
}



int main()
{
    RUN_TEST(test_Grilla);
    RUN_TEST(test_constructor);
    RUN_TEST(test_agregarFilas);
    RUN_TEST(test_agregarColumnas);
    

    return 0;
}