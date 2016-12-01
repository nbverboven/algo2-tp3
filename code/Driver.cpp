#include "Driver.h"

// Instanciar un mapa y un juego 

Driver::Driver(const Conj< Coordenada > & cs)
{
	Mapa m;
	Conj<Coordenada> c = cs;
	Conj<Coordenada>::const_Iterador it = c.CrearIt();

	while ( it.HaySiguiente() )
	{
		m.AgregarCoordenada(it.Siguiente());
	}

	driver_juego_ = Juego(m);
}


Driver::~Driver()
{}


void Driver::agregarPokemon(const Pokemon & p, const Coordenada & c)
{
	driver_juego_.AgregarPokemon(p, c);
}


Jugador Driver::agregarJugador()
{
	return driver_juego_.AgregarJugador();
}


void Driver::conectarse(const Jugador & j, const Coordenada & c)
{
	driver_juego_.Conectarse(j, c);
}


void Driver::desconectarse(const Jugador & j)
{
	driver_juego_.Desconectarse(j);
}


void Driver::moverse(const Jugador & j, const Coordenada & c)
{
	driver_juego_.Moverse(j, c);
}


Conj< Coordenada > Driver::mapa() const
{
	return driver_juego_.mapa().Coordenadas();
}


bool Driver::hayCamino(const Coordenada & c1, const Coordenada & c2) const
{
	return driver_juego_.mapa().HayCamino(c1, c2);
}


bool Driver::posExistente(const Coordenada & c) const
{
	return driver_juego_.mapa().PosicionExistente(c);
}


Conj< Jugador > Driver::jugadores() const
{
	Conj<Jugador> res;
	Conj<Jugador>::const_Iterador it = driver_juego_.Jugadores();

	while ( it.HaySiguiente() )
	{
		res.AgregarRapido(it.Siguiente());
		it.Avanzar();
	}

	return res;
}


bool Driver::estaConectado(const Jugador & j) const
{
	return driver_juego_.EstaConectado(j);
}


Nat Driver::sanciones(const Jugador & j) const
{
	return driver_juego_.Sanciones(j);
}


Coordenada Driver::posicion(const Jugador & j) const
{
	return driver_juego_.Posicion(j);
}


Dicc< Pokemon , Nat > Driver::pokemons(const Jugador & j) const
{
	Dicc<Pokemon,Nat> res;
	Lista< typename Juego::Tupla<Pokemon,Nat> >::const_Iterador it = driver_juego_.Pokemons(j);

	while ( it.HaySiguiente() )
	{
		Pokemon siguiente_pokemon = it.Siguiente().primero();
		Nat cantidad = it.Siguiente().segundo();

		res.Definir(siguiente_pokemon, cantidad);
		it.Avanzar();
	}

	return res;
}


Conj< Jugador > Driver::expulsados() const
{
	return driver_juego_.Expulsados();
}


Conj< Coordenada > Driver::posConPokemons() const
{
	return driver_juego_.PosConPokemons();
}


Pokemon Driver::pokemonEnPos(const Coordenada & c) const
{
	return driver_juego_.PokemonEnPos(c);
}


Nat Driver::cantMovimientosParaCaptura(const Coordenada & c) const
{
	return driver_juego_.CantMovimientosParaCaptura(c);
}


bool Driver::puedoAgregarPokemon(const Coordenada & c) const
{
	return driver_juego_.PuedoAgregarPokemon(c);
}


bool Driver::hayPokemonCercano(const Coordenada & c) const
{
	return driver_juego_.HayPokemonCercano(c);
}


Coordenada Driver::posPokemonCercano(const Coordenada & c) const
{
	return driver_juego_.PosPokemonCercano(c);
}


Conj<Jugador> Driver::entrenadoresPosibles(const Coordenada & c) const
{
	return driver_juego_.EntrenadoresPosibles(c, driver_juego_.JugadoresConectados());
}


Nat Driver::indiceRareza(const Pokemon & p) const
{
	return driver_juego_.IndiceDeRareza(p);
}


Nat Driver::cantPokemonsTotales() const
{
	return driver_juego_.CantPokemonsTotales();
}


Nat Driver::cantMismaEspecie(const Pokemon& p) const
{
	return driver_juego_.CantMismaEspecie(p);
}