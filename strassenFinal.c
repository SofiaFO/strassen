#include <stdio.h>
#include <stdlib.h>
#define MAX 128

//estrutura para cada cor de cada pixel
typedef struct
{
    int vermelho, verde, azul;
} cor;

//funcao para alocar as matrizes das cores
cor **alocarMatrizes(int n)
{
    cor **matriz = (cor **)malloc(n * sizeof(cor *));
    for (int i = 0; i < n; i++)
    {
        matriz[i] = (cor *)malloc(n * sizeof(cor));
    }
    return matriz;
}

//funcao para liberar a matriz
void liberarMatrizes(cor **matriz, int n) {
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

//funcao que le a matriz da imagem
void leImagem(cor **imagem, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d %d %d", &imagem[i][j].vermelho, &imagem[i][j].verde, &imagem[i][j].azul);
        }
    }
}

//funcao que le a matriz do filtro
void leFiltro(cor **filtro, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d %d %d", &filtro[i][j].vermelho, &filtro[i][j].verde, &filtro[i][j].azul);
        }
    }
}

//funcao utilizada pelo strassen para soma das matrizes
cor **somaMatriz(cor **mat1, cor **mat2, int n)
{
    cor **matTemp = alocarMatrizes(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matTemp[i][j].vermelho = mat1[i][j].vermelho + mat2[i][j].vermelho;
            matTemp[i][j].verde = mat1[i][j].verde + mat2[i][j].verde;
            matTemp[i][j].azul = mat1[i][j].azul + mat2[i][j].azul;
        }
    }
    return matTemp;
}

//funcao utilizada pelo strassen para subtracao das matrizes
cor **subtraiMatriz(cor **mat1, cor **mat2, int n)
{
    cor **matTemp = alocarMatrizes(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matTemp[i][j].vermelho = mat1[i][j].vermelho - mat2[i][j].vermelho;
            matTemp[i][j].verde = mat1[i][j].verde - mat2[i][j].verde;
            matTemp[i][j].azul = mat1[i][j].azul - mat2[i][j].azul;
        }
    }
    return matTemp;
}

//funcao que utiliza multiplicacao normal de matrizes
cor **filtroMultiplicacaoComum(cor **mat1, cor **mat2, int n) {
    cor **matTemp = alocarMatrizes(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matTemp[i][j].vermelho = 0;
            matTemp[i][j].verde = 0;
            matTemp[i][j].azul = 0;
            for (int k = 0; k < n; k++) {
                matTemp[i][j].vermelho += mat1[i][k].vermelho * mat2[k][j].vermelho;
                matTemp[i][j].verde += mat1[i][k].verde * mat2[k][j].verde;
                matTemp[i][j].azul += mat1[i][k].azul * mat2[k][j].azul;
            }
        }
    }
    return matTemp;
}

