#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Personaje.h"
#include "EnemigoFinal.h"

const int FILAS = 10;
const int COLUMNAS = 10;

void inicializarNivel(std::vector<std::vector<char>>& nivel);
void mostrarNivel(const std::vector<std::vector<char>>& nivel);
void colocarEnemigos(std::vector<std::vector<char>>& nivel, int cantidad);
void colocarGuarida(std::vector<std::vector<char>>& nivel);
void moverHeroe(Personaje& heroe, std::vector<std::vector<char>>& nivel, bool& juegoTerminado);
bool batalla(Personaje& heroe, Personaje& enemigo);
bool batallaFinal(Personaje& heroe, EnemigoFinal& enemigoFinal);

int main() {

    std::vector<std::vector<char>> nivel(FILAS, std::vector<char>(COLUMNAS, ' '));
    inicializarNivel(nivel);

    Personaje heroe("Heroe", 150, 20, 0, 0);
    nivel[heroe.getPosicionX()][heroe.getPosicionY()] = 'H';

    colocarEnemigos(nivel, 5);
    colocarGuarida(nivel);

    bool juegoTerminado = false;
    while (!juegoTerminado) {
        mostrarNivel(nivel);
        moverHeroe(heroe, nivel, juegoTerminado);

        if (nivel[heroe.getPosicionX()][heroe.getPosicionY()] == 'G') {
            std::cout << "Has encontrado la guarida! Para salir necesitar enfrentarte al BOSS FINAL" << std::endl;
            EnemigoFinal enemigoFinal("Enemigo Final", 150, 30, heroe.getPosicionX(), heroe.getPosicionY(), 50, 70);
            if (batallaFinal(heroe, enemigoFinal)) {
                std::cout << "Has ganado al BOSS FINAL" << std::endl;
                std::cout << "Felicidades, has logrado escapar!" << std::endl;
            }
            else {
                std::cout << "Has sido derrotado por el BOSS FINAL." << std::endl;
            }
            juegoTerminado = true;
        }
    }

    return 0;
}

void inicializarNivel(std::vector<std::vector<char>>& nivel) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            nivel[i][j] = ' ';
        }
    }
}

void mostrarNivel(const std::vector<std::vector<char>>& nivel) {
    std::cout << "  ";
    for (int j = 0; j < COLUMNAS; ++j) {
        std::cout << j << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < FILAS; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < COLUMNAS; ++j) {
            std::cout << nivel[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void colocarEnemigos(std::vector<std::vector<char>>& nivel, int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        int x = rand() % FILAS;
        int y = rand() % COLUMNAS;
        if (nivel[x][y] == ' ') {
            nivel[x][y] = 'E';
        }
        else {
            --i; 
        }
    }
}

void colocarGuarida(std::vector<std::vector<char>>& nivel) {
    int y = rand() % COLUMNAS;
    nivel[FILAS - 1][y] = 'G';
}

void moverHeroe(Personaje& heroe, std::vector<std::vector<char>>& nivel, bool& juegoTerminado) {
    char movimiento;
    std::cout << "Para mover al Heroe usa: (WASD): ";
    std::cin >> movimiento;

    int nuevaX = heroe.getPosicionX();
    int nuevaY = heroe.getPosicionY();

    switch (movimiento) {
    case 'W': 
        if (nuevaX > 0) --nuevaX;
        break;
    case 'S': 
        if (nuevaX < FILAS - 1) ++nuevaX;
        break;
    case 'A': 
        if (nuevaY > 0) --nuevaY;
        break;
    case 'D': 
        if (nuevaY < COLUMNAS - 1) ++nuevaY;
        break;
    default:
        std::cout << "Movimiento no encontrado" << std::endl;
        return;
    }

    if (nivel[nuevaX][nuevaY] == 'G') {
        std::cout << "Has encontrado la guarida! Para salir necesitar enfrentarte al BOSS FINAL" << std::endl;
        juegoTerminado = true;

        EnemigoFinal enemigoFinal("Enemigo Final", 125, 30, heroe.getPosicionX(), heroe.getPosicionY(), 5, 30);
        if (batallaFinal(heroe, enemigoFinal)) {
            std::cout << "Has ganado al BOSS FINAL!" << std::endl;
            std::cout << "Felicidades, has logrado escapar!" << std::endl;

        }
        else {
            std::cout << "Has sido derrotado por el BOSS FINAL." << std::endl;
        }

        return; 
    }

    if (nivel[nuevaX][nuevaY] != 'E') {
        nivel[heroe.getPosicionX()][heroe.getPosicionY()] = ' ';
        nivel[nuevaX][nuevaY] = 'H';
        heroe.mover(nuevaX, nuevaY);
    }
    else {
        Personaje enemigo("Enemigo", 50, 10, nuevaX, nuevaY);
        if (batalla(heroe, enemigo)) {
            std::cout << "Has derrotado al enemigo." << std::endl;
            nivel[nuevaX][nuevaY] = ' '; 
            nivel[heroe.getPosicionX()][heroe.getPosicionY()] = 'H';
        }
        else {
            std::cout << "Has sido derrotado por el enemigo." << std::endl;
            juegoTerminado = true;
        }
    }
}

bool batalla(Personaje& heroe, Personaje& enemigo) {
    while (heroe.estaVivo() && enemigo.estaVivo()) {
        int danioHeroe = rand() % 11 + 15;  
        enemigo.setVida(enemigo.getVida() - danioHeroe);
        std::cout << "Has quitado " << danioHeroe << " de vida. Vida del enemigo: " << enemigo.getVida() << std::endl;

        if (!enemigo.estaVivo()) {
            return true;
        }

        int danioEnemigo = rand() % 15 + 1;  
        heroe.setVida(heroe.getVida() - danioEnemigo);
        std::cout << "El enemigo te ha quitado " << danioEnemigo << " de vida. Tu vida: " << heroe.getVida() << std::endl;
    }

    return false;
}

bool batallaFinal(Personaje& heroe, EnemigoFinal& enemigoFinal) {
    while (heroe.estaVivo() && enemigoFinal.estaVivo()) {
        int danioHeroe = heroe.getAtaque();
        enemigoFinal.setVida(enemigoFinal.getVida() - danioHeroe);
        std::cout << " Has quitado " << danioHeroe << " de vida. Vida del BOSS FINAL: " << enemigoFinal.getVida() << std::endl;

        if (!enemigoFinal.estaVivo()) {
            return true;
        }

        int danioEnemigo = enemigoFinal.usarSuperAtaque();
        heroe.setVida(heroe.getVida() - danioEnemigo);
        std::cout << "El BOSS FINAL te ha quitado " << danioEnemigo << " de vida. Tu vida: " << heroe.getVida() << std::endl;

        if (!heroe.estaVivo()) {
            return false;
        }
    }

    return false;
}

