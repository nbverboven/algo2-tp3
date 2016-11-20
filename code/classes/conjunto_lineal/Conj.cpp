#include "Conj.h"

using namespace aed2;



template<class T>
std::ostream& operator<<(std::ostream&, const Conj<T>&);


template<class T>
bool operator==(const Conj<T>&, const Conj<T>&);


	//  Implementacion de Conjunto

template<class T>
Conj<T>::Conj()
{}


template<class T>
Conj<T>::Conj(const Conj<T>& otro)
	: dicc_( otro.dicc_ )
{}


template<class T>
typename Conj<T>::Iterador Conj<T>::Agregar(const T& e)
{
	return Iterador(dicc_.Definir(e, true));
}


template<class T>
typename Conj<T>::Iterador Conj<T>::AgregarRapido(const T& e)
{
	return Iterador(dicc_.DefinirRapido(e, true));
}


template<class T>
void Conj<T>::Eliminar(const T& e)
{
	if(Pertenece(e))
	{
		dicc_.Borrar(e);
	}
}


template<class T>
bool Conj<T>::EsVacio() const
{
	return dicc_.CantClaves()==0;
}


template<class T>
bool Conj<T>::Pertenece(const T& e) const
{
	return dicc_.Definido(e);
}


template<class T>
Nat Conj<T>::Cardinal() const
{
	return dicc_.CantClaves();
}


template<class T>
bool Conj<T>::operator==(const Conj<T>& otro) const
{
	return dicc_ == otro.dicc_;
}


template<class T>
typename Conj<T>::Iterador Conj<T>::CrearIt()
{
	return Iterador(*this);
}

template<class T>
typename Conj<T>::const_Iterador Conj<T>::CrearIt() const
{
	return const_Iterador(*this);
}


	// Implementacion Iterador

template<class T>
Conj<T>::Iterador::Iterador(const typename Conj<T>::Iterador& otra)
	: it_dicc_(otra.it_dicc_)
{}


template<class T>
typename Conj<T>::Iterador& Conj<T>::Iterador::operator = (const typename Conj<T>::Iterador& otra)
{
	it_dicc_ = otra.it_dicc_;
	return *this;
}


template<class T>
Conj<T>::Iterador::Iterador()
{}

template<class T>
bool Conj<T>::Iterador::operator == (const typename Conj<T>::Iterador& otro) const
{
	return it_dicc_ == otro.it_dicc_;
}


template<class T>
bool Conj<T>::Iterador::HaySiguiente() const
{
	return it_dicc_.HaySiguiente();
}


template<class T>
bool Conj<T>::Iterador::HayAnterior() const
{
	return it_dicc_.HayAnterior();
}

template<class T>
const T& Conj<T>::Iterador::Siguiente() const
{
	#ifdef DEBUG
	assert( HaySiguiente() );
	#endif

	return it_dicc_.SiguienteClave();
}


template<class T>
const T& Conj<T>::Iterador::Anterior() const
{
	#ifdef DEBUG
	assert( HayAnterior() );
	#endif

	return it_dicc_.AnteriorClave();
}



template<class T>
void Conj<T>::Iterador::Avanzar()
{
	#ifdef DEBUG
	assert( HaySiguiente() );
	#endif

	it_dicc_.Avanzar();
}


template<class T>
void Conj<T>::Iterador::Retroceder()
{
	#ifdef DEBUG
	assert( HayAnterior() );
	#endif

	it_dicc_.Retroceder();
}


template<class T>
void Conj<T>::Iterador::EliminarAnterior()
{
	#ifdef DEBUG
	assert( HayAnterior() );
	#endif

	it_dicc_.EliminarAnterior();
}


template<class T>
void Conj<T>::Iterador::EliminarSiguiente()
{
	#ifdef DEBUG
	assert( HaySiguiente() );
	#endif

	it_dicc_.EliminarSiguiente();
}


template<class T>
Conj<T>::Iterador::Iterador(Conj<T>& c)
	: it_dicc_( c.dicc_.CrearIt() )
{}


template<class T>
Conj<T>::Iterador::Iterador(const typename Dicc<T,bool>::Iterador& iter)
	: it_dicc_(iter)
{}


	// Implementacion const_Iterador

template<class T>
Conj<T>::const_Iterador::const_Iterador()
{}


template<class T>
Conj<T>::const_Iterador::const_Iterador(const typename Conj<T>::Iterador& otra)
	: it_dicc_( otra.it_dicc_ )
{}


template<class T>
Conj<T>::const_Iterador::const_Iterador(const typename Conj<T>::const_Iterador& otra)
	: it_dicc_( otra.it_dicc_ )
{}


template<class T>
typename Conj<T>::const_Iterador& Conj<T>::const_Iterador::operator = (const typename Conj<T>::const_Iterador& otra)
{
	it_dicc_ = otra.it_dicc_;

	return *this;
}


template<class T>
bool Conj<T>::const_Iterador::operator == (const typename Conj<T>::const_Iterador& otro) const
{
	return it_dicc_ == otro.it_dicc_;
}


template<class T>
bool Conj<T>::const_Iterador::HaySiguiente() const
{
	return it_dicc_.HaySiguiente();
}


template<class T>
bool Conj<T>::const_Iterador::HayAnterior() const
{
	return it_dicc_.HayAnterior();
}


template<class T>
const T& Conj<T>::const_Iterador::Siguiente() const
{
	#ifdef DEBUG
	assert( HaySiguiente() );
	#endif

	return it_dicc_.SiguienteClave();
}


template<class T>
const T& Conj<T>::const_Iterador::Anterior() const
{
	#ifdef DEBUG
	assert( HayAnterior() );
	#endif

	return it_dicc_.AnteriorClave();
}


template<class T>
void Conj<T>::const_Iterador::Avanzar()
{
	#ifdef DEBUG
	assert( HaySiguiente() );
	#endif

	it_dicc_.Avanzar();
}


template<class T>
void Conj<T>::const_Iterador::Retroceder()
{
	#ifdef DEBUG
	assert( HayAnterior() );
	#endif

	it_dicc_.Retroceder();
}


template<class T>
Conj<T>::const_Iterador::const_Iterador(const Conj<T>& c)
	: it_dicc_( c.dicc_.CrearIt() )
{}


	// Otras implementaciones

template<class T>
bool operator==(const Conj<T>& c1, const Conj<T>& c2)
{
	return c1.operator==(c2);
}


template<class T>
std::ostream& operator<<(std::ostream& os, const Conj<T>& c)
{
	return Mostrar(os, c, '{', '}');
}