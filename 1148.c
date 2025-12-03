#include <stdio.h>
#include <string.h>

#define INF 1000000000
#define MAXN 505

int N, E;
int adj[MAXN][MAXN];
int scc[MAXN], comp_count;
int index[MAXN], lowlink[MAXN], onstack[MAXN], stack[MAXN];
int idx, top;

int min(int a, int b) { return a < b ? a : b; }

void strongconnect(int v) {
    index[v] = lowlink[v] = ++idx;
    stack[top++] = v;
    onstack[v] = 1;

    for (int w = 1; w <= N; w++) {
        if (adj[v][w] < INF) {
            if (index[w] == 0) {
                strongconnect(w);
                lowlink[v] = min(lowlink[v], lowlink[w]);
            } else if (onstack[w]) {
                lowlink[v] = min(lowlink[v], index[w]);
            }
        }
    }

    if (lowlink[v] == index[v]) {
        int w;
        do {
            w = stack[--top];
            onstack[w] = 0;
            scc[w] = comp_count;
        } while (w != v);
        comp_count++;
    }
}

void tarjan() {
    idx = 0; top = 0; comp_count = 0;
    memset(index, 0, sizeof(index));
    memset(onstack, 0, sizeof(onstack));
    for (int v = 1; v <= N; v++) {
        if (index[v] == 0) strongconnect(v);
    }
}

int main() {
    while (1) {
        scanf("%d %d", &N, &E);
        if (N == 0 && E == 0) break;

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                adj[i][j] = INF;
            }
            adj[i][i] = 0;
        }

        for (int i = 0; i < E; i++) {
            int x, y, h;
            scanf("%d %d %d", &x, &y, &h);
            if (h < adj[x][y]) adj[x][y] = h;
        }

        tarjan();

        // Construir grafo condensado
        int comp_dist[comp_count][comp_count];
        for (int i = 0; i < comp_count; i++) {
            for (int j = 0; j < comp_count; j++) {
                comp_dist[i][j] = INF;
            }
            comp_dist[i][i] = 0;
        }

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (adj[i][j] < INF && scc[i] != scc[j]) {
                    int ci = scc[i], cj = scc[j];
                    if (adj[i][j] < comp_dist[ci][cj]) {
                        comp_dist[ci][cj] = adj[i][j];
                    }
                }
            }
        }

        // Floyd-Warshall nos componentes
        for (int k = 0; k < comp_count; k++) {
            for (int i = 0; i < comp_count; i++) {
                if (comp_dist[i][k] == INF) continue;
                for (int j = 0; j < comp_count; j++) {
                    if (comp_dist[k][j] == INF) continue;
                    if (comp_dist[i][k] + comp_dist[k][j] < comp_dist[i][j]) {
                        comp_dist[i][j] = comp_dist[i][k] + comp_dist[k][j];
                    }
                }
            }
        }

        int K;
        scanf("%d", &K);
        while (K--) {
            int o, d;
            scanf("%d %d", &o, &d);
            if (scc[o] == scc[d]) {
                printf("0\n");
            } else {
                int ans = comp_dist[scc[o]][scc[d]];
                if (ans >= INF) {
                    printf("Nao e possivel entregar a carta\n");
                } else {
                    printf("%d\n", ans);
                }
            }
        }
        printf("\n");
    }
    return 0;
}
