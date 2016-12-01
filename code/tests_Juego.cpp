#include <iostream>
#include <fstream>
#include "Juego.h"
#include "mini_test.h"

Nat cantPoke(const Pokemon& p, const Lista<Pokemon>& l)
{
    Lista<Pokemon>::const_Iterador it = l.CrearIt();
    Nat res = 0;

    while ( it.HaySiguiente() )
    {
        if ( it.Siguiente() == p )
        {
            res += 1;
        }

        it.Avanzar();
    }

    return res;
}


Conj<Jugador> armarConj(Conj<Jugador>::const_Iterador it)
{
    Conj<Jugador> res;

    while ( it.HaySiguiente() )
    {
        res.Agregar(it.Siguiente());
        it.Avanzar();
    }

    return res;
}


void test_crearJuego()
{
	Mapa m;

	Coordenada a(13,1);
	Coordenada b(11,24);
	Coordenada c(10,3);
	Coordenada e(10,2);
	Coordenada d(2,2);
	Coordenada f(20,2);
	Coordenada g(1,1);
	Coordenada h(1,2);
	Coordenada i(1,3);
	Coordenada j(1,10);
	Coordenada k(2,10);
	Coordenada c1(2,3);
	Coordenada c2(2,11);
	Coordenada c3(5,2);
	Coordenada c4(6,2);
	Coordenada c5(20,3);
	Coordenada c6(20,1);
	Coordenada c7(19,1);
	Coordenada c8(18,2);
	Coordenada c9(17,2);
	Coordenada c10(19,2);
	Coordenada c11(20,2);
	Coordenada c12(16,2);
	Coordenada c13(15,2);
	Coordenada c14(14,2);
	Coordenada c15(13,2);
	Coordenada c16(12,2);
	Coordenada c17(11,2);
	Coordenada c18(9,3);
	Coordenada c19(8,3);
	Coordenada c20(7,3);
	Coordenada c21(6,3);
	Coordenada c22(4,2);
	Coordenada c23(3,2);
	Coordenada c24(1,4);
	Coordenada c25(1,5);
	Coordenada c26(1,6);
	Coordenada c27(1,7);
	Coordenada c28(1,8);
	Coordenada c29(1,9);
	Coordenada c30(3,11);
	Coordenada c31(3,12);
	Coordenada c32(3,13);
	Coordenada c33(2,13);
	Coordenada c34(1,13);
	Coordenada c35(8,4);
	Coordenada c36(8,5);
	Coordenada c37(8,6);
	Coordenada c38(8,7);
	Coordenada c39(8,8);
	Coordenada c40(8,9);
	Coordenada c41(8,10);
	Coordenada c42(11,7);


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

	m.AgregarCoordenada(c1);
	m.AgregarCoordenada(c2);
	m.AgregarCoordenada(c3);
	m.AgregarCoordenada(c4);
	m.AgregarCoordenada(c5);
	m.AgregarCoordenada(c6);
	m.AgregarCoordenada(c7);
	m.AgregarCoordenada(c8);
	m.AgregarCoordenada(c9);
	m.AgregarCoordenada(c10);

	m.AgregarCoordenada(c11);
	m.AgregarCoordenada(c12);
	m.AgregarCoordenada(c13);
	m.AgregarCoordenada(c14);
	m.AgregarCoordenada(c15);
	m.AgregarCoordenada(c16);
	m.AgregarCoordenada(c17);
	m.AgregarCoordenada(c18);
	m.AgregarCoordenada(c19);
	m.AgregarCoordenada(c20);
	m.AgregarCoordenada(c21);
	m.AgregarCoordenada(c22);
	m.AgregarCoordenada(c23);
	m.AgregarCoordenada(c24);
	m.AgregarCoordenada(c25);
	m.AgregarCoordenada(c26);
	m.AgregarCoordenada(c27);
	m.AgregarCoordenada(c28);
	m.AgregarCoordenada(c29);
	m.AgregarCoordenada(c30);
	m.AgregarCoordenada(c31);
	m.AgregarCoordenada(c32);
	m.AgregarCoordenada(c33);
	m.AgregarCoordenada(c34);
	m.AgregarCoordenada(c35);
	m.AgregarCoordenada(c36);
	m.AgregarCoordenada(c37);
	m.AgregarCoordenada(c38);
	m.AgregarCoordenada(c39);
	m.AgregarCoordenada(c40);

	m.AgregarCoordenada(c42);

    Juego juego(m);
    ASSERT_EQ(juego.JugadoresConectados().EsVacio(),true);
    ASSERT_EQ(juego.TodosLosPokemons().EsVacia(),true);
    ASSERT_EQ(juego.PosConPokemons().EsVacio(),true);
    ASSERT_EQ(juego.PuedoAgregarPokemon(c42),true);
    ASSERT_EQ(juego.PuedoAgregarPokemon(c41),false);

}
void test_agregarPokemon()
{
    Mapa m;

    Coordenada a(13,1);
    Coordenada b(11,24);
    Coordenada c(10,3);
    Coordenada e(10,2);
    Coordenada d(2,2);
    Coordenada f(20,2);
    Coordenada g(1,1);
    Coordenada h(1,2);
    Coordenada i(1,3);
    Coordenada j(1,10);
    Coordenada k(2,10);
    Coordenada c1(2,3);
    Coordenada c2(2,11);
    Coordenada c3(5,2);
    Coordenada c4(6,2);
    Coordenada c5(20,3);
    Coordenada c6(20,1);
    Coordenada c7(19,1);
    Coordenada c8(18,2);
    Coordenada c9(17,2);
    Coordenada c10(19,2);
    Coordenada c11(20,2);
    Coordenada c12(16,2);
    Coordenada c13(15,2);
    Coordenada c14(14,2);
    Coordenada c15(13,2);
    Coordenada c16(12,2);
    Coordenada c17(11,2);
    Coordenada c18(9,3);
    Coordenada c19(8,3);
    Coordenada c20(7,3);
    Coordenada c21(6,3);
    Coordenada c22(4,2);
    Coordenada c23(3,2);
    Coordenada c24(1,4);
    Coordenada c25(1,5);
    Coordenada c26(1,6);
    Coordenada c27(1,7);
    Coordenada c28(1,8);
    Coordenada c29(1,9);
    Coordenada c30(3,11);
    Coordenada c31(3,12);
    Coordenada c32(3,13);
    Coordenada c33(2,13);
    Coordenada c34(1,13);
    Coordenada c35(8,4);
    Coordenada c36(8,5);
    Coordenada c37(8,6);
    Coordenada c38(8,7);
    Coordenada c39(8,8);
    Coordenada c40(8,9);
    Coordenada c41(8,10);
    Coordenada c42(11,7);


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

    m.AgregarCoordenada(c1);
    m.AgregarCoordenada(c2);
    m.AgregarCoordenada(c3);
    m.AgregarCoordenada(c4);
    m.AgregarCoordenada(c5);
    m.AgregarCoordenada(c6);
    m.AgregarCoordenada(c7);
    m.AgregarCoordenada(c8);
    m.AgregarCoordenada(c9);
    m.AgregarCoordenada(c10);

    m.AgregarCoordenada(c11);
    m.AgregarCoordenada(c12);
    m.AgregarCoordenada(c13);
    m.AgregarCoordenada(c14);
    m.AgregarCoordenada(c15);
    m.AgregarCoordenada(c16);
    m.AgregarCoordenada(c17);
    m.AgregarCoordenada(c18);
    m.AgregarCoordenada(c19);
    m.AgregarCoordenada(c20);
    m.AgregarCoordenada(c21);
    m.AgregarCoordenada(c22);
    m.AgregarCoordenada(c23);
    m.AgregarCoordenada(c24);
    m.AgregarCoordenada(c25);
    m.AgregarCoordenada(c26);
    m.AgregarCoordenada(c27);
    m.AgregarCoordenada(c28);
    m.AgregarCoordenada(c29);
    m.AgregarCoordenada(c30);
    m.AgregarCoordenada(c31);
    m.AgregarCoordenada(c32);
    m.AgregarCoordenada(c33);
    m.AgregarCoordenada(c34);
    m.AgregarCoordenada(c35);
    m.AgregarCoordenada(c36);
    m.AgregarCoordenada(c37);
    m.AgregarCoordenada(c38);
    m.AgregarCoordenada(c39);
    m.AgregarCoordenada(c40);
    m.AgregarCoordenada(c41);
    m.AgregarCoordenada(c42);
    Juego juego(m);
    Pokemon p="pikachu";
    Pokemon r="raichu";
    Pokemon ar="arbok";
    Pokemon n="nidoran";
    Pokemon v="vulpix";
    juego.AgregarPokemon(p,c40);
    juego.AgregarPokemon(r,a);
    juego.AgregarPokemon(r,c24);
    juego.AgregarPokemon(ar,c33);
    juego.AgregarPokemon(ar,c36);
    juego.AgregarPokemon(v,c29);
    juego.AgregarPokemon(p,c6);
    ASSERT_EQ(juego.JugadoresConectados().EsVacio(),true);
    ASSERT_EQ(juego.TodosLosPokemons().EsVacia(),false);
    ASSERT_EQ(juego.PosConPokemons().EsVacio(),false);
    ASSERT_EQ(juego.CantPokemonsTotales()==7,true);
    ASSERT_EQ(juego.PuedoAgregarPokemon(c41),false);
    ASSERT_EQ(juego.PuedoAgregarPokemon(c1),false);
    ASSERT_EQ(juego.CantMovimientosParaCaptura(c40)==0,true);
    ASSERT_EQ(juego.CantMismaEspecie(p)==2,true);
    ASSERT_EQ(juego.PosPokemonCercano(c39)==c40,true);

}

