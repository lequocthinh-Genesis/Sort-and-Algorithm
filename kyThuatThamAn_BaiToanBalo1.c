#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
	char TenDV[20];
	float TL,GT,DG;
	int So_DV_Duoc_Chon;
}DoVat;

void swap(DoVat *x, DoVat *y){
	DoVat temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

DoVat * ReadFromFile(float *w, int *n){
	FILE *f;
	f = fopen("balo1.txt","r"); 
	fscanf(f,"%f",w);
	DoVat * dsdv;
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while(!feof(f)){
		fscanf(f,"%f%f%[^\n]",&dsdv[i].TL,&dsdv[i].GT,&dsdv[i].TenDV);
		dsdv[i].DG = dsdv[i].GT/dsdv[i].TL;
		dsdv[i].So_DV_Duoc_Chon = 0;
		i++;
		dsdv = realloc(dsdv,sizeof(DoVat)*(i+1));
	}
	
	*n = i;
	fclose(f);
	return dsdv;
}

void InDSDV(DoVat *dsdv,int n, float w){
	int i;
	float TongTL = 0.0,TongGT = 0.0;
	printf("|---|--------------------|----------|----------|----------|---------------|\n");
	printf("|STT|Ten Do Vat          |T.Luong   |Gia Tri   |Don Gia   |So DV Duoc Chon|\n");
	printf("|---|--------------------|----------|----------|----------|---------------|\n");
	for(i = 0 ; i < n ; i++){
		printf("|%3d|%20s|%10.2f|%10.2f|%10.2f|%15d|\n",i+1,dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT,dsdv[i].DG,dsdv[i].So_DV_Duoc_Chon);
		TongTL += dsdv[i].So_DV_Duoc_Chon * dsdv[i].TL;
		TongGT += dsdv[i].So_DV_Duoc_Chon * dsdv[i].GT;
	}
	printf("|---|--------------------|----------|----------|----------|---------------|\n");
	printf("\nTrong luong cua ba lo la : %.2f\n",w);
	printf("\nTong Trong luong cua cac vat duoc chon la : %.2f\n",TongTL);
	printf("\nTong Gia Tri cua cac vat duoc chon la : %.2f\n",TongGT);
	
}


void BubbleSort(DoVat *dsdv, int n){
	int i,j;
	for(i = 0 ; i <= n - 2 ; i++){
		for(j = n - 1 ; j >= i + 1 ; j-- ){
			if( dsdv[j].DG > dsdv[j-1].DG){
				swap(&dsdv[j],&dsdv[j-1]);
			}
		}
	}
}

void Greedy(DoVat * dsdv, int n, float w){
	int i;
	for(i = 0 ; i < n ; i++){
		dsdv[i].So_DV_Duoc_Chon = (w/dsdv[i].TL);
		w = w - dsdv[i].So_DV_Duoc_Chon * dsdv[i].TL;
	}
}

int main(){
	DoVat * dsdv;
	int n;
	float w;
//	printf("123");
	dsdv = ReadFromFile(&w,&n);
	
	BubbleSort(dsdv,n);
	
	Greedy(dsdv,n,w);
	
	InDSDV(dsdv,n,w);
	
	free(dsdv);
	return 0;
}

