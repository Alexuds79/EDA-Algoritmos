#include"monticulo.h"
#include<time.h>
#include <stdlib.h>
#include <stdio.h>

#define N 10

void filtradoDescendente(Monticulo *m, int i){
	int hijoMin;
	tipoElementoM temp;

	while(i*2<=m->tamanno){
		if(i*2+1 > m->tamanno) hijoMin = i*2;
		else if(m->elemento[i*2].clave < m->elemento[i*2+1].clave) hijoMin = i*2;
		else hijoMin = i*2+1;
		
		if(m->elemento[i].clave > m->elemento[hijoMin].clave){
			temp = m->elemento[i];
			m->elemento[i] = m->elemento[hijoMin];
			m->elemento[hijoMin] = temp;
		}
		
		i = hijoMin;
	}
}


void filtradoAscendente(Monticulo *m, int i){
	tipoElementoM temp;
	
	while(i/2 > 0){
		if(m->elemento[i].clave < m->elemento[i/2].clave){
			temp = m->elemento[i];
			m->elemento[i] = m->elemento[i/2];
			m->elemento[i/2] = temp;
		}
		
		i/=2;
	}
}

void iniciaMonticulo(Monticulo *m){
	m->elemento[0].clave=-1;
	m->elemento[0].informacion=-1;
	m->tamanno = 0;
}

int vacioMonticulo(Monticulo m){
	if(m.tamanno==0) return 1;
	else return 0;
}

int insertar(tipoElementoM x, Monticulo *m){
	m->tamanno++;
	if(m->tamanno > MAXIMO) return -1;
	m->elemento[m->tamanno] = x;
	filtradoAscendente(m, m->tamanno);
	return 0;
}


int eliminarMinimo(Monticulo *m, tipoElementoM *minimo){
	if(vacioMonticulo(*m)) return -1;
	else{
		*minimo = m->elemento[1];
		m->elemento[1] = m->elemento[m->tamanno];
		m->tamanno--;
		filtradoDescendente(m, 1);
		return 0;
	}
}


void decrementarClave(int pos, tipoClave cantidad, Monticulo *m){ //filtrado ascendente, si procede
	m->elemento[pos].clave-=cantidad;
	filtradoAscendente(m, pos);

}

void incrementarClave(int pos, tipoClave cantidad, Monticulo *m){ //filtrado descendente, si procede
	m->elemento[pos].clave+=cantidad;
	filtradoDescendente(m, pos);
}

int esMonticulo(Monticulo m){
	int i;
	
	for(i=1; i*2<m.tamanno; i++){
		if(m.elemento[i].clave > m.elemento[i*2].clave) return 0;
	}
	
	return 1;
}

void crearMonticulo(Monticulo *m){
	int i, n;
	n = m->tamanno;
	
	for(i=n/2; i>=1; i--){
		filtradoDescendente(m, i);
	}
}

void heapsort(Monticulo *m){
	int i, n=m->tamanno;
	tipoElementoM minimo;
	
	for(i=1; i<=n; i++){
		eliminarMinimo(m, &minimo);
		m->elemento[m->tamanno+1] = minimo;
	}
	
	m->tamanno=n;
}




















