#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
	char TenDV[20];
	float TL,GT,DG;
	int PA;
}DoVat;

void swap(DoVat *x, DoVat *y){
	DoVat temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void BubbleSort(DoVat *dsdv, int n){
	int i,j;
	for(i = 0 ; i < n - 2 ; i++){
		for(j = n - 1 ; j >= i+1 ; j--){
			if( dsdv[j].DG > dsdv[j-1].DG){
				swap(&dsdv[j],&dsdv[j-1]);
			}
		}
	}
}

DoVat * ReadFromFile(float *w, int *n){
	FILE *f;
	f = fopen("balo3.txt","r");
	fscanf(f,"%f",w);
	DoVat * dsdv;
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while(!feof(f)){
		fscanf(f,"%f%f%[^\n]",&dsdv[i].TL,&dsdv[i].GT,&dsdv[i].TenDV);
		dsdv[i].DG = dsdv[i].GT/dsdv[i].TL;
		dsdv[i].PA = 0;
		i++;
		dsdv = realloc(dsdv,sizeof(DoVat)*(i+1));
	}
	*n = i;
	fclose(f);
	return dsdv;
}

void InDSDV(DoVat * dsdv, int n, float w){
	int i;
	float TongGT = 0.0,TongTL = 0.0;
	printf("|---|--------------------|----------|----------|----------|---------------|\n");
	printf("|STT|Ten Do Vat          |T.Luong   |Gia Tri   |Don Gia   |So DV Duoc Chon|\n");
	printf("|---|--------------------|----------|----------|----------|---------------|\n");
	for(i = 0 ; i< n ; i++){
		printf("|%3d|%20s|%10.2f|%10.2f|%10.2f|%15d|\n",i+1,dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT,dsdv[i].DG,dsdv[i].PA);
		
		TongGT = TongGT + dsdv[i].PA * dsdv[i].GT;
		TongTL += dsdv[i].PA * dsdv[i].TL;
	}
	printf("|---|--------------------|----------|----------|----------|---------------|\n");
	
	printf("\nTrong luong cua ba lo la : %.2f\n",w);
	
	printf("\nTong Trong luong cua cac vat duoc chon la : %.2f\n",TongTL);
	
	printf("\nTong Gia tri cua cac vat duoc chon la : %.2f\n",TongGT);
	
	
}



void Tao_Nut_Goc(float w, float *v, float *CT, float *GLNTT, float *TGT, float DG_Max){
	*v = w;
	*CT = *v * DG_Max;
	*TGT = 0.0;
	*GLNTT = 0.0;
}

void Cap_Nhat_GLNTT(float TGT, float *GLNTT, int x[], DoVat *dsdv, int n){
	int i;
	if( TGT > *GLNTT){
		*GLNTT = TGT;
		for(i = 0 ; i < n ; i++){
			dsdv[i].PA = x[i];
		}
	}
}
int min(int a , int b){
	return a<b?a:b;
}

void Nhanh_Can(int i, float *TGT, float *CT, float *v , float *GLNTT, int x[], DoVat *dsdv, int n){
	int j;
	int T = min(1,*v/dsdv[i].TL);
	for(j = T ; j >=0 ; j--){
		*TGT += j*dsdv[i].GT;
		*v -= j*dsdv[i].TL;
		*CT = *TGT + *v*dsdv[i+1].DG;
		if(*CT > *GLNTT){
			x[i] = j;
			if( (i == n - 1) || ( *v == 0)) Cap_Nhat_GLNTT(*TGT,GLNTT,x,dsdv,n);
			else Nhanh_Can(i+1,TGT,CT,v,GLNTT,x,dsdv,n);
		}
		x[i] = 0;
		*TGT -= j*dsdv[i].GT;
		*v += j*dsdv[i].TL;
	}
}

//void Nhanh_Can(int i, float *TGT, float *CT, float *v , float *GLNTT, int x[], DoVat * dsdv, int n){
//	int j;
//	int T = min(1,*v/dsdv[i].TL);
//	for(j = T ; j >= 0 ; j--){
//		*TGT += j*dsdv[i].GT;
//		*v -= j*dsdv[i].TL;
//		*CT = *TGT + *v*dsdv[i+1].DG;
//		if( *CT > *GLNTT){
//			x[i] = j;
//			if( (i == n-1 ) || (*v == 0)) Cap_Nhat_GLNTT(*TGT,GLNTT,x,dsdv,n);
//			else Nhanh_Can(i+1,TGT,CT,v,GLNTT,x,dsdv,n);
//		}
//		x[i] = 0;
//		*TGT -= j*dsdv[i].GT;
//		*v += j*dsdv[i].TL;
//	}
//}	
int main(){
	DoVat *dsdv;
	int n,i;
	float w;
	
	float CT;
	float TGT;
	float GLNTT;
	float v;
	
	
	dsdv = ReadFromFile(&w,&n);
	int x[n];
	
	BubbleSort(dsdv,n);
	printf("123");
	Tao_Nut_Goc(w,&v,&CT,&GLNTT,&TGT,dsdv[0].DG);
	
	Nhanh_Can(0,&TGT,&CT,&v,&GLNTT,x,dsdv,n);
	
	InDSDV(dsdv,n,w);
	
	free(dsdv);
	return 0;
}