void test_agregarJugador()
{
    Mapa m;

    Coordenada a(13,1);
    Coordenada b(11,24);
    Coordenada c(10,3);
    Coordenada e(10,2);
    Coordenada d(2,2);
    Coordenada f(20,2);
    Coordenada g(1,1);
    Coordenada h(1,2);
    Coordenada i(1,3);
    Coordenada j(1,10);
    Coordenada k(2,10);
    Coordenada c1(2,3);
    Coordenada c2(2,11);
    Coordenada c3(5,2);
    Coordenada c4(6,2);
    Coordenada c5(20,3);
    Coordenada c6(20,1);
    Coordenada c7(19,1);
    Coordenada c8(18,2);
    Coordenada c9(17,2);
    Coordenada c10(19,2);
    Coordenada c11(20,2);
    Coordenada c12(16,2);
    Coordenada c13(15,2);
    Coordenada c14(14,2);
    Coordenada c15(13,2);
    Coordenada c16(12,2);
    Coordenada c17(11,2);
    Coordenada c18(9,3);
    Coordenada c19(8,3);
    Coordenada c20(7,3);
    Coordenada c21(6,3);
    Coordenada c22(4,2);
    Coordenada c23(3,2);
    Coordenada c24(1,4);
    Coordenada c25(1,5);
    Coordenada c26(1,6);
    Coordenada c27(1,7);
    Coordenada c28(1,8);
    Coordenada c29(1,9);
    Coordenada c30(3,11);
    Coordenada c31(3,12);
    Coordenada c32(3,13);
    Coordenada c33(2,13);
    Coordenada c34(1,13);
    Coordenada c35(8,4);
    Coordenada c36(8,5);
    Coordenada c37(8,6);
    Coordenada c38(8,7);
    Coordenada c39(8,8);
    Coordenada c40(8,9);
    Coordenada c41(8,10);
    Coordenada c42(11,7);


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

    m.AgregarCoordenada(c1);
    m.AgregarCoordenada(c2);
    m.AgregarCoordenada(c3);
    m.AgregarCoordenada(c4);
    m.AgregarCoordenada(c5);
    m.AgregarCoordenada(c6);
    m.AgregarCoordenada(c7);
    m.AgregarCoordenada(c8);
    m.AgregarCoordenada(c9);
    m.AgregarCoordenada(c10);

    m.AgregarCoordenada(c11);
    m.AgregarCoordenada(c12);
    m.AgregarCoordenada(c13);
    m.AgregarCoordenada(c14);
    m.AgregarCoordenada(c15);
    m.AgregarCoordenada(c16);
    m.AgregarCoordenada(c17);
    m.AgregarCoordenada(c18);
    m.AgregarCoordenada(c19);
    m.AgregarCoordenada(c20);
    m.AgregarCoordenada(c21);
    m.AgregarCoordenada(c22);
    m.AgregarCoordenada(c23);
    m.AgregarCoordenada(c24);
    m.AgregarCoordenada(c25);
    m.AgregarCoordenada(c26);
    m.AgregarCoordenada(c27);
    m.AgregarCoordenada(c28);
    m.AgregarCoordenada(c29);
    m.AgregarCoordenada(c30);
    m.AgregarCoordenada(c31);
    m.AgregarCoordenada(c32);
    m.AgregarCoordenada(c33);
    m.AgregarCoordenada(c34);
    m.AgregarCoordenada(c35);
    m.AgregarCoordenada(c36);
    m.AgregarCoordenada(c37);
    m.AgregarCoordenada(c38);
    m.AgregarCoordenada(c39);
    m.AgregarCoordenada(c40);
    m.AgregarCoordenada(c41);
    m.AgregarCoordenada(c42);

    Juego juego(m);
    Pokemon p="pikachu";
    juego.AgregarPokemon(p,c40);
    juego.AgregarJugador();
    juego.AgregarJugador();
    juego.AgregarJugador();
    juego.AgregarJugador();
    juego.AgregarJugador();
    ASSERT_EQ(juego.Jugadores().HaySiguiente(),true);
    ASSERT_EQ(juego.EstaConectado(0),false);
    ASSERT_EQ(juego.Sanciones(0)==0,true);

}


