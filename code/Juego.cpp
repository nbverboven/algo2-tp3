#include "Juego.h"



/*
 * Para simplificar la escritura y poder identificar a quién correspondían los
 * atributos, se utilizaron los siguientes prefijos:
 * 
 *   1) JG_ para referirse a los atributos de la clase Juego.
 *   2) tupla_ para los atributos de la clase Juego.
 *   3) jG_ para los atributos de jugadorStruct.
 *   4) pS_ para los atributos de posicionStruct.
 *   5) pAC_ para los atributos de pokemonACapturar.
 */

/********************************************************************************
*********                    IMPLEMENTACIÓN DE TUPLA                    *********
*********************************************************************************/

template <class P, class S>
Juego::Tupla<P,S>::Tupla()
	: tupla_prm_(), tupla_sgd_()
{}


template <class P, class S>
Juego::Tupla<P,S>::Tupla(const P& prim, const S& seg)
	: tupla_prm_(prim), tupla_sgd_(seg)
{}


template <class P, class S>
const P& Juego::Tupla<P,S>::primero() const
{
	return tupla_prm_;
}


template <class P, class S>
const S& Juego::Tupla<P,S>::segundo() const
{
	return tupla_sgd_;
}


template <class P, class S>
bool Juego::Tupla<P,S>::operator==(const Tupla& otra) const
{
	return tupla_prm_ == otra.tupla_prm_ && tupla_sgd_ == otra.tupla_sgd_;
}


template <class P, class S>
bool Juego::Tupla<P,S>::operator<(const Tupla& otra) const
{
	return tupla_prm_ < otra.tupla_prm_ || tupla_sgd_ < otra.tupla_sgd_;
}


template <class P, class S>
bool Juego::Tupla<P,S>::operator>(const Tupla& otra) const
{
	return !(*this < otra) && !(*this == otra);
}


// Constructor
Juego::Juego()
{}

Juego::Juego(const Mapa& map)
	: JG_mapa_(map), JG_jugNoExpulsados_(), JG_jugadores_(),
	  JG_posConPokemones_(), JG_pokemonesSalvajes_(),
	  JG_pokemonesCapturados_(), JG_posiciones_(CrearPosiciones(map)),
	  JG_cantPokemonsTotales_(0)
{}


// Destructor
Juego::~Juego()
{}





/********************************************************************************
*********                        GENERADORES                            *********
*********************************************************************************/

void Juego::AgregarPokemon(const Pokemon &poke, const Coordenada& coord)
{
	// assert(PuedoAgregarPokemon(coord));

	Nat nuevaCantPokemonTotal = JG_cantPokemonsTotales_ + 1;
	JG_cantPokemonsTotales_ = nuevaCantPokemonTotal;
	Conj<Coordenada>::Iterador itConjPoke = JG_posConPokemones_.AgregarRapido(coord);
	PosicionarPokemon(poke, coord, itConjPoke);

	if (JG_pokemonesSalvajes_.Definido(poke))
	{
		Nat cantidad = JG_pokemonesSalvajes_.Obtener(poke);
		JG_pokemonesSalvajes_.Definir(poke, cantidad+1);
	}
	else
	{
		JG_pokemonesSalvajes_.Definir(poke, 1);
	}
}


Jugador Juego::AgregarJugador()
{
	Jugador nuevoID = ProxID();
	Conj<Jugador>::Iterador itNoExpulsados = JG_jugNoExpulsados_.AgregarRapido(nuevoID);
	typename Juego::jugadorStruct nuevo_jugador(itNoExpulsados);
	JG_jugadores_.AgregarAtras(nuevo_jugador);

	return nuevoID;
}


void Juego::Conectarse(const Jugador& jug, Coordenada coord)
{
	JG_jugadores_[jug].jS_conectado_ = true;
	JG_jugadores_[jug].jS_pos_ = coord;

	typename Juego::posStruct* datos_de_la_posicion = &(JG_posiciones_[coord.Latitud()][coord.Longitud()]);
	typename Juego::Tupla<Nat,Jugador> tupla(JG_jugadores_[jug].jS_pokemonesTotales_, jug);

	JG_jugadores_[jug].jS_itPosJug_ = datos_de_la_posicion->pS_jugadores_.encolar(tupla);

	if ( HayPokemonCercano(coord) )
	{
		Coordenada coordPoke = PosPokemonCercano(coord);
		typename Juego::pokemonACapturar* pokeACapturar = JG_posiciones_[coordPoke.Latitud()][coordPoke.Longitud()].pS_pokemonACapturar_;
		JG_jugadores_[jug].jS_itCapturarPoke_ = pokeACapturar->pAC_jugACapturarlo_.encolar(tupla);
		pokeACapturar->pAC_movAfuera_ = 0;
	}
}


