/*
 * Diccionario implementado sobre dos listas enlazadas (Lista.h),
 * una de claves_ y una de significados_.
 * 
 * Created on 30 de octubre de 2010
 */

#ifndef AED2_DICC_H_
#define	AED2_DICC_H_

#include <ostream>
#include "../lista_enlazada/Lista.h"
#include "../lista_enlazada/Lista.cpp"

namespace aed2
{

template<class K,class S>
class Dicc
{
  public:

    //para iterar las tuplas vamos a usar los siguientes tipos
    struct Elem;
    struct const_Elem;

    class Iterador;
    class const_Iterador;

    Dicc();
    Dicc(const Dicc<K,S>& otro);
    Dicc<K,S>& operator=(const Dicc<K,S>& otro);

    Iterador Definir(const K& clave, const S& significado);
    Iterador DefinirRapido(const K& clave, const S& significado);

    bool Definido(const K& clave) const;
    const S& Significado(const K& clave) const;
    S& Significado(const K& clave);
    void Borrar(const K& clave);
    Nat CantClaves() const;
    Iterador CrearIt();
    const_Iterador CrearIt() const;

    //Estas funciones son utiles para saber si algo esta definido
    //y ver cual es su signficado, sin recorrer dos veces.
    Iterador Buscar(const K&);
    const_Iterador Buscar(const K&) const;

    class Iterador
    {
      public:

        Iterador();

        Iterador(const typename Dicc<K, S>::Iterador& otro);

        Iterador& operator = (const typename Dicc<K, S>::Iterador& otro);

        bool operator == (const typename Dicc<K,S>::Iterador&) const;

        bool HaySiguiente() const;
        bool HayAnterior() const;
        const K& SiguienteClave() const;
        S& SiguienteSignificado();
        const K& AnteriorClave() const;
        S& AnteriorSignificado();
        Elem Siguiente();
        Elem Anterior();
        void Avanzar();
        void Retroceder();
        void EliminarSiguiente();
        void EliminarAnterior();

      private:

        typename Lista<K>::Iterador it_claves_;
        typename Lista<S>::Iterador it_significados_;

        Iterador(Dicc<K,S>* d);

        friend typename Dicc<K,S>::Iterador Dicc<K,S>::CrearIt();
        friend class Dicc<K, S>::const_Iterador;
    };

    class const_Iterador
    {
      public:

        const_Iterador();

        const_Iterador(const typename Dicc<K,S>::Iterador& otro);

        const_Iterador(const typename Dicc<K, S>::const_Iterador& otro);

        const_Iterador& operator = (const typename Dicc<K, S>::const_Iterador& otro);

        bool operator==(const typename Dicc<K,S>::const_Iterador&) const;

        bool HaySiguiente() const;
        bool HayAnterior() const;
        const K& SiguienteClave() const;
        const S& SiguienteSignificado() const;
        const K& AnteriorClave() const;
        const S& AnteriorSignificado() const;
        const_Elem Siguiente() const;
        const_Elem Anterior() const;
        void Avanzar();
        void Retroceder();

    private:

        typename Lista<K>::const_Iterador it_claves_;
        typename Lista<S>::const_Iterador it_significados_;

        const_Iterador(const Dicc<K,S>* d);

        friend typename Dicc<K,S>::const_Iterador Dicc<K,S>::CrearIt() const;
    };

    struct Elem
    {
      public:

        const K& clave;
        S& significado;

        Elem(const K& c, S& s) : clave(c), significado(s) {}
        //Para sacar esto de aca, necesitariamos definir rasgos y otras yerbas
        //Lamentablemente, sino C++ no reconoce bien los tipos

        friend std::ostream& operator<<(std::ostream& os, const Dicc<K,S>::Elem& e) {
          return os << e.clave << ":" << e.significado;
        }

      private:

        typename Dicc<K,S>::Elem& operator=(const Dicc<K,S>::Elem&);
    };

    struct const_Elem
    {
      public:

        const K& clave;
        const S& significado;

        const_Elem(const K& c, const S& s) : clave(c), significado(s) {}

        //Para sacar esto de aca, necesitariamos definir rasgos y otras yerbas
        //Lamentablemente, sino C++ no reconoce bien los tipos
        friend std::ostream& operator << (std::ostream& os, const Dicc<K,S>::const_Elem& e) {
          return os << e.clave << ":" << e.significado;
        }

      private:

        typename Dicc<K,S>::const_Elem& operator = (const Dicc<K,S>::const_Elem&);
    };

  private:

    Lista<K> claves_;
    Lista<S> significados_;

};


}

#endif	//AED2_DICC_H_
