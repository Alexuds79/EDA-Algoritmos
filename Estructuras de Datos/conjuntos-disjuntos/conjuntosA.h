#ifndef __CONJUNTOS_A_H
#define __CONJUNTOS_A_H

#define MAXIMO_C 16

typedef int particion[MAXIMO_C];
typedef int tipoConjunto;
typedef int tipoElemento;

// Funciones a implementar

void crea(particion C);
tipoElemento buscar(tipoElemento x, particion C);
void unir(tipoElemento x, tipoElemento y, particion C);
// Función proporcionada
void verParticion(particion C);
#endif

