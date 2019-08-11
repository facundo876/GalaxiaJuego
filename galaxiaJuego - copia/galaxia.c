#include "galaxia.h"
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include "LinkedList.h"
#include<stdbool.h>// Booleanos
#include <conio.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ENTER 13

#define VIDAS 1


void hasAlgo(NAVE* const miInstancia){

    miInstancia->x =5;
}

void gotoXY(int x, int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hcon, dwPos);
}

void esconderCursor()
{

    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;

    SetConsoleCursorInfo(hcon, &cci);

}

void pintar(int x, int y){

    gotoXY(x, y);
    printf("  %c", 30);
    gotoXY(x, y+1);
    printf(" %c%c%c", 40,207,41);
    gotoXY(x, y+2);
    printf("%c%c %c%c", 30,190,190,30);
}

void borrar(int x, int y){

    gotoXY(x, y);
    printf("       ");
    gotoXY(x, y+1);
    printf("       ");
    gotoXY(x, y+2);
    printf("       ");
}

void pintar_Limites(){

    for(int i=2; i<78; i++){
        gotoXY(i, 3);
        printf("%c", 205);
        gotoXY(i, 33);
        printf("%c", 205);
    }
    for(int i=4; i<33; i++){
        gotoXY(2,i);
        printf("%c", 186);
        gotoXY(77,i);
        printf("%c", 186);
    }
    gotoXY(2,3); printf("%c", 201);
    gotoXY(2,33); printf("%c", 200);
    gotoXY(77,3); printf("%c", 187);
    gotoXY(77,33); printf("%c", 188);
}

void pintar_Corazones(int corazones, int vidas, int puntos){

    gotoXY(50,2); printf("VIDAS %d", vidas);
    gotoXY(5,2); printf("PUNTOS %d", puntos);
    gotoXY(64,2); printf("Salud");
    gotoXY(70,2); printf("      ");

    for(int i=0; i<corazones; i++){

        gotoXY(70+i,2); printf("%c",3);
    }

}

void animacionMorir(int x, int y){

      borrar(x-2,y);
      gotoXY(x-2,y);   printf("    **    ");
      gotoXY(x-2,y+1); printf("  ******  ");
      gotoXY(x-2,y+2); printf("    **    ");
      Sleep(200);

      borrar(x-2,y);
      gotoXY(x-2,y);   printf("  * **  * ");
      gotoXY(x-2,y+1); printf("  ******  ");
      gotoXY(x-2,y+2); printf("  * **  * ");
      Sleep(200);
        borrar(x,y);
    pintar_Limites();
    pintar(x, y);
}
//asteriode


void pintarAsteroide(int x, int y){

    gotoXY(x,y); printf("%c", 184);
}

void moverAstroide(int* x, int* y){

    gotoXY(*x, *y); printf("  ");
    *y= *y+1;

        if(*y > 32){
            generaAsteroide(x, y);
        }

    pintarAsteroide(*x, *y);
}

void generaAsteroide(int* x, int* y){

    *x = rand()%71 + 4;
    *y=4;
}

void choque(int naveX, int naveY, LinkedList* this, eAsteroide* aux, int* salud, int* vidas){

    //if(naveX >= asteroideX && naveX < asteroideX+6 && naveY >= asteroideY && naveY < asteroideY+2){

    for(int i=0; i<ll_len(this); i++){
            aux = ll_get(this, i);

        if(aux->x >= naveX && aux->x < naveX+5 && aux->y >= naveY && aux->y < naveY+2){

        animacionMorir(naveX, naveY);
        *salud = *salud-1;
        aux->y =32;

        if(*salud == 0){
            *vidas = *vidas-1;
            *salud = 3;
        }

    }
    }

}

void generarBala(int* x, int* y, LinkedList* listaBalas){

    eBala* bala = (eBala*)malloc(sizeof(eBala));

        bala->x = *x+2;
        bala->y = *y-1;
        bala->borrar = 0;

        ll_push(listaBalas, 0, bala);//ague una bala y la colaca primera en la lista

}

void moverBala(int* x, int* y, int borrar){

        gotoXY(*x, *y); printf(" ");

        *y = *y-1;
        if(borrar != 1){
           gotoXY(*x, *y); printf("*");
        }



}

