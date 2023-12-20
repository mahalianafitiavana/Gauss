#include <stdio.h>
#include <stdlib.h>
#include <math.h>
float *newVect (int dim);
float **newMat (int dim);
void displayResult ( float * b,int lignes);
void display (float ** a,float * b,int dim,int * p);
void tri_sup(float **a, float *b, int dim, int * p) ;
void gauss (float **a, float *b, int dim,float* x, int * p) ;
void getData (int * dim, float *** A, float ** b , float ** x, int ** p);
void problem (char * message);
int main (){
    printf("resolution du Syteme  d' équation\n");
    //données
    int dim = 1;
    int * p = NULL;         
    float **A = NULL, *b = NULL, *x = NULL;
    getData(&dim,&A,&b,&x,&p);
    
    // traitement
    gauss(A,b,dim,x,p);

    //resultat
    display (A,b,dim,p);
    displayResult(x,dim);
    free(x);
    free(b);
    for(int i = 0 ;   i < dim ; i++){
        free(A[p[i]]);
    }
    free(A);
    free(p);
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
void getData (int * dim, float *** A, float ** b , float ** x, int ** p){
    float **M = NULL, *v = NULL, *sol = NULL;
    int * pt = NULL;
    FILE * pf =  NULL ; // pointeur de fichier
    pf = fopen("data.txt","r"); // ouvrir le fichier et le mode
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
        pt = malloc( (*dim) * sizeof(int));
        if(pt == NULL) problem ("ne peut getter les valeurs");
        for(int i = 0 ;   i < *dim ; i++){
            pt[i] = i;         // initialiser les positions de lignes
        }
    }else{
        problem("cant open file");
        exit(2);
    }
    // renvois les address 
    *A = M;
    *b = v;
    *x = sol;
    *p = pt;
}
void gauss (float **A, float *b, int dim,float* x, int * p)  {
    tri_sup(A,b,dim,p);
    int n = dim;
    int i = n - 1 ;
    x[n-1] =  b[p[n-1]]/ A[p[n-1]][n-1];
    for(i = n -2;   0 <= i ; i--){
        float k = 0.0;
        for(int j = i+1; j<= n -1  ;j++){
            k += A[p[i]][j] * x[j];
        } 
        x[i] = (b[p[i]] - k)/A[p[i]][i];
    }
}
void  tri_sup(float **A, float *b, int dim, int * p ){
    int n = dim; int lpiv ,t; float piv ; 
    for (int k = 0; k < n; k++) {
        /// Recher d un plus grand pivot ( en valeur absolue) en position lpiv
        lpiv = k; piv = fabs(A[p[k]][k]);  //en ligne p[k] au debut
        for(int i = k+1; i < n;i++){
            if(fabs( A[p[i]][k]) > piv  ){
                piv =  fabs(A[p[i]][k]) ;
                lpiv  = i;
            }
        }
        // permutation des lignes k et lpiv
        t = p[k];
        p[k] = p[lpiv];
        p[lpiv] = t ;
        //elimination
        for (int i = k + 1; i < n ; i++) {
            for (int j = k + 1; j <  n; j++) {
                A[p[i]][j]  -= ( A[p[i]][k] / A[p[k]][k]) * A[p[k]][j];
            }
            b[p[i]] -= (A[p[i]][k] / A[p[k]][k]) * b[p[k]];
            A[p[i]][k] = 0;
        }
    }
}
void display (float ** a,float * b,int dim,int * p ){
    int lignes = dim ;
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < lignes; j++) {
            printf("%.2f\t ", a[p[i]][j]);
        }
            printf("%.2f\t ", b[p[i]]);
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