#include <stdio.h>
#include <stdlib.h>
void displayResult ( float * b,int lignes);
void display (float ** a,float*b ,int lignes, int colonnes);
void tri_sup(float **a, float *b, int dim) ;
void gauss_pivot (float **a, float *b, int dim,float* x) ;
void getData (int * dim, float *** A, float ** b , float ** x);
void problem (char * message);
int main (){
    printf("resolution du Syteme  d' équation\n");
    //données
    int dim = 1;
    float **A = NULL, *b = NULL, *x = NULL;
    getData(&dim,&A,&b,&x);
    
    // traitement
    gauss_pivot(A,b,dim,x);

    //resultat
    displayResult(x,dim);
    free(x);
    free(b);
    for(int i = 0 ;   i < dim ; i++){
        free(A[i]);
    }
    free(A);
    return 0;
}
float *newVect (int dim){       // allouer ligne
    float* v = NULL;
    v = malloc(dim* sizeof(float));
    if(v == NULL)  problem ("Ne peut allouer un vecteur !!!");
    return v;
}
float **newMat (int dim){       // alouer colonne
    float ** A = NULL;
    A = malloc (dim * sizeof(float*));
    if(A == NULL)  problem ("Ne peut allouer un vecteur");
    for(int i = 0 ;   i < dim ; i++){
        A[i] = malloc(dim * sizeof(float));
        if(A[i] == NULL) problem ("Ne peut allouer une ligne de  matrice");
    }
    return A;
}
void problem (char * message){
    printf ("%s",message);
    exit(2);
}
void getData (int * dim, float *** A, float ** b , float ** x){
    float **M = NULL, *v = NULL, *sol = NULL;
    FILE * pf =  NULL ; // pointeur de fichier
    pf = fopen("data2.txt","r"); // ouvrir le fichier et le mode
    if (pf != NULL){
        fscanf(pf,"%d",dim);    // recuperer la dimension
        M = newMat(*dim);       // creer la matrice dinamiquement
        v = newVect (*dim);      // creer le second membre dinamiquement
        sol = newVect(*dim);      // creer  l allocation la solutoin 
        for(int i = 0 ;   i < *dim ; i++){
            for(int j = 0; j< *dim   ;j++){
                fscanf(pf,"%f",&M[i][j]);            //lecture des donnees ligen par ligne
            } 
        }
        for(int i = 0 ;   i < *dim ; i++){
            fscanf(pf,"%f",&v[i]);            //lecture 2e memebre ligen par ligne
        }
        fclose(pf);
        for(int i = 0 ;   i < *dim ; i++){
            sol[i] = 0;         // initialiser les solution
        }
    }else{
        problem("cant open file");
        exit(2);
    }
    // renvois les address 
    *A = M;
    *b = v;
    *x = sol;
}
void gauss (float **a, float *b, int dim,float* x)  {
    tri_sup(a,b,dim);
    int n = dim;
    int i = n - 1 ;
    x[n-1] =  b[n-1]/ a[n-1][n-1];
    for(i = n -2;   0 <= i ; i--){
        float k = 0.0;
        for(int j = i+1; j<= n -1  ;j++){
            k += a[i][j] * x[j];
        } 
        x[i] = (b[i] - k)/a[i][i];
    }
}
void gauss_pivot (float **a, float *b, int dim,float* x)  {
    tri_sup(a,b,dim);
    int n = dim;
    int i = n - 1 ;
    x[n-1] =  b[n-1]/ a[n-1][n-1];
    for(i = n -2;   0 <= i ; i--){
        float k = 0.0;
        for(int j = i+1; j<= n -1  ;j++){
            k += a[i][j] * x[j];
        } 
        x[i] = (b[i] - k)/a[i][i];
    }
}
void  tri_sup(float **a, float *b, int dim) {
    int n = dim;
    for (int k = 0; k <= n-1; k++) {
        for (int i = k + 1; i <= n-1 ; i++) {
            for (int j = k + 1; j <= n -1; j++) {
                a[i][j] = a[i][j] - (a[i][k] / a[k][k]) * a[k][j];
            }
            b[i] = b[i] - (a[i][k] / a[k][k]) * b[k];
            a[i][k] = 0;
        }
    }
}
void display (float ** a, float * b,int dim, int colonnes){
    int lignes = dim ;
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            printf("%.2f\t ", a[i][j]);
        }
        printf("%.2f ", b[i]);
        printf("\n");
    }
}
void displayResult ( float * b,int lignes){
    printf("les solutions du systeme : \n");
    for (int i = 0; i < lignes; i++) {
        printf("x%i: %.2f ",i+1 ,b[i]);
    }
    printf("\n");
}