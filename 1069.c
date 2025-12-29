#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

void processar_mina_de_diamantes() {
    
    char *texto_da_mina = (char *) malloc(1001 * sizeof(char));
    
   
    if (texto_da_mina == NULL) {
        return;
    }

    if (scanf("%s", texto_da_mina) != EOF) {
        int estoque_abertura = 0;
        int diamantes_totais = 0;

        for (int i = 0; texto_da_mina[i] != '\0'; i++) {
            if (texto_da_mina[i] == '<') {
                estoque_abertura++;
            } 
            else if (texto_da_mina[i] == '>') {
                if (estoque_abertura > 0) {
                    diamantes_totais++;
                    estoque_abertura--;
                }
            }
        }
        printf("%d\n", diamantes_totais);
    }

   
    free(texto_da_mina);
}

int main() {
    int num_casos;

    if (scanf("%d", &num_casos) != EOF) {
        while (num_casos--) {
            processar_mina_de_diamantes();
        }
    }

    return 0;
}
