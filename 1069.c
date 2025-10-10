#include <stdio.h>
#include <string.h>

int main() {
    int N;
    scanf("%d", &N);
    getchar();
    
    for(int i = 0; i < N; i++) {
        char linha[1001];
        fgets(linha, 1001, stdin);
        
        int diamantes = 0;
        int abre = 0;
        
        for(int j = 0; j < strlen(linha); j++) {
            if(linha[j] == '<') {
                abre++;
            } else if(linha[j] == '>' && abre > 0) {
                diamantes++;
                abre--;
            }
        }
        
        printf("%d\n", diamantes);
    }
    
    return 0;
}
