#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define NUM 10
#define NUM_MONEDAS 8

//ESQUEMA DIVIDE Y VENCERÁS
/*---------------------------------------------------------*/
void Hanoi(int n,int origen, int destino, int aux);
void HanoiERC(int n,int origen, int destino, int aux);
int bTernaria(int *vector, int base, int tope,int x);
long int potIterativa(long int a, int n);
long int potRecursiva(long int a, int n);
long int potDyV(long int a, int n);

int* InsercionB(int *vector, int elem);
int *creaVector(int elem, int rango);
void muestraVector(int *vector, int elem);
/*---------------------------------------------------------*/

//ESQUEMA VORAZ
/*-------------------------------------------------------------------------*/
int *cambio(int cambio, int *monedas,int numMonedas);
int *cambio2(int cambio, int *monedas,int *disponibles, int numMonedas);
/*-------------------------------------------------------------------------*/

int main(int argc, char *argv[]){
	int *vector, *vectorOrdenado, rango=10000, pos, valor, i;

	//LAS TORRES DE HANOI	
	/*-----------------------------------------------------*/
	printf("\nTORRES DE HANOI\n");
	Hanoi(3,1,3,2);
	printf("\nEliminando recursividad de cola...\n");
   	HanoiERC(3,1,3,2);
	/*-----------------------------------------------------*/


	//BUSQUEDA TERNARIA	
	/*-------------------------------------------------------------------------------------*/
	printf("\n\nBUSQUEDA TERNARIA\n");
	vector = creaVector(NUM,rango);
	vectorOrdenado=InsercionB(vector, NUM);
	muestraVector(vector, NUM);

	srand(time(NULL));
	valor = vector[rand()%NUM];
	pos = bTernaria(vectorOrdenado, 0, NUM-1, valor);

   	if (pos==-1) printf("\nNo existe valor %d\n", valor);
	else{
		printf("\n\n| %15s | %15s |", "VALOR", "POSICION");
		printf("\n| %15d | %15d |\n", valor, pos);
	}
	/*-------------------------------------------------------------------------------------*/


	//POTENCIA
	/*-----------------------------------------------------------------------*/ 
	printf( "\n\nPOTENCIA\n%d elevado a %d es %ld\n", 2, 10, potDyV(2,10));
	/*-----------------------------------------------------------------------*/

	
	//PROBLEMA DEL CAMBIO
	/*-----------------------------------------------------------------------*/
	printf("\n\nCAMBIO DE 15,45€...\n");
	printf("| %5s | %5s | %5s | %5s | %5s | %5s | %7s | %7s |\n",
			"1ct", "2ct", "5ct", "10ct", "20ct", "50ct", "1€", "2€");
	
	int monedas[NUM_MONEDAS]={1,2,5,10,20,50,100,200}; //Funcion de Selección
	int *solucionCambio;

  	solucionCambio = cambio(1545, monedas, NUM_MONEDAS);
  	
	for (i =0; i<NUM_MONEDAS; i++) printf("| %5d ", solucionCambio[i]);
	printf("|\n");
	/*-----------------------------------------------------------------------*/

	
	//PROBLEMA DEL CAMBIO 2
	/*-----------------------------------------------------------------------*/
	int disponibles[NUM_MONEDAS] = {300, 150, 75, 50, 35, 20, 10, 5};
  	
	solucionCambio = cambio2(1545, monedas, disponibles, NUM_MONEDAS);
	
	for (i=0; i<NUM_MONEDAS; i++) printf("%d ", solucionCambio[i]);
	printf("\n");
	/*-----------------------------------------------------------------------*/

}


void Hanoi(int n,int origen, int destino, int aux){
	if (n>0){
			Hanoi(n-1,origen, aux, destino);
          	printf(" Mueve dico n %d desde %d a %d \n",n, origen, destino);
          	Hanoi(n-1, aux,destino, origen);
     	}
}


void HanoiERC(int n,int origen, int destino, int aux){
	int temp;	
	while(n>0){
		HanoiERC(n-1, origen, aux, destino);
		printf(" Mueve disco n %d desde %d a %d \n", n, origen, destino);
		temp=origen;		
		origen=aux;
		aux=temp;
		n--;
	}
}



int bTernaria(int *vector, int base, int tope, int x){
	int ptercio;
	int stercio;
	int k;

	if(base<tope){
		k = (tope-base)/3;
		ptercio=base+k;
		stercio = 2*ptercio;

		if(x==vector[ptercio]) return ptercio;
		else if(x==vector[stercio]) return stercio;
		else{
			if(x<vector[ptercio]) tope=ptercio-1;
			else if(x>vector[stercio]) base=stercio+1;
			else{
				base=ptercio+1;
				tope=stercio-1;
			}
		}

		return bTernaria(vector, base, tope, x);
	}
}


long int potDyV(long int a, int n){
	int rto;
	if(n==1) return a;
	
	else if(n%2==0){
		rto = potDyV(a,n/2);
		return rto*rto;
	}
	
	else if(n%2!=0){
		 return a*potDyV(a,n-1);
	}

}

int* InsercionB(int *vector, int elem){
	int  i, j, aux, base, tope, mitad;

	for(i=1; i<elem; i++){
		base=0;
		tope=i-1;
		aux=vector[i];

		while(base<=tope){
			mitad=(base+tope)/2;
			if(aux<=vector[mitad]) tope=mitad-1;
			else base=mitad+1;
		}

		for(j=i-1; j>=base; j--){
			vector[j+1]=vector[j];
		}
	
		vector[base]=aux;
	}

	return vector;
}


int *creaVector(int elem, int rango){
	srand(time(NULL));
	int i;
	
	int *vector;
	vector = (int *)malloc(elem*sizeof(int));

	for(i=0; i<elem; i++){
		vector[i]=rand()%rango;
	}	

	return vector;
	
}

void muestraVector(int *vector, int elem){
	int i;
	for(i=0; i<elem; i++){
		printf("%d\t", vector[i]);
	}
}

/*-----------------------------------------------------------*/

int *cambio(int cambio, int *monedas, int numMonedas){
	int cambioAcumulado = 0;
	int j = numMonedas-1, i;
	int *solucion;
	solucion = (int *)malloc(numMonedas*sizeof(int));

	for(i=0; i<numMonedas; i++){
		solucion[i]=0;
	}

	while(cambioAcumulado != cambio){
		while( (monedas[j] > (cambio-cambioAcumulado)) && (j>=0)){
			j--;
		}

		if(j==0){
			printf("\n\nNO EXISTE SOLUCION !!\n\n");
			exit(-1);
		}

		solucion[j] = (cambio-cambioAcumulado)/monedas[j];
		cambioAcumulado += monedas[j]*solucion[j];
	}

	return solucion;

}

int *cambio2(int cambio, int *monedas, int *disponibles, int numMonedas){
	int cambioAcumulado = 0;
	int j = numMonedas-1, i;
	int *solucion;
	solucion = (int *)malloc(numMonedas*sizeof(int));

	for(i=0; i<numMonedas; i++){
		solucion[i]=0;
	}

	while(cambioAcumulado!=cambio){
		while( (monedas[j] > (cambio-cambioAcumulado)) && (j>=0)){
			j--;
		}

		if(j==0){
			printf("\n\nNO EXISTE SOLUCION !!\n\n");
			exit(-1);
		}

		solucion[j] = (cambio-cambioAcumulado)/monedas[j];
		cambioAcumulado += monedas[j]*solucion[j];
	}

	return solucion;
}
