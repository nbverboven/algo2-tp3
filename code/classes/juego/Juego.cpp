#include "Juego.h"


/********************************************************************************
*********                    IMPLEMENTACIÓN DE TUPLA                    *********
*********************************************************************************/

template <class P, class S>
Juego::Tupla::Tupla(const P& prim, const S& seg)
    : tupla_prm(prim), tupla_sgd(seg)
{}


template <class P, class S>
const P& Juego::Tupla::primero() const
{
    return tupla_prm;
}


template <class P, class S>
const S& Juego::Tupla::segundo() const
{
    return tupla_sgd;
}


template <class P, class S>
bool Juego::Tupla::operator<(const Tupla& otra) const
{
    return tupla_prm < otra.tupla_prm || tupla_sgd < otra.tupla_sgd;
}


template <class P, class S>
bool Juego::Tupla::operator==(const Tupla& otra) const
{
    return tupla_prm == otra.tupla_prm && tupla_sgd == otra.tupla_sgd;
}





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

void Juego::AgregarPokemon(const Pokemon& poke, const Coordenada& coord)
{
    Nat nuevaCantPokemonTotal = CantPokemonsTotales()+1;
    CantPokemonsTotales() = nuevaCantPokemonTotal;
    Conj<Coordenada>::Iterador itConjPoke = posConPokemones.AgregarRapido(coord);
    PosicionarPokemon(poke,coord,itConjPoke);

    if (pokemonesSalvajes.Definido(poke))
    {
        Nat cantidad = DiccString::Obtener(pokemonesSalvajes,poke);
        pokemonesSalvajes.Definir(poke,cantidad+1);
    }
    else
    {
        pokemonesSalvajes.Definir(poke,1);
    }

}

Nat Juego::AgregarJugador()
{
    jugadores.AgregarAtras(jugador);
    Conj<Coordenada>::Iterador itNoExpulsados = jugNoExpulsados.AgregarRapido(jugador);
    jugadores[i] = jugadorStruct(itNoExpulsados);

    return jugadores.Longitud();
}

void Juego::Conectarse(const Jugador& jug, Coordenada coord)
{
    jugadores[jug].conectado=true;
    jugadores[jug].pos = coord;
    posStruct = &posiciones[coord.Latitud()][coord.Latitud()];
    TuplaNatJug tupla(jugadores[jug].pokemonesTotales,jug);
    jugadores[jug].itPosJug = posStruct.jugadores.encolar(tupla);

    if (HayPokemonCercano(coord))
    {
        Coordenada coordPoke = PosPokemonCercano(coord);
        pokemonACapturar pokeACapturar = &posiciones[coordPoke.Latitud()][coordPoke.Latitud()].pokemonACapturar;
        jugadores[jug].itCapturarPoke = pokeACapturar.jugACapturarlo.encolar(tupla);
    }
}

void Juego::Desconectarse(const Jugador& jug)
{
    jugadores[jug].conectado=false;
    jugadores[jug].itPosJug.eliminarSiguiente();

    if (HayPokemonCercano(jugadores[jug].pos))
    {
        jugadores[jug].itCapturarPoke.eliminarSiguiente();
    }
}

