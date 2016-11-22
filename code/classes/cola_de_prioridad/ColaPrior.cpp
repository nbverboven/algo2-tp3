#include "ColaPrior.h"

using namespace aed2;


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
    it.siftUp();

    return it;
}


template <class T>
void ColaPrior<T>::desencolar()
{
    typename ColaPrior<T>::ItColaPrior it = crearIt();
    it.eliminarSiguiente();
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
const T& ColaPrior<T>::ItColaPrior::siguiente() const
{
    return *(itCP_siguiente_->nodoCP_dato_);
}


template <class T>
ColaPrior<T>::ItColaPrior::ItColaPrior(typename ColaPrior<T>::Nodo* primero, ColaPrior<T>* cola)
    : itCP_siguiente_(primero), itCP_colaP_(cola)
{}


template <class T>
bool ColaPrior<T>::ItColaPrior::haySiguiente() const
{
    return itCP_siguiente_ != NULL;
}


template <class T>
void ColaPrior<T>::ItColaPrior::eliminarSiguiente()
{
    // Primero veo si la cola tiene un solo elemento
    if ( itCP_colaP_->CP_tamanio_ == 1 )
    {
        typename ColaPrior<T>::Nodo* tmp = itCP_colaP_->CP_raiz_;
        itCP_colaP_->CP_raiz_ = NULL;

        delete tmp;
    }
    else
    {
        typename ColaPrior<T>::Nodo* primero = itCP_colaP_->CP_raiz_;
        typename ColaPrior<T>::Nodo* ultimo = (itCP_colaP_->CP_raiz_)->nodoCP_anterior_;
        typename ColaPrior<T>::Nodo* ult_padre = (ultimo->nodoCP_padre_);
        typename ColaPrior<T>::Nodo* desordenado = itCP_siguiente_;

        // Intercambio el nodo que quiero eliminar con el último.
        // Luego de esto, el siguiente del iterador apunta al último
        // elemento del heap.
        swap(itCP_siguiente_, ultimo);

        // Reencadeno los nodos anterior y siguiente del que ahora
        // voy a eliminar,
        (itCP_siguiente_->nodoCP_anterior_)->nodoCP_siguiente_ = (itCP_siguiente_->nodoCP_siguiente_);
        (itCP_siguiente_->nodoCP_siguiente_)->nodoCP_anterior_ = (itCP_siguiente_->nodoCP_anterior_);

        // El padre del último va a perder un hijo. Veo cuál
        if ( ult_padre != NULL )
        {
            if ( ult_padre->nodoCP_hijoD_ == itCP_siguiente_ )
            {
                ult_padre->nodoCP_hijoD_ = NULL;
            }
            else
            {
                ult_padre->nodoCP_hijoI_ = NULL;
            }
        }

        // Hago que el siguiente del iterador apunte al elemento que 
        // rompe el invariante de minHeap
        itCP_siguiente_ = desordenado;

        // Restauro el invariante
        siftDown();

        // Con esto me aseguro de que el delete solo afecte al 
        // nodo que quiero eliminar
        ultimo->nodoCP_hijoD_ = NULL;
        ultimo->nodoCP_hijoI_ = NULL;

        delete ultimo;

    }

    // Actualizo el tamaño de la cola
    itCP_colaP_->CP_tamanio_ -= 1;
}


template <class T>
void ColaPrior<T>::ItColaPrior::siftDown()
{
    typename ColaPrior<T>::Nodo* der = itCP_siguiente_->nodoCP_hijoD_;
    typename ColaPrior<T>::Nodo* izq = itCP_siguiente_->nodoCP_hijoI_;
    typename ColaPrior<T>::Nodo* min;

    if ( izq != NULL && *(itCP_siguiente_->nodoCP_dato_) > *(izq->nodoCP_dato_) )
    {
        min = izq;
    }
    else
    {
        min = itCP_siguiente_;
    }

    if ( der != NULL && ( *(min->nodoCP_dato_) > *(der->nodoCP_dato_) ) )
    {
        min = der;
    }

    if ( min != itCP_siguiente_)
    {
        swap(itCP_siguiente_, min);
        siftDown();
    }
}


template <class T>
void ColaPrior<T>::ItColaPrior::siftUp()
{
    while ( itCP_siguiente_->nodoCP_padre_ != NULL && *(itCP_siguiente_->nodoCP_dato_) < *( (itCP_siguiente_->nodoCP_padre_)->nodoCP_dato_ ) )
    {
        swap(itCP_siguiente_, itCP_siguiente_->nodoCP_padre_);
    }
}


template <class T>
void ColaPrior<T>::ItColaPrior::swap(typename ColaPrior<T>::Nodo* un_nodo, typename ColaPrior<T>::Nodo* otro_nodo)
{
    if ( un_nodo != otro_nodo && un_nodo != NULL && otro_nodo != NULL )
    {
        // Intercambio los datos
        T* dato_aux = un_nodo->nodoCP_dato_;
        un_nodo->nodoCP_dato_ = otro_nodo->nodoCP_dato_;
        otro_nodo->nodoCP_dato_ = dato_aux;

        // Actualizo el siguiente del iterador
        if ( itCP_siguiente_ == otro_nodo )
        {
            itCP_siguiente_ = un_nodo;
        }
        else
        {
            itCP_siguiente_ = otro_nodo;
        }
    }

    // if ( un_nodo != otro_nodo && un_nodo != NULL && otro_nodo != NULL )
    // {
    //  typename ColaPrior<T>::Nodo* rz = itCP_colaP_->CP_raiz_;

    //  if ( rz == un_nodo )
    //  {
    //      itCP_colaP_->CP_raiz_ = otro_nodo;
    //  }

    //  if ( rz == otro_nodo )
    //  {
    //      itCP_colaP_->CP_raiz_ = un_nodo;
    //  }

    //  typename ColaPrior<T>::Nodo* un_nodo_parent = un_nodo->nodoCP_padre_;
    //  typename ColaPrior<T>::Nodo* un_nodo_rchild = un_nodo->nodoCP_hijoD_;
    //  typename ColaPrior<T>::Nodo* un_nodo_lchild = un_nodo->nodoCP_hijoI_;
    //  typename ColaPrior<T>::Nodo* un_nodo_prev = un_nodo->nodoCP_anterior_;
    //  typename ColaPrior<T>::Nodo* un_nodo_next = un_nodo->nodoCP_siguiente_;

    //  (un_nodo->nodoCP_anterior_)->nodoCP_siguiente_ = otro_nodo;
    //  (un_nodo->nodoCP_siguiente_)->nodoCP_anterior_ = otro_nodo;

    //  (otro_nodo->nodoCP_anterior_)->nodoCP_siguiente_ = un_nodo;
    //  (otro_nodo->nodoCP_siguiente_)->nodoCP_anterior_ = un_nodo;

    //  un_nodo->nodoCP_padre_ = otro_nodo->nodoCP_padre_;
    //  un_nodo->nodoCP_hijoD_ = otro_nodo->nodoCP_hijoD_;
    //  un_nodo->nodoCP_hijoI_ = otro_nodo->nodoCP_hijoI_;
    //  un_nodo->nodoCP_anterior_ = otro_nodo->nodoCP_anterior_;
    //  un_nodo->nodoCP_siguiente_ = otro_nodo->nodoCP_siguiente_;

    //  otro_nodo->nodoCP_padre_ = un_nodo_parent; 
    //  otro_nodo->nodoCP_hijoD_ = un_nodo_rchild;
    //  otro_nodo->nodoCP_hijoI_ = un_nodo_lchild;
    //  otro_nodo->nodoCP_anterior_ = un_nodo_prev;
    //  otro_nodo->nodoCP_siguiente_ = un_nodo_next;

    //  // if ( itCP_siguiente_ == otro_nodo )
    //  // {
    //  //  itCP_siguiente_ = un_nodo;
    //  // }
    //  // else
    //  // {
    //  //  itCP_siguiente_ = otro_nodo;
    //  // }
    // }

}


template <class T>
void ColaPrior<T>::ItColaPrior::agregarAlFinal(const T& elem)
{
    typename ColaPrior<T>::Nodo* sig = itCP_colaP_->CP_raiz_;
    typename ColaPrior<T>::Nodo* nuevo = new Nodo(elem);

    if ( sig == NULL )
    {
        nuevo->nodoCP_anterior_ = nuevo;
        nuevo->nodoCP_siguiente_ = nuevo;
        itCP_colaP_->CP_raiz_ = nuevo;
    }
    else
    {
        nuevo->nodoCP_anterior_ = sig->nodoCP_anterior_;
        nuevo->nodoCP_siguiente_ = sig;
        typename ColaPrior<T>::Nodo* padre_del_nuevo = (nuevo->nodoCP_anterior_)->nodoCP_padre_;

        if ( padre_del_nuevo == NULL )
        {
            (nuevo->nodoCP_anterior_)->nodoCP_hijoI_ = nuevo;
            nuevo->nodoCP_padre_ = itCP_colaP_->CP_raiz_;
        }
        else
        {
            if ( padre_del_nuevo->nodoCP_hijoI_ == NULL )
            {
                padre_del_nuevo->nodoCP_hijoI_ = nuevo;
            }
            else
            {
                if ( padre_del_nuevo->nodoCP_hijoD_== NULL )
                {
                    padre_del_nuevo->nodoCP_hijoD_ = nuevo;
                }
                else
                {
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
}


/***************************************
 * Implementación funciones auxiliares *
 ***************************************/

template <class T>
void ColaPrior<T>::ItColaPrior::avanzar()
{
    assert(haySiguiente());

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
}