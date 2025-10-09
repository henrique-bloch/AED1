#include <stdio.h>
#include <stdlib.h>

int verifica_array(int arr[]) {
    int contador[10] = {0};
    
    for (int i = 0; i < 9; i++) {
        if (arr[i] < 1 || arr[i] > 9) {
            return 0;
        }
        contador[arr[i]]++;
    }
    
    for (int i = 1; i <= 9; i++) {
        if (contador[i] != 1) {
            return 0;
        }
    }
    
    return 1;
}

int verifica_linhas(int matriz[9][9]) {
    for (int i = 0; i < 9; i++) {
        if (!verifica_array(matriz[i])) {
            return 0;
        }
    }
    return 1;
}

int verifica_colunas(int matriz[9][9]) {
    int coluna[9];
    
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            coluna[i] = matriz[i][j];
        }
        if (!verifica_array(coluna)) {
            return 0;
        }
    }
    return 1;
}

int verifica_regioes(int matriz[9][9]) {
    int regiao[9];
    int index;
    
    for (int regiao_i = 0; regiao_i < 3; regiao_i++) {
        for (int regiao_j = 0; regiao_j < 3; regiao_j++) {
            index = 0;
            for (int i = regiao_i * 3; i < regiao_i * 3 + 3; i++) {
                for (int j = regiao_j * 3; j < regiao_j * 3 + 3; j++) {
                    regiao[index++] = matriz[i][j];
                }
            }
            if (!verifica_array(regiao)) {
                return 0;
            }
        }
    }
    return 1;
}

int eh_solucao_valida(int matriz[9][9]) {
    return verifica_linhas(matriz) && 
           verifica_colunas(matriz) && 
           verifica_regioes(matriz);
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int k = 1; k <= n; k++) {
        int matriz[9][9];
        
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                scanf("%d", &matriz[i][j]);
            }
        }
        
        printf("Instancia %d\n", k);
        
        if (eh_solucao_valida(matriz)) {
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
        
        if (k < n) {
            printf("\n");
        }
    }
    
    return 0;
}