void Juego::Moverse(const Jugador& jug, const Coordenada& coord)
{
    jugadorStruct jugador = jugadores[jug];
    Coordenada posAnterior = jugador.pos;

    if (!(Mapa().HayCamino(coord,posAnterior)) || Coordenada::distEuclidea(coord,posAnterior)>=100)
    {
        Nat sancionesNuevo = jugador.sanciones+1;
        jugador.sanciones = sancionesNuevo;
    }

    jugador.itPosJug.eliminarSiguiente();
    if(HayPokemonCercano(posAnterior) && !(HayPokemonCercano(coord)))
    {
        jugador.itCapturarPoke.eliminarSiguiente();
    }

    if (jugador.sanciones<5)
    {
        jugador.pos=coord;
        posStruct pStruct = &posiciones[coord.Latitud()][coord.Longitud()];
        TuplaNatJug tupla(jugador.pokemonesTotales,jug);
        jugador.itPosJug = pStruct.jugadores.encolar(tupla);

        if (HayPokemonCercano(coord) && !(HayPokemonCercano(posAnterior)))
        {
            Coordenada coorPoke = PosPokemonCercano(coord);
            pokemonACapturar pokeACapturar = &posiciones[coorPoke.Latitud()][coorPoke.Longitud()].pokemonACapturar;
            jugadores[jug].itCapturarPoke = pokeACapturar.jugACapturarlo.encolar(tupla);
            pokeACapturar.movAfuera=0;
        }

        Conj::Iterador itPosConPoke = posConPokemones.CrearIt();

        while(itPosConPoke.HaySiguiente())
        {
            Coordenada posConPoke= itPosConPoke.Siguiente();
            Nat lat = posConPoke.Latitud();
            Nat lon = posConPoke.Longitud();
            pokemonACapturar pokeACapturar = posiciones[lat][lon].pokemonACapturar;

            if (Coordenada.distEuclidea(posConPoke,coord)>4)
            {
                Nat nuevoMovAf = pokeACapturar.movAfuera+1;
                pokeACapturar.movAfuera=nuevoMovAf;
            }

            if (pokeACapturar.movAfuera==10)
            {
                TuplaNatJug jugACapt = pokeACapturar.jugACapturarlo.proximo();
                capturarPokemon(jugACapt.jug(),pokeACapturar.pokemon);
                pokeACapturar.itCoord.EliminarSiguiente();
                posiciones[lat][lon].pokemonACapturar = NULL;
            }

            itPosConPoke.Avanzar();
        }
        else
        {
            jugador.itJugNoExpulsados.EliminarSiguiente();
            Lista<TuplaPokeNat>::Iterador pokemones =jugador.pokemones.CrearIt();

            while (pokemones.HaySiguiente()) 
            {
                Pokemon poke = pokemones.Siguiente().poke;
                Nat cantPoke = pokemones.Siguiente().cant;
                Nat nuevaCantPokemonTotal = cantPokemonsTotales - cantPoke;
                cantPokemonsTotales = nuevaCantPokemonTotal;
                Nat nuevaCantPoke = pokemonesCapturados.Obtener(poke)-cantPoke;
                pokemonesCapturados.Definir(poke,nuevaCantPoke);
            }
        }
    }

    jugadores[jug]=jugador;
}





/********************************************************************************
*********                     OBSERVADORES BÁSICOS                      *********
*********************************************************************************/

const Mapa& Juego::mapa() const
{
    return mapa;
}

Conj<Jugador>::const_Iterador Juego::Jugadores() const
{
    return jugNoExpulsados.CrearIt();
}

bool Juego::EstaConectado(const Jugador& jug) const
{
    return jugadores[jug].conectado
}

Nat Juego::Sanciones(const Jugador& jug) const
{
    return jugadores[jug].sanciones;
}

Coordenada Juego::Posicion(const Jugador& jug) const
{
    return jugadores[jug].pos;
}

Lista::Iterador Juego::Pokemons(const Jugador& jug) const
{
    return jugadores[jug].pokemones.CrearIt();
}

Conj<Jugador> Juego::Expulsados() const
{
    Conj<Jugador> res;
    Jugador i=0;
    while (i<jugadores.Longitud()){
        if (jugadores[i].sanciones==5){
            res.AgregarRapido(i);
        }
        i++;
    }
    return res;
}

Conj<Coordenada> Juego::PosConPokemons() const
{
    return posConPokemones;
}

Pokemon Juego::PokemonEnPos(const Coordenada& coord) const
{
    return posiciones[coord.Longitud()][coord.Latitud()].pokemonACapturar->pokemon;
}

Nat Juego::CantMovimientosParaCaptura(const Coordenada& coord) const
{
    return posiciones[coord.Longitud()][coord.Latitud()].pokemonACapturar->movAfuera;

}





/********************************************************************************
*********                      OTRAS OPERACIONES                        *********
*********************************************************************************/

Jugador Juego::ProxID() const
{
    return jugadores.Longitud()+1;
}

Conj<Jugador> Juego::JugadoresConectados() const
{
    Conj<Jugador> res;
    Jugador i=0;
    while (i<jugadores.Longitud()){
        if (Juego.jugadores[i].conectado && jugadores[i].sanciones<5){
            res.AgregarRapido(i);
        }
        i++;
    }
    return res;
}

Conj<Jugador> Juego::SoloLosConectados(const Conj<Jugador>& jugadores) const
{
    Conj<Jugador> res;
    Conj::const_Iterador it = jugadores.CrearIt();
    while (it.HaySiguiente()){
        if(jugadores[it.Siguiente()].conectado){
            res.AgregarRapido(it.Siguiente());
        }
        it.Avanzar();
    }
    return res;
}

