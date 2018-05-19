#ifndef COLA_PRIOR_H_INCLUDED
#define COLA_PRIOR_H_INCLUDED

#include "aed2.h"
#include <iostream>
#include <cassert>

using namespace aed2;

/*
 * Implementación del módulo Cola de Prioridad(alpha). 
 * Se reemplaza alpha por T, del cual se asume que posee un 
 * constructor por copia, una función de igualdad y una relación de 
 * orden total estricto <.
 */
template <class T>
class ColaPrior
{
public:

	// Forward declaration
	class ItColaPrior;

	// Destructor
	~ColaPrior();

	// Generadores
	ColaPrior();
	ItColaPrior encolar(const T& elem);

	// Observadores básicos
	bool esVacia() const;
	void desencolar();
	const T& proximo();
	
	// Otras operaciones
	Nat tamanio() const;

	// Iterador
	ItColaPrior crearIt();


	/**********************************************
	 * Iterador de Cola de Prioridad, modificable *
	 **********************************************/
	class ItColaPrior
	{
	  public:

		ItColaPrior();

		bool haySiguiente() const;
		const T& siguiente() const;
		void eliminarSiguiente();
		void avanzar();

        // Modifica el elemento apuntado por el iterador y 
        // se ocupa de que no se pierda la propiedad del minHeap
		// Cuidado: si el iterador es inválido, se pudre todo
		void modificarSiguiente(const T& e);

	  private:

		// Constructor que toma una cola de prioridad como parámetro
		ItColaPrior(typename ColaPrior<T>::Nodo* primero, ColaPrior<T>* cola);

		void siftUp();
		void siftDown();
		void swap(typename ColaPrior<T>::Nodo* nodo, typename ColaPrior<T>::Nodo* otro_nodo);
		void agregarAlFinal(const T& asd);
		
		// Intercambia los punteros entre un padre y su hijo
		void swapParentChildNodes(typename ColaPrior<T>::Nodo* parent, typename ColaPrior<T>::Nodo* child);
		
		// Intercambia los punteros entre dos nodos no relacionados
		void swapUnrelatedNodes(typename ColaPrior<T>::Nodo* foo, typename ColaPrior<T>::Nodo* bar);
		
		// Intercambia los punteros entre dos nodos tales que uno es el siguiente del otro
		void swapPrevNextNodes(typename ColaPrior<T>::Nodo* prev, typename ColaPrior<T>::Nodo* next);
		
		friend void ColaPrior<T>::desencolar();
		friend typename ColaPrior<T>::ItColaPrior ColaPrior<T>::encolar(const T& elem);
		friend typename ColaPrior<T>::ItColaPrior ColaPrior<T>::crearIt();

		// Atributos de la clase
		typename ColaPrior<T>::Nodo* itCP_siguiente_;
		ColaPrior<T>* itCP_colaP_;
	};


private:

	struct Nodo {
		Nodo(const T& elem)
			: nodoCP_dato_(new T(elem)), nodoCP_padre_(NULL), nodoCP_hijoD_(NULL), 
			  nodoCP_hijoI_(NULL), nodoCP_siguiente_(NULL), nodoCP_anterior_(NULL) {}

		~Nodo() {
			delete nodoCP_dato_;
			delete nodoCP_hijoD_;
			delete nodoCP_hijoI_;
		}

		// Atributos del nodo
		T* nodoCP_dato_;
		Nodo* nodoCP_padre_;
		Nodo* nodoCP_hijoD_;
		Nodo* nodoCP_hijoI_;
		Nodo* nodoCP_siguiente_;
		Nodo* nodoCP_anterior_;
	};

	// Atributos de la clase
	Nodo* CP_raiz_;
	Nat CP_tamanio_;

};



/************************************
 * Implementación cola de prioridad *
 ************************************/

template <class T>
ColaPrior<T>::ColaPrior()
	: CP_raiz_(NULL), CP_tamanio_(0)
{}


template <class T>
ColaPrior<T>::~ColaPrior()
{
	delete CP_raiz_;
}


template <class T>
bool ColaPrior<T>::esVacia() const
{
	return CP_raiz_ == NULL;
}


template <class T>
Nat ColaPrior<T>::tamanio() const
{
	return CP_tamanio_;
}


