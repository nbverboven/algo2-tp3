#include "Coordenada.h"

Coordenada::Coordenada()
{

}

Coordenada::~Coordenada()
{

}

const Nat Coordenada::latitud() const
{
    return this->latitud;
}

const Nat Coordenada::longitud() const
{
    return this->longitud;
}

/** 
* Poniendo static, no necesito tener una instancia de una coordenada para llamar a la función.
* Ej de llamada: Coordenada::distEuclidea(c1,c2);
*/
static Nat Coordenada::distEuclidea(const Coordenada coord1, const Coordenada coord2) const
{

}

Coordenada Coordenada::CoordenadaArriba() const
{

}

Coordenada Coordenada::CoordenadaAbajo() const
{

}

Coordenada Coordenada::CoordenadaALaDerecha() const
{

}

Coordenada Coordenada::CoordenadaALaIzquierda() const
{
    
}

bool Coordenada::operator==(const Coordenada &c1, const Coordenada &c2) const
{
    return c1.latitud == c2.latitud and c1.longitud == c2.longitud;
}

bool Coordenada::operator!=(const Coordenada &c1, const Coordenada &c2) const
{
    return not(c1 == c2);
}