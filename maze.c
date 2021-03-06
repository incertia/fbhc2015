#include <stdio.h>
#include <stdlib.h>

typedef int BOOL;
#define TRUE    1
#define FALSE   0

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct _node_t {
    int n; int t;
    BOOL visited;
    size_t d;
    struct _node_t **v;
} node_t;

typedef struct {
    int x; int y;
} pair_t;

BOOL valid(int x, int y, int m, int n);
BOOL cantravel(char mz[100][100], int x, int y, int t, int m, int n, pair_t *l, int _);
pair_t rot(char l, int t);
int h(int x, int y, int t);
size_t solve(node_t *g, pair_t start, pair_t goal);

int main(int argc, char **argv){
    int T, m, n, t, _, __;
    int i = 0, x, y;
    char mz[100][100];
    pair_t l[10000]; node_t g[40000];
    pair_t start = {0, 0}, goal = {0, 0};
    size_t res;
    scanf("%d", &T);
    for(; i < T; i++){
        t = 0;
        scanf("%d %d", &m, &n);
        for(y = 0; y < m; y++){
            scanf("%s", mz[y]);
            for(x = 0; x < n; x++)
                if(mz[y][x] == '^' || mz[y][x] == 'v' || mz[y][x] == '<' || mz[y][x] == '>'){
                    l[t].x = x, l[t].y = y; t++;
                }
        }
        for(_ = 0; _ < 4; _++)
            for(y = 0; y < m; y++)
                for(x = 0; x < n; x++){
                    g[h(x, y, _)].v = malloc(4 * sizeof(node_t *));
                    __ = 0;
                    if(cantravel(mz, x - 1, y, _ + 1, m, n, l, t)) g[h(x, y, _)].v[__++] = &g[h(x - 1, y, (_ + 1) % 4)];
                    if(cantravel(mz, x + 1, y, _ + 1, m, n, l, t)) g[h(x, y, _)].v[__++] = &g[h(x + 1, y, (_ + 1) % 4)];
                    if(cantravel(mz, x, y - 1, _ + 1, m, n, l, t)) g[h(x, y, _)].v[__++] = &g[h(x, y - 1, (_ + 1) % 4)];
                    if(cantravel(mz, x, y + 1, _ + 1, m, n, l, t)) g[h(x, y, _)].v[__++] = &g[h(x, y + 1, (_ + 1) % 4)];
                    g[h(x, y, _)].t = _; g[h(x, y, _)].n = __;
                    if(mz[y][x] == 'S') start.x = x, start.y = y;
                    if(mz[y][x] == 'G') goal.x = x, goal.y = y;
                    g[h(x, y, _)].visited = FALSE;
                    g[h(x, y, _)].d = -1;
                }
        res = solve(g, start, goal);
        if(res == -1) printf("Case #%d: impossible\n", i + 1);
        else printf("Case #%d: %lu\n", i + 1, res);
        for(_ = 0; _ < 4; _++) for(y = 0; y < m; y++) for(x = 0; x < n; x++) free(g[h(x, y, _)].v);
    }
    return 0;
}

size_t solve(node_t *g, pair_t start, pair_t goal){
    node_t *q[40000], *c;
    int a = 0, b = 0, i;
    g[h(start.x, start.y, 0)].d = 0;
    q[b++] = &g[h(start.x, start.y, 0)]; b %= 40000;
    while(a != b){
        c = q[a++]; a %= 40000;
        for(i = 0; i < c->n; i++)
            if(!c->visited && c->d + 1 < c->v[i]->d){
                c->v[i]->d = c->d + 1;
                q[b++] = c->v[i]; b %= 40000;
            }
        c->visited = TRUE;
    }
    return MIN(MIN(g[h(goal.x, goal.y, 0)].d, g[h(goal.x, goal.y, 1)].d), MIN(g[h(goal.x, goal.y, 2)].d, g[h(goal.x, goal.y, 3)].d));
}

BOOL valid(int x, int y, int m, int n){ return x >= 0 && y >= 0 && y < m && x < n; }

BOOL cantravel(char mz[100][100], int x, int y, int t, int m, int n, pair_t *l, int _){
    int a = 0, xx, yy;
    pair_t d;
    t %= 4;
    if(!valid(x, y, m, n)){
        return FALSE;
    } else if(mz[y][x] == '#' || mz[y][x] == '<' || mz[y][x] == '^' || mz[y][x] == '>' || mz[y][x] == 'v'){
        return FALSE;
    } else {
        for(; a < _; a++){
            xx = l[a].x, yy = l[a].y;
            if(xx != x && yy != y) continue;
            d = rot(mz[yy][xx], t);
            yy += d.y, xx += d.x;
            while(valid(xx, yy, m, n) && mz[yy][xx] != '#' && mz[yy][xx] != '<' && mz[yy][xx] != '^' && mz[yy][xx] != '>' && mz[yy][xx] != 'v'){
                if(xx == x && yy == y) return FALSE;
                yy += d.y, xx += d.x;
            }
        }
        return TRUE;
    }
    return FALSE;
}

pair_t rot(char l, int t){
    pair_t d = {0, 0};
    switch(l){
    case '<':
        d.x = -1, d.y = 0;
        break;
    case '^':
        d.x = 0, d.y = -1;
        break;
    case '>':
        d.x = 1, d.y = 0;
        break;
    case 'v':
        d.x = 0, d.y = 1;
        break;
    }
    while(t--){
        d.x ^= d.y; d.y ^= d.x; d.x ^= d.y;
        d.x = -d.x;
    }
    return d;
}

int h(int x, int y, int t){ return 4 * (100 * y + x) + t; }
