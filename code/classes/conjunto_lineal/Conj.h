/*
 * Author: Fede
 * Maintainer: tfischer
 * 
 * Conjunto (lineal) imlementado sobre Diccionario (Dicc.h),
 * que está implementado sobre listas enlazadas (Lista.h).
 * 
 * Created on 30 de octubre de 2010
 */

#ifndef AED2_CONJ_H_INCLUDED
#define	AED2_CONJ_H_INCLUDED

#include <iostream>
#include "../diccionario_lineal/Dicc.h"
#include "../diccionario_lineal/Dicc.cpp"

namespace aed2
{

template<class T>
class Conj
{
  public:

    //forward declarations
    class Iterador;
    class const_Iterador;

    // Generadores

    Conj();
    Conj(const Conj<T>& otro);

    Iterador Agregar(const T& e);
    Iterador AgregarRapido(const T& e);

    void Eliminar(const T& e);

    // Observadores

    bool EsVacio() const;

    bool Pertenece(const T& e) const;

    Nat Cardinal() const;

    Iterador CrearIt();
    const_Iterador CrearIt() const;

    //esta funcion la agregamos aca, porque nos conviene acceder a
    //la representación.  Sino, no haria falta.
    bool operator == (const Conj<T>& otro) const;

    /************************************
    * Iterador de Conjunto, modificable *
    ************************************/
    class Iterador
    {
      public:

        Iterador();

        Iterador(const typename Conj<T>::Iterador& otra);

        Iterador& operator = (const typename Conj<T>::Iterador& otra);

        bool operator == (const typename Conj<T>::Iterador& otro) const;

        bool HaySiguiente() const;
        bool HayAnterior() const;

        const T& Siguiente() const;
        const T& Anterior() const;

        void Avanzar();
        void Retroceder();

        void EliminarAnterior();
        void EliminarSiguiente();

      private:
      
        typename Dicc<T,bool>::Iterador it_dicc_;

        Iterador(Conj<T>& c);

        Iterador(const typename Dicc<T,bool>::Iterador& itDict);

        friend class Conj<T>::const_Iterador;

        friend typename Conj<T>::Iterador Conj<T>::CrearIt();
        friend typename Conj<T>::Iterador Conj<T>::Agregar(const T&);
        friend typename Conj<T>::Iterador Conj<T>::AgregarRapido(const T&);
    };

    /*********************************************
    * const_Iterador de Conjunto, no modificable *
    *********************************************/
    class const_Iterador
    {
      public:

        const_Iterador();

        const_Iterador(const typename Conj<T>::Iterador& otra);

        const_Iterador(const typename Conj<T>::const_Iterador& otra);

        const_Iterador& operator = (const typename Conj<T>::const_Iterador& otra);

        bool operator==(const typename Conj<T>::const_Iterador& otro) const;

        bool HaySiguiente()const;
        bool HayAnterior()const;

        const T& Siguiente()const;
        const T& Anterior()const;

        void Avanzar();
        void Retroceder();

      private:

        typename Dicc<T,bool>::const_Iterador it_dicc_;

        const_Iterador(const Conj<T>& c);

        friend typename Conj<T>::const_Iterador Conj<T>::CrearIt() const;

    };

  private:

    Dicc<T,bool> dicc_;
};



}

#endif	//AED2_CONJ_H_INCLUDED
