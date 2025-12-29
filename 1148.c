#include <stdio.h>
#include <string.h>

#define INFINITO 1000000000
#define MAX_CIDADES 505

int adjacencia[MAX_CIDADES][MAX_CIDADES];
int id_pais[MAX_CIDADES], total_paises;
int indice[MAX_CIDADES], link_baixo[MAX_CIDADES], na_pilha[MAX_CIDADES], pilha[MAX_CIDADES];
int contador_idx, topo_pilha;
int n_cidades, n_acordos;

int menor(int a, int b) { return a < b ? a : b; }


void encontrar_paises(int v) {
    indice[v] = link_baixo[v] = ++contador_idx;
    pilha[topo_pilha++] = v;
    na_pilha[v] = 1;

    for (int w = 1; w <= n_cidades; w++) {
        if (adjacencia[v][w] < INFINITO) {
            if (indice[w] == 0) {
                encontrar_paises(w);
                link_baixo[v] = menor(link_baixo[v], link_baixo[w]);
            } else if (na_pilha[w]) {
                link_baixo[v] = menor(link_baixo[v], indice[w]);
            }
        }
    }

    if (link_baixo[v] == indice[v]) {
        int w;
        do {
            w = pilha[--topo_pilha];
            na_pilha[w] = 0;
            id_pais[w] = total_paises;
        } while (w != v);
        total_paises++;
    }
}

int main() {
    while (scanf("%d %d", &n_cidades, &n_acordos) && (n_cidades != 0)) {
       
        for (int i = 1; i <= n_cidades; i++) {
            for (int j = 1; j <= n_cidades; j++) {
                adjacencia[i][j] = INFINITO;
            }
            adjacencia[i][i] = 0;
            indice[i] = 0; 
        }

        for (int i = 0; i < n_acordos; i++) {
            int origem, destino, horas;
            scanf("%d %d %d", &origem, &destino, &horas);
            adjacencia[origem][destino] = horas;
        }

       
        contador_idx = 0; topo_pilha = 0; total_paises = 0;
        for (int i = 1; i <= n_cidades; i++) {
            if (indice[i] == 0) encontrar_paises(i);
        }

       
        int dist_paises[total_paises][total_paises];
        for (int i = 0; i < total_paises; i++) {
            for (int j = 0; j < total_paises; j++) dist_paises[i][j] = INFINITO;
            dist_paises[i][i] = 0;
        }

       
        for (int i = 1; i <= n_cidades; i++) {
            for (int j = 1; j <= n_cidades; j++) {
                if (adjacencia[i][j] < INFINITO && id_pais[i] != id_pais[j]) {
                    int p_origem = id_pais[i], p_destino = id_pais[j];
                    if (adjacencia[i][j] < dist_paises[p_origem][p_destino]) {
                        dist_paises[p_origem][p_destino] = adjacencia[i][j];
                    }
                }
            }
        }

       
        for (int k = 0; k < total_paises; k++) {
            for (int i = 0; i < total_paises; i++) {
                if (dist_paises[i][k] == INFINITO) continue;
                for (int j = 0; j < total_paises; j++) {
                    if (dist_paises[k][j] < INFINITO && dist_paises[i][k] + dist_paises[k][j] < dist_paises[i][j]) {
                        dist_paises[i][j] = dist_paises[i][k] + dist_paises[k][j];
                    }
                }
            }
        }

        int n_consultas;
        scanf("%d", &n_consultas);
        while (n_consultas--) {
            int o, d;
            scanf("%d %d", &o, &d);
            if (id_pais[o] == id_pais[d]) {
                printf("0\n");
            } else {
                int resultado = dist_paises[id_pais[o]][id_pais[d]];
                if (resultado >= INFINITO) printf("Nao e possivel entregar a carta\n");
                else printf("%d\n", resultado);
            }
        }
        printf("\n");
    }
    return 0;
}
