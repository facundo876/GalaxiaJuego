#ifndef GALAXIA
#define GALAXIA
#include "LinkedList.h"


typedef struct{

    int x,y;

}NAVE;

typedef struct{

    int x,y;
    int borrar;

}eAsteroide;

typedef struct{

    int x,y;
    int borrar;

}eBala;

typedef struct{
    int primerPuesto;
    int segundoPuesto;
    int tercerPuesto;

}ePuntos;
//Galaxia
int galaxiaMain(ePuntos* pPuntos);

//esenario
void gotoXY(int x, int y);
void esconderCursor();
void pintar_Corazones(int corazones, int vidas, int puntos);
void pintar_Limites();
void pintar_Corazones(int corazones, int vidas, int puntos);

//asteroide
void generarAsteroides(LinkedList* listaAteroides);
void moverAstroides(LinkedList* this, eAsteroide* eAst);


//Nave
void pintar(int x, int y);
void choque(int naveX, int naveY, LinkedList* this, eAsteroide* aux, int* salud, int* vidas);

//balas
void choqueBalaAsteroide(LinkedList* listaBalas, LinkedList* listaAst, eBala* auxBala, eAsteroide* auxAst, int* puntos);
void moverBala(int* x, int* y, int borrar);
void borrar(int x, int y);
void generarBala(int* x, int* y, LinkedList* listaBalas);//genera nuevas cordenadas

//Menus
int menuSalida();
int menuPrincipal(ePuntos* pPuntos);
int gameOverMenu(int puntos);

//Puntos
void contarPuntos(int puntos, ePuntos* aux);
void subirPuntos(ePuntos* pPuntos);
void cagarPuntos(ePuntos* pPuntos);

#endif // GALAXIA
