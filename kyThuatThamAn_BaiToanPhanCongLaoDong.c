#include <stdio.h>
#define size 100

typedef struct{
	int CN,CV,TG;
}PhanCong;

typedef struct{
	int TG,STT;
}Data;

void ReadData(Data a[][size], int *n){
	FILE *f;
	f = fopen("data_bai_toan_phan_cong_lao_dong.txt", "r");
	if(f == NULL){
		printf("Mo file co loi");
		return;
	}
	fscanf(f,"%d",n);
	int i,j;
	for(i = 0; i < *n; i++){
		for(j = 0; j < *n; j++){
			fscanf(f , "%d",&a[i][j].TG);
			a[i][j].STT = 0;
		}
	}
	fclose(f);
}
void PrintData(Data a[size][size],int n){
	int i,j;
	printf("\nMa tran thoi gian da cho:\n");
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%3d",a[i][j].TG);
		}
		printf("\n");
	}
}
void Cap_Nhat_Cong_Viec(Data a[][size],int n, int j){
	int i;
	for(i = 0; i < n; i++){
		a[i][j].STT = 1;
	}
}

int Min_of_Row(Data a[][size],int n, int i,int *j){
	int TGMin = 32767,k;
	for(k = 0; k < n; k++){
		if(a[i][k].STT == 0 && a[i][k].TG < TGMin){
			TGMin = a[i][k].TG;
			*j = k;
		}
	}
	return TGMin;
}

void Greedy(Data a[][size],int n, PhanCong PA[]){
	int i,j;
	for(i = 0; i < n; i++){
		PA[i].CN = i + 1;
		PA[i].TG = Min_of_Row(a,n,i,&j);
		PA[i].CV = j + 1;
		Cap_Nhat_Cong_Viec(a, n, j);
	}
}

void PrintPA(PhanCong PA[], int n){
	int i, sum = 0;
	printf("\nKy thuat Tham an: Nguoi chon viec\nPhuong an phan cong nhu sau:\n");
	printf("Cong nhan	Cong viec	Thoi gian thuc hien\n");
	for(i = 0; i < n; i++){
		printf("%5d		%5d%21d\n",PA[i].CN,PA[i].CV,PA[i].TG);
		sum += PA[i].TG;
	}
	printf("Tong thoi gian thuc hien la: %d\n",sum);
}

int main(){
	Data a[size][size];
	int n;
	ReadData(a,&n);
	PhanCong PA[n];
	PrintData(a,n);
	Greedy(a,n,PA);
	PrintPA(PA,n);
	return 0;
}
