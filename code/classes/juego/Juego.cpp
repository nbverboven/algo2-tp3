#include "Juego.h"

// Constructor
Juego::Juego() 
{

}

// Destructor
Juego::~Juego() 
{

}





/********************************************************************************
*********                        GENERADORES                            *********
*********************************************************************************/

void AgregarPokemon(const Pokemon poke, const Coordenada coord)
{
}

void AgregarJugador()
{
}

void Conectarse(const Jugador jug, Coordenada coord)
{
}

void Desconectarse(const Jugador jug)
{
}

void Moverse(const Jugador jug, const Coordenada coord)
{
}





/********************************************************************************
*********                     OBSERVADORES BÁSICOS                      *********
*********************************************************************************/

const Mapa Juego::Mapa() const
{
}

const Conj<Jugador>::const_Iterador Juego::Jugadores() const
{
}

const bool Juego::EstaConectado(const Juagdor jug) const
{
}

const Nat Juego::Sanciones(const Jugador jug) const
{
}

const Coordenada Juego::Posicion(const Jugador jug) const
{
}

const Vector<tuple<Pokemon, Nat>> Juego::Pokemons(const Jugador jug) const
{
}

const Vector<Jugador> Juego::Expulsados() const
{
}

const Vector<Coordenada> Juego::PosConPokemons() const
{
}

const Pokemon Juego::PokemonEnPos(const Coordenada coord) const
{
}

const Nat Juego::CantMovimientosParaCaptura(const Coordenada coord) const
{
}





/********************************************************************************
*********                      OTRAS OPERACIONES                        *********
*********************************************************************************/

const Jugador Juego::ProxID() const
{
}

const Lista<Jugador> Juego::JugadoresConectados() const
{
}

const Lista<Jugador> Juego::SoloLosConectados(const Conj<Jugador> jugadores) const
{
}

const bool Juego::PuedoAgregarPokemon(const Coordenada coord) const
{
}

const Conj<bool> Juego::HayPokemonEnTerritorio(const Coordenada coord, const Conj<Coordenada> conjCoord) const
{
}

const bool Juego::DebeSancionarse(const Jugador jug, const Coordenada coord) const
{
}

const bool Juego::DebeExpulsarse(const Jugador jug, const Coordenada coord) const
{
}

const Coordenada Juego::HayPokemonCercano(const Coordenada coord) const
{
}

const Coordenada Juego::PosPokemonCercano(const Coordenada coord) const
{
}

const Conj<Jugador> Juego::EntrenadoresPosibles(const Coordenada coord, const Conj<Jugador> jugadores) const
{
}

const Conj<Coordenada> Juego::PosDePokemonsACapturar(const Coordenada coord, const Conj<Coordenada> conjCoord) const
{
}

const bool Juego::SeCapturo(const Coordenada coord1, const Coordenada coord2) const
{
}

const Nat Juego::IndiceDeRareza(const Pokemon poke) const
{
}

const Nat Juego::CantPokemonsTotales() const
{
}

const Lista<Pokemon> Juego::TodosLosPokemons() const
{
}

const Lista<Pokemon> Juego::PokemonsSalvajes(const Conj<Coordenada> conjCoord) const
{
}

const Lista<Pokemon> Juego::PokemonsCapturados(const Conj<Jugador> jugadores) const
{
}

const Conj<Coordenada> Juego::BuscarPokemonsCercanos(const Coordenada coord, const Conj<Coordenada> conjCoord) const
{
}

const Nat Juego::CantMismaEspecie(const Pokemon poke, const Conj<Pokemon> pokemones) const
{
}





/********************************************************************************
*********                    FUNCIONES AUXILIARES                       *********
*********************************************************************************/

Arreglo< Arreglo<posStruct> > Juego::CrearPosiciones(const Mapa map)
{
}

void Juego::PosicionarPokemon(const Pokemon poke, const Coordenada coord, Conj<Coordenada>::const_Iterador itCoord)
{
}

void Juego::capturarPokemon(const Jugador jug, const Pokemon poke)
{
}

//  Constructor de pokemonACapturar
Juego::pokemonACapturar::pokemonACapturar(const Pokemon poke, Conj<Coordenada>::const_Iterador itCoord, ColaPrior< tuple<Nat, Jugador> > &jugACapturarlo)
{
}

//  Constructor de jugadorStruct
Juego::jugadorStruct::jugadorStruct(Conj<Jugador>::Iterador itNoExpulsados)
{
}