void generarAsteroides(LinkedList* listaAteroides){

    for(int i=0; i<5; i++){

        eAsteroide* auxA = (eAsteroide*)malloc(sizeof(eAsteroide));
        auxA->x = rand()%75+3;
        auxA->y = rand()%5+4;

        ll_add(listaAteroides, auxA);
    }


}

void moverAstroides(LinkedList* this, eAsteroide* eAst){


    for(int i=0; i<ll_len(this); i++){

        eAst=ll_get(this, i);

        moverAstroide(&eAst->x, &eAst->y);


    }


}

void choqueBalaAsteroide(LinkedList* listaBalas, LinkedList* listaAst, eBala* auxBala, eAsteroide* auxAst, int* puntos){

    for(int i=0; i<ll_len(listaAst); i++){

         auxAst = ll_get(listaAst, i);

        for(int j=0; j<ll_len(listaBalas); j++){
           auxBala = ll_get(listaBalas, j);

            if((auxAst->x == auxBala->x || auxAst->x+1 == auxBala->x || auxAst->x-1 == auxBala->x  ) && (auxAst->y+1 == auxBala->y || auxAst->y == auxBala->y )){

                    gotoXY(auxAst->x, auxAst->y); printf(" ");
                    gotoXY(auxBala->x, auxBala->y); printf(" ");

                    auxBala->borrar =1;//no se vuelve a dibujar
                    auxAst->y = 32;

                    *puntos = *puntos+5;


          }


        }
    }


}

int menuPrincipal(ePuntos* pPuntos){

    char tecla;
    int ok = 0;
    int posicion=0;
    system("cls");
    gotoXY(30, 10);printf("  %c   NUEVO JUEGO", 223);
    gotoXY(30, 13);printf("     OPCIONES");
    gotoXY(30, 16);printf("     SALIR");

    gotoXY(30, 19);printf(" ___________________");
    gotoXY(30, 22);printf(" MEJORES PUNTUACIONES");
    gotoXY(32, 24);printf(" 1%c PRIMER: %d",248, pPuntos->primerPuesto);
    gotoXY(32, 26);printf(" 2%c PRIMER: %d",248, pPuntos->segundoPuesto);
    gotoXY(32, 28);printf(" 3%c PRIMER: %d",248, pPuntos->tercerPuesto);


    do{
        if(kbhit()){
            tecla = getch();

            if(tecla == ARRIBA && posicion != 0){

                if(posicion == 1){
                    gotoXY(30, 10);printf("  %c   NUEVO JUEGO", 223);
                    gotoXY(30, 13);printf("     OPCIONES ");

                    posicion--;
                }
                if(posicion == 2){
                    gotoXY(30, 13);printf("  %c   OPCIONES", 223);
                    gotoXY(30, 16);printf("     SALIR ");

                    posicion--;
                }

            }
            if(tecla == ABAJO){


                if(posicion == 1){
                    gotoXY(30, 13);printf("     OPCIONES ");
                    gotoXY(30, 16);printf("  %c   SALIR", 223);

                    posicion++;
                }
                if(posicion == 0){
                    gotoXY(30, 10);printf("     NUEVO JUEGO ");
                    gotoXY(30, 13);printf("  %c   OPCIONES", 223);

                    posicion++;
                }
            }
            if(tecla == ENTER){
                ok =1;
            }


        }

    }while(ok == 0);

    return posicion;
}

int menuSalida(){

    char tecla;
    int posicion;
    int ok = 0;
    gotoXY(32, 11);printf("DESEA SALIR?");
    gotoXY(33, 13);printf("SI   %c NO", 223);

    do{
        if(kbhit()){
            tecla = getch();

            if(tecla == DERECHA){

               gotoXY(33, 13);printf("SI   %c NO ", 223);
               posicion = 0;

            }
            if(tecla == IZQUIERDA){

                gotoXY(33, 13);printf("%c SI    NO", 223);
                posicion = 1;
            }
            if(tecla == ENTER){
                ok =1;
            }

        }

    }while(ok == 0);

    return posicion;
}

