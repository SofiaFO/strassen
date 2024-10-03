#include <stdio.h>
#include <stdlib.h>
#define MAX 64

typedef struct {
    int vermelho, verde, azul;
} cor;

cor** alocarMatrizes(int n){
    cor **matriz = (cor**) malloc(n * sizeof(cor*));
    for(int i = 0; i < n; i++){
        matriz[i] = (cor*) malloc(n * sizeof(cor));
    }
    return matriz;
}

void liberarMatrizes(cor **matriz, int n) {
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void leImagem(cor **imagem, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d %d %d", &imagem[i][j].vermelho, &imagem[i][j].verde, &imagem[i][j].azul);
        }
    }
}

void leFiltro(cor **filtro, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d %d %d", &filtro[i][j].vermelho, &filtro[i][j].verde, &filtro[i][j].azul);
        }
    }
}

void filtroMultiplicacaoComum(cor **mat1, cor **mat2, cor **matTemp, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matTemp[i][j].vermelho = 0;
            matTemp[i][j].verde = 0;
            matTemp[i][j].azul = 0;
            for (int k = 0; k < N; k++) {
                matTemp[i][j].vermelho += mat1[i][k].vermelho * mat2[k][j].vermelho;
                matTemp[i][j].verde += mat1[i][k].verde * mat2[k][j].verde;
                matTemp[i][j].azul += mat1[i][k].azul * mat2[k][j].azul;
            }
        }
    }
}

void divideMatriz(cor **a, cor **a11, cor **a12, cor **a21, cor **a22, int n) {
    int meio = n / 2;

    for (int i = 0; i < meio; i++) {
        for (int j = 0; j < meio; j++) {
            a11[i][j] = a[i][j];                  
            a12[i][j] = a[i][j + meio];           
            a21[i][j] = a[i + meio][j];           
            a22[i][j] = a[i + meio][j + meio];    
        }
    }
}

void somaMatriz(cor **a, cor **b, cor **c, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j].vermelho = a[i][j].vermelho + b[i][j].vermelho;
            c[i][j].verde = a[i][j].verde + b[i][j].verde;
            c[i][j].azul = a[i][j].azul + b[i][j].azul;
        }
    }
}

void subtraiMatriz(cor **a, cor **b, cor **c, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j].vermelho = a[i][j].vermelho - b[i][j].vermelho;
            c[i][j].verde = a[i][j].verde - b[i][j].verde;
            c[i][j].azul = a[i][j].azul - b[i][j].azul;
        }
    }
}

void mesclaMatrizes(cor **c, cor **c11, cor **c12, cor **c21, cor **c22, int n) {
    int meio = n / 2;

    for (int i = 0; i < meio; i++) {
        for (int j = 0; j < meio; j++) {
            c[i][j] = c11[i][j];               
            c[i][j + meio] = c12[i][j];         
            c[i + meio][j] = c21[i][j];         
            c[i + meio][j + meio] = c22[i][j];  
        }
    }
}

