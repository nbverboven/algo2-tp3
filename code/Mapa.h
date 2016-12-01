#ifndef H_MAPA
#define H_MAPA

#include "aed2/aed2.h"
#include "Grilla.h"
#include "Coordenada.h"

using namespace aed2;
using namespace std;

class Mapa
{

  public:
    // Constructor y destructor
    Mapa(); //CrearMapa
    ~Mapa();

    // Generadores
    void AgregarCoordenada(Coordenada coord);

    // Observadores básicos
    Conj<Coordenada> Coordenadas() const;

    // Otras operaciones

    bool PosicionExistente(const Coordenada& c) const;
    bool HayCamino(const Coordenada& c1, const Coordenada& c2) const;
    bool ExisteCamino(const Coordenada& c1, const Coordenada& c2, const Conj<Coordenada>& cs) ;
    const Nat MaxLatitud () const;
    const Nat MaxLongitud () const;
    // Operadores

    // Asignacion
    Mapa& operator=(const Mapa& aCopiar);

    /*friend ostream& operator<<(ostream& os) {
        return os;
    }*/

  private:
    struct grillaStruct
    {
        Grilla<Nat> caminos;
        bool disponible;
    };

    Grilla<grillaStruct> grl;
    Conj<Coordenada> coordenadas;
    Nat maxLatitud;
    Nat maxLongitud;

    // Funciones auxiliares
    void RestaurarDisponibilidad() ;
    void GrillaHayCamino(const Coordenada& c);
    bool ExisteCaminoAux(const Coordenada& c1, const Coordenada& c2) ;
    bool ExisteCaminoPorArriba(const Coordenada& c1, const Coordenada& c2) ;
    bool ExisteCaminoPorAbajo(const Coordenada& c1, const Coordenada& c2) ;
    bool ExisteCaminoPorDerecha(const Coordenada& c1, const Coordenada& c2) ;
    bool ExisteCaminoPorIzquierda(const Coordenada& c1, const Coordenada& c2) ;
};





#endif /* H_MAPA */