int galaxiaMain(ePuntos* pPuntos){


    int x = 10, y = 10;
    int* salud; salud = 3;
    int* vidas; vidas = VIDAS;
    int* puntos; puntos =0;
    int* asteroideX;
    int* asteroideY;
    char tecla;

    int gameOver = 0;

    LinkedList* balas = ll_newLinkedList();//crea balas
    eBala* aux;

    LinkedList* asteroides = ll_newLinkedList();// crea asteroides
    eAsteroide* auxA;

    gotoXY(x, y);

    generarAsteroides(asteroides);
    esconderCursor();
    pintar_Limites();
    pintar_Corazones(salud, vidas, puntos);
    pintar(x,y);

    while(gameOver == 0){

        moverAstroides(asteroides, auxA);
        choque(x, y, asteroides, auxA, &salud, &vidas);//choque asteroide
        pintar_Corazones(salud, vidas, puntos);//corazones
        choqueBalaAsteroide(balas, asteroides, aux, auxA, &puntos);

        if(!ll_isEmpty(balas)){//animacion balas

            for(int i =0; i< ll_len(balas); i++){

                aux = ll_get(balas, i);
                if(aux->y > 4 ){

                  moverBala(&aux->x, &aux->y, aux->borrar);
                }
                else{
                    gotoXY(aux->x, aux->y); printf(" ");
                    free(ll_pop(balas, i));

                }

            }

        }


        if(kbhit()){
            tecla = getch();
            borrar(x,y);
            if(tecla == IZQUIERDA && x-2 > 3){
                x--;
                x--;
            }

            if(tecla == DERECHA && x+6 < 76){
                x++;
                x++;
            }
            if(tecla == ARRIBA && y > 4){
                y--;
                y--;
            }
            if(tecla == ABAJO && y+3 < 32){
                y++;
                y++;
            }

            if(tecla == 'a'){

                generarBala(&x, &y, balas);
            }

            pintar(x,y);
        }
        if(vidas == 0){

            gameOver= 1;
        }

        Sleep(30);
    }

    contarPuntos(puntos,pPuntos);

    free(balas);
    free(asteroides);

    return gameOverMenu(puntos);
}

int gameOverMenu(int puntos){

    char tecla;
    int posicion;
    int ok = 0;

     system("cls");
    gotoXY(35, 12); printf("GAME OVER");
    gotoXY(35, 13); printf("PUNTOS: %d", puntos);

    gotoXY(35, 17);printf("CONTINUAR?");
    gotoXY(35, 18);printf("SI   %c NO", 223);

    do{
        if(kbhit()){
            tecla = getch();

            if(tecla == DERECHA){

               gotoXY(35, 18);printf("SI   %c NO ", 223);
               posicion = 0;

            }
            if(tecla == IZQUIERDA){

                gotoXY(35, 18);printf("%c SI    NO", 223);
                posicion = 1;
            }
            if(tecla == ENTER){
                ok =1;
            }

        }

    }while(ok == 0);

    return posicion;

}

void contarPuntos(int puntos, ePuntos* aux){

    if(puntos > aux->primerPuesto){
        aux->tercerPuesto = aux->segundoPuesto;
        aux->segundoPuesto = aux->primerPuesto;
        aux->primerPuesto = puntos;

    }
    else{
        if(puntos > aux->segundoPuesto){
            aux->tercerPuesto = aux->segundoPuesto;
            aux->segundoPuesto = puntos;
        }
        else{
                aux->tercerPuesto = puntos;
        }
    }

}

void subirPuntos(ePuntos* pPuntos){

    FILE* f = fopen("puntos.bin","rb");
    if(f==NULL){
        printf("Error al Cagar Puntos");
    }
    else{
        if(pPuntos != NULL){
           fread(pPuntos,sizeof(ePuntos),1,f);
        }
        else{
            printf("Error pPuntos");
        }

    }
    fclose(f);
}

void cagarPuntos(ePuntos* pPuntos){

    FILE* f = fopen("puntos.bin","wb");
    if(f==NULL){
        printf("Error al Cagar Puntos");
    }
    else{
        if(pPuntos != NULL){
           fwrite(pPuntos,sizeof(ePuntos),1,f);
        }
        else{
            printf("Error pPuntos");
        }

    }
    fclose(f);
}