void test_conectar()
{
    Mapa m;

    Coordenada a(13,1);
    Coordenada b(11,24);
    Coordenada c(10,3);
    Coordenada e(10,2);
    Coordenada d(2,2);
    Coordenada f(20,2);
    Coordenada g(1,1);
    Coordenada h(1,2);
    Coordenada i(1,3);
    Coordenada j(1,10);
    Coordenada k(2,10);
    Coordenada c1(2,3);
    Coordenada c2(2,11);
    Coordenada c3(5,2);
    Coordenada c4(6,2);
    Coordenada c5(20,3);
    Coordenada c6(20,1);
    Coordenada c7(19,1);
    Coordenada c8(18,2);
    Coordenada c9(17,2);
    Coordenada c10(19,2);
    Coordenada c11(20,2);
    Coordenada c12(16,2);
    Coordenada c13(15,2);
    Coordenada c14(14,2);
    Coordenada c15(13,2);
    Coordenada c16(12,2);
    Coordenada c17(11,2);
    Coordenada c18(9,3);
    Coordenada c19(8,3);
    Coordenada c20(7,3);
    Coordenada c21(6,3);
    Coordenada c22(4,2);
    Coordenada c23(3,2);
    Coordenada c24(1,4);
    Coordenada c25(1,5);
    Coordenada c26(1,6);
    Coordenada c27(1,7);
    Coordenada c28(1,8);
    Coordenada c29(1,9);
    Coordenada c30(3,11);
    Coordenada c31(3,12);
    Coordenada c32(3,13);
    Coordenada c33(2,13);
    Coordenada c34(1,13);
    Coordenada c35(8,4);
    Coordenada c36(8,5);
    Coordenada c37(8,6);
    Coordenada c38(8,7);
    Coordenada c39(8,8);
    Coordenada c40(8,9);
    Coordenada c41(8,10);
    Coordenada c42(11,7);


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

    m.AgregarCoordenada(c1);
    m.AgregarCoordenada(c2);
    m.AgregarCoordenada(c3);
    m.AgregarCoordenada(c4);
    m.AgregarCoordenada(c5);
    m.AgregarCoordenada(c6);
    m.AgregarCoordenada(c7);
    m.AgregarCoordenada(c8);
    m.AgregarCoordenada(c9);
    m.AgregarCoordenada(c10);

    m.AgregarCoordenada(c11);
    m.AgregarCoordenada(c12);
    m.AgregarCoordenada(c13);
    m.AgregarCoordenada(c14);
    m.AgregarCoordenada(c15);
    m.AgregarCoordenada(c16);
    m.AgregarCoordenada(c17);
    m.AgregarCoordenada(c18);
    m.AgregarCoordenada(c19);
    m.AgregarCoordenada(c20);
    m.AgregarCoordenada(c21);
    m.AgregarCoordenada(c22);
    m.AgregarCoordenada(c23);
    m.AgregarCoordenada(c24);
    m.AgregarCoordenada(c25);
    m.AgregarCoordenada(c26);
    m.AgregarCoordenada(c27);
    m.AgregarCoordenada(c28);
    m.AgregarCoordenada(c29);
    m.AgregarCoordenada(c30);
    m.AgregarCoordenada(c31);
    m.AgregarCoordenada(c32);
    m.AgregarCoordenada(c33);
    m.AgregarCoordenada(c34);
    m.AgregarCoordenada(c35);
    m.AgregarCoordenada(c36);
    m.AgregarCoordenada(c37);
    m.AgregarCoordenada(c38);
    m.AgregarCoordenada(c39);
    m.AgregarCoordenada(c40);
    m.AgregarCoordenada(c41);
    m.AgregarCoordenada(c42);
    Juego juego(m);
    Pokemon p="pikachu";
    Pokemon r="raichu";
    Pokemon ar="arbok";
    Pokemon n="nidoran";
    Pokemon v="vulpix";
    juego.AgregarPokemon(p,c40);
    juego.AgregarPokemon(r,a);
    juego.AgregarPokemon(r,c24);
    juego.AgregarPokemon(ar,c33);
    juego.AgregarPokemon(ar,c36);
    juego.AgregarPokemon(v,c29);
    juego.AgregarPokemon(p,c6);
    juego.AgregarPokemon(n,c9);
    Jugador j0=juego.AgregarJugador();
    Jugador j1=juego.AgregarJugador();
    Jugador j2=juego.AgregarJugador();
    Jugador j3=juego.AgregarJugador();
    Jugador j4=juego.AgregarJugador();
    juego.Conectarse(j0,g);
    juego.Conectarse(j1,c25);
    juego.Conectarse(j2,c19);
    juego.Conectarse(j3,g);
    juego.Conectarse(j4,a);
    ASSERT_EQ(juego.EstaConectado(0),true);
    ASSERT_EQ(juego.EstaConectado(1),true);
    ASSERT_EQ(juego.EstaConectado(2),true);
    ASSERT_EQ(juego.EstaConectado(3),true);
    ASSERT_EQ(juego.EstaConectado(4),true);

}


