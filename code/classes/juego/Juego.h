#ifndef H_JUEGO
#define H_JUEGO

#include "../aed2/aed2.h"
#include "../cola_de_prioridad/ColaPrior.h"
#include "../cola_de_prioridad/ColaPrior.cpp"
#include "../coordenada/Coordenada.h"
// #include "../coordenada/Coordenada.cpp"
#include "../diccionario_string/DiccString.h"
#include "../diccionario_string/DiccString.cpp"
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
    Juego();
    Juego(const Mapa& map); //CrearJuego
    ~Juego();

    // Generadores
    void AgregarPokemon(const Pokemon &poke, const Coordenada& coord);
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
    Lista< Tupla<Pokemon,Nat> >::Iterador Pokemons(const Jugador& jug);
    Lista< Tupla<Pokemon,Nat> >::const_Iterador Pokemons(const Jugador& jug) const;
    Conj<Jugador> Expulsados() const;
    Conj<Coordenada> PosConPokemons() const;
    Pokemon PokemonEnPos(const Coordenada& coord);
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

        bool operator<(const Tupla& otra) const
        {
            return tupla_prm_ < otra.tupla_prm_ || tupla_sgd_ < otra.tupla_sgd_;
        }

        bool operator>(const Tupla& otra) const
        {
            return tupla_prm_ > otra.tupla_prm_ || tupla_sgd_ > otra.tupla_sgd_;
        }

        bool operator==(const Tupla& otra) const
        {
            return tupla_prm_ == otra.tupla_prm_ && tupla_sgd_ == otra.tupla_sgd_;
        }

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
        // Constructor de pokemonACapturar
        pokemonACapturar(const Pokemon poke, Conj<Coordenada>::Iterador itCoord,
                         const ColaPrior< Tupla<Nat,Jugador> >& jugACapturarlo)
            : pAC_pokemon_(poke), pAC_movAfuera_(0),
              pAC_itCoord_(itCoord), pAC_jugACapturarlo_(jugACapturarlo)
        {}

        const Pokemon pAC_pokemon_;
        Nat pAC_movAfuera_;
        Conj<Coordenada>::Iterador pAC_itCoord_;
        ColaPrior< Tupla<Nat,Jugador> > pAC_jugACapturarlo_;
    };

    struct posStruct
    {
        posStruct() : pS_pokemonACapturar_(NULL){}

        ~posStruct()
        {
            //delete pS_pokemonACapturar_;
        }

        ColaPrior< Tupla<Nat,Jugador> > pS_jugadores_;
        pokemonACapturar* pS_pokemonACapturar_;

    };



    struct jugadorStruct
    {
        // Constructor de jugadorStruct
        jugadorStruct(Conj<Jugador>::Iterador itNoExpulsados)
            : jS_conectado_(false), jS_sanciones_(0), jS_pokemonesTotales_(0),
              jS_pos_(Coordenada(0,0)), jS_pokemones_(), jS_itJugNoExpulsados_(itNoExpulsados),
              jS_itPosJug_(), jS_itCapturarPoke_()
        {}

        bool jS_conectado_;
        Nat jS_sanciones_;
        Nat jS_pokemonesTotales_;
        Coordenada jS_pos_;
        Lista< Tupla<Pokemon,Nat> > jS_pokemones_;
        DiccString< Lista< Tupla<Pokemon,Nat> >::Iterador > jS_itPokemones_;
        Conj<Jugador>::Iterador jS_itJugNoExpulsados_;
        ColaPrior< Tupla< Nat,Jugador> >::ItColaPrior jS_itPosJug_;
        ColaPrior< Tupla< Nat,Jugador> >::ItColaPrior jS_itCapturarPoke_;
    };

    Mapa JG_mapa_;
    Conj<Jugador> JG_jugNoExpulsados_;
    Vector<jugadorStruct> JG_jugadores_;
    Conj<Coordenada> JG_posConPokemones_;
    DiccString<Nat> JG_pokemonesSalvajes_;
    DiccString<Nat> JG_pokemonesCapturados_;
    Arreglo< Arreglo<posStruct> > JG_posiciones_;
    Nat JG_cantPokemonsTotales_;

    // Funciones auxiliares
    Arreglo< Arreglo< posStruct > > CrearPosiciones(const Mapa& map);
    void PosicionarPokemon(const Pokemon& poke, const Coordenada& coord, Conj<Coordenada>::Iterador itCoord);
    void capturarPokemon(const Jugador& jug, const Pokemon& poke);
    // pokemonACapturar* nuevoPokemonACapturar(const Pokemon& poke, Conj<Coordenada>::const_Iterador itCoord, 
    //                                         const ColaPrior< Tupla<Nat,Jugador> >& jugACapturarlo);
    
}; /* class Juego */


#endif /* H_JUEGO */