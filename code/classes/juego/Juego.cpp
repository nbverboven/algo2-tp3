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

void AgregarPokemon(const Pokemon& poke, const Coordenada& coord)
{
    Nat nuevaCantPokemonTotal = Juego::CantPokemonsTotales()+1;
    Juego::CantPokemonsTotales() = nuevaCantPokemonTotal;
    Conj<Coordenada>::Iterador itConjPoke = Juego::posConPokemones.AgregarRapido(coord);
    Juego::PosicionarPokemon(poke,coord,itConjPoke);
    if (Juego::pokemonesSalvajes.Definido(poke)) {
        Nat cantidad = DiccString::Obtener(Juego::pokemonesSalvajes,poke);
        Juego::pokemonesSalvajes.Definir(poke,cantidad+1);
    }
    else {
        Juego::pokemonesSalvajes.Definir(poke,1);
    }

}

const Nat AgregarJugador()
{
    Juego::jugadores.AgregarAtras(jugador);
    Conj<Coordenada>::Iterador itNoExpulsados = Juego::jugNoExpulsados.AgregarRapido(jugador);
    Juego::jugadores[i] = Juego::jugadorStruct(itNoExpulsados);
    return Juego::jugadores.Longitud();
}

void Conectarse(const Jugador& jug, Coordenada coord)
{
    Juego::jugadores[jug].conectado=true;
    Juego::jugadores[jug].pos = coord;
    Juego::posStruct = &Juego::posiciones[coord.Latitud()][coord.Latitud()];
    Juego::TuplaNatJug tupla(Juego::jugadores[jug].pokemonesTotales,jug);
    Juego::jugadores[jug].itPosJug = Juego::posStruct.jugadores.encolar(tupla);
    if (Juego::HayPokemonCercano(coord))    {
        Coordenada coordPoke = Juego::PosPokemonCercano(coord);
        Juego::pokemonACapturar pokeACapturar = &Juego::posiciones[coordPoke.Latitud()][coordPoke.Latitud()].pokemonACapturar;
        Juego::jugadores[jug].itCapturarPoke = pokeACapturar.jugACapturarlo.encolar(tupla);
    }
}

void Desconectarse(const Jugador& jug)
{
    Juego::jugadores[jug].conectado=false;
    Juego::jugadores[jug].itPosJug.eliminarSiguiente();
    if (Juego::HayPokemonCercano(Juego::jugadores[jug].pos)) {
        Juego::jugadores[jug].itCapturarPoke.eliminarSiguiente();
    }
}

