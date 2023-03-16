#include <stdio.h>
#include <malloc.h>
typedef int keytype;
typedef float othertype;
typedef struct{
	keytype key;
	othertype otherfields;
}recordtype;

 void Read_Data(recordtype a[], int *n){
 	FILE *f;
 	f = fopen("data_x_mu_n.txt" , "r");
 	int i = 0;
 	if( f != NULL)
 	while(!feof(f)){
 		fscanf(f,"%d%f",&a[i].key, &a[i].otherfields);
 		i++;
	}
	else printf("Loi mo file\n");
	fclose(f);
	*n=i;
 }
void Print_Data(recordtype a[] , int n){
	int i;
	for(i = 0; i < n ; i++){
		printf("%3d%5d%8.2f\n",i+1,a[i].key,a[i].otherfields);
	}
}
float pow(float x, int n)
{
    if(n == 1) {
        return x;
    } else {
        int temp = pow(x, n/2);
        if(n % 2 == 0)
            return temp * temp;
        else
            return temp * temp * x;
    }
}
int main(){
	recordtype a[100];
	float A[100];
	int n,i;
	Read_Data(a,&n);
	printf("Du lieu ban dau :\n");
	Print_Data(a,n);
	for( i = 0; i < n ; i++){
		A[i] = pow(a[i].otherfields,a[i].key);
	}
	printf("Ket qua x mu n la :\n");
	for(i = 0; i < n; i++){
		printf("%d\t%.2f\n",i+1,A[i]);
	}
	return 0;
}

