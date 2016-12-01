#ifndef COORDENADA_H
#define COORDENADA_H

#include "aed2/aed2.h"
using namespace aed2;
using namespace std;

class Coordenada
{
  public:
    
    // Constructor y destructor
    Coordenada(const Nat& x, const Nat& y); //CrearCoordenda
    ~Coordenada();

    // Observadores básicos
    Nat Latitud() const;
    Nat Longitud() const;

    // Otras operaciones
    Coordenada CoordenadaArriba() const;
    Coordenada CoordenadaAbajo() const;
    Coordenada CoordenadaALaDerecha() const;
    Coordenada CoordenadaALaIzquierda() const;
    
    static Nat distEuclidea(const Coordenada& coord1, const Coordenada& coord2); 

    // Operadores
    bool operator==(const Coordenada &otra) const;
    bool operator!=(const Coordenada &otra) const;

    // Asignacion
    Coordenada& operator=(const Coordenada& aCopiar);

    /*friend ostream& operator<<(ostream& os) {
        return os;
    }*/

  private:
  
    Nat latitud_;
    Nat longitud_;

    // Funciones auxiliares

};

#endif /* COORDENADA_H */