void Moverse(const Jugador& jug, const Coordenada& coord)
{
    Juego::jugadorStruct jugador = Juego::jugadores[jug];
    Coordenada posAnterior = jugador.pos;
    if (!(Juego::Mapa().HayCamino(coord,posAnterior)) || Coordenada::distEuclidea(coord,posAnterior)>=100){
        Nat sancionesNuevo = jugador.sanciones+1;
        jugador.sanciones = sancionesNuevo;
    }
    jugador.itPosJug.eliminarSiguiente();
    if(Juego::HayPokemonCercano(posAnterior) && !(Juego::HayPokemonCercano(coord))){
        jugador.itCapturarPoke.eliminarSiguiente();
    }
    if (jugador.sanciones<5){
        jugador.pos=coord;
        Juego::posStruct pStruct = &Juego::posiciones[coord.Latitud()][coord.Longitud()];
        Juego::TuplaNatJug tupla(jugador.pokemonesTotales,jug);
        jugador.itPosJug = pStruct.jugadores.encolar(tupla);
        if (Juego::HayPokemonCercano(coord) && !(Juego::HayPokemonCercano(posAnterior))){
            Coordenada coorPoke = Juego::PosPokemonCercano(coord);
            Juego::pokemonACapturar pokeACapturar = &Juego::posiciones[coorPoke.Latitud()][coorPoke.Longitud()].pokemonACapturar;
            Juego::jugadores[jug].itCapturarPoke = pokeACapturar.jugACapturarlo.encolar(tupla);
            pokeACapturar.movAfuera=0;
        }
        Conj::Iterador itPosConPoke = Juego::posConPokemones.CrearIt();
        while(itPosConPoke.HaySiguiente()){
            Coordenada posConPoke= itPosConPoke.Siguiente();
            Nat lat = posConPoke.Latitud();
            Nat lon = posConPoke.Longitud();
            Juego::pokemonACapturar pokeACapturar = Juego::posiciones[lat][lon].pokemonACapturar;
            if (Coordenada.distEuclidea(posConPoke,coord)>4){
                Nat nuevoMovAf = pokeACapturar.movAfuera+1;
                pokeACapturar.movAfuera=nuevoMovAf;
            }
            if (pokeACapturar.movAfuera==10){
                Juego::TuplaNatJug jugACapt = pokeACapturar.jugACapturarlo.proximo();
                Juego::capturarPokemon(jugACapt.jug(),pokeACapturar.pokemon);
                pokeACapturar.itCoord.EliminarSiguiente();
                Juego::posiciones[lat][lon].pokemonACapturar = NULL;
            }
            itPosConPoke.Avanzar();
        }
        else    {
            jugador.itJugNoExpulsados.EliminarSiguiente();
            Lista<Juego::TuplaPokeNat>::Iterador pokemones =jugador.pokemones.CrearIt();
            while (pokemones.HaySiguiente()) {
                Pokemon poke = pokemones.Siguiente().poke;
                Nat cantPoke = pokemones.Siguiente().cant;
                Nat nuevaCantPokemonTotal = Juego::cantPokemonsTotales - cantPoke;
                Juego::cantPokemonsTotales = nuevaCantPokemonTotal;
                Nat nuevaCantPoke = Juego::pokemonesCapturados.Obtener(poke)-cantPoke;
                Juego::pokemonesCapturados.Definir(poke,nuevaCantPoke);
            }
        }
    }
    Juego::jugadores[jug]=jugador;
}





/********************************************************************************
*********                     OBSERVADORES BÁSICOS                      *********
*********************************************************************************/

const Mapa Juego::Mapa() const
{
    return mapa;
}

const Conj<Jugador>::const_Iterador Juego::Jugadores() const
{
    return Juego::jugNoExpulsados.CrearIt();
}

const bool Juego::EstaConectado(const Jugador& jug) const
{
    return Juego::jugadores[jug].conectado
}

const Nat Juego::Sanciones(const Jugador& jug) const
{
    return Juego::jugadores[jug].sanciones;
}

const Coordenada Juego::Posicion(const Jugador& jug) const
{
    return Juego::jugadores[jug].pos;
}

const Lista::Iterador Juego::Pokemons(const Jugador& jug) const
{
    return Juego::jugadores[jug].pokemones.CrearIt();
}

const Conj<Jugador> Juego::Expulsados() const
{
    Conj<Jugador> res;
    Jugador i=0;
    while (i<Juego::jugadores.Longitud()){
        if (Juego::jugadores[i].sanciones==5){
            res.AgregarRapido(i);
        }
        i++;
    }
    return res;
}

const Conj<Coordenada> Juego::PosConPokemons() const
{
    return Juego::posConPokemones;
}

const Pokemon Juego::PokemonEnPos(const Coordenada& coord) const
{
    return Juego::posiciones[coord.Longitud()][coord.Latitud()].pokemonACapturar->pokemon;
}

const Nat Juego::CantMovimientosParaCaptura(const Coordenada& coord) const
{
    return Juego::posiciones[coord.Longitud()][coord.Latitud()].pokemonACapturar->movAfuera;

}





/********************************************************************************
*********                      OTRAS OPERACIONES                        *********
*********************************************************************************/

const Jugador Juego::ProxID() const
{
    return Juego::jugadores.Longitud()+1;
}

const Conj<Jugador> Juego::JugadoresConectados() const
{
    Conj<Jugador> res;
    Jugador i=0;
    while (i<Juego::jugadores.Longitud()){
        if (Juego.jugadores[i].conectado && Juego::jugadores[i].sanciones<5){
            res.AgregarRapido(i);
        }
        i++;
    }
    return res;
}

