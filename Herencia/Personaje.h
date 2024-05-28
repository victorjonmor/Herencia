#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <string>

class Personaje {
protected:
    int vida;
    int ataque;
    std::string nombre;
    int posicionX;
    int posicionY;

public:
    Personaje(std::string n, int v, int a, int x, int y);

    int getVida() const;
    int getAtaque() const;
    std::string getNombre() const;
    int getPosicionX() const;
    int getPosicionY() const;

    void setVida(int v);
    void setAtaque(int a);
    void setNombre(const std::string& n);
    void setPosicionX(int x);
    void setPosicionY(int y);

    void mover(int x, int y);
    bool estaVivo() const;
};

#endif