template <class T>
typename ColaPrior<T>::ItColaPrior ColaPrior<T>::encolar(const T& elem)
{
	typename ColaPrior<T>::ItColaPrior it = crearIt();
	it.agregarAlFinal(elem);

	return it;
}


template <class T>
void ColaPrior<T>::desencolar()
{
	crearIt().eliminarSiguiente();
}


template <class T>
const T& ColaPrior<T>::proximo()
{
	return crearIt().siguiente();
}


template <class T>
typename ColaPrior<T>::ItColaPrior ColaPrior<T>::crearIt()
{
	return ItColaPrior(CP_raiz_, this);
}


/***************************
 * Implementación iterador *
 ***************************/

template <class T>
ColaPrior<T>::ItColaPrior::ItColaPrior()
{}


template <class T>
ColaPrior<T>::ItColaPrior::ItColaPrior(typename ColaPrior<T>::Nodo* primero, ColaPrior<T>* cola)
	: itCP_siguiente_(primero), itCP_colaP_(cola)
{}


template <class T>
const T& ColaPrior<T>::ItColaPrior::siguiente() const
{
	return *(itCP_siguiente_->nodoCP_dato_);
}


template <class T>
bool ColaPrior<T>::ItColaPrior::haySiguiente() const
{
	return itCP_siguiente_ != NULL;
}


template <class T>
void ColaPrior<T>::ItColaPrior::eliminarSiguiente()
{
	// Primero, veo si la cola tiene un solo elemento
	if ( itCP_colaP_->CP_tamanio_ == 1 )
	{
		typename ColaPrior<T>::Nodo* tmp = itCP_colaP_->CP_raiz_;
		itCP_colaP_->CP_raiz_ = NULL;

		delete tmp;
		itCP_siguiente_ = NULL;

		// Actualizo el tamaño de la cola
		itCP_colaP_->CP_tamanio_ -= 1;
	}
	else
	{
		typename ColaPrior<T>::Nodo* ultimo = (itCP_colaP_->CP_raiz_)->nodoCP_anterior_;

		// Intercambio el nodo que quiero eliminar con el último.
		// Luego de esto, el siguiente del iterador apunta al último
		// elemento del heap.
		swap(itCP_siguiente_, ultimo);
		
		typename ColaPrior<T>::Nodo* ult_padre = (itCP_siguiente_->nodoCP_padre_);

		// Reencadeno los nodos anterior y siguiente del que ahora
		// voy a eliminar
		(itCP_siguiente_->nodoCP_anterior_)->nodoCP_siguiente_ = (itCP_siguiente_->nodoCP_siguiente_);
		(itCP_siguiente_->nodoCP_siguiente_)->nodoCP_anterior_ = (itCP_siguiente_->nodoCP_anterior_);

		// El padre del último va a perder un hijo. Veo cuál
		if ( ult_padre->nodoCP_hijoD_ == itCP_siguiente_ )
		{
			ult_padre->nodoCP_hijoD_ = NULL;
		}
		else
		{
			ult_padre->nodoCP_hijoI_ = NULL;
		}

		// Apunto al nodo que voy a borrar
		typename ColaPrior<T>::Nodo* a_borrar = itCP_siguiente_;

		// Hago que el siguiente del iterador apunte al elemento que 
		// rompe el invariante de minHeap
		itCP_siguiente_ = ultimo;

		// Actualizo el tamaño de la cola
		itCP_colaP_->CP_tamanio_ -= 1;

		// Restauro el invariante
		siftDown();
		itCP_siguiente_ = NULL;

		delete a_borrar;
	}
}


template <class T>
void ColaPrior<T>::ItColaPrior::modificarSiguiente(const T& e) {
	T *old_elem = itCP_siguiente_->nodoCP_dato_;
	itCP_siguiente_->nodoCP_dato_ = new T(e);
	delete old_elem;
	siftUp();
	siftDown();
}