const Conj<Jugador> Juego::SoloLosConectados(const Conj<Jugador>& jugadores) const
{
    Conj<Jugador> res;
    Conj::const_Iterador it = jugadores.CrearIt();
    while (it.HaySiguiente()){
        if(Juego::jugadores[it.Siguiente()].conectado){
            res.AgregarRapido(it.Siguiente());
        }
        it.Avanzar();
    }
    return res;
}

const bool Juego::PuedoAgregarPokemon(const Coordenada& coord) const
{
    return !(HayPokemonCercano(coord));
}

const Conj<bool> Juego::HayPokemonEnTerritorio(const Coordenada& coord, const Conj<Coordenada>& conjCoord) const
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

const bool Juego::DebeSancionarse(const Jugador& jug, const Coordenada& coord) const
{
    Juego::jugadorStruct jugador = Juego::jugadores[jug];
    return !(Juego::mapa.HayCamino(jugador.pos,c) || Coordenada::distEuclidea(jugador.pos,c)>100);
}

const bool Juego::DebeExpulsarse(const Jugador& jug, const Coordenada& coord) const
{
    Juego::jugadorStruct jugador = Juego::jugadores[jug];
    return (DebeSancionarse(jug,coord) && jugador.sanciones>=4);
}

const Coordenada Juego::HayPokemonCercano(const Coordenada& coord) const
{
    bool res = false;
    Nat lat = coord.Latitud();
    Nat lon = coord.Longitud();
    Nat latDesde = 0;
    if (lat-2>0){
        latDesde = lat-2;
    }
    while (latDesde <= lat+2 && latDesde < Juego::Mapa.maxLatitud){
        Nat lonDesde=0;
        if (lon-2>0){
            lonDesde=lon-2;
        }
        while(lonDesde<=lat+2 && lonDesde < Juego::Mapa.maxLongitud){
            if(Coordenada.distEuclidea(Coordenada(latDesde,lonDesde),coord)<=4){
                Juego::posStruct tupla = &Juego::posiciones[coord.Latitud()][coord.Longitud()];
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

const Coordenada Juego::PosPokemonCercano(const Coordenada& coord) const
{
    Nat lat = coord.Latitud();
    Nat lon = coord.Longitud();
    Nat latDesde=0;
    if (lat-2>=0){
        latDesde=lat-2;
    }
    while (latDesde <= lat+2 && latDesde < Juego::Mapa.maxLatitud){
        Nat lonDesde=0;
        if(lon-2>0){
            lonDesde= lon-2;
        }
        while(lonDesde<lat+2 && lonDesde<Juego::Mapa.maxLongitud){
            Coordenada retCoor(latDesde,lonDesde);
            if(Coordenada.distEuclidea(resCoor,coord)<=4){
                Juego::posStruct tupla = &Juego.posiciones[coord.Latitud()][coord.Longitud()];
                if(tupla.pokemonACapturar!=NULL){
                    return retCoor;
                }
            }
            lonDesde ++;
        }
        latDesde ++;
    }
}

const Conj<Jugador> Juego::EntrenadoresPosibles(const Coordenada& coord, const Conj<Jugador>& jugadores) const
{
    Conj<Jugador> res;
    Conj<Jugador> ::const_Iterador it = jugadores.CrearIt();
    while (it.HaySiguiente()){
        Jugador jug = it.Siguiente;
        Coordenada coordJug = Juego::jugadores[jug].pos;
        if (Coordenada.distEuclidea(coord,coordJug)<=4){
            res.AgregarRapido(jug);
        }
        it.Avanzar();
    }
    return res;
}

const Conj<Coordenada> Juego::PosDePokemonsACapturar(const Coordenada& coord, const Conj<Coordenada>& conjCoord) const
{
    Conj<Coordenada> res;
    Conj<Coordenada> ::const_Iterador it= conjCoord.CrearIt();
    while(it.HaySiguiente()){
        Coordenada pCoord = it.Siguiente();
        if(Juego::SeCapturo(pCoord,coord)){
            res.AgregarRapido(pCoord);
        }
        it.Avanzar();
    }
    return res;
}

const bool Juego::SeCapturo(const Coordenada& coord1, const Coordenada& coord2) const
{
    bool res = false;
    Juego::posStruct tupla = &Juego::posiciones[coord1.Latitud()][coord1.Longitud()];
    if(Juego::HayPokemonCercano(coord2)){
        if (Juego::PosPokemonCercano(coord2)!=coord1 && tupla.pokemonACapturar!=NULL){
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

const Nat Juego::IndiceDeRareza(const Pokemon& poke) const
{
    Nat cant =0;
    if(Juego::pokemonesSalvajes.Definido(poke)){
        cant = Juego::pokemonesSalvajes.Obtener(poke)+cant;
    }
    if (Juego::pokemonesCapturados.Definido(poke)){
        cant = Juego::pokemonesCapturados.Obtener(poke)+cant;
    }
    return 100-(100*cant/cantPokemonsTotales);
}

const Nat Juego::CantPokemonsTotales() const
{
    return Juego::cantPokemonsTotales;
}

const Lista<Pokemon> Juego::TodosLosPokemons() const
{
    Lista<Pokemon> res;
    Lista<Pokemon>::const_Iterador it= Juego::PokemonsCapturados(Juego::jugNoExpulsados).CrearIt();
    while(it.HaySiguiente()){
        Pokemon poke = it.Siguiente();
        res.AgregarAtras(poke);
        it.Avanzar();
    }
    return res;

}

const Lista<Pokemon> Juego::PokemonsSalvajes(const Conj<Coordenada>& conjCoord) const
{
    Lista<Pokemon> res;
    Conj<Coordenada>::const_Iterador it = conjCoord.CrearIt();
    while(it.HaySiguiente()){
        Coordenada coordPoke = it.Siguiente();
        if(Juego::PosConPokemons().Pertenece(coordPoke)){
            Juego::posStruct tupla = Juego::posiciones[coordPoke.Latitud()][coordPoke.Longitud()];
            Pokemon poke = tupla.pokemonACapturar->pokemon;
            res.AgregarAtras(poke);
        }
        it.Avanzar();
    }
    return res;
}

const Lista<Pokemon> Juego::PokemonsCapturados(const Conj<Jugador>&& jugadores) const
{
    Lista<Pokemon> res;
    Lista<Pokemon> ::const_Iterador it = jugadores.CrearIt();
    while(it.HaySiguiente()){
        Jugador jug = it.Siguiente();
        Lista<Pokemon> :: const_Iterador itPoke = Juego::Pokemons(jug);
        while (itPoke.HaySiguiente()){
            Juego::TuplaPokeNat tupPoke = itPoke.Siguiente();
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

const Conj<Coordenada> Juego::BuscarPokemonsCercanos(const Coordenada&& coord, const Conj<Coordenada>&& conjCoord) const
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

const Nat Juego::CantMismaEspecie(const Pokemon&& poke, const Conj<Pokemon>&& pokemones) const
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

Arreglo< Arreglo<posStruct> > Juego::CrearPosiciones(const Mapa&& map)
{
    Nat ancho = Juego::Mapa().MaxLatitud();
    Nat largo = Juego::Mapa().MaxLongitud();
    Arreglo<Arreglo<posStruct> > posiciones(largo);
    Nat lg = 0;
    while (lg<largo){
        Arreglo<posStruct> arrAncho(ancho);
        posiciones[lg]=arrAncho;
        lg ++;
    }
}

void Juego::PosicionarPokemon(const Pokemon&& poke, const Coordenada&& coord, Conj<Coordenada>::const_Iterador itCoord)
{
    Juego::posStruct tupla = &Juego::posiciones[coord.Latitud()][coord.Longitud()];
    ColaPrior< TuplaNatJug > jugACapturarlo;
    Nat lat = coord.Latitud();
    Nat lon = coord.Longitud();
    Nat latDesde = 0;
    if (lat-2>0){
        latDesde = lat-2;
    }
    while (latDesde<= lat+2 && latDesde<Juego::Mapa.MaxLatitud()){
        Nat lonDesde = 0;
        if (lon-2>0){
            lonDesde=lon-2;
        }
        while (lonDesde<=lat+2 && lonDesde<Juego::Mapa.MaxLongitud()){
            if(Coordenada::distEuclidea(Coordenada(latDesde,lonDesde),coord)){
                posStruct subTupla = &Juego::jugadores[lonDesde][latDesde];
                ColaPrior::ItColaPrior itJugadores = subTupla.jugadores.crearIt();
                while(itJugadores.haySiguiente()){
                    Juego::TuplaNatJug jugador = itJugadores.siguiente();
                    jugadorStruct jugStruct = &Juego.jugadores[jugador.jug()];
                    jugStruct.itCapturarPoke = jugACapturarlo.encolar(jugador);
                    itJugadores.avanzar();
                }
            }
            lonDesde++;
        }
        latDesde ++;
    }
    Juego::pokemonACapturar puntero = &Juego::nuevoPokemonACapturar(poke,itCoord,jugACapturarlo);
    tupla.pokemonACapturar = puntero;

}

Juego::pokemonACapturar Juego::nuevoPokemonACapturar(const Pokemon& poke, Conj<Coordenada>::const_Iterador itCoord,ColaPrior<Juego::TuplaNatJug> jugACapturarlo){
    Juego::pokemonACapturar res;
    res.pokemon=poke;
    res.movAfuera=0;
    res.jugACapturarlo = jugACapturarlo;
    res.itCoord = itCoord;
    return res;
}


void Juego::capturarPokemon(const Jugador& jug, const Pokemon& poke)
{
    Juego::jugadorStruct jugador = juego.jugadores[jug];
    Nat cantPoke = Juego::pokemonesSalvajes.Obtener(poke);
    Juego::pokemonesSalvajes.Definir(poke,cantPoke-1);
    if(Juego::pokemonesSalvajes.Definido(poke)){
        Nat cantPoke = Juego::pokemonesCapturados.Obtener(poke);
        Juego::pokemonesCapturados.Definir(poke,cantPoke+1);
    }
    else {
        Juego::pokemonesCapturados.Definir(poke,1);
    }
    if (jugador.itPokemones.Definido(poke)){
        Lista< TuplaPokeNat>::Iterador itPokemones = jugador.itPokemones.Obtener(poke);
        Nat cantPoke = itPokemones.Siguiente().cant_;
        itPokemones.Siguiente().cant_ = cantPoke+1;
    }
    else {
        Lista<Juego::TuplaPokeNat>::Iterador itPoke = jugador.pokemones.CrearItUlt();

        itPoke.AgregarComoSiguiente(Juego::TuplaPokeNat(poke,1));
        jugador.itPokemones.Definir(poke,itPoke);
    }
    jugador.pokemonesTotales = jugador.pokemonesTotales+1;
    juego.jugadores[jug]=jugador;
}

//  Constructor de pokemonACapturar
Juego::pokemonACapturar::pokemonACapturar(const Pokemon& poke, Conj<Coordenada>::const_Iterador itCoord, ColaPrior<TuplaNatJug> &jugACapturarlo)
{
    Juego::pokemonACapturar res;
    res.pokemon = poke;
    res.movAfuera = 0;
    res.jugACapturarlo = jugACapturarlo;
    res.itCoord = itCoord;
    return res;
}

//  Constructor de jugadorStruct
Juego::jugadorStruct::jugadorStruct(Conj<Jugador>::Iterador itNoExpulsados)
{
    Juego::jugadorStruct res;
    Coordenada nueva(0,0);
    Lista<Juego::TuplaNatJug> jug; //falta inicializar TuplaNatJug
    Lista<TuplaPokeNat> pokemones; //falta inicializar TuplaPokeNat
    res.conectado = false;
    res.sanciones = 0;
    res.pos = nueva;
    res.pokemonesTotales = 0;
    res.itCapturarPoke = jug.CrearIt();
    res.pokemones = pokemones.CrearIt();

}
