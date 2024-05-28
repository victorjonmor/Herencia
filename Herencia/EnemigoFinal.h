#ifndef ENEMIGOFINAL_H
#define ENEMIGOFINAL_H

#include "Personaje.h"

class EnemigoFinal : public Personaje {
private:
    int superAtaque1;
    int superAtaque2;

public:
    EnemigoFinal(std::string n, int v, int a, int x, int y, int sa1, int sa2);

    int getSuperAtaque1() const;
    int getSuperAtaque2() const;

    int usarSuperAtaque();
};

#endif 