template <class T>
void ColaPrior<T>::ItColaPrior::siftDown()
{
	typename ColaPrior<T>::Nodo* der = itCP_siguiente_->nodoCP_hijoD_;
	typename ColaPrior<T>::Nodo* izq = itCP_siguiente_->nodoCP_hijoI_;
	typename ColaPrior<T>::Nodo* min;

	if ( izq != NULL && ( *(itCP_siguiente_->nodoCP_dato_) > *(izq->nodoCP_dato_) ) ) {
		min = izq;
	}
	else {
		min = itCP_siguiente_;
	}

	if ( der != NULL && ( *(min->nodoCP_dato_) > *(der->nodoCP_dato_) ) ) {
		min = der;
	}

	if ( min != itCP_siguiente_) {
		swap(itCP_siguiente_, min);
		siftDown();
	}
}


template <class T>
void ColaPrior<T>::ItColaPrior::siftUp()
{
	// El ciclo continúa mientras it.siguiente tenga padre y no se cumpla el 
	// invariante de minHeap
	while ( itCP_siguiente_->nodoCP_padre_ != NULL && *(itCP_siguiente_->nodoCP_dato_) < *( (itCP_siguiente_->nodoCP_padre_)->nodoCP_dato_ ) )
	{
		swap(itCP_siguiente_, itCP_siguiente_->nodoCP_padre_);
	}
}


template <class T>
void ColaPrior<T>::ItColaPrior::swapParentChildNodes(typename ColaPrior<T>::Nodo* parent, typename ColaPrior<T>::Nodo* child) {
	typename ColaPrior<T>::Nodo* parent_parent = parent->nodoCP_padre_;
	typename ColaPrior<T>::Nodo* parent_rchild = parent->nodoCP_hijoD_;
	typename ColaPrior<T>::Nodo* parent_lchild = parent->nodoCP_hijoI_;

	// typename ColaPrior<T>::Nodo* child_parent = child->nodoCP_padre_;
	typename ColaPrior<T>::Nodo* child_rchild = child->nodoCP_hijoD_;
	typename ColaPrior<T>::Nodo* child_lchild = child->nodoCP_hijoI_;

	child->nodoCP_padre_ = parent_parent;
	parent->nodoCP_padre_ = child;
	parent->nodoCP_hijoD_ = child_rchild;
	parent->nodoCP_hijoI_ = child_lchild;

	// Actualizo el padre del padre
	if (parent_parent != NULL) {
		if (parent_parent->nodoCP_hijoI_ == parent)
			parent_parent->nodoCP_hijoI_ = child;
		else
			parent_parent->nodoCP_hijoD_ = child;
	}

	// Actualizo los que eran hijos del primer nodo
	if (child_rchild != NULL)
		child_rchild->nodoCP_padre_ = parent;

	if (child_lchild != NULL)
		child_lchild->nodoCP_padre_ = parent;

	// Actualizo los que eran hijos del segundo nodo
	if (parent_lchild == child) {
		child->nodoCP_hijoD_ = parent_rchild;
		child->nodoCP_hijoI_ = parent;

		// Actualizo el padre del otro hijo.
		if (parent_rchild != NULL)
			parent_rchild->nodoCP_padre_ = child;
	}
	else {
		child->nodoCP_hijoD_ = parent;
		child->nodoCP_hijoI_ = parent_lchild;

		// Actualizo el padre del otro hijo.
		if ( parent_lchild != NULL )
			parent_lchild->nodoCP_padre_ = child;
	}
}


