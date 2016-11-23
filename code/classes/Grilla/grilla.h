#include "../../TiposJuego.h"
#include "../aed2/aed2/Vector.h"
#include <iostream>
#include <cassert>

using namespace aed2;
using namespace std;

template<class T>
    class Grilla {
        public:
            Grilla();
            Grilla(const Grilla<T>& otro);
            void AgregarColumnas(const Nat n,const T& elem);
	    void AgregarFilas(const Nat n,const T& elem);
            Nat CantFilas() const;
            Nat CantColumnas() const;
	    const T& operator() (Nat i, Nat j) const;

        private:
            Vector< Vector<T> > vector_;
            };


template<class T>
Grilla<T>::Grilla() {}

template<class T>
Grilla<T>::Grilla(const Grilla<T>& otro) : vector_(otro.vector_){}

template <class T>
Nat Grilla<T> :: CantColumnas () const{
    if (vector_.EsVacio()) {
        return 0;
	}
	else { 
        return this->vector_[0].Longitud();
	}

}
template <class T>
Nat Grilla<T> :: CantFilas () const{
    return this->vector_.Longitud();
}
template<class T>
void Grilla<T>::AgregarColumnas(const Nat n,const T& elem) {
	Nat i = 0 ;
    while ( i < this->CantFilas()){
		Nat j = 0 ;
		while (j<n) {
            this->vector_[i].AgregarAtras(elem);
			j++;
			}
		i++;
	}
}

template<class T>
void Grilla<T>::AgregarFilas(const Nat n,const T& elem) {
    Vector<T> nuevo;
    if (vector_.EsVacio()){
      nuevo.AgregarAtras(elem);
    }
    else{
        for (Nat p=0; p < this->CantColumnas(); p ++) nuevo.AgregarAtras(elem) ;}
    for (Nat j = 0; j < n ; j++) this->vector_.AgregarAtras(nuevo);
	}
template <class T>
const T& Grilla<T> :: operator() (Nat i, Nat j) const {
	assert (i < CantFilas());
	assert (j < CantColumnas());
    return vector_[i][j];
}
