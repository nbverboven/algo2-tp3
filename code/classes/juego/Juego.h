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
    template <class P, class S>
    class Tupla;

    // Constructor y destructor
    Juego(); //CrearJuego
    ~Juego();

    // Generadores
    void AgregarPokemon(const Pokemon& poke, const Coordenada& coord);
    Jugador AgregarJugador();
    void Conectarse(const Jugador& jug, Coordenada coord);
    void Desconectarse(const Jugador& jug);
    void Moverse(const Jugador& jug, const Coordenada& coord);

    // Observadores básicos
    const Mapa& mapa() const;
    Conj<Jugador>::const_Iterador Jugadores() const;
    bool EstaConectado(const Jugador& jug) const;
    Nat Sanciones(const Jugador& jug) const;
    Coordenada Posicion(const Jugador& jug) const;
    Lista< Tupla<Pokemon,Nat> >::Iterador Pokemons(const Jugador& jug) const;
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
    bool HayPokemonCercano(const Coordenada& coord) const;
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
    Nat CantMismaEspecie(const Pokemon& poke) const;

    
    /* 
     * Defino una tupla de tipos genéricos porque si es privada, hay funciones que no puedo
     * usar afuera de la clase. Por ejemplo, en Juego::Pokemons() no podría ver ni el pokemon 
     * ni la cantidad del siguiente del iterador.
     * Se asume que, tanto P como S, tienen definida la igualdad y una relación de orden total
     * estricto.
     */
    template <class P, class S>
    class Tupla
    {
      public:

        Tupla();
        Tupla(const P& prim, const S& seg);

        const P& primero() const;
        const S& segundo() const;

        bool operator<(const Tupla& otra) const ;
        bool operator==(const Tupla& otra) const;

      private:

        P tupla_prm_;
        S tupla_sgd_;
    };



  private:

    /*struct pokemonCapturado
    {
        Pokemon pokemon;
        Nat cantidad;
    };*/


    struct pokemonACapturar
    {
        pokemonACapturar(const Pokemon& poke, Conj<Coordenada>::const_Iterador itCoord, ColaPrior< Tupla<Nat,Jugador> > &jugACapturarlo);

        Pokemon pokemon_;
        Nat movAfuera_;
        Conj<Coordenada>::Iterador itCoord_;
        ColaPrior< Tupla<Nat,Jugador> > jugACapturarlo_;
    };

    struct posStruct
    {
        ColaPrior< Tupla<Nat,Jugador> > jugadores_;
        pokemonACapturar* pokemonACapturar_;
    };

    // struct TuplaNatJug
    // {
    //     TuplaNatJug(const Nat& p, const Jugador& s) : cant_(p), jug_(s) {}
    //     TuplaNatJug(const TuplaNatJug& otra) { cant_ = otra.cant_, jug_ = otra.jug_; }
    //     const Nat& cant() const { return cant_; }
    //     const Jugador& jug() const { return jug_; }
    //     bool operator<(const TuplaNatJug& otra) const { return cant_ < otra.cant_ || jug_ < otra.jug_; }
    //     bool operator==(const TuplaNatJug& otra) const { return cant_ == otra.cant_ && jug_ == otra.jug_; }
    //     Nat cant_;
    //     Jugador jug_;
    // };

    // struct TuplaPokeNat
    // {
    //     TuplaPokeNat(const Pokemon& p, const Nat& s) : poke_(p), cant_(s) {}
    //     TuplaPokeNat(const TuplaPokeNat& otra) { poke_ = otra.poke_, cant_ = otra.cant_; }
    //     const Pokemon& poke() const { return poke_; }
    //     const Nat& cant() const { return cant_; }
    //     bool operator==(const TuplaPokeNat& otra) const { return poke_ == otra.poke_ && cant_ == otra.cant_; }
    //     Pokemon poke_;
    //     Nat cant_;
    // };

    struct jugadorStruct
    {
        jugadorStruct(Conj<Jugador>::Iterador itNoExpulsados);

        bool conectado;
        Nat sanciones;
        Coordenada pos;
        Lista< Tupla<Pokemon,Nat> > pokemones;
        DiccString< Lista< Tupla<Pokemon,Nat> >::Iterador > itPokemones;
        Nat pokemonesTotales;
        Conj<Jugador>::Iterador itJugNoExpulsados;
        ColaPrior< Tupla< Nat,Jugador> >::ItColaPrior itPosJug;
        ColaPrior< Tupla< Nat,Jugador> >::ItColaPrior itCapturarPoke;
    };

    Mapa mapa_;
    Conj<Jugador> jugNoExpulsados_;
    Vector<jugadorStruct> jugadores_;
    Conj<Coordenada> posConPokemones_;
    DiccString<Nat> pokemonesSalvajes_;
    DiccString<Nat> pokemonesCapturados_;
    Arreglo< Arreglo<posStruct> > posiciones_;
    Nat cantPokemonsTotales_;

    // Funciones auxiliares
    Arreglo< Arreglo<posStruct> > CrearPosiciones(const Mapa& map);
    void PosicionarPokemon(const Pokemon& poke, const Coordenada& coord, Conj<Coordenada>::const_Iterador itCoord);
    void capturarPokemon(const Jugador& jug, const Pokemon& poke);
    pokemonACapturar nuevoPokemonACapturar (const Pokemon& poke, Conj<Coordenada>::const_Iterador itCoord, ColaPrior< Juego::Tupla<Nat,Jugador> > jugACapturarlo);
    
}; /* class Juego */


#endif /* H_JUEGO */