bool Juego::PuedoAgregarPokemon(const Coordenada& coord) const
{
    return !(HayPokemonCercano(coord));
}

Conj<bool> Juego::HayPokemonEnTerritorio(const Coordenada& coord, const Conj<Coordenada>& conjCoord) const
{
    Conj<bool> res;
    Conj<bool>::const_Iterador it = conjCoord.CrearIt();
    while(it.HaySiguiente()){
        Coordenada coordPoke = it.Siguiente();
        res.AgregarRapido(Coordenada::distEuclidea(coord,coordPoke)<=4);
        it.Avanzar();
    }
    return res;
}

bool Juego::DebeSancionarse(const Jugador& jug, const Coordenada& coord) const
{
    jugadorStruct jugador = jugadores[jug];
    return !(mapa.HayCamino(jugador.pos,c) || Coordenada::distEuclidea(jugador.pos,c)>100);
}

bool Juego::DebeExpulsarse(const Jugador& jug, const Coordenada& coord) const
{
    jugadorStruct jugador = jugadores[jug];
    return (DebeSancionarse(jug,coord) && jugador.sanciones>=4);
}

Coordenada Juego::HayPokemonCercano(const Coordenada& coord) const
{
    bool res = false;
    Nat lat = coord.Latitud();
    Nat lon = coord.Longitud();
    Nat latDesde = 0;
    if (lat-2>0){
        latDesde = lat-2;
    }
    while (latDesde <= lat+2 && latDesde < Mapa.maxLatitud){
        Nat lonDesde=0;
        if (lon-2>0){
            lonDesde=lon-2;
        }
        while(lonDesde<=lat+2 && lonDesde < Mapa.maxLongitud){
            if(Coordenada.distEuclidea(Coordenada(latDesde,lonDesde),coord)<=4){
                posStruct tupla = &posiciones[coord.Latitud()][coord.Longitud()];
                if(tupla.pokemonACapturar!=NULL){
                    res =true;
                }
            }
            lonDesde ++;
        }
        latDesde ++;
    }
    return res;
}

Coordenada Juego::PosPokemonCercano(const Coordenada& coord) const
{
    Nat lat = coord.Latitud();
    Nat lon = coord.Longitud();
    Nat latDesde=0;
    if (lat-2>=0){
        latDesde=lat-2;
    }
    while (latDesde <= lat+2 && latDesde < Mapa.maxLatitud){
        Nat lonDesde=0;
        if(lon-2>0){
            lonDesde= lon-2;
        }
        while(lonDesde<lat+2 && lonDesde<Mapa.maxLongitud){
            Coordenada retCoor(latDesde,lonDesde);
            if(Coordenada.distEuclidea(resCoor,coord)<=4){
                posStruct tupla = &Juego.posiciones[coord.Latitud()][coord.Longitud()];
                if(tupla.pokemonACapturar!=NULL){
                    return retCoor;
                }
            }
            lonDesde ++;
        }
        latDesde ++;
    }
}

Conj<Jugador> Juego::EntrenadoresPosibles(const Coordenada& coord, const Conj<Jugador>& jugadores) const
{
    Conj<Jugador> res;
    Conj<Jugador> ::const_Iterador it = jugadores.CrearIt();
    while (it.HaySiguiente()){
        Jugador jug = it.Siguiente;
        Coordenada coordJug = jugadores[jug].pos;
        if (Coordenada.distEuclidea(coord,coordJug)<=4){
            res.AgregarRapido(jug);
        }
        it.Avanzar();
    }
    return res;
}

Conj<Coordenada> Juego::PosDePokemonsACapturar(const Coordenada& coord, const Conj<Coordenada>& conjCoord) const
{
    Conj<Coordenada> res;
    Conj<Coordenada> ::const_Iterador it= conjCoord.CrearIt();
    while(it.HaySiguiente()){
        Coordenada pCoord = it.Siguiente();
        if(SeCapturo(pCoord,coord)){
            res.AgregarRapido(pCoord);
        }
        it.Avanzar();
    }
    return res;
}

