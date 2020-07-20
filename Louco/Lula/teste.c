#include <stdio.h>
#include <stdlib.h>
#define len 10

int *heapify(int *pont,int i,int varlen){
	int aux = 0;
	int direita = (i*2)+2;
	int esquerda = (i*2)+1;
	if (i>varlen){
		return pont;
	}
	else if(esquerda<varlen){
		if (direita<varlen){
			if(pont[i]<pont[esquerda]){
				if(pont[esquerda]<pont[direita]){
					aux = pont[i];
					pont[i] = pont[direita];
					pont[direita] = aux;
					i = direita;
					pont = heapify(pont,i,varlen);
					return pont;
				}
				else{
					aux = pont[i];
					pont[i] = pont[esquerda];
					pont[esquerda] = aux;
					i = esquerda;
					pont = heapify(pont,i,varlen);
					return pont;
				}
			}
			else if(pont[i]<pont[direita]){
				aux = pont[i];
				pont[i] = pont[direita];
				pont[direita] = aux;
				i = direita;
				pont = heapify(pont,i,varlen);
				return pont;
			}
		}
		else if (pont[i]<pont[esquerda]){
			aux = pont[i];
			pont[i] = pont[esquerda];
			pont[esquerda] = aux;
			i = esquerda;
			pont = heapify(pont,i,varlen);		
			return pont;	
		}
	}
	else{
		return pont;
	}
	return pont;
}

int *maxheap(int *pont, int varlen){
	for (int j=(len/2)-1;j>=0;j--){
		pont = heapify(pont, j,len);
	}
	return pont;
}

void printar(int * pont){
	for (int i=0;i<len;i++){
		printf("%d ", pont[i]);
	}
	printf("\n");
}

int main(void){
	int arr[len] = {};
	int *pont = arr;
	int aux;
	int varlen = len-1;
	pont = maxheap(pont,varlen);
	for(int varlen = len-1;varlen>=0;varlen--){
		int i = 0;
		aux = arr[0];
		arr[0]=arr[varlen];
		arr[varlen]=aux;
		pont = heapify(pont,i,varlen);
	}
	for(int i = 0;i<tam-1;i++){
		if pont[i]<pont[i+1]{
			printf("FUDEU\n");
			return 1;
		}
	}
}