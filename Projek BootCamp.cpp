#include <stdio.h>
#include <string.h>

int total, kembalian;
int n = 4;
// struct untuk pengisian bon 
struct Bon{
    char name[100];
    int r1 ;
    char jenisR1[20];
    int r2 ;
    char jenisR2[20];
    int r3  ;
    char jenisR3[20];
    int r4 ;
    char jenisR4[20];
    int uangcus ;
};

// sorting untuk jenis roti dari paling besar ke kecil
void merge(char jenis[4][20], int arr[], int left, int mid, int right){
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    int leftArr[leftSize];
    char leftJenis[leftSize][20];
    int rightArr[rightSize];
    char rightJenis[rightSize][20];

    for(int i = 0; i < leftSize; i++){
        leftArr[i] = arr[i + left];
        strcpy(leftJenis[i], jenis[i+left]);
    }
    for(int i = 0; i < rightSize; i++){
        rightArr[i] = arr[i + mid + 1];
        strcpy(rightJenis[i], jenis[i + mid + 1]);
    }

    int idx = left;
    int idxL = 0;
    int idxR = 0;

    while(idxL < leftSize && idxR < rightSize){
        if(leftArr[idxL] > rightArr[idxR]){
            arr[idx] = leftArr[idxL];
            strcpy(jenis[idx], leftJenis[idxL]);
            idx++;
            idxL++;
        }
        else{
            arr[idx] = rightArr[idxR];
            strcpy(jenis[idx], rightJenis[idxR]);
            idx++;
            idxR++;
        }
    }

    while(idxL < leftSize){
        arr[idx] = leftArr[idxL];
        strcpy(jenis[idx], leftJenis[idxL]);
        idx++;
        idxL++;
    }

    while(idxR < rightSize){
        arr[idx] = rightArr[idxR];
        strcpy(jenis[idx], rightJenis[idxR]);
        idx++;
        idxR++;
    }
}

void split(char jenis[4][20], int arr[], int left, int right){
    if(left >= right){
        return;
    }
    int mid = (left + right) / 2;
    split(jenis, arr, left, mid);
    split(jenis, arr, mid + 1, right);

    merge(jenis, arr, left, mid, right);
}


void sort(char jenis[4][20], int arr[], int n){
    split(jenis, arr, 0, n - 1);
}


void print(char jenis[4][20], int arr[], int a, int b, int c, int d){
    struct Bon bon;
    for(int i = 0; i < n; i++){
        printf("%s %dX\n", jenis[i], arr[i]);
    }
    printf("\n");
}

// buat input bon
void BikinBon(){
    struct Bon bon;

	printf("Input Name : ");
    scanf("%[^\n]", bon.name); getchar(); 
	printf("Input Roti Abon : ");
	scanf("%d", &bon.r1); getchar();
	printf("Input Roti Pisang : ");
	scanf("%d", &bon.r2); getchar();
	printf("Input Roti Coklat : ");
	scanf("%d", &bon.r3); getchar();
	printf("Input Roti Keju : ");
    scanf("%d", &bon.r4); getchar();
    printf("Input Pembayaran : Rp");
    scanf("%d", &bon.uangcus); getchar();
     
    char jenis[4][20] = {"Roti Abon", "Roti Pisang", "Roti Coklat", "Roti Keju"};
    int arr[] = {bon.r1, bon.r2, bon.r3, bon.r4};
    
    int total = ((bon.r1*5000)+(bon.r2*6000)+(bon.r3*4000)+(bon.r4*8000)); 
    int kembalian = bon.uangcus-total;
    sort(jenis, arr, n);
    
    // save setelah di sort
    bon.r1 = arr[0];
    strcpy(bon.jenisR1, jenis[0]);
    bon.r2 = arr[1];
    strcpy(bon.jenisR2, jenis[1]);
    bon.r3 = arr[2];
    strcpy(bon.jenisR3, jenis[2]);
    bon.r4 = arr[3];
    strcpy(bon.jenisR4, jenis[3]);
    if(kembalian < 0){
			printf("Transaksi Gagal\n");
			puts("");
			printf("Jumlah Uang yang Kurang : Rp%d \n", (total-bon.uangcus));
			return ;
		}
    printf("================================ \n");
    printf("Nama Customer: %s\n", bon.name);
    print(jenis, arr, bon.r1, bon.r2, bon.r3, bon.r4);
    printf("Total : Rp%d\n", total );
    printf("Kembalian : Rp%d\n", kembalian);
    printf("  Terima Kasih Sudah Berbelanja\n");
    printf("================================ \n");
    puts("");

    FILE *fp = fopen ("daftartransaksi.txt", "a");
    fprintf(fp, "%s#%s#%d#%s#%d#%s#%d#%s#%d#%d#%d\n", bon.name, bon.jenisR1, bon.r1, bon.jenisR2, bon.r2, bon.jenisR3, bon.r3, bon.jenisR4, bon.r4, total, kembalian );
    fclose(fp);
}