template <class T>
void ColaPrior<T>::ItColaPrior::swapUnrelatedNodes(typename ColaPrior<T>::Nodo* foo, typename ColaPrior<T>::Nodo* bar){
	typename ColaPrior<T>::Nodo* foo_parent = foo->nodoCP_padre_;
	typename ColaPrior<T>::Nodo* foo_rchild = foo->nodoCP_hijoD_;
	typename ColaPrior<T>::Nodo* foo_lchild = foo->nodoCP_hijoI_;

	typename ColaPrior<T>::Nodo* bar_parent = bar->nodoCP_padre_;
	typename ColaPrior<T>::Nodo* bar_rchild = bar->nodoCP_hijoD_;
	typename ColaPrior<T>::Nodo* bar_lchild = bar->nodoCP_hijoI_;

	// Ubico a foo en la posición que anteriormente correspondía 
	// a bar
	foo->nodoCP_padre_ = bar->nodoCP_padre_;
	foo->nodoCP_hijoD_ = bar->nodoCP_hijoD_;
	foo->nodoCP_hijoI_ = bar->nodoCP_hijoI_;

	// Ubico a bar en la posición que anteriormente correspondía 
	// a foo
	bar->nodoCP_padre_ = foo_parent; 
	bar->nodoCP_hijoD_ = foo_rchild;
	bar->nodoCP_hijoI_ = foo_lchild;

	// Actualizo el que era padre de foo y los que eran sus hijos
	if (foo_parent != NULL) {
		if ( foo_parent->nodoCP_hijoI_ == foo )
			foo_parent->nodoCP_hijoI_ = bar;
		else
			foo_parent->nodoCP_hijoD_ = bar;
	}

	if (foo_rchild != NULL)
		foo_rchild->nodoCP_padre_ = bar;

	if (foo_lchild != NULL)
		foo_lchild->nodoCP_padre_ = bar;

	// Actualizo el que era padre de bar y los que eran sus hijos
	if (bar_parent != NULL) {
		if (bar_parent->nodoCP_hijoI_ == bar)
			bar_parent->nodoCP_hijoI_ = foo;
		else
			bar_parent->nodoCP_hijoD_ = foo;
	}

	if (bar_rchild != NULL)
		bar_rchild->nodoCP_padre_ = foo;

	if (bar_lchild != NULL)
		bar_lchild->nodoCP_padre_ = foo;
}


template <class T>
void ColaPrior<T>::ItColaPrior::swapPrevNextNodes(typename ColaPrior<T>::Nodo* prev, typename ColaPrior<T>::Nodo* next) {
	typename ColaPrior<T>::Nodo* prev_prev = prev->nodoCP_anterior_;
	// typename ColaPrior<T>::Nodo* prev_next = prev->nodoCP_siguiente_;

	// typename ColaPrior<T>::Nodo* next_prev = next->nodoCP_anterior_;
	typename ColaPrior<T>::Nodo* next_next = next->nodoCP_siguiente_;

	(next->nodoCP_siguiente_)->nodoCP_anterior_ = prev;
	(prev->nodoCP_anterior_)->nodoCP_siguiente_ = next;

	next->nodoCP_anterior_ = prev_prev;
	next->nodoCP_siguiente_ = prev;

	prev->nodoCP_anterior_ = next;
	prev->nodoCP_siguiente_ = next_next;
}


template <class T>
void ColaPrior<T>::ItColaPrior::swap(typename ColaPrior<T>::Nodo* un_nodo, typename ColaPrior<T>::Nodo* otro_nodo) {
	if (un_nodo != otro_nodo) {
		typename ColaPrior<T>::Nodo* rz = itCP_colaP_->CP_raiz_;

		// Si alguno de los dos parámetros corresponde a la raíz de 
		// la cola de prioridad, la actualizo
		if (rz == un_nodo)
			itCP_colaP_->CP_raiz_ = otro_nodo;

		if (rz == otro_nodo)
			itCP_colaP_->CP_raiz_ = un_nodo;

		// Intercambio padres e hijos
		// Me fijo si el segundo nodo es el padre del primero
		if (un_nodo->nodoCP_padre_ == otro_nodo) {
			swapParentChildNodes(otro_nodo, un_nodo);
		}
		else {
			// Me fijo si el primer nodo es el padre del segundo
			if (otro_nodo->nodoCP_padre_ == un_nodo) {
				swapParentChildNodes(un_nodo, otro_nodo);
			}
			else {
				// Ninguno es el padre del otro
				swapUnrelatedNodes(un_nodo, otro_nodo);
			}
		}

		// Intercambio anteriores y siguientes
		// Guardo los nodos a los que apunta cada uno
		typename ColaPrior<T>::Nodo* un_nodo_prev = un_nodo->nodoCP_anterior_;
		typename ColaPrior<T>::Nodo* un_nodo_next = un_nodo->nodoCP_siguiente_;

		if (itCP_colaP_->CP_tamanio_ > 2) {
			// Me fijo si otro_nodo es el anterior de un_nodo
			if ( un_nodo->nodoCP_anterior_ == otro_nodo ) {
				swapPrevNextNodes(otro_nodo, un_nodo);
			}
			else {
				// Me fijo si un_nodo es el anterior de otro_nodo
				if (otro_nodo->nodoCP_anterior_ == un_nodo) {
					swapPrevNextNodes(un_nodo, otro_nodo);
				}
				else {
					// Hago que el anterior del siguiente y el siguiente del anterior de
					// un_nodo sean otro_nodo y viceversa.
					(un_nodo->nodoCP_anterior_)->nodoCP_siguiente_ = otro_nodo;
					(un_nodo->nodoCP_siguiente_)->nodoCP_anterior_ = otro_nodo;

					(otro_nodo->nodoCP_anterior_)->nodoCP_siguiente_ = un_nodo;
					(otro_nodo->nodoCP_siguiente_)->nodoCP_anterior_ = un_nodo;

					// Ubico a un_nodo en la posición que anteriormente correspondía 
					// a otro_nodo
					un_nodo->nodoCP_anterior_ = otro_nodo->nodoCP_anterior_;
					un_nodo->nodoCP_siguiente_ = otro_nodo->nodoCP_siguiente_;

					// Ubico a otro_nodo en la posición que anteriormente correspondía 
					// a un_nodo
					otro_nodo->nodoCP_anterior_ = un_nodo_prev;
					otro_nodo->nodoCP_siguiente_ = un_nodo_next;
				}
			}
		}
	}
}


