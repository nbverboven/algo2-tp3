#ifndef H_JUEGO
#define H_JUEGO

#include "../aed2/aed2.h"
#include "../cola_de_prioridad/ColaPrior.h"
#include "../coordenada/Coordenada.h"
#include "../diccionario_string/DiccString.h"
#include "../Grilla/grilla.h"
#include "../mapa/Mapa.h"

using namespace aed2;
using namespace std;


class Juego
{

public:

    // Forward declarations
    struct TuplaPokeNat;
    struct TuplaNatJug;
    struct JugadorStruct;

    // Constructor y destructor
    Juego(); //CrearJuego
    ~Juego();

    // Generadores
    void AgregarPokemon(const Pokemon& poke, const Coordenada& coord);
    Nat AgregarJugador(const Jugador& jugador);
    void Conectarse(const Jugador& jug, Coordenada coord);
    void Desconectarse(const Jugador& jug);
    void Moverse(const Jugador& jug, const Coordenada& coord);

    // Observadores básicos
    Mapa Mapa() const;
    Conj<Jugador>::const_Iterador Jugadores() const;
    bool EstaConectado(const Jugador& jug) const;
    Nat Sanciones(const Jugador& jug) const;
    Coordenada Posicion(const Jugador& jug) const;
    Lista< TuplaPokeNat>::Iterador Pokemons(const Jugador& jug) const;
    Conj<Jugador> Expulsados() const;
    Conj<Coordenada> PosConPokemons() const;
    Pokemon PokemonEnPos(const Coordenada& coord) const;
    Nat CantMovimientosParaCaptura(const Coordenada& coord) const;

    // Otras operaciones
    Jugador ProxID() const;
    Conj<Jugador> JugadoresConectados() const;
    Conj<Jugador> SoloLosConectados(const Conj<Jugador>& jugadores) const;
    bool PuedoAgregarPokemon(const Coordenada& coord) const;
    Conj<bool> HayPokemonEnTerritorio(const Coordenada& coord, const Conj<Coordenada>& conjCoord) const;
    bool DebeSancionarse(const Jugador& jug, const Coordenada& coord) const;
    bool DebeExpulsarse(const Jugador& jug, const Coordenada& coord) const;
    Coordenada HayPokemonCercano(const Coordenada& coord) const;
    Coordenada PosPokemonCercano(const Coordenada& coord) const;
    Conj<Jugador> EntrenadoresPosibles(const Coordenada& coord, const Conj<Jugador>& jugadores) const;
    Conj<Coordenada> PosDePokemonsACapturar(const Coordenada& coord, const Conj<Coordenada>& conjCoord) const;
    bool SeCapturo(const Coordenada& coord1, const Coordenada& coord2) const;
    Nat IndiceDeRareza(const Pokemon& poke) const;
    Nat CantPokemonsTotales() const;
    Lista<Pokemon> TodosLosPokemons() const;
    Lista<Pokemon> PokemonsSalvajes(const Conj<Coordenada>& conjCoord) const;
    Lista<Pokemon> PokemonsCapturados(const Conj<Jugador>& jugadores) const;
    Conj<Coordenada> BuscarPokemonsCercanos(const Coordenada& coord, const Conj<Coordenada>& conjCoord) const;
    Nat CantMismaEspecie(const Pokemon poke, const Conj<Pokemon>& pokemones) const;

    /*friend ostream& operator<<(ostream& os) {
        return os;
    }*/

private:

    /*struct pokemonCapturado
    {
        Pokemon pokemon;
        Nat cantidad;
    };*/

    struct posStruct
    {
        ColaPrior< TuplaNatJug > jugadores;
        pokemonACapturar* pokemonACapturar;
    };

    struct pokemonACapturar
    {
        pokemonACapturar(const Pokemon& poke, Conj<Coordenada>::const_Iterador itCoord, ColaPrior< TuplaNatJug > &jugACapturarlo);

        Pokemon pokemon;
        Nat movAfuera;
        Conj<Coordenada>::Iterador itCoord;
        ColaPrior< TuplaNatJug > jugACapturarlo;
    };

    struct TuplaNatJug
    {
        TuplaNatJug(const Nat& p, const Jugador& s) : cant_(p), jug_(s) {}
        TuplaNatJug(const TuplaNatJug& otra) { cant_ = otra.cant_, jug_ = otra.jug_; }
        const Nat& cant() const { return cant_; }
        const Jugador& jug() const { return jug_; }
        bool operator<(const TuplaNatJug& otra) const { return cant_ < otra.cant_ || jug_ < otra.jug_; }
        bool operator==(const TuplaNatJug& otra) const { return cant_ == otra.cant_ && jug_ == otra.jug_; }
        Nat cant_;
        Jugador jug_;
    };

    struct TuplaPokeNat
    {
        TuplaPokeNat(const Pokemon& p, const Nat& s) : poke_(p), cant_(s) {}
        TuplaPokeNat(const TuplaPokeNat& otra) { poke_ = otra.poke_, cant_ = otra.cant_; }
        const Pokemon& poke() const { return poke_; }
        const Nat& cant() const { return cant_; }
        bool operator==(const TuplaPokeNat& otra) const { return poke_ == otra.poke_ && cant_ == otra.cant_; }
        Pokemon poke_;
        Nat cant_;
    };

    struct jugadorStruct
    {
        jugadorStruct(Conj<Jugador>::Iterador itNoExpulsados);

        bool conectado;
        Nat sanciones;
        Coordenada pos;
        Lista <TuplaPokeNat> pokemones;
        DiccString< Pokemon, Lista< TuplaPokeNat>::Iterador > itPokemones;
        Nat pokemonesTotales;
        Conj<Jugador>::Iterador itJugNoExpulsados;
        ColaPrior< TuplaNatJug >::ItColaPrior itPosJug;
        ColaPrior< TuplaNatJug >::ItColaPrior itCapturarPoke;
    };

    Mapa mapa;
    Conj<Jugador> jugNoExpulsados;
    Vector<jugadorStruct> jugadores;
    Conj<Coordenada> posConPokemones;
    DiccString<Pokemon, Nat> pokemonesSalvajes;
    DiccString<Pokemon, Nat> pokemonesCapturados;
    Arreglo< Arreglo<posStruct> > posiciones;
    Nat cantPokemonsTotales;

    // Funciones auxiliares
    Arreglo< Arreglo<posStruct> > CrearPosiciones(const Mapa& map);
    void PosicionarPokemon(const Pokemon& poke, const Coordenada& coord, Conj<Coordenada>::const_Iterador itCoord);
    void capturarPokemon(const Jugador& jug, const Pokemon& poke);
    pokemonACapturar nuevoPokemonACapturar (const Pokemon& poke, Conj<Coordenada>::const_Iterador itCoord, ColaPrior<Juego::TuplaNatJug> jugACapturarlo);
    
}; /* class Juego */


#endif /* H_JUEGO */