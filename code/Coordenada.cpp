#include "Coordenada.h"
using namespace aed2;

Coordenada::Coordenada(const Nat& x, const Nat& y) 
: latitud_(x), longitud_(y)
{}


Coordenada::~Coordenada()
{}


Nat Coordenada::Latitud() const
{
    return this->latitud_;
}


Nat Coordenada::Longitud() const
{
    return this->longitud_;
}


/** 
* Poniendo static, no necesito tener una instancia de una coordenada para llamar a la función.
* Ej de llamada: Coordenada::distEuclidea(c1,c2);
*/
Nat Coordenada::distEuclidea(const Coordenada& coord1, const Coordenada& coord2)// const
{      
    int aux = 0;
    
    if (coord1.latitud_ >= coord2.latitud_) 
    {
        aux = (coord1.latitud_-coord2.latitud_)*(coord1.latitud_-coord2.latitud_);
    }
    else
    {
        aux = (coord2.latitud_-coord1.latitud_)*(coord2.latitud_-coord1.latitud_);
    }
    
    if (coord1.longitud_ >= coord2.longitud_)
    {
         aux = aux + (coord1.longitud_-coord2.longitud_)*(coord1.longitud_-coord2.longitud_);
    }
    else
    {
        aux = aux + (coord2.longitud_-coord1.longitud_)*(coord2.longitud_-coord1.longitud_);
    }

    return aux;
}


Coordenada Coordenada::CoordenadaArriba() const
{
    return Coordenada (this->latitud_+1, this->longitud_);
}


Coordenada Coordenada::CoordenadaAbajo() const
{
    return Coordenada (this->latitud_-1, this->longitud_);
}

Coordenada Coordenada::CoordenadaALaDerecha() const
{
    return Coordenada (this->latitud_, this->longitud_+1);
}


Coordenada Coordenada::CoordenadaALaIzquierda() const
{
    return Coordenada (this->latitud_, this->longitud_-1);
}


bool Coordenada::operator==(const Coordenada& otra) const
{
    return this->latitud_ == otra.latitud_ && this->longitud_ == otra.longitud_;
}


bool Coordenada::operator!=(const Coordenada& otra) const
{
    return !(*this == otra);
}


Coordenada& Coordenada::operator=(const Coordenada& aCopiar)
{
    this->latitud_ = aCopiar.latitud_;
    this->longitud_ = aCopiar.longitud_;

    return *this;
}


std::ostream& operator<<(std::ostream& os, const Coordenada& c)
{
    os << '(' << c.Latitud() << ',' << c.Longitud() << ')';

    return os;
}