#include<stdio.h>

int main() 
{ 
 int mat1[][2] = { { 2, 4 }, { 3, 4 }, {1, 2}, {1,3} }; 
 int mat2[][5] = { { 1, 2, 3, 4, 5 }, { 1, 1, 1, 1, 1 } }; 
 int m1 = 4, m2 = 2, n1 = 2, n2 = 5; 
 
 int x, i, j; 
 int res[m1][n2]; 
 for (i = 0; i < m1; i++) 
 { 
  for (j = 0; j < n2; j++) 
  { 
   res[i][j] = 0; 
   for (x = 0; x < m2; x++) 
   { 
    *(*(res + i) + j) += *(*(mat1 + i) + x) * 
         *(*(mat2 + x) + j); 
   } 
  } 
 } 
 
 
 for (i = 0; i < m1; i++) 
 { 
  for (j = 0; j < n2; j++) 
  { 
   printf("%d ", *(*(res + i) + j)); 
  } 
  printf("\n"); 
 } 
 return 0; 
}
