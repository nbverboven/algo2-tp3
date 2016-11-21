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

    // Observadores básicos

    // Otras operaciones

    // Operadores

    // Asignacion
    //Juego &operator=(const Juego &aCopiar);

    /*friend ostream& operator<<(ostream& os) {
        return os;
    }*/

  private:

    struct pokemonCapturado
    {
        Pokemon pokemon;
        Nat cantidad;
    };

    struct posStruct
    {
        ColaPrior< tuple<Nat, Jugador> > jugadores;
        pokemonACapturar* pokemonACapturar;
    };

    struct pokemonACapturar
    {
        Pokemon pokemon;
        Nat movAfuera;
        itConj<Coordenada> itCoord;
        ColaPrior< tuple<Nat, Jugador> > jugACapturarlo;
    };

    struct jugadorStruct
    {
        bool conectado;
        Nat sanciones;
        Coordenada pos;
        Dicc<Pokemon,Nat> pokemones;
        DiccString< Pokemon, itLista< tuple<Pokemon, Nat> > > itPokemones;
        Nat pokemonesTotales;
        itConj<jugador> itJugNoExpulsados;
        itColaPrior< tuple<Nat, Jugador> > itPosJug;
        itColaPrior< tuple<Nat, Jugador> > itCapturarPoke;
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
    
};
