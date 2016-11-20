#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include "../conjunto_lineal/Conj.h"
#include <string>
#include <iostream>
#include <cassert>


namespace aed2
{
  template<typename T>
  class DiccString 
  {
  public:
      
    ~DiccString();

    DiccString();
    DiccString(const DiccString<T>&);

    void Definir(const String& clave, const T& significado);
    bool Definido(const String& clave) const;

    const T& Obtener(const String& clave) const;
    T& Obtener(const String& clave);

    void Borrar(const String& clave);
    const Conj<String>& Claves() const;

  private:

    struct Nodo
    {
      Nodo()
      {
        siguientes_ = new Nodo*[256];
        for (int i = 0; i < 256; i++)
        {
            siguientes_[i] = NULL;
        }
        definicion_ = NULL;
        padre_ = NULL;
      }

      ~Nodo()
      {
          delete definicion_;
          delete[] siguientes_;
      }

      T* definicion_;
      Nodo* padre_;
      Nodo** siguientes_;
    };

    Nodo* raiz_;
    Conj<String> claves_;

    
    int caminosPosibles(const Nodo* actual) const;
    void borrarSubString(const Nodo* desde, Nodo* hasta, const char& ultimo_char_borrado);
  };


} /* namespace aed2 */
    
#endif /* DICC_STRING_H_ */