void Juego::Desconectarse(const Jugador& jug)
{
	JG_jugadores_[jug].jS_conectado_ = false;
	JG_jugadores_[jug].jS_itPosJug_.eliminarSiguiente();

	if ( HayPokemonCercano(JG_jugadores_[jug].jS_pos_) )
	{
		JG_jugadores_[jug].jS_itCapturarPoke_.eliminarSiguiente();
	}
}


void Juego::Moverse(const Jugador& jug, const Coordenada& coord)
{
	// assert(JG_jugNoExpulsados_.Pertenece(jug));
	// assert(EstaConectado(jug));
	// assert(JG_mapa_.PosicionExistente(coord));

	typename Juego::jugadorStruct* jugador = &JG_jugadores_[jug];
	Coordenada posAnterior = jugador->jS_pos_;

	if ( DebeSancionarse(jug, coord) && !DebeExpulsarse(jug, coord) )
	{
		jugador->jS_sanciones_ += 1;

	}
	else
	{
		if ( DebeExpulsarse(jug, coord) )
		{
			jugador->jS_sanciones_ += 1;
			jugador->jS_itJugNoExpulsados_.EliminarSiguiente();
			Lista< typename Juego::Tupla<Pokemon,Nat> >::Iterador pokemones = jugador->jS_pokemones_.CrearIt();

			if ( HayPokemonCercano(posAnterior) )
			{
				jugador->jS_itCapturarPoke_.eliminarSiguiente();
			}

			while ( pokemones.HaySiguiente() ) 
			{
				Pokemon poke = pokemones.Siguiente().primero();
				Nat cantPoke = pokemones.Siguiente().segundo();
				Nat nuevaCantPokemonTotal = JG_cantPokemonsTotales_ - cantPoke;
				JG_cantPokemonsTotales_ = nuevaCantPokemonTotal;
				Nat nuevaCantPoke = JG_pokemonesCapturados_.Obtener(poke) - cantPoke;
				JG_pokemonesCapturados_.Definir(poke, nuevaCantPoke);

				pokemones.Avanzar();
			}
		}
		else 
		{
			typename Juego::Tupla<Nat,Jugador> tupla(jugador->jS_pokemonesTotales_, jug);

			jugador->jS_itPosJug_.eliminarSiguiente(); // problema
			jugador->jS_itPosJug_ = JG_posiciones_[coord.Latitud()][coord.Longitud()].pS_jugadores_.encolar(tupla);
			jugador->jS_pos_ = coord;

			if ( HayPokemonCercano(posAnterior) )
			{
				if ( HayPokemonCercano(coord) )
				{
					if ( PosPokemonCercano(posAnterior) != PosPokemonCercano(coord) )
					{
						jugador->jS_itCapturarPoke_.eliminarSiguiente(); // problema
						Coordenada coorPoke = PosPokemonCercano(coord);
						typename Juego::pokemonACapturar* pokeACapturar = JG_posiciones_[coorPoke.Latitud()][coorPoke.Longitud()].pS_pokemonACapturar_;
						jugador->jS_itCapturarPoke_ = pokeACapturar->pAC_jugACapturarlo_.encolar(tupla);
						pokeACapturar->pAC_movAfuera_ = 0;
					}
				}
				else
				{
					jugador->jS_itCapturarPoke_.eliminarSiguiente(); // problema
				}
			}
			else
			{
				if ( HayPokemonCercano(coord) )
				{
					Coordenada coorPoke = PosPokemonCercano(coord);
					typename Juego::pokemonACapturar* pokeACapturar = JG_posiciones_[coorPoke.Latitud()][coorPoke.Longitud()].pS_pokemonACapturar_;
					jugador->jS_itCapturarPoke_ = pokeACapturar->pAC_jugACapturarlo_.encolar(tupla);
					pokeACapturar->pAC_movAfuera_ = 0;
				}
			}


			Conj<Coordenada>::Iterador itPosConPoke = JG_posConPokemones_.CrearIt();

			while ( itPosConPoke.HaySiguiente() )
			{
				Coordenada posConPoke = itPosConPoke.Siguiente();
				Nat lat = posConPoke.Latitud();
				Nat lon = posConPoke.Longitud();
				typename Juego::pokemonACapturar* pokeACap = JG_posiciones_[lat][lon].pS_pokemonACapturar_;

				if ( Coordenada::distEuclidea(posConPoke, coord) > 4 )
				{
					pokeACap->pAC_movAfuera_ += 1;
				}

				if ( pokeACap->pAC_movAfuera_ == 10 && !(pokeACap->pAC_jugACapturarlo_.esVacia()) )
				{
					typename Juego::Tupla<Nat,Jugador> jugACapt = pokeACap->pAC_jugACapturarlo_.proximo();

					capturarPokemon(jugACapt.segundo(), pokeACap->pAC_pokemon_);

					itPosConPoke.EliminarSiguiente();

					delete pokeACap;
					JG_posiciones_[lat][lon].pS_pokemonACapturar_ = NULL;
				}

				if ( !itPosConPoke.HaySiguiente() )
				{
					break;
				}

				itPosConPoke.Avanzar();
			}
		}
	}
}





