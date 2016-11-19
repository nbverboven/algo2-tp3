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
    bool ExisteCamino(const Coordenada c1, const Coordenada c2, const Conj<Coordenada> cs) const;

    // Operadores

    // Asignacion
    //Mapa &operator=(const Mapa &aCopiar);

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

};
