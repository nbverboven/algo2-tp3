#include "../aed2/aed2.h"
#include "../Grilla/grilla.h"
#include "../coordenada/Coordenada.h"

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
    const Conj<Coordenada> Coordenadas() const;

    // Otras operaciones

    bool PosicionExistente(const Coordenada c) const;
    bool HayCamino(const Coordenada c1, const Coordenada c2) const;
    bool ExisteCamino(const Coordenada c1, const Coordenada c2, const Conj<Coordenada> cs) ;
    const Nat MaxLatitud () const;
    const Nat MaxLongitud () const;
    // Operadores

    // Asignacion
    Mapa &operator=(const Mapa &aCopiar);

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
    void GrillaHayCamino(const Coordenada c);
    bool ExisteCaminoAux(const Coordenada c1, const Coordenada c2) ;
    bool ExisteCaminoPorArriba(const Coordenada c1, const Coordenada c2) ;
    bool ExisteCaminoPorAbajo(const Coordenada c1, const Coordenada c2) ;
    bool ExisteCaminoPorDerecha(const Coordenada c1, const Coordenada c2) ;
    bool ExisteCaminoPorIzquierda(const Coordenada c1, const Coordenada c2) ;
};


Mapa::Mapa(): maxLongitud(0), maxLatitud(0){}

Mapa::~Mapa()
{}

Mapa& Mapa:: operator=(const Mapa &aCopiar){
   Conj<Coordenada>::const_Iterador it = aCopiar.coordenadas.CrearIt();
   while (it.HaySiguiente()){
       this->AgregarCoordenada(it.Siguiente());
       it.Avanzar();
   }
   return *this;
}

const Nat Mapa::MaxLatitud () const{
    return maxLatitud;
}
const Nat Mapa::MaxLongitud () const{
    return maxLongitud;
}

const Conj<Coordenada> Mapa::Coordenadas() const
{
    return coordenadas;
}

void Mapa::AgregarCoordenada(Coordenada coord){
    if (coord.Latitud() >= grl.CantFilas()){
        grillaStruct tupla;
        tupla.disponible=false;
        grl.AgregarFilas(coord.Latitud()+1-grl.CantFilas(),tupla);
        maxLatitud = coord.Latitud();
    }
    if (coord.Longitud() >=grl.CantColumnas()){
        grillaStruct tupla;
        tupla.disponible=false;
        Grilla<Nat> grilla;
        tupla.caminos = grilla;
        grl.AgregarColumnas(coord.Longitud()+1-grl.CantColumnas(),tupla);
        maxLongitud = coord.Longitud();
    }
    if (grl(coord.Latitud(),coord.Longitud()).caminos.EsVacio()){
        coordenadas.AgregarRapido(coord);
        grl(coord.Latitud(),coord.Longitud()).disponible=true;
        Conj<Coordenada>::const_Iterador it = coordenadas.CrearIt();
        while (it.HaySiguiente()){
            Mapa::GrillaHayCamino(Coordenada(it.Siguiente().Latitud(),it.Siguiente().Longitud()));
            it.Avanzar();
            }
        }

}


bool Mapa::PosicionExistente(const Coordenada c) const
{
    return c.Latitud()<grl.CantFilas() && c.Longitud() < grl.CantColumnas() &&   !(grl(c.Latitud(),c.Longitud()).caminos.EsVacio());
}

bool Mapa::HayCamino(const Coordenada c1, const Coordenada c2) const
{
    return grl(c1.Latitud(),c1.Longitud()).caminos(c2.Latitud(),c2.Longitud())==1;
}


void Mapa::RestaurarDisponibilidad(){
    Conj<Coordenada>::const_Iterador it = coordenadas.CrearIt();
    while (it.HaySiguiente()){
        grl(it.Siguiente().Latitud(),it.Siguiente().Longitud()).disponible = true;
        it.Avanzar();
    }
}

void Mapa:: GrillaHayCamino(const Coordenada c){
    Conj<Coordenada>::const_Iterador it = coordenadas.CrearIt();
    while (it.HaySiguiente()){
        Nat difFilas= grl.CantFilas()- grl(it.Siguiente().Latitud(),it.Siguiente().Longitud()).caminos.CantFilas();
        grl(it.Siguiente().Latitud(),it.Siguiente().Longitud()).caminos.AgregarFilas(difFilas,0);
        Nat difColumnas = grl.CantColumnas()- grl(it.Siguiente().Latitud(),it.Siguiente().Longitud()).caminos.CantColumnas();
        grl(it.Siguiente().Latitud(),it.Siguiente().Longitud()).caminos.AgregarColumnas(difColumnas,0);
        if(grl(c.Latitud(),c.Longitud()).caminos(it.Siguiente().Latitud(),it.Siguiente().Longitud())==0){
            if(ExisteCamino(c,it.Siguiente(),coordenadas)){
                grl(c.Latitud(),c.Longitud()).caminos(it.Siguiente().Latitud(),it.Siguiente().Longitud())=1;
                }
            }
        it.Avanzar();
    }
}

bool Mapa::ExisteCamino(const Coordenada c1, const Coordenada c2, const Conj<Coordenada> cs){
    bool retval = ExisteCaminoAux(c1,c2);
    RestaurarDisponibilidad();
    return retval;
}

bool Mapa::ExisteCaminoAux(const Coordenada c1, const Coordenada c2){
    grl(c1.Latitud(),c1.Longitud()).disponible=false;
    if (c1==c2){
        return true;
    }
    else    {
        return ExisteCaminoPorArriba(c1,c2) || ExisteCaminoPorAbajo(c1,c2) || ExisteCaminoPorDerecha(c1,c2) || ExisteCaminoPorIzquierda(c1,c2);
    }
}

bool Mapa ::ExisteCaminoPorArriba(const Coordenada c1, const Coordenada c2)  {
    if (c1.CoordenadaArriba().Latitud()<grl.CantFilas() && grl(c1.CoordenadaArriba().Latitud(),c1.Longitud()).disponible){
        return ExisteCaminoAux(c1.CoordenadaArriba(),c2);
        }
    else    {
        return false;
        }
}


bool Mapa ::ExisteCaminoPorAbajo(const Coordenada c1, const Coordenada c2)  {
    if (c1.Latitud()>0 && grl(c1.CoordenadaAbajo().Latitud(),c1.Longitud()).disponible){
        return ExisteCaminoAux(c1.CoordenadaAbajo(),c2);
        }
    else    {
        return false;
        }
}

bool Mapa ::ExisteCaminoPorDerecha(const Coordenada c1, const Coordenada c2)  {
    if (c1.CoordenadaALaDerecha().Longitud()<grl.CantColumnas() && grl(c1.Latitud(),c1.CoordenadaALaDerecha().Longitud()).disponible){
        return ExisteCaminoAux(c1.CoordenadaALaDerecha(),c2);
        }
    else {

        return false;
    }
 }

bool Mapa ::ExisteCaminoPorIzquierda(const Coordenada c1, const Coordenada c2) {
    if (c1.Longitud()>0 && grl(c1.Latitud(),c1.CoordenadaALaIzquierda().Longitud()).disponible){

        return ExisteCaminoAux(c1.CoordenadaALaIzquierda(),c2);
        }
    else {

        return false;
    }
}