/********************************************************************************
*********                     OBSERVADORES BÁSICOS                      *********
*********************************************************************************/

const Mapa& Juego::mapa() const
{
	return JG_mapa_;
}


Conj<Jugador>::const_Iterador Juego::Jugadores() const
{
	return JG_jugNoExpulsados_.CrearIt();
}


bool Juego::EstaConectado(const Jugador& jug) const
{
	return JG_jugadores_[jug].jS_conectado_;
}


Nat Juego::Sanciones(const Jugador& jug) const
{
	return JG_jugadores_[jug].jS_sanciones_;
}


Coordenada Juego::Posicion(const Jugador& jug) const
{
	return JG_jugadores_[jug].jS_pos_;
}


Lista< typename Juego::Tupla<Pokemon,Nat> >::Iterador Juego::Pokemons(const Jugador& jug)
{
	return JG_jugadores_[jug].jS_pokemones_.CrearIt();
}


Lista< typename Juego::Tupla<Pokemon,Nat> >::const_Iterador Juego::Pokemons(const Jugador& jug) const
{
	return JG_jugadores_[jug].jS_pokemones_.CrearIt();
}


Conj<Jugador> Juego::Expulsados() const
{
	Conj<Jugador> res;
	Jugador i = 0;

	while ( i < JG_jugadores_.Longitud() )
	{
		if (JG_jugadores_[i].jS_sanciones_ == 5)
		{
			res.AgregarRapido(i);
		}

		i++;
	}

	return res;
}


Conj<Coordenada> Juego::PosConPokemons() const
{
	return JG_posConPokemones_;
}


Pokemon Juego::PokemonEnPos(const Coordenada& coord) const
{
	return JG_posiciones_[coord.Latitud()][coord.Longitud()].pS_pokemonACapturar_->pAC_pokemon_;
}


Nat Juego::CantMovimientosParaCaptura(const Coordenada& coord) const
{
	return JG_posiciones_[coord.Latitud()][coord.Longitud()].pS_pokemonACapturar_->pAC_movAfuera_;
}




/********************************************************************************
*********                      OTRAS OPERACIONES                        *********
*********************************************************************************/

Jugador Juego::ProxID() const
{
	return JG_jugadores_.Longitud();
}


Conj<Jugador> Juego::JugadoresConectados() const
{
	Conj<Jugador> res;
	Jugador i = 0;

	while ( i < JG_jugadores_.Longitud() )
	{
		if ( JG_jugadores_[i].jS_conectado_ && JG_jugadores_[i].jS_sanciones_ < 5 )
		{
			res.AgregarRapido(i);
		}

		i++;
	}

	return res;
}


