#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "galaxia.h"
#include <conio.h>
#include "LinkedList.h"

int main(){

    int opcion;
    int salir = 0;

    ePuntos* pPuntos = (ePuntos*)malloc(sizeof(ePuntos));
    subirPuntos(pPuntos);

    esconderCursor();

    do{
       switch(opcion=menuPrincipal(pPuntos)){

            case 0:
                system("cls");

                while(galaxiaMain(pPuntos)){
                    cagarPuntos(pPuntos);
                    system("cls");
                }

                break;
            case 1:
                system("cls");
                //printf("opcion 1");

                system("pause");
                break;
            case 2:

                system("cls");
                salir = menuSalida();


        }
    }while(salir != 1);

    free(pPuntos);
    return 0;
}
