#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cola.h"
#include "../pilas/pila.h"
#include "../pilas/pila.c"

void colaImprime(Cola *c) {
    tipoCelda *aImprimir;
    int posicion;
    
    if (c == NULL || c->frente == NULL) {
        return;
    }
    else {
        posicion = 1;
        aImprimir = c->frente;
        while (aImprimir != NULL) {
            printf("Valor: %d en posición: %d\n", aImprimir->elemento, posicion++);
            aImprimir = aImprimir->sig;
        }
        printf("%d valores en la lista\n", posicion-1);
    }
}

int main(int argc, char *argv[]){
	//Detección de palíndromos mediante pila+cola

	Cola cola;
	Pila pila;
	int i=0;
	char cadena[100];
	char c, charCola, charPila;
	int flag=0;

	colaCreaVacia(&cola);
	pilaCreaVacia(&pila);
	
	printf("Ingrese una palabra o frase(sin espacios): ");
	scanf("%s", cadena);
	
	c=cadena[0];
	
	while(c!='\0'){
		colaInserta(c, &cola);
		pilaInserta(c, &pila);
		c=cadena[++i];
		
	}
	
	while(!colaVacia(&cola)){
		flag=0;
		charCola=colaSuprime(&cola);
		charPila=pilaSuprime(&pila);
		printf("%c - %c\n", charCola, charPila);
		
		if(charCola!=charPila){
			flag=1;
			break;
		}
	}
	
	if(flag==0) printf("Es un palindromo!\n");
	else printf("No es un palindromo...\n");

	return 0;
}