void test_varios()
{
    Mapa m;

    Coordenada a(13,1);
    Coordenada b(11,24);
    Coordenada c(10,3);
    Coordenada e(10,2);
    Coordenada d(2,2);
    Coordenada f(20,2);
    Coordenada g(1,1);
    Coordenada h(1,2);
    Coordenada i(1,3);
    Coordenada j(1,10);
    Coordenada k(2,10);
    Coordenada c1(2,3);
    Coordenada c2(2,11);
    Coordenada c3(5,2);
    Coordenada c4(6,2);
    Coordenada c5(20,3);
    Coordenada c6(20,1);
    Coordenada c7(19,1);
    Coordenada c8(18,2);
    Coordenada c9(17,2);
    Coordenada c10(19,2);
    Coordenada c11(20,2);
    Coordenada c12(16,2);
    Coordenada c13(15,2);
    Coordenada c14(14,2);
    Coordenada c15(13,2);
    Coordenada c16(12,2);
    Coordenada c17(11,2);
    Coordenada c18(9,3);
    Coordenada c19(8,3);
    Coordenada c20(7,3);
    Coordenada c21(6,3);
    Coordenada c22(4,2);
    Coordenada c23(3,2);
    Coordenada c24(1,4);
    Coordenada c25(1,5);
    Coordenada c26(1,6);
    Coordenada c27(1,7);
    Coordenada c28(1,8);
    Coordenada c29(1,9);
    Coordenada c30(3,11);
    Coordenada c31(3,12);
    Coordenada c32(3,13);
    Coordenada c33(2,13);
    Coordenada c34(1,13);
    Coordenada c35(8,4);
    Coordenada c36(8,5);
    Coordenada c37(8,6);
    Coordenada c38(8,7);
    Coordenada c39(8,8);
    Coordenada c40(8,9);
    Coordenada c41(8,10);
    Coordenada c42(11,7);


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

    m.AgregarCoordenada(c1);
    m.AgregarCoordenada(c2);
    m.AgregarCoordenada(c3);
    m.AgregarCoordenada(c4);
    m.AgregarCoordenada(c5);
    m.AgregarCoordenada(c6);
    m.AgregarCoordenada(c7);
    m.AgregarCoordenada(c8);
    m.AgregarCoordenada(c9);
    m.AgregarCoordenada(c10);

    m.AgregarCoordenada(c11);
    m.AgregarCoordenada(c12);
    m.AgregarCoordenada(c13);
    m.AgregarCoordenada(c14);
    m.AgregarCoordenada(c15);
    m.AgregarCoordenada(c16);
    m.AgregarCoordenada(c17);
    m.AgregarCoordenada(c18);
    m.AgregarCoordenada(c19);
    m.AgregarCoordenada(c20);
    m.AgregarCoordenada(c21);
    m.AgregarCoordenada(c22);
    m.AgregarCoordenada(c23);
    m.AgregarCoordenada(c24);
    m.AgregarCoordenada(c25);
    m.AgregarCoordenada(c26);
    m.AgregarCoordenada(c27);
    m.AgregarCoordenada(c28);
    m.AgregarCoordenada(c29);
    m.AgregarCoordenada(c30);
    m.AgregarCoordenada(c31);
    m.AgregarCoordenada(c32);
    m.AgregarCoordenada(c33);
    m.AgregarCoordenada(c34);
    m.AgregarCoordenada(c35);
    m.AgregarCoordenada(c36);
    m.AgregarCoordenada(c37);
    m.AgregarCoordenada(c38);
    m.AgregarCoordenada(c39);
    m.AgregarCoordenada(c40);
    m.AgregarCoordenada(c41);
    m.AgregarCoordenada(c42);
    m.AgregarCoordenada(Coordenada(12,7));
    m.AgregarCoordenada(Coordenada(12,8));
    m.AgregarCoordenada(Coordenada(11,8));

    Juego juego(m);

    Pokemon p = "pikachu";
    Pokemon r = "raichu";
    Pokemon ar = "arbok";
    Pokemon n = "nidoran";
    Pokemon v = "vulpix";

    juego.AgregarPokemon(p,c40);
    juego.AgregarPokemon(r,a);
    juego.AgregarPokemon(r,c24);
    juego.AgregarPokemon(ar,c33);
    juego.AgregarPokemon(ar,c36);
    juego.AgregarPokemon(v,c29);
    juego.AgregarPokemon(p,c6);
    juego.AgregarPokemon(n,c9);
    Jugador j0 = juego.AgregarJugador();
    Jugador j1 = juego.AgregarJugador();
    Jugador j2 = juego.AgregarJugador();
    Jugador j3 = juego.AgregarJugador();
    Jugador j4 = juego.AgregarJugador();
    juego.Conectarse(j0,g);
    juego.Conectarse(j1,c25);
    juego.Conectarse(j2,c19);
    juego.Conectarse(j3,g);
    juego.Conectarse(j4,a);

    Conj<Coordenada> conj_pos_poke;
    conj_pos_poke.Agregar(c40);
    conj_pos_poke.Agregar(a);
    conj_pos_poke.Agregar(c24);
    conj_pos_poke.Agregar(c33);
    conj_pos_poke.Agregar(c36);
    conj_pos_poke.Agregar(c29);
    conj_pos_poke.Agregar(c6);
    conj_pos_poke.Agregar(c9);


    // Verifico que las posiciones con pokemons sean las correctas
    ASSERT( juego.PosConPokemons() == conj_pos_poke);

    // Verifico que la cantidad de pokemones salvajes total y separada por tipo
    // sea correcta
    ASSERT_EQ( juego.PokemonsSalvajes(juego.PosConPokemons()).Longitud(), 8 );
    ASSERT_EQ( cantPoke("pikachu", juego.PokemonsSalvajes(juego.PosConPokemons())), 2);
    ASSERT_EQ( cantPoke("raichu", juego.PokemonsSalvajes(juego.PosConPokemons())), 2);
    ASSERT_EQ( cantPoke("arbok", juego.PokemonsSalvajes(juego.PosConPokemons())), 2);
    ASSERT_EQ( cantPoke("nidoran", juego.PokemonsSalvajes(juego.PosConPokemons())), 1);
    ASSERT_EQ( cantPoke("vulpix", juego.PokemonsSalvajes(juego.PosConPokemons())), 1);

    juego.Moverse(j1, Coordenada(1,1));
    juego.Moverse(j2, Coordenada(1,1));

    ASSERT( juego.Posicion(j0) == Coordenada(1,1) );
    ASSERT( juego.Posicion(j1) == Coordenada(1,1) );
    ASSERT( juego.Posicion(j2) == Coordenada(1,1) );
    ASSERT( juego.Posicion(j3) == Coordenada(1,1) );
    ASSERT( juego.Posicion(j4) == Coordenada(13,1) );
    ASSERT_EQ(juego.CantMovimientosParaCaptura(Coordenada(13,1)), 2);

    ASSERT( juego.HayPokemonCercano(Coordenada(13,1)) );

    juego.Moverse(j2, Coordenada(1,1));
    juego.Moverse(j2, Coordenada(1,2));
    juego.Moverse(j2, Coordenada(1,1));
    juego.Moverse(j2, Coordenada(1,2));
    juego.Moverse(j2, Coordenada(1,1));
    juego.Moverse(j2, Coordenada(1,2));
    juego.Moverse(j2, Coordenada(1,1));
    juego.Moverse(j2, Coordenada(1,2)); // Acá debería capturarse el raichu que está en (13, 1).


    // Compruebo que se haya capturado un raichu. En particular, que lo haya hecho el jugador
    // j4
    typename Lista< typename Juego::Tupla<Pokemon,Nat> >::const_Iterador it = juego.Pokemons(j4);

    ASSERT( it.HaySiguiente() );
    ASSERT_EQ( it.Siguiente().primero(), "raichu" );
    ASSERT_EQ( juego.PokemonsCapturados(armarConj(juego.Jugadores())).Longitud(), 1 );
 

    // Verifico que la cantidad de pokemones salvajes total y separada por tipo
    // sea correcta
    ASSERT_EQ( juego.PokemonsSalvajes(juego.PosConPokemons()).Longitud(), 7 );
    ASSERT_EQ( cantPoke("pikachu", juego.PokemonsSalvajes(juego.PosConPokemons())), 2);
    ASSERT_EQ( cantPoke("raichu", juego.PokemonsSalvajes(juego.PosConPokemons())), 1);
    ASSERT_EQ( cantPoke("arbok", juego.PokemonsSalvajes(juego.PosConPokemons())), 2);
    ASSERT_EQ( cantPoke("nidoran", juego.PokemonsSalvajes(juego.PosConPokemons())), 1);
    ASSERT_EQ( cantPoke("vulpix", juego.PokemonsSalvajes(juego.PosConPokemons())), 1);
    
}


