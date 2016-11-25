#ifndef COLA_PRIOR_H_INCLUDED
#define COLA_PRIOR_H_INCLUDED

#include "../aed2/aed2/TiposBasicos.h"
#include <iostream>
#include <cassert>



namespace aed2
{
  /*
   * Implementación del módulo Cola de Prioridad(alpha). 
   * Se reemplaza alpha por T, del cual se asume que posee un 
   * constructor por copia, una función de igualdad y una relación de 
   * orden total <=.
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

    // Iterador (versión modificable y no modificable)
    ItColaPrior crearIt();


    /**********************************************
     * Iterador de Cola de Prioridad, modificable *
     **********************************************/
    class ItColaPrior
    {
    public:

      bool haySiguiente() const;
      const T& siguiente() const;
      void eliminarSiguiente();

      void avanzar();

    private:

      // Constructor que toma una cola de prioridad como parámetro
      ItColaPrior(typename ColaPrior<T>::Nodo* primero, ColaPrior<T>* cola);

      void siftUp();
      void siftDown();
      void swap(typename ColaPrior<T>::Nodo* nodo, typename ColaPrior<T>::Nodo* otro_nodo);
      void agregarAlFinal(const T& asd);

      friend void ColaPrior<T>::desencolar();
      friend typename ColaPrior<T>::ItColaPrior ColaPrior<T>::encolar(const T& elem);
      friend typename ColaPrior<T>::ItColaPrior ColaPrior<T>::crearIt();

      // Atributos de la clase
      typename ColaPrior<T>::Nodo* itCP_siguiente_;
      ColaPrior<T>* itCP_colaP_;
    };


  private:

    struct Nodo
    {
      Nodo(const T& elem)
        : nodoCP_dato_(new T(elem)), nodoCP_padre_(NULL), nodoCP_hijoD_(NULL), 
          nodoCP_hijoI_(NULL), nodoCP_siguiente_(NULL), nodoCP_anterior_(NULL)
      {}

      ~Nodo()
      {
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


} /* namespace aed2 */

#endif /* COLA_PRIOR_H_INCLUDED */