Conj<Jugador> Juego::SoloLosConectados(const Conj<Jugador>& jugadores) const
{
	Conj<Jugador> res;
	Conj<Jugador>::const_Iterador it = jugadores.CrearIt();

	while ( it.HaySiguiente() )
	{
		if ( JG_jugadores_[it.Siguiente()].jS_conectado_ )
		{
			res.AgregarRapido(it.Siguiente());
		}

		it.Avanzar();
	}

	return res;
}


bool Juego::PuedoAgregarPokemon(const Coordenada& coord) const
{
	return !HayPokemonEnTerritorio(coord, JG_posConPokemones_) && JG_mapa_.PosicionExistente(coord);
}


bool Juego::HayPokemonEnTerritorio(const Coordenada& coord, const Conj<Coordenada>& conjCoord) const
{
	bool res = false;
	Conj<Coordenada>::const_Iterador it = conjCoord.CrearIt();

	while ( it.HaySiguiente() )
	{
		Coordenada coordPoke = it.Siguiente();
		res = res || Coordenada::distEuclidea(coord, coordPoke) <= 25;
		it.Avanzar();
	}

	return res;
}


bool Juego::DebeSancionarse(const Jugador& jug, const Coordenada& coord) const
{
	typename Juego::jugadorStruct jugador = JG_jugadores_[jug];

	return !(JG_mapa_.HayCamino(jugador.jS_pos_, coord)) || Coordenada::distEuclidea(jugador.jS_pos_,coord) > 100;
}


bool Juego::DebeExpulsarse(const Jugador& jug, const Coordenada& coord) const
{
	return DebeSancionarse(jug, coord) && JG_jugadores_[jug].jS_sanciones_ >= 4;
}