void test_capturarPoke()
{
    Mapa m;

    Coordenada a(13,1);
    Coordenada b(11,24);
    Coordenada c(10,3);
    Coordenada e(10,2);
    Coordenada d(2,2);
    Coordenada f(20,2);
    Coordenada g(1,1);
    Coordenada h(1,2);
    Coordenada i(1,3);
    Coordenada j(1,10);
    Coordenada k(2,10);
    Coordenada c1(2,3);
    Coordenada c2(2,11);
    Coordenada c3(5,2);
    Coordenada c4(6,2);
    Coordenada c5(20,3);
    Coordenada c6(20,1);
    Coordenada c7(19,1);
    Coordenada c8(18,2);
    Coordenada c9(17,2);
    Coordenada c10(19,2);
    Coordenada c11(20,2);
    Coordenada c12(16,2);
    Coordenada c13(15,2);
    Coordenada c14(14,2);
    Coordenada c15(13,2);
    Coordenada c16(12,2);
    Coordenada c17(11,2);
    Coordenada c18(9,3);
    Coordenada c19(8,3);
    Coordenada c20(7,3);
    Coordenada c21(6,3);
    Coordenada c22(4,2);
    Coordenada c23(3,2);
    Coordenada c24(1,4);
    Coordenada c25(1,5);
    Coordenada c26(1,6);
    Coordenada c27(1,7);
    Coordenada c28(1,8);
    Coordenada c29(1,9);
    Coordenada c30(3,11);
    Coordenada c31(3,12);
    Coordenada c32(3,13);
    Coordenada c33(2,13);
    Coordenada c34(1,13);
    Coordenada c35(8,4);
    Coordenada c36(8,5);
    Coordenada c37(8,6);
    Coordenada c38(8,7);
    Coordenada c39(8,8);
    Coordenada c40(8,9);
    Coordenada c41(8,10);
    Coordenada c42(11,7);


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

    m.AgregarCoordenada(c1);
    m.AgregarCoordenada(c2);
    m.AgregarCoordenada(c3);
    m.AgregarCoordenada(c4);
    m.AgregarCoordenada(c5);
    m.AgregarCoordenada(c6);
    m.AgregarCoordenada(c7);
    m.AgregarCoordenada(c8);
    m.AgregarCoordenada(c9);
    m.AgregarCoordenada(c10);

    m.AgregarCoordenada(c11);
    m.AgregarCoordenada(c12);
    m.AgregarCoordenada(c13);
    m.AgregarCoordenada(c14);
    m.AgregarCoordenada(c15);
    m.AgregarCoordenada(c16);
    m.AgregarCoordenada(c17);
    m.AgregarCoordenada(c18);
    m.AgregarCoordenada(c19);
    m.AgregarCoordenada(c20);
    m.AgregarCoordenada(c21);
    m.AgregarCoordenada(c22);
    m.AgregarCoordenada(c23);
    m.AgregarCoordenada(c24);
    m.AgregarCoordenada(c25);
    m.AgregarCoordenada(c26);
    m.AgregarCoordenada(c27);
    m.AgregarCoordenada(c28);
    m.AgregarCoordenada(c29);
    m.AgregarCoordenada(c30);
    m.AgregarCoordenada(c31);
    m.AgregarCoordenada(c32);
    m.AgregarCoordenada(c33);
    m.AgregarCoordenada(c34);
    m.AgregarCoordenada(c35);
    m.AgregarCoordenada(c36);
    m.AgregarCoordenada(c37);
    m.AgregarCoordenada(c38);
    m.AgregarCoordenada(c39);
    m.AgregarCoordenada(c40);
    m.AgregarCoordenada(c41);
    m.AgregarCoordenada(c42);
    Juego juego(m);
    Pokemon p="pikachu";
    Pokemon r="raichu";
    Pokemon ar="arbok";
    Pokemon n="nidoran";
    Pokemon v="vulpix";
   juego.AgregarPokemon(p,c40);
   juego.AgregarPokemon(r,a);
   juego.AgregarPokemon(r,c24);
   juego.AgregarPokemon(ar,c33);
   juego.AgregarPokemon(ar,c36);
   juego.AgregarPokemon(v,c29);
   juego.AgregarPokemon(p,c6);
   juego.AgregarPokemon(n,c9);
    Jugador j0=juego.AgregarJugador();
    Jugador j1=juego.AgregarJugador();
    Jugador j2=juego.AgregarJugador();
    Jugador j3=juego.AgregarJugador();
    Jugador j4=juego.AgregarJugador();
    juego.Conectarse(j0,g);
    juego.Conectarse(j1,c25);
    juego.Conectarse(j2,c19);
    juego.Conectarse(j3,g);
    juego.Conectarse(j4,c5);
    juego.Moverse(j2,c18);
    juego.Moverse(j2,c);
    juego.Moverse(j2,c17);
    juego.Moverse(j2,c16);
    juego.Moverse(j2,c15);
    juego.Moverse(j2,c14);
    juego.Moverse(j2,c13);
    juego.Moverse(j2,c12);
    juego.Moverse(j2,c9);
    ASSERT_EQ(juego.HayPokemonCercano(a),true);
    //ASSERT_EQ(juego.HayPokemonCercano(c6),true);
   // ASSERT_EQ(juego.HayPokemonCercano(c24),true);
    ASSERT_EQ(juego.HayPokemonCercano(c5),true);
    //ASSERT_EQ(juego.CantMovimientosParaCaptura(c24)==9,true)
    //ASSERT_EQ(juego.EntrenadoresPosibles(c24,juego.JugadoresConectados()).Pertenece(j1),true);
    ASSERT_EQ(juego.CantPokemonsTotales(),8);
    juego.Moverse(j2,c8);
    
}


    

int main()
{
    RUN_TEST(test_crearJuego);
    RUN_TEST(test_agregarPokemon);
    RUN_TEST(test_agregarJugador);
    RUN_TEST(test_conectar);
    RUN_TEST(test_varios);
    RUN_TEST(test_capturarPoke);

    return 0;
}