bool Juego::SeCapturo(const Coordenada& coord1, const Coordenada& coord2) const
{
    bool res = false;
    posStruct tupla = &posiciones[coord1.Latitud()][coord1.Longitud()];
    if(HayPokemonCercano(coord2)){
        if (PosPokemonCercano(coord2)!=coord1 && tupla.pokemonACapturar!=NULL){
            res = true;
        }
        else{
            if (tupla.pokemonACapturar!=NULL){
                res=true;
            }
        }
    }
    return res;
}

Nat Juego::IndiceDeRareza(const Pokemon& poke) const
{
    Nat cant =0;
    if(pokemonesSalvajes.Definido(poke)){
        cant = pokemonesSalvajes.Obtener(poke)+cant;
    }
    if (pokemonesCapturados.Definido(poke)){
        cant = pokemonesCapturados.Obtener(poke)+cant;
    }
    return 100-(100*cant/cantPokemonsTotales);
}

Nat Juego::CantPokemonsTotales() const
{
    return cantPokemonsTotales;
}

const Lista<Pokemon> Juego::TodosLosPokemons() const
{
    Lista<Pokemon> res;
    Lista<Pokemon>::const_Iterador it= PokemonsCapturados(jugNoExpulsados).CrearIt();
    while(it.HaySiguiente()){
        Pokemon poke = it.Siguiente();
        res.AgregarAtras(poke);
        it.Avanzar();
    }
    return res;

}

Lista<Pokemon> Juego::PokemonsSalvajes(const Conj<Coordenada>& conjCoord) const
{
    Lista<Pokemon> res;
    Conj<Coordenada>::const_Iterador it = conjCoord.CrearIt();
    while(it.HaySiguiente()){
        Coordenada coordPoke = it.Siguiente();
        if(PosConPokemons().Pertenece(coordPoke)){
            posStruct tupla = posiciones[coordPoke.Latitud()][coordPoke.Longitud()];
            Pokemon poke = tupla.pokemonACapturar->pokemon;
            res.AgregarAtras(poke);
        }
        it.Avanzar();
    }
    return res;
}

Lista<Pokemon> Juego::PokemonsCapturados(const Conj<Jugador>&& jugadores) const
{
    Lista<Pokemon> res;
    Lista<Pokemon> ::const_Iterador it = jugadores.CrearIt();
    while(it.HaySiguiente()){
        Jugador jug = it.Siguiente();
        Lista<Pokemon> :: const_Iterador itPoke = Pokemons(jug);
        while (itPoke.HaySiguiente()){
            TuplaPokeNat tupPoke = itPoke.Siguiente();
            Nat CantParaAgregar = tupPoke.cant();
            while (CantParaAgregar>0){
                res.AgregarAtras(tupPoke.poke());
                CantParaAgregar = CantParaAgregar-1;
            }
            itPoke.Avanzar();
        }
        it.Avanzar();
    }
    return res;
}

Conj<Coordenada> Juego::BuscarPokemonsCercanos(const Coordenada&& coord, const Conj<Coordenada>&& conjCoord) const
{
    Conj<Coordenada> res;
    Conj<Coordenada>::const_Iterador it = conjCoord.CrearIt();
    while ( it.HaySiguiente()){
        Coordenada coordPoke = it.Siguiente();
        if(Coordenada.distEuclidea(coord,coordPoke)<=4){
            res.AgregarRapido(coordPoke);
        }
        it.Avanzar();
    }
    return res;
}

Nat Juego::CantMismaEspecie(const Pokemon&& poke, const Conj<Pokemon>&& pokemones) const
{
    Nat cant=0;
    Conj<Pokemon>::const_Iterador it = pokemones.CrearIt();
    while(it.HaySiguiente()){
        Pokemon poke2 = it.Siguiente();
        if(poke==poke2){
            cant ++ ;
        }
        it.Avanzar();
    }
    return cant;
}





/********************************************************************************
*********                    FUNCIONES AUXILIARES                       *********
*********************************************************************************/

Arreglo< Arreglo<posStruct> > Juego::CrearPosiciones(const Mapa& map)
{
    Nat ancho = Mapa().MaxLatitud();
    Nat largo = Mapa().MaxLongitud();
    Arreglo<Arreglo<posStruct> > posiciones(largo);
    Nat lg = 0;
    while (lg<largo){
        Arreglo<posStruct> arrAncho(ancho);
        posiciones[lg]=arrAncho;
        lg ++;
    }
}

