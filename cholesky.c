#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void displayResult ( float * b,int lignes);
void display (float ** a,float*b ,int dim );
void tri_sup(float **a, float *b, int dim) ;
void matriceB (float **a,int dim);
void getData (int * dim, float *** A, float ** b , float ** x, float ** y);
void problem (char * message);
void yyy (float **a,float *b, int dim, float * y);
void resolution (float **a, float *b, int dim,float* x, float * y)  ;
int main (){
    printf("resolution du Syteme  d' équation\n");
    //données
    int dim = 1;
    float **A = NULL, *b = NULL, *x = NULL, *y = NULL;
    getData(&dim,&A,&b,&x,&y);
    display (A, b, dim);
    // traitement

    resolution (A, b,  dim, x,  y) ;

    //resultat
        displayResult(y,dim);
    displayResult(x,dim);

    free(x);
    free(b);
    free(y);
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
void getData (int * dim, float *** A, float ** b , float ** x, float **y){
    float **M = NULL, *v = NULL, *sol = NULL, *Y =NULL;
    FILE * pf =  NULL ; // pointeur de fichier
    pf = fopen("data3.txt","r"); // ouvrir le fichier et le mode
    if (pf != NULL){
        fscanf(pf,"%d",dim);    // recuperer la dimension
        M = newMat(*dim);       // creer la matrice dinamiquement
        v = newVect (*dim);      // creer le second membre dinamiquement
        sol = newVect(*dim);      // creer  l allocation la solutoin 
        Y = newVect(*dim);
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
        for(int i = 0 ;   i < *dim ; i++){
            Y[i] = 0;         // initialiser les solution
        }
    }else{
        problem("cant open file");
        exit(2);
    }
    // renvois les address 
    *A = M;
    *b = v;
    *x = sol;
    *y = Y;
}
/*matrice B*/
void matriceB (float **a, int dim){
    for(int i = 0 ;   i < dim ; i++ ){
        for(int j = 0 ; j < i  ;j++){
            float s = 0.0;
            for(int k = 0; k < j  ;k++){
                float so = a[i][k]*a[j][k];
                printf("%f   \n",so);
                s += so;
            } 
            a[i][j] = (a[i][j]-s)/(a[j][j]);
        }         
        float s = 0.0;
        for(int k = 0; k < i ;k++){
            s += pow(a[i][k],2);
        } 
        a[i][i] = sqrt(a[i][i] - s);
        for(int j = i+1 ; j < dim  ;j++){
            a[i][j] = 0;
        } 
    }

}
/* calcul de y */
void yyy (float **a,float *b, int dim, float * y){
    for(int i = 0;   i < dim ; i++){
        float s = 0.0;
        for(int j = 0; j< dim ;j++){
            s += a[i][j] * y[j];
        } 
        y[i] = (b[i]-s)/a[i][i];
    }
}

void resolution (float **a, float *b, int dim,float* x, float * y)  {
    matriceB(a,dim);
    yyy (a,b,  dim,  y);
    for(int i = dim - 1;   0 <= i ; i--){
        float s = 0.0;
        for(int j = i+1 ; j< dim ;j++){
            s += a[j][i] * x[j];
        } 
        x[i] = (y[i] - s )/a[i][i] ;
    }
}
void display (float ** a, float * b,int dim){
    int lignes = dim ;
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < lignes; j++) {
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