// buat menampilkan semua daftar transaksi
void TampilBon(){
    FILE *fp = fopen ("./daftartransaksi.txt", "r");
    struct Bon bon;
    while(fscanf(fp, "%[^#]#%[^#]#%d#%[^#]#%d#%[^#]#%d#%[^#]#%d#%d#%d\n",
    bon.name, bon.jenisR1, &bon.r1, bon.jenisR2, &bon.r2, bon.jenisR3, &bon.r3, bon.jenisR4, &bon.r4, &total, &kembalian) != EOF ){
    	puts("================================");
        printf("Nama : %s \n", bon.name);
        printf("%s : %d \n", bon.jenisR1, bon.r1);
        printf("%s : %d \n", bon.jenisR2, bon.r2);
        printf("%s : %d \n", bon.jenisR3, bon.r3);
        printf("%s : %d \n", bon.jenisR4, bon.r4);
        printf("Total: %d \n", total);
        printf("Kembalian: %d \n", kembalian);
		puts("================================");
		printf("\n"); 
    }
    fclose(fp);
    
}

// buat mencari nama customer 
void CariBon(){
	char namesrc[100];
	int find = 0;
	printf("Masukkan Nama Customer yang ingin dicari:");
	scanf("%[^\n]", namesrc); getchar();
	
	FILE *fp = fopen ("./daftartransaksi.txt", "r");
    struct Bon bon;
    while(fscanf(fp, "%[^#]#%[^#]#%d#%[^#]#%d#%[^#]#%d#%[^#]#%d#%d#%d\n",
    bon.name, bon.jenisR1, &bon.r1, bon.jenisR2, &bon.r2, bon.jenisR3, &bon.r3, bon.jenisR4, &bon.r4, &total, &kembalian) != EOF ){
    	
    if(strncmp(namesrc, bon.name, strlen(namesrc)) == 0 )	{
    	puts("---------------------------------");
    	printf("%s \n", bon.name);
    	printf("%s : %d \n", bon.jenisR1, bon.r1);
        printf("%s : %d \n", bon.jenisR2, bon.r2);
        printf("%s : %d \n", bon.jenisR3, bon.r3);
        printf("%s : %d \n", bon.jenisR4, bon.r4);
        printf("Total: %d \n", total);
        printf("Kembalian: %d \n", kembalian); 
    	puts("---------------------------------");
    	puts("");
    	find = 1;

	}
}
	if(find == 0){
	
	printf("Nama Customer Tidak Ditemukan \n");
}
}


int main(){
    int choice;
    do{
        puts("---------------------------------");
        puts("|Pilih opsi yang diinginkan:    |");
        puts("|1. Buat Bon                    |");
        puts("|2. Tampilkan Semua Bon         |");
        puts("|3. Cari Nama Customer          |");
        puts("|4. Tampilkan Harga             |");
        puts("|5. Exit                        |");
        puts("---------------------------------");
        scanf("%d", &choice); getchar();
        switch(choice){
            case 1:{
                BikinBon();
                break;
            }
            case 2:{
                TampilBon();
                break;
            }
            case 3:{
                CariBon();
                break;
        	}
        	case 4:{
        		puts("Roti Abon	: Rp5000");
        		puts("Roti Pisang	: Rp6000 ");
        		puts("Roti Coklat	: Rp4000 ");
        		puts("Roti Keju	: Rp8000 ");
        		
				break;
			}
 		}
	}while (choice != 5);

    return 0;
}
