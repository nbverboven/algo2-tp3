#include "classes/aed2/aed2.h"
using namespace aed2;
using namespace std;

class Juego
{

  public:
    // Constructor y destructor
    Juego(); //CrearJuego
    ~Juego();

    // Generadores
    void AgregarPokemon(const Pokemon poke, const Coordenada coord);
    void AgregarJugador();
    void Conectarse(const Jugador jug, Coordenada coord);
    void Desconectarse(const Jugador jug);
    void Moverse(const Jugador jug, const Coordenada coord);

    // Observadores básicos
    const Mapa Mapa() const;
    const Conj<Jugador>::const_Iterador Jugadores() const;
    const bool EstaConectado(const Juagdor jug) const;
    const Nat Sanciones(const Jugador jug) const;
    const Coordenada Posicion(const Jugador jug) const;
    const Vector< tuple<Pokemon, Nat> > Pokemons(const Jugador jug) const;
    const Vector< Jugador > Expulsados() const;
    const Vector< Coordenada > PosConPokemons() const;
    const Pokemon PokemonEnPos(const Coordenada coord) const;
    const Nat CantMovimientosParaCaptura(const Coordenada coord) const;
 
    // Otras operaciones
    const Jugador ProxID() const;
    const Lista<Jugador> JugadoresConectados() const;
    const Lista<Jugador> SoloLosConectados(const Conj<Jugador> jugadores) const;
    const bool PuedoAgregarPokemon(const Coordenada coord) const;
    const Conj<bool> HayPokemonEnTerritorio(const Coordenada coord, const Conj<Coordenada> conjCoord) const;
    const bool DebeSancionarse(const Jugador jug, const Coordenada coord) const;
    const bool DebeExpulsarse(const Jugador jug, const Coordenada coord) const;
    const Coordenada HayPokemonCercano(const Coordenada coord) const;
    const Coordenada PosPokemonCercano(const Coordenada coord) const;
    const Conj<Jugador> EntrenadoresPosibles(const Coordenada coord, const Conj<Jugador> jugadores) const;
    const Conj<Coordenada> PosDePokemonsACapturar(const Coordenada coord, const Conj<Coordenada> conjCoord) const;
    const bool SeCapturo(const Coordenada coord1, const Coordenada coord2) const;
    const Nat IndiceDeRareza(const Pokemon poke) const;
    const Nat CantPokemonsTotales() const;
    const Lista<Pokemon> TodosLosPokemons() const;
    const Lista<Pokemon> PokemonsSalvajes(const Conj<Coordenada> conjCoord) const;
    const Lista<Pokemon> PokemonsCapturados(const Conj<Jugador> jugadores) const;
    const Conj<Coordenada> BuscarPokemonsCercanos(const Coordenada coord, const Conj<Coordenada> conjCoord) const;
    const Nat CantMismaEspecie(const Pokemon poke, const Conj<Pokemon> pokemones) const;

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
        ColaPrior< tuple<Nat, Jugador> > jugadores;
        pokemonACapturar* pokemonACapturar;
    };

    struct pokemonACapturar
    {
        pokemonACapturar(const Pokemon poke, Conj<Coordenada>::const_Iterador itCoord, ColaPrior< tuple<Nat, Jugador> > &jugACapturarlo);

        Pokemon pokemon;
        Nat movAfuera;
        Conj<Coordenada>::Iterador itCoord;
        ColaPrior< tuple<Nat, Jugador> > jugACapturarlo;
    };

    struct jugadorStruct
    {
        jugadorStruct(Conj<Jugador>::Iterador itNoExpulsados);

        bool conectado;
        Nat sanciones;
        Coordenada pos;
        Dicc<Pokemon,Nat> pokemones;
        DiccString< Pokemon, Lista< tuple<Pokemon, Nat> >::Iterador > itPokemones;
        Nat pokemonesTotales;
        Conj<jugador>::Iterador itJugNoExpulsados;
        ColaPrior< tuple<Nat, Jugador> >::ItColaPrior itPosJug;
        ColaPrior< tuple<Nat, Jugador> >::ItColaPrior itCapturarPoke;
    };

    Mapa mapa;
    Conj<Jugador> jgNoExpulsados;
    Vector<jugadorStruct> jugadores;
    Conj<Coordenada> posConPokemones;
    DiccString<Pokemon, Nat> pokemonesSalvajes;
    DiccString<Pokemon, Nat> pokemonesCapturados;
    Arreglo< Arreglo<posStruct> > posiciones;
    Nat cantPokemonsTotales;

    // Funciones auxiliares
    Arreglo< Arreglo<posStruct> > CrearPosiciones(const Mapa map);
    void PosicionarPokemon(const Pokemon poke, const Coordenada coord, Conj<Coordenada>::const_Iterador itCoord);
    void capturarPokemon(const Jugador jug, const Pokemon poke);
    
};