template <class T>
void ColaPrior<T>::ItColaPrior::agregarAlFinal(const T& elem)
{
	typename ColaPrior<T>::Nodo* sig = itCP_colaP_->CP_raiz_;
	typename ColaPrior<T>::Nodo* nuevo = new Nodo(elem);

	if (sig == NULL) {
		nuevo->nodoCP_anterior_ = nuevo;
		nuevo->nodoCP_siguiente_ = nuevo;
		itCP_colaP_->CP_raiz_ = nuevo;
	}
	else {
		nuevo->nodoCP_anterior_ = sig->nodoCP_anterior_;
		nuevo->nodoCP_siguiente_ = sig;
		typename ColaPrior<T>::Nodo* padre_del_nuevo = (nuevo->nodoCP_anterior_)->nodoCP_padre_;

		if (padre_del_nuevo == NULL) {
			(nuevo->nodoCP_anterior_)->nodoCP_hijoI_ = nuevo;
			nuevo->nodoCP_padre_ = itCP_colaP_->CP_raiz_;
		}
		else {
			if (padre_del_nuevo->nodoCP_hijoI_ == NULL) {
				padre_del_nuevo->nodoCP_hijoI_ = nuevo;
			}
			else {
				if (padre_del_nuevo->nodoCP_hijoD_== NULL) {
					padre_del_nuevo->nodoCP_hijoD_ = nuevo;
				}
				else {
					padre_del_nuevo = padre_del_nuevo->nodoCP_siguiente_;
					padre_del_nuevo->nodoCP_hijoI_ = nuevo;
				}
			}

			nuevo->nodoCP_padre_ = padre_del_nuevo;
		}
	}

	(nuevo->nodoCP_anterior_)->nodoCP_siguiente_ = nuevo;
	(nuevo->nodoCP_siguiente_)->nodoCP_anterior_ = nuevo;
	itCP_siguiente_ = nuevo;
	itCP_colaP_->CP_tamanio_ += 1;
	siftUp();
}


/***************************************
 * Implementación funciones auxiliares *
 ***************************************/

template <class T>
void ColaPrior<T>::ItColaPrior::avanzar()
{
	// assert(haySiguiente());

	itCP_siguiente_ = itCP_siguiente_->nodoCP_siguiente_;

	if ( itCP_siguiente_ == itCP_colaP_->CP_raiz_ )
	{
		itCP_siguiente_ = NULL;
	}
}


template <class T>
std::ostream& operator<<(std::ostream& os, ColaPrior<T>& cola) 
{
	os << '[';
	typename ColaPrior<T>::ItColaPrior it = cola.crearIt();

	while ( it.haySiguiente() )
	{
		os << it.siguiente();
		it.avanzar();

		if ( it.haySiguiente() )
		{
			os << ", ";
		}
	}

	os << ']' << '\n';

	return os;
}

#endif /* COLA_PRIOR_H_INCLUDED */
