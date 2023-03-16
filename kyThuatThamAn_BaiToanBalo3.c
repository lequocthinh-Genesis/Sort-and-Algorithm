#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
	char TenDV[20];
	float TL,GT,DG; //trong luong ,gia tri , don gia
	int So_DV_Duoc_Chon;
}DoVat;

DoVat * ReadFromFile(float *W,int *n){
	FILE *f;
	f = fopen("balo3.txt", "r");
	fscanf(f, "%f" , W);//xac dinh trong luong balo
	DoVat *dsdv;
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while(!feof(f)){
		fscanf(f,"%f%f%[^\n]",&dsdv[i].TL,&dsdv[i].GT,&dsdv[i].TenDV);
		dsdv[i].DG = dsdv[i].GT/dsdv[i].TL;
		dsdv[i].So_DV_Duoc_Chon = 0;
		i++;
		dsdv = realloc(dsdv, sizeof(DoVat)*(i+1));
	}
	*n = i; //so luong do vat
	fclose(f);
	return dsdv; //mang cac do vat
	
}

void InDSDV(DoVat *dsdv ,int n, float W){
	int i;
	float TongTL = 0.0, TongGT = 0.0;
	printf("\nPhuong an thu duoc tu ky thuat THAM AN nhu sau:\n");
	printf("|---|--------------------|----------|----------|----------|---------------|\n");
	printf("|STT|     Ten Do Vat     | T.Luong  | Gia Tri  | Don Gia  |So DV duoc chon|\n");
	printf("|---|--------------------|----------|----------|----------|---------------|\n");
	for(i = 0; i < n ; i++){
		printf("|%-3d|%-20s|%10.2f|%10.2f|%10.2f|%8d       |\n",i + 1,dsdv[i].TenDV,dsdv[i].TL,
																dsdv[i].GT,dsdv[i].DG,dsdv[i].So_DV_Duoc_Chon);
		TongTL = TongTL + dsdv[i].So_DV_Duoc_Chon * dsdv[i].TL;	
		TongGT = TongGT + dsdv[i].So_DV_Duoc_Chon * dsdv[i].GT;
	}
	printf("|---|--------------------|----------|----------|----------|---------------|\n");
	printf("\nTrong luong cua ba lo = %-10.2f\n",W);
	printf("\nTong trong luong cac vat duoc chon = %-10.2f\n\nTong gia tri = %-10.2f\n",TongTL,TongGT);
	
}

void swap(DoVat *x,DoVat *y){
	DoVat temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void BubbleSort(DoVat * dsdv,int n){
	int i,j;
	for(i = 0; i <= n - 2; i++){
		for( j = n-1; j >= i+1; j--){
			if(dsdv[j].DG > dsdv[j - 1].DG){
				swap(&dsdv[j],&dsdv[j - 1]);
			}
		}
	}
}
void Greedy(DoVat * dsdv,int n,float W){
	int i;
	for(i = 0; i < n ; i++){
		dsdv[i].So_DV_Duoc_Chon = (W/dsdv[i].TL);
		W = W-dsdv[i].So_DV_Duoc_Chon * dsdv[i].TL;
	}
}
int main(){
	int n;
	float W;
	DoVat * dsdv;
	dsdv = ReadFromFile(&W,&n);
	BubbleSort(dsdv,n);
	Greedy(dsdv,n,W);
	InDSDV(dsdv,n,W);
	free(dsdv);
	return 0;
}
