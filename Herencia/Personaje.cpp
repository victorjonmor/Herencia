#include "Personaje.h"

Personaje::Personaje(std::string n, int v, int a, int x, int y)
    : nombre(n), vida(v), ataque(a), posicionX(x), posicionY(y) {}

int Personaje::getVida() const { return vida; }
int Personaje::getAtaque() const { return ataque; }
std::string Personaje::getNombre() const { return nombre; }
int Personaje::getPosicionX() const { return posicionX; }
int Personaje::getPosicionY() const { return posicionY; }

void Personaje::setVida(int v) { vida = v; }
void Personaje::setAtaque(int a) { ataque = a; }
void Personaje::setNombre(const std::string& n) { nombre = n; }
void Personaje::setPosicionX(int x) { posicionX = x; }
void Personaje::setPosicionY(int y) { posicionY = y; }

void Personaje::mover(int x, int y) {
    posicionX = x;
    posicionY = y;
}

bool Personaje::estaVivo() const {
    return vida > 0;
}
