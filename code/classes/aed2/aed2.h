#ifndef AED2_INCLUDED_H
#define AED2_INCLUDED_H

/** 
 * Comentando o descomentando la siguiente linea, se deshabilita 
 * o habilita el chequeo de precondiciones al llamar a las funciones 
 * de los modulos basicos. Si se habilita, dichas funciones 
 * ya no cumplirán con la complejiad algoritmica especificada 
 * en el apunte correspondiente.
 */
#define DEBUG

#include "aed2/TiposJuego.h"
#include "aed2/Arreglo.h"
#include "aed2/Lista.h"
#include "aed2/Vector.h"
#include "aed2/Dicc.h"
#include "aed2/Conj.h"
#include "aed2/ConjAcotado.h"
#include "../cola_de_prioridad/ColaPrior.h"
#include "../coordenada/Coordenada.h"
#include "../diccionario_string/DiccString.h"
#include "../Grilla/grilla.h"
#include "../mapa/Mapa.h"

using namespace aed2;

#endif //AED2_INCLUDED_H
