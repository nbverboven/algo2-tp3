/*
 * Author: ?
 *
 * Lista doblemente enlazada.
 * 
 */

#ifndef AED2_LISTA_H_
#define AED2_LISTA_H_

#include <ostream>
#include "../../TiposBasicos.h"

namespace aed2
{

template <typename T>
class Lista
{
  public:
  // forward declarations
  // Las estructuras estan definidas mas abajo
  class Iterador;
  class const_Iterador;

  /// Crea una lista enlazada vacía. (Operación Vacia())
  Lista();

  /// Crea por copia una lista enlazada (operación Copiar())
  Lista(const Lista& otra);

  /// Destruye la lista, incluyendo los T alojados
  ~Lista();

  /// Operacion de asignacion
  Lista<T>& operator=(const Lista<T>& otra);

  /// Opreaciones básicas
  bool EsVacia() const;
  Nat Longitud() const;

  /// Acceso al primero y último elemento (en O(1) )
  /// Versiones modificables y no modificables
  T& Primero();
  const T& Primero() const;

  T& Ultimo();
  const T& Ultimo() const;

  /// Operador "iésimo"
  T& operator[](Nat i);
  const T& operator[](Nat i) const;

  /// Elimina el primer elemento
  void Fin();
  /// Elimina el último elemento
  void Comienzo();

  /// Inserción de elementos
  Iterador AgregarAdelante(const T& elem);
  Iterador AgregarAtras(const T& elem);

  /// Creación del Iterador
  Iterador CrearIt();
  Iterador CrearItUlt();

  /// Creación del const_Iterador
  const_Iterador CrearIt() const;
  const_Iterador CrearItUlt() const;

  /**********************************
   * Iterador de Lista, modificable *
   **********************************/
  class Iterador
  {
    public:

      Iterador();

      Iterador(const typename Lista<T>::Iterador& otro);

      Iterador& operator = (const typename Lista<T>::Iterador& otro);

      bool HayAnterior() const;
      bool HaySiguiente() const;

      T& Anterior();
      T& Siguiente();
      const T& Anterior() const;
      const T& Siguiente() const;

      void Avanzar();
      void Retroceder();

      void AgregarComoAnterior(const T& elem);
      void AgregarComoSiguiente(const T& elem);

      void EliminarAnterior();
      void EliminarSiguiente();

      bool operator == (const typename Lista<T>::Iterador& otro) const;

  private:

      Lista<T>* lista_;

      typename Lista<T>::Nodo* nodo_siguiente_;

      /// El constructor es privado, necesitamos el friend.
      Iterador(Lista<T>* lista, typename Lista<T>::Nodo* proximo);

      friend typename Lista<T>::Iterador Lista<T>::CrearIt();
      friend typename Lista<T>::Iterador Lista<T>::CrearItUlt();
      friend class Lista<T>::const_Iterador;

      // devuelve el nodo siguiente en la lista circular
      typename Lista<T>::Nodo* SiguienteReal() const;
  };

  /*******************************************
   * const_Iterador de Lista, no modificable *
   *******************************************/
  class const_Iterador
  {
    public:

      const_Iterador();

      const_Iterador(const typename Lista<T>::const_Iterador& otro);

      const_Iterador(const typename Lista<T>::Iterador& otro);

      const_Iterador& operator = (const typename Lista<T>::const_Iterador& otro);

      bool HayAnterior() const;
      bool HaySiguiente() const;

      const T& Anterior() const;
      const T& Siguiente() const;

      void Avanzar();
      void Retroceder();

      bool operator == (const typename Lista<T>::const_Iterador& otro) const;

  private:

      const Lista<T>* lista_;

      const typename Lista<T>::Nodo* nodo_siguiente_;

      /// El constructor es privado, necesitamos el friend.
      const_Iterador(const Lista<T>* lista, const typename Lista<T>::Nodo* proximo);

      friend typename Lista<T>::const_Iterador Lista<T>::CrearIt() const;
      friend typename Lista<T>::const_Iterador Lista<T>::CrearItUlt() const;

      //devuelve el nodo siguiente en la lista circular
      const typename Lista<T>::Nodo* SiguienteReal() const;
  };

private:

  struct Nodo
  {
    Nodo(const T& d) : dato(d), anterior(NULL), siguiente(NULL) {};

    T dato;
    Nodo* anterior;
    Nodo* siguiente;
  };

  Nodo* primero_;
  Nat longitud_;
};



}

#endif // AED2_LISTA_H_INCLUDED