bool Juego::HayPokemonCercano(const Coordenada& coord) const
{
	bool res = false;
	Nat lat = coord.Latitud();
	Nat lon = coord.Longitud();
	Nat latDesde = 0;

	if ( lat > 2 )
	{
		latDesde = lat - 2;
	}
	while ( latDesde <= lat+2 && latDesde <= JG_mapa_.MaxLatitud() )
	{
		Nat lonDesde = 0;

		if ( lon > 2 )
		{
			lonDesde = lon - 2;
		}
		while ( lonDesde <= lon+2 && lonDesde <= JG_mapa_.MaxLongitud() )
		{
			if ( Coordenada::distEuclidea(Coordenada(latDesde,lonDesde),coord) <= 4 )
			{
				if ( JG_posiciones_[latDesde][lonDesde].pS_pokemonACapturar_ != NULL )
				{
					res = true;
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
	// assert(HayPokemonCercano(coord));

	Coordenada res(0,0);
	bool lo_encontre = false;
	Nat lat = coord.Latitud();
	Nat lon = coord.Longitud();
	Nat latDesde = 0;

	if ( lat > 2 )
	{
		latDesde = lat - 2;
	}

	while (latDesde <= lat+2 && latDesde <= JG_mapa_.MaxLatitud() && !lo_encontre )
	{
		Nat lonDesde = 0;

		if ( lon > 2 )
		{
			lonDesde= lon-2;
		}

		while ( lonDesde <= lon+2 && lonDesde <= JG_mapa_.MaxLongitud() && !lo_encontre )
		{
			Coordenada retCoor(latDesde,lonDesde);

			if ( Coordenada::distEuclidea(retCoor,coord) <= 4 )
			{
				if ( JG_posiciones_[latDesde][lonDesde].pS_pokemonACapturar_ != NULL )
				{
					lo_encontre = true;
					res = retCoor;
				}
			}

			lonDesde ++;
		}

		latDesde ++;
	}

	return res;
}


Conj<Jugador> Juego::EntrenadoresPosibles(const Coordenada& coord, const Conj<Jugador>& jugadores) const
{
	Conj<Jugador> res;
	Conj<Jugador>::const_Iterador it = jugadores.CrearIt();

	while ( it.HaySiguiente() )
	{
		Jugador jug = it.Siguiente();
		Coordenada coordJug = JG_jugadores_[jug].jS_pos_;

		if ( Coordenada::distEuclidea(coord,coordJug) <= 4 )
		{
			res.AgregarRapido(jug);
		}

		it.Avanzar();
	}

	return res;
}


Conj<Coordenada> Juego::PosDePokemonsACapturar(const Coordenada& coord, const Conj<Coordenada>& conjCoord) const
{
	Conj<Coordenada> res;
	Conj<Coordenada>::const_Iterador it = conjCoord.CrearIt();

	while ( it.HaySiguiente() )
	{
		Coordenada pCoord = it.Siguiente();

		if ( SeCapturo(pCoord, coord) )
		{
			res.AgregarRapido(pCoord);
		}

		it.Avanzar();
	}

	return res;
}


bool Juego::SeCapturo(const Coordenada& coord1, const Coordenada& coord2) const
{
	bool res = false;

	if ( HayPokemonCercano(coord2) )
	{
		res = PosPokemonCercano(coord2) != coord1 && CantMovimientosParaCaptura(coord1) >= 9 && 
		      !(EntrenadoresPosibles(coord1, JugadoresConectados()).EsVacio());
	}
	else
	{
		res = CantMovimientosParaCaptura(coord1) >= 9 && !(EntrenadoresPosibles(coord1, JugadoresConectados()).EsVacio());
	}
	return res;
}


Nat Juego::IndiceDeRareza(const Pokemon& poke) const
{
	Nat cant = CantMismaEspecie(poke);

	return 100-(100*cant/JG_cantPokemonsTotales_);
}


Nat Juego::CantPokemonsTotales() const
{
	return JG_cantPokemonsTotales_;
}


Lista<Pokemon> Juego::TodosLosPokemons() const
{
	Lista<Pokemon> res = PokemonsSalvajes(PosConPokemons());
	Lista<Pokemon>::const_Iterador it = PokemonsCapturados(JG_jugNoExpulsados_).CrearIt();

	while ( it.HaySiguiente() )
	{
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

	while ( it.HaySiguiente() )
	{
		Coordenada coordPoke = it.Siguiente();

		if ( JG_posConPokemones_.Pertenece(coordPoke) )
		{
			Pokemon poke = JG_posiciones_[coordPoke.Latitud()][coordPoke.Longitud()].pS_pokemonACapturar_->pAC_pokemon_;
			res.AgregarAtras(poke);
		}

		it.Avanzar();
	}

	return res;
}


Lista<Pokemon> Juego::PokemonsCapturados(const Conj<Jugador>& jugadores) const
{
	Lista<Pokemon> res;
	Conj<Jugador>::const_Iterador it = jugadores.CrearIt();

	while ( it.HaySiguiente() )
	{
		Jugador jug = it.Siguiente();
		Lista< Tupla<Pokemon,Nat> >::const_Iterador itPoke = Pokemons(jug);

		while ( itPoke.HaySiguiente() )
		{
			typename Juego::Tupla<Pokemon,Nat> tupPoke = itPoke.Siguiente();
			Nat CantParaAgregar = tupPoke.segundo();

			while ( CantParaAgregar > 0 )
			{
				res.AgregarAtras(tupPoke.primero());
				CantParaAgregar -= 1;
			}

			itPoke.Avanzar();
		}

		it.Avanzar();
	}

	return res;
}


Conj<Coordenada> Juego::BuscarPokemonsCercanos(const Coordenada& coord, const Conj<Coordenada>& conjCoord) const
{
	Conj<Coordenada> res;
	Conj<Coordenada>::const_Iterador it = conjCoord.CrearIt();

	while ( it.HaySiguiente() )
	{
		Coordenada coordPoke = it.Siguiente();

		if ( Coordenada::distEuclidea(coord,coordPoke) <= 4 )
		{
			res.AgregarRapido(coordPoke);
		}

		it.Avanzar();
	}

	return res;
}


Nat Juego::CantMismaEspecie(const Pokemon& poke) const
{
	Nat cant = 0;

	if ( JG_pokemonesSalvajes_.Definido(poke) )
	{
		cant += JG_pokemonesSalvajes_.Obtener(poke);
	}

	if ( JG_pokemonesCapturados_.Definido(poke) )
	{
		cant += JG_pokemonesCapturados_.Obtener(poke);
	}

	return cant;
}





/********************************************************************************
*********                    FUNCIONES AUXILIARES                       *********
*********************************************************************************/

Arreglo< Arreglo< typename Juego::posStruct > > Juego::CrearPosiciones(const Mapa& map)
{
	Nat ancho = map.MaxLongitud() + 1;
	Nat largo = map.MaxLatitud() + 1;
	Arreglo<Arreglo<posStruct> > posiciones(largo);
	Nat an = 0;
	Arreglo<posStruct> arrAncho(ancho);

	while ( an < ancho )
	{
		typename Juego::posStruct nueva;
		arrAncho.Definir(an,nueva);
		an ++;
	}

	Nat lg = 0;

	while ( lg < largo )
	{
		posiciones.Definir(lg,arrAncho);
		lg++;
	}

	return posiciones;
}


void Juego::PosicionarPokemon(const Pokemon& poke, const Coordenada& coord, Conj<Coordenada>::Iterador itCoord)
{
	typename Juego::posStruct* tupla = &JG_posiciones_[coord.Latitud()][coord.Longitud()];
	tupla->pS_pokemonACapturar_ = new pokemonACapturar(poke, itCoord);
	
	Nat lat = coord.Latitud();
	Nat lon = coord.Longitud();
	Nat latDesde = 0;

	if ( lat > 2 )
	{
		latDesde = lat - 2;
	}

	while ( latDesde <= lat+2 && latDesde <= JG_mapa_.MaxLatitud() )
	{
		Nat lonDesde = 0;

		if ( lon > 2 )
		{
			lonDesde = lon - 2;
		}

		while ( lonDesde <= lon+2 && lonDesde <= JG_mapa_.MaxLongitud() )
		{
			if ( Coordenada::distEuclidea(Coordenada(latDesde,lonDesde), coord) <= 4 )
			{
				typename Juego::posStruct* subTupla = &JG_posiciones_[latDesde][lonDesde];
				ColaPrior< typename Juego::Tupla<Nat,Jugador> >::ItColaPrior itJugadores = subTupla->pS_jugadores_.crearIt();

				while ( itJugadores.haySiguiente() )
				{
					typename Juego::Tupla<Nat,Jugador> jugador = itJugadores.siguiente();
					typename Juego::jugadorStruct* jSuct = &JG_jugadores_[jugador.segundo()];

					jSuct->jS_itCapturarPoke_ = tupla->pS_pokemonACapturar_->pAC_jugACapturarlo_.encolar(jugador);
					itJugadores.avanzar();
				}
			}

			lonDesde++;
		}

		latDesde ++;
	}
}


void Juego::capturarPokemon(const Jugador& jug, const Pokemon& poke)
{
	typename Juego::jugadorStruct* jugador = &JG_jugadores_[jug];
	Nat cantPoke = JG_pokemonesSalvajes_.Obtener(poke);
	JG_pokemonesSalvajes_.Definir(poke, cantPoke-1);

	if ( JG_pokemonesCapturados_.Definido(poke) )
	{
		Nat cantPoke = JG_pokemonesCapturados_.Obtener(poke);
		JG_pokemonesCapturados_.Definir(poke, cantPoke+1);
	}
	else
	{
		JG_pokemonesCapturados_.Definir(poke, 1);
	}

	if ( jugador->jS_itPokemones_.Definido(poke) )
	{
		Lista< typename Juego::Tupla<Pokemon,Nat> >::Iterador itPokemones = jugador->jS_itPokemones_.Obtener(poke);
		Nat cantPoke = itPokemones.Siguiente().segundo();
		itPokemones.EliminarSiguiente();

		typename Juego::Tupla<Pokemon,Nat> nueva_tupla(poke, cantPoke + 1);
		itPokemones.AgregarComoSiguiente(nueva_tupla);

		jugador->jS_itPokemones_.Definir(poke, itPokemones);
	}
	else
	{
		typename Juego::Tupla<Pokemon,Nat> nueva_tupla(poke, 1);
		Lista< typename Juego::Tupla<Pokemon,Nat> >::Iterador itPoke = jugador->jS_pokemones_.CrearItUlt();
		itPoke.AgregarComoSiguiente(nueva_tupla);

		jugador->jS_itPokemones_.Definir(poke, itPoke);
	}

	jugador->jS_pokemonesTotales_ += 1;
}
