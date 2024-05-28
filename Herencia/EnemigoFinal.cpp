#include "EnemigoFinal.h"
#include <cstdlib> 

EnemigoFinal::EnemigoFinal(std::string n, int v, int a, int x, int y, int sa1, int sa2)
    : Personaje(n, v, a, x, y), superAtaque1(sa1), superAtaque2(sa2) {}

int EnemigoFinal::getSuperAtaque1() const { return superAtaque1; }
int EnemigoFinal::getSuperAtaque2() const { return superAtaque2; }

int EnemigoFinal::usarSuperAtaque() {
    int choice = rand() % 2;
    return (choice == 0) ? superAtaque1 : superAtaque2;
}
