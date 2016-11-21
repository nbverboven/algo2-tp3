#include "Coordenada.h"
using namespace aed2;

Coordenada::Coordenada(const Nat x, const Nat y) : latitud(x), longitud(y)
{}


Coordenada::~Coordenada()
{}


const Nat Coordenada::Latitud() const
{
    return this->latitud;
}


const Nat Coordenada::Longitud() const
{
    return this->longitud;
}


/** 
* Poniendo static, no necesito tener una instancia de una coordenada para llamar a la función.
* Ej de llamada: Coordenada::distEuclidea(c1,c2);
*/
static Nat Coordenada::distEuclidea(const Coordenada coord1, const Coordenada coord2) const
{
    Nat c1_lat = coord1.latitud;
    Nat c1_lon = coord1.longitud;
    Nat c2_lat = coord2.latitud;
    Nat c2_lon = coord2.longitud;
    
    return pow( (c1_lat >= c2_lat) ? (c1_lat - c2_lat) : (c2_lat - c1_lat), 2 ) +
           pow( (c1_lon >= c2_lon) ? (c1_lon - c2_lon) : (c2_lon - c1_lon), 2 );
    
    
    /*
    int aux = 0;
    
    if (coord1.latitud >= coord2.latitud) 
    {
        aux = (coord1.latitud-coord2.latitud)*(coord1.latitud-coord2.latitud);
    }
    else
    {
        aux = (coord2.latitud-coord1.latitud)*(coord2.latitud-coord1.latitud);
    }
    
    if (coord1.longitud>=coord2.longitud)
    {
         aux = aux +(coord1.longitud-coord2.longitud)*(coord1.longitud-coord2.longitud);
    }
    else
    {
        aux = aux +(coord2.longitud-coord1.longitud)*(coord2.longitud-coord1.longitud);
    }
    return aux;
    */
}


Coordenada Coordenada::CoordenadaArriba() const
{
    return Coordenada (this->latitud+1,this->longitud);
}


Coordenada Coordenada::CoordenadaAbajo() const
{
    return Coordenada (this->latitud-1,this->longitud);
}

Coordenada Coordenada::CoordenadaALaDerecha() const
{
    return Coordenada (this->latitud,this->longitud+1);
}

Coordenada Coordenada::CoordenadaALaIzquierda() const
{
    return Coordenada (this->latitud,this->longitud-1);
}

bool Coordenada::operator==(const Coordenada &otra) const
{
    return this->latitud==Latitud(otra) && this->longitud==Longitud(otra);
}

bool Coordenada::operator!=(const Coordenada &otra) const
{
    return !(this == otra);
}