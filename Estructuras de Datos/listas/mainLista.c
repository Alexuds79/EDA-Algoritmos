#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"
#define N_ELEM 25
#define MAX 10

int main(int argc, char *argv[]){
	/*Para probar las funciones se construye el programa PURGA
	de la teoría*/
	
	/*Funciones de lista.c que no aparecen en este main:
		- vacia -> Usada auxiliarmente en funciones como suprime, localiza, recupera y anula, que sí aparecen
		- anterior -> Usada auxiliarmente en la función suprime, que sí aparece
	*/
	
	//1. Creamos una lista con elementos aleatorios
	Lista *lista = malloc(sizeof(Lista));
	int i;
	
	creaVacia(lista);
	srand(time(NULL));
	for(i=0; i<N_ELEM; i++){
		inserta(rand()%MAX, fin(lista), lista);
	}
	
	imprime(lista);
	
	//2. Purgamos la lista para eliminar repetidos
	printf("\nLista purgada...\n");
	
	tipoPosicion actual, aux;
	actual = primero(lista);
	
	while(actual!=fin(lista)){
		aux = siguiente(actual, lista);	
		
		while(aux!=fin(lista)){
			if(recupera(aux, lista) == recupera(actual, lista)){
				suprime(aux, lista);
			}
			else{
				aux=siguiente(aux, lista);
			}
		}	
			
		actual=siguiente(actual, lista);
	}
	
	imprime(lista);
	
	//3. Localizamos un elemento al azar de la nueva lista (o fuera de ella, en cuyo caso localiza devuelve el último) y lo mostramos
	int valor = rand()%(2*MAX);
	tipoPosicion pos = localiza(valor, lista);
	printf("\n\nEl numero aleatorio generado es: %d\n", valor);
	printf("El valor localizado mediante la funcion localiza es: %d\n\n", pos->elemento);
	
	//4. Anulamos la lista y la destruímos
	anula(lista);
	printf("Lista anulada...\n");
	imprime(lista);
	destruye(lista);

	return 0;
}