//funcao para multiplicacao das matrizes usando o strassen
cor **multiplicacaoStrassen(cor **mat1, cor **mat2, int n) {
    //se a matriz for 1x1 multiplica diretamente
    if (n == 1) {
        cor **resultado = alocarMatrizes(1);
        resultado[0][0].vermelho = mat1[0][0].vermelho * mat2[0][0].vermelho;
        resultado[0][0].verde = mat1[0][0].verde * mat2[0][0].verde;
        resultado[0][0].azul = mat1[0][0].azul * mat2[0][0].azul;
        return resultado;
    }

    int meio = n / 2;//calcula a metade da matriz
    //aloca as submatizes
    cor **a = alocarMatrizes(meio);
    cor **b = alocarMatrizes(meio);
    cor **c = alocarMatrizes(meio);
    cor **d = alocarMatrizes(meio);
    cor **e = alocarMatrizes(meio);
    cor **f = alocarMatrizes(meio);
    cor **g = alocarMatrizes(meio);
    cor **h = alocarMatrizes(meio);
    cor **matFinal = alocarMatrizes(n);

    //divisao das matrizes em submatrizes
    for (int i = 0; i < meio; i++) {
        for (int j = 0; j < meio; j++) {
            a[i][j] = mat1[i][j];
            b[i][j] = mat1[i][meio + j];
            c[i][j] = mat1[meio + i][j];
            d[i][j] = mat1[meio + i][meio + j];
            e[i][j] = mat2[i][j];
            f[i][j] = mat2[i][meio + j];
            g[i][j] = mat2[meio + i][j];
            h[i][j] = mat2[meio + i][meio + j];
        }
    }

    cor **p1 = multiplicacaoStrassen(a, subtraiMatriz(f, h, meio), meio);
    cor **p2 = multiplicacaoStrassen(somaMatriz(a, b, meio), h, meio);
    cor **p3 = multiplicacaoStrassen(somaMatriz(c, d, meio), e, meio);
    cor **p4 = multiplicacaoStrassen(d, subtraiMatriz(g, e, meio), meio);
    cor **p5 = multiplicacaoStrassen(somaMatriz(a, d, meio), somaMatriz(e, h, meio), meio);
    cor **p6 = multiplicacaoStrassen(subtraiMatriz(b, d, meio), somaMatriz(g, h, meio), meio);
    cor **p7 = multiplicacaoStrassen(subtraiMatriz(a, c, meio), somaMatriz(e, f, meio), meio);

    //mescla p1, p2, p3, p4, p5, p6, p7 em matrizes
    for (int i = 0; i < meio; i++) {
        for (int j = 0; j < meio; j++) {
            matFinal[i][j] = subtraiMatriz(somaMatriz(somaMatriz(p5, p4, meio), p6, meio), p2, meio)[i][j];
            matFinal[i][j + meio] = somaMatriz(p1, p2, meio)[i][j];
            matFinal[meio + i][j] = somaMatriz(p3, p4, meio)[i][j];
            matFinal[meio + i][meio + j] = subtraiMatriz(subtraiMatriz(somaMatriz(p5, p1, meio), p3, meio), p7, meio)[i][j];
        }
    }

    liberarMatrizes(a, meio);
    liberarMatrizes(b, meio);
    liberarMatrizes(c, meio);
    liberarMatrizes(d, meio);
    liberarMatrizes(e, meio);
    liberarMatrizes(f, meio);
    liberarMatrizes(g, meio);
    liberarMatrizes(h, meio);
    liberarMatrizes(p1, meio);
    liberarMatrizes(p2, meio);
    liberarMatrizes(p3, meio);
    liberarMatrizes(p4, meio);
    liberarMatrizes(p5, meio);
    liberarMatrizes(p6, meio);
    liberarMatrizes(p7, meio);

    return matFinal;
}


void imprime(char formato[4], int valvalMax, cor **matriz, int n) {
    printf("%s\n", formato);
    printf("%d %d\n", n, n);
    printf("%d\n", valvalMax);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d %d %d ", matriz[i][j].vermelho, matriz[i][j].verde, matriz[i][j].azul);
        }
        printf("\n");
    }
}

int main()
{
    int n, valMax;
    char formato[4];

    scanf("%s", formato);            
    scanf("%d %d", &n, &n); 
    scanf("%d", &valMax);                 

    cor **imagem = alocarMatrizes(n);
    cor **filtro = alocarMatrizes(n);

    leImagem(imagem, n);
    leFiltro(filtro, n);

    cor **imagemFinal;

    if(n <= MAX){
        imagemFinal = filtroMultiplicacaoComum(imagem, filtro, n);
    }else{
        imagemFinal = multiplicacaoStrassen(imagem, filtro, n);
    }

    imprime(formato, valMax, imagemFinal, n);

    liberarMatrizes(imagem, n);
    liberarMatrizes(filtro, n);
    liberarMatrizes(imagemFinal, n);

    return 0;
}
