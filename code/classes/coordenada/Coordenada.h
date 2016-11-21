#include "classes/aed2/aed2.h"
#include <cmath>
using namespace aed2;
using namespace std;

class Coordenada
{

  public:
    // Constructor y destructor
    Coordenada(const Nat x, const Nat y); //CrearCoordenda
    ~Coordenada();

    // Generadores

    // Observadores básicos
    const Nat Latitud() const;
    const Nat Longitud() const;

    // Otras operaciones
    static Nat distEuclidea(const Coordenada coord1, const Coordenada coord2) const; 
    Coordenada CoordenadaArriba() const;
    Coordenada CoordenadaAbajo() const;
    Coordenada CoordenadaALaDerecha() const;
    Coordenada CoordenadaALaIzquierda() const;

    // Operadores
    bool operator==(const Coordenada &otra) const;
    bool operator!=(const Coordenada &otra) const;

    // Asignacion
    //Coordenada &operator=(const Coordenada &aCopiar);

    /*friend ostream& operator<<(ostream& os) {
        return os;
    }*/

  private:
  
    Nat latitud;
    Nat longitud;

    // Funciones auxiliares


};
