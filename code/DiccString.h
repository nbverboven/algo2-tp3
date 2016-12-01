#ifndef DICC_STRING_H_INCLUDED
#define DICC_STRING_H_INCLUDED

#include "aed2.h"
#include <string>
#include <iostream>
#include <cassert>

using namespace aed2;


template<typename T>
class DiccString 
{
  public:
	
	~DiccString();

	DiccString();
	DiccString(const DiccString<T>&);

	void Definir(const String& clave, const T& significado);
	bool Definido(const String& clave) const;

	const T& Obtener(const String& clave) const;
	T& Obtener(const String& clave);

	void Borrar(const String& clave);
	const Conj<String>& Claves() const;

  private:

	struct Nodo
	{

		Nodo()
		{
			siguientes_ = new Nodo*[256];

			for (int i = 0; i < 256; i++)
			{
				siguientes_[i] = NULL;
			}

			definicion_ = NULL;
			padre_ = NULL;
		}

		~Nodo()
		{
			delete definicion_;
			delete[] siguientes_;
		}

		T* definicion_;
		Nodo* padre_;
		Nodo** siguientes_;
	};

	Nodo* raiz_;
	Conj<String> claves_;


	int caminosPosibles(const Nodo* actual) const;
	void borrarSubString(const Nodo* desde, Nodo* hasta, const char& ultimo_char_borrado);
};

	



template <typename T>
DiccString<T>::DiccString()
	: raiz_(NULL), claves_()
{}


template <typename T>
DiccString<T>::DiccString(const DiccString& d) 
{
	raiz_ = NULL;

	Conj<String>::const_Iterador it = d.Claves().CrearIt(); 

	while ( it.HaySiguiente() )
	{
		Definir(it.Siguiente(), d.Obtener(it.Siguiente()));
		it.Avanzar();
	}
}


template <typename T>
DiccString<T>::~DiccString()
{

	while ( claves_.Cardinal() >0 )
	{
		Conj<String>::Iterador it = claves_.CrearIt();
		String s = it.Siguiente();
		Borrar(s);
	}

	delete raiz_;
}


template <typename T>
void DiccString<T>::Definir(const String& clave, const T& significado)
{
	// Notar que no es posible definir el string vacío.
	if (clave.size() > 0)
	{
		// En primer lugar, agrego la clave al conjunto de claves del
		// diccionario.
		claves_.Agregar(clave);

		if (raiz_ == NULL)
		{
			raiz_ = new Nodo();
		}

		Nodo* actual = raiz_;

		// Inserto la clave en el trie
		for (unsigned i = 0; i < clave.size(); ++i)
		{
			int indice = int(clave[i]);

			if (actual->siguientes_[indice] == NULL)
			{
				actual->siguientes_[indice] = new Nodo();
				actual->siguientes_[indice]->padre_ = actual;
			}

			actual = actual->siguientes_[indice];
		}

		// Borro el viejo significado (de haberlo)
		if (actual->definicion_ != NULL)
		{
			delete actual->definicion_;
			actual->definicion_ = NULL;
		}

		// Defino el nuevo significado
		actual->definicion_ = new T(significado);
	}
}


template <typename T>
bool DiccString<T>::Definido(const String& clave) const
{
	bool esta_definido = false;
	unsigned i = 0;
	Nodo* actual = raiz_;

	// Busco la posición en donde debería estar la definición.
	while (i < clave.size() && actual != NULL)
	{
		actual = actual->siguientes_[int(clave[i])];
		++i;
	}

	if (actual != NULL && actual->definicion_ != NULL)
	{
		esta_definido = true;
	}

	return esta_definido;
}


template <typename T>
T& DiccString<T>::Obtener(const String& clave) 
{   
	assert(Definido(clave));
	
	Nodo* actual = raiz_;

	for (unsigned i = 0; i < clave.size(); ++i)
	{
		actual = actual->siguientes_[int(clave[i])];
	}

	return *(actual->definicion_);
}


template <typename T>
const T& DiccString<T>::Obtener(const String& clave) const 
{
	assert(Definido(clave));

	Nodo* actual = raiz_;

	for (unsigned i = 0; i < clave.size(); ++i)
	{
		actual = actual->siguientes_[int(clave[i])];
	}

	return *(actual->definicion_);
}


template <typename T>
const Conj<String>& DiccString<T>::Claves() const
{
	return claves_;
}


template <typename T>
void DiccString<T>::Borrar(const String& clave) 
{
	assert(Definido(clave));

	claves_.Eliminar(clave);

	Nodo* actual = raiz_;

	// Si una parte de la clave se comparte con otras del diccionario, 
	// esta es la posición que marca dónde se diferencia la clave actual
	Nodo* hasta_aca_es_prefijo = raiz_;
	char borro_desde_esta_letra = clave[0];

	// Busco el el trie hasta encontrar el lugar en donde se encuentra 
	// definida la clave
	for (unsigned i = 0; i < clave.size(); ++i)
	{
		// Guardo la posición de las "bifurcaciones" que voy encontrando.
		if (caminosPosibles(actual) > 1 || actual->definicion_ != NULL)
		{
			hasta_aca_es_prefijo = actual;
			borro_desde_esta_letra = clave[i];
		}

		actual = actual->siguientes_[int(clave[i])];
	}

	// if: la clave es prefijo de otra
	// else: caso contrario
	if (caminosPosibles(actual) > 0)
	{
		delete actual->definicion_;
		actual->definicion_ = NULL;
	}
	else
	{
		borrarSubString(hasta_aca_es_prefijo, actual, borro_desde_esta_letra);
	}
}


template <typename T>
int DiccString<T>::caminosPosibles(const Nodo* actual) const 
{
	int count = 0;

	for (int i = 0; i < 256; ++i)
	{
		if (actual->siguientes_[i] != NULL)
		{
			count += 1;
		}
	}

	return count;
}


template <typename T>
void DiccString<T>::borrarSubString(const Nodo* desde, Nodo* hasta, const char& ultimo_char_borrado)
{
	while (desde != hasta)
	{
		Nodo* anterior = hasta->padre_;
		hasta->padre_ = NULL;
		delete hasta;
		hasta = anterior;
	}

	desde->siguientes_[int(ultimo_char_borrado)] = NULL;
}




#endif /* DICC_STRING_H_INCLUDED */