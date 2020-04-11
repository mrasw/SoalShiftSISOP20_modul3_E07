#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int bar1 = 4, kol1 = 2;
int bar2 = 2, kol2 = 5;
int bar3 = 4, kol3 = 5;
int mat1[10][10];
int mat2[10][10];
int mat3[10][10];

int count = 0;

void* perkalian(void* arg) {

    int batas = count++; 

	for (int i = batas; i < (batas + 1); i++) { 
		for (int j = 0; j < kol2; j++) { 
			for (int k = 0; k < bar2; k++) { 
				mat3[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

}


int main() {
	
	// fungsi join thread
    int pthread_join(pthread_t thread, void **rval_ptr);
               
	// menyimpan angka random		       
    int matrix;
    
    // array thread
    pthread_t threads[4];

	// Mengisi matriks 1 dengan range angka 1-20
    for(int i = 0; i < bar1; i++) {
        for(int j=0; j<kol1; j++) {
            matrix = rand() % 20 + 1;
            mat1[i][j] = matrix;
        }
    }
    printf("\n");

	// Menampilkan isi dari matriks 1
    printf("Matriks 1 : \n");
    for(int i = 0; i<bar1; i++) {
        for(int j = 0; j<kol1; j++) {
            printf("%d ", mat1[i][j]);
        }
        printf("\n");
    }

	// Mengisi matriks 2 dengan range angka 1-20
    for(int i=0; i<bar2; i++) {
        for(int j=0; j<kol2; j++) {
			matrix = rand() % 20 + 1;
            mat2[i][j] = matrix;
        }
    }
    printf("\n");

	// Menampilkan isi dari matriks 2
    printf("Matriks 2 : \n");
    for(int i = 0; i<bar2; i++) {
        for(int j = 0; j<kol2; j++) {
            printf("%d ", mat2[i][j]);
        }
        printf("\n");
    }

	// Membuat 4 threads setiap threads akan menjalankan bagiannya 
	int p;
    for (int i = 0; i < bar3; i++) { 
		p = pthread_create(&threads[i], NULL, perkalian, NULL);
        if(p!=0) //cek error
		{
			printf("\n can't create thread : [%s]",strerror(p));
		}
		else
		{
			// printf("\n create thread success\n");
		} 
	}

	// join threads sampai menyelesaikan tugasnya 
	for (int i = 0; i < 4; i++) {
		pthread_join(threads[i], NULL);
    }
    
	//Menampilkan hasil matriks 3
    printf("\n Hasil perkalian matriks 1 dengan 2 :\n");
    for(int i=0; i<bar3; i++) {
        for(int j=0; j<kol3; j++) {
            printf("%d ", mat3[i][j]);
        }
        printf("\n");
    }
}