void Juego::PosicionarPokemon(const Pokemon& poke, const Coordenada& coord, Conj<Coordenada>::const_Iterador itCoord)
{
    posStruct tupla = &posiciones[coord.Latitud()][coord.Longitud()];
    ColaPrior< TuplaNatJug > jugACapturarlo;
    Nat lat = coord.Latitud();
    Nat lon = coord.Longitud();
    Nat latDesde = 0;
    if (lat-2>0){
        latDesde = lat-2;
    }
    while (latDesde<= lat+2 && latDesde<Mapa.MaxLatitud()){
        Nat lonDesde = 0;
        if (lon-2>0){
            lonDesde=lon-2;
        }
        while (lonDesde<=lat+2 && lonDesde<Mapa.MaxLongitud()){
            if(Coordenada::distEuclidea(Coordenada(latDesde,lonDesde),coord)){
                posStruct subTupla = &jugadores[lonDesde][latDesde];
                ColaPrior::ItColaPrior itJugadores = subTupla.jugadores.crearIt();
                while(itJugadores.haySiguiente()){
                    TuplaNatJug jugador = itJugadores.siguiente();
                    jugadorStruct jugStruct = &Juego.jugadores[jugador.jug()];
                    jugStruct.itCapturarPoke = jugACapturarlo.encolar(jugador);
                    itJugadores.avanzar();
                }
            }
            lonDesde++;
        }
        latDesde ++;
    }
    pokemonACapturar puntero = &nuevoPokemonACapturar(poke,itCoord,jugACapturarlo);
    tupla.pokemonACapturar = puntero;

}

pokemonACapturar Juego::nuevoPokemonACapturar(const Pokemon& poke, Conj<Coordenada>::const_Iterador itCoord,ColaPrior<TuplaNatJug> jugACapturarlo){
    pokemonACapturar res;
    res.pokemon=poke;
    res.movAfuera=0;
    res.jugACapturarlo = jugACapturarlo;
    res.itCoord = itCoord;
    return res;
}


void Juego::capturarPokemon(const Jugador& jug, const Pokemon& poke)
{
    jugadorStruct jugador = juego.jugadores[jug];
    Nat cantPoke = pokemonesSalvajes.Obtener(poke);
    pokemonesSalvajes.Definir(poke,cantPoke-1);
    if(pokemonesSalvajes.Definido(poke)){
        Nat cantPoke = pokemonesCapturados.Obtener(poke);
        pokemonesCapturados.Definir(poke,cantPoke+1);
    }
    else {
        pokemonesCapturados.Definir(poke,1);
    }
    if (jugador.itPokemones.Definido(poke)){
        Lista< TuplaPokeNat>::Iterador itPokemones = jugador.itPokemones.Obtener(poke);
        Nat cantPoke = itPokemones.Siguiente().cant_;
        itPokemones.Siguiente().cant_ = cantPoke+1;
    }
    else {
        Lista<TuplaPokeNat>::Iterador itPoke = jugador.pokemones.CrearItUlt();

        itPoke.AgregarComoSiguiente(TuplaPokeNat(poke,1));
        jugador.itPokemones.Definir(poke,itPoke);
    }
    jugador.pokemonesTotales = jugador.pokemonesTotales+1;
    juego.jugadores[jug]=jugador;
}

//  Constructor de pokemonACapturar
Juego::pokemonACapturar::pokemonACapturar(const Pokemon& poke, Conj<Coordenada>::const_Iterador itCoord, ColaPrior<TuplaNatJug> &jugACapturarlo)
{
    pokemonACapturar res;
    res.pokemon = poke;
    res.movAfuera = 0;
    res.jugACapturarlo = jugACapturarlo;
    res.itCoord = itCoord;
    return res;
}

//  Constructor de jugadorStruct
Juego::jugadorStruct::jugadorStruct(Conj<Jugador>::Iterador itNoExpulsados)
{
    jugadorStruct res;
    Coordenada nueva(0,0);
    Lista<TuplaNatJug> jug; //falta inicializar TuplaNatJug
    Lista<TuplaPokeNat> pokemones; //falta inicializar TuplaPokeNat
    res.conectado = false;
    res.sanciones = 0;
    res.pos = nueva;
    res.pokemonesTotales = 0;
    res.itCapturarPoke = jug.CrearIt();
    res.pokemones = pokemones.CrearIt();

}