void multiplicaStrassen(cor **a, cor **b, cor **c, int n) {
    if (n == 1) {
        c[0][0].vermelho = a[0][0].vermelho * b[0][0].vermelho;
        c[0][0].verde = a[0][0].verde * b[0][0].verde;
        c[0][0].azul = a[0][0].azul * b[0][0].azul;
        return;
    }

    int meio = n / 2;

    cor **a11 = alocarMatrizes(meio);
    cor **a12 = alocarMatrizes(meio);
    cor **a21 = alocarMatrizes(meio);
    cor **a22 = alocarMatrizes(meio);
    cor **b11 = alocarMatrizes(meio);
    cor **b12 = alocarMatrizes(meio);
    cor **b21 = alocarMatrizes(meio);
    cor **b22 = alocarMatrizes(meio);
    cor **c11 = alocarMatrizes(meio);
    cor **c12 = alocarMatrizes(meio);
    cor **c21 = alocarMatrizes(meio);
    cor **c22 = alocarMatrizes(meio);
    cor **p1 = alocarMatrizes(meio);
    cor **p2 = alocarMatrizes(meio);
    cor **p3 = alocarMatrizes(meio);
    cor **p4 = alocarMatrizes(meio);
    cor **p5 = alocarMatrizes(meio);
    cor **p6 = alocarMatrizes(meio);
    cor **p7 = alocarMatrizes(meio);
    cor **tempa = alocarMatrizes(meio);
    cor **tempb = alocarMatrizes(meio);

    divideMatriz(a, a11, a12, a21, a22, n);
    divideMatriz(b, b11, b12, b21, b22, n);

    subtraiMatriz(b12, b22, tempb, meio);
    multiplicaStrassen(a11, tempb, p1, meio);

    somaMatriz(a11, a12, tempa, meio);
    multiplicaStrassen(tempa, b22, p2, meio);

    somaMatriz(a21, a22, tempa, meio);
    multiplicaStrassen(tempa, b11, p3, meio);

    subtraiMatriz(b21, b11, tempb, meio);
    multiplicaStrassen(a22, tempb, p4, meio);

    somaMatriz(a11, a22, tempa, meio);
    somaMatriz(b11, b22, tempb, meio);
    multiplicaStrassen(tempa, tempb, p5, meio);

    subtraiMatriz(a12, a22, tempa, meio);
    somaMatriz(b21, b22, tempb, meio);
    multiplicaStrassen(tempa, tempb, p6, meio);

    subtraiMatriz(a11, a21, tempa, meio);
    somaMatriz(b11, b12, tempb, meio);
    multiplicaStrassen(tempa, tempb, p7, meio);

    somaMatriz(p5, p4, tempa, meio);
    subtraiMatriz(tempa, p2, tempb, meio);
    somaMatriz(tempb, p6, c11, meio);

    somaMatriz(p1, p2, c12, meio);

    somaMatriz(p3, p4, c21, meio);

    somaMatriz(p1, p5, tempa, meio);
    subtraiMatriz(tempa, p3, tempb, meio);
    subtraiMatriz(tempb, p7, c22, meio);

    mesclaMatrizes(c, c11, c12, c21, c22, n);

    liberarMatrizes(a11, meio);
    liberarMatrizes(a12, meio);
    liberarMatrizes(a21, meio);
    liberarMatrizes(a22, meio);
    liberarMatrizes(b11, meio);
    liberarMatrizes(b12, meio);
    liberarMatrizes(b21, meio);
    liberarMatrizes(b22, meio);
    liberarMatrizes(c11, meio);
    liberarMatrizes(c12, meio);
    liberarMatrizes(c21, meio);
    liberarMatrizes(c22, meio);
    liberarMatrizes(p1, meio);
    liberarMatrizes(p2, meio);
    liberarMatrizes(p3, meio);
    liberarMatrizes(p4, meio);
    liberarMatrizes(p5, meio);
    liberarMatrizes(p6, meio);
    liberarMatrizes(p7, meio);
    liberarMatrizes(tempa, meio);
    liberarMatrizes(tempb, meio);
}

void imprime(char formato[4], int valMax, cor **matriz, int n) {
    printf("%s\n", formato);
    printf("%d %d\n", n, n);
    printf("%d\n", valMax);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d %d %d ", matriz[i][j].vermelho, matriz[i][j].verde, matriz[i][j].azul);
        }
        printf("\n");
    }
}

int main() {
    int n, valMax;
    char formato[4];
    
    scanf("%s", formato);  
    scanf("%d %d", &n, &n);
    scanf("%d", &valMax);

    cor **imagem = alocarMatrizes(n);
    cor **filtro = alocarMatrizes(n);
    cor **matTemp = alocarMatrizes(n);

    leImagem(imagem, n);
    leFiltro(filtro, n);

    if(n < MAX){
        filtroMultiplicacaoComum(imagem, filtro, matTemp, n);
    }else{
        multiplicaStrassen(imagem, filtro, matTemp, n);
    }

    imprime(formato, valMax, matTemp, n);

    liberarMatrizes(imagem, n);
    liberarMatrizes(filtro, n);
    liberarMatrizes(matTemp, n);

    return 0;
}
