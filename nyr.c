#include <stdio.h>

typedef int BOOL;
#define TRUE    1
#define FALSE   0

BOOL search(int gp, int gc, int gf, int *pp, int *cc, int *ff, int _, int k){
    gp -= pp[_], gc -= cc[_], gf -= ff[_]; _++;
    if(gp < 0 || gc < 0 || gf < 0) return FALSE;
    else if(gp == 0 && gc == 0 && gf == 0) return TRUE;
    else for(; _ < k; _++) if(search(gp, gc, gf, pp, cc, ff, _, k)) return TRUE;
    return FALSE;
}

int main(int argc, char **argv){
    int pp[20], cc[20], ff[20];
    int T, Gp, Gc, Gf, p, c, f;
    int n, i = 0, j, k;
    BOOL hope;
    scanf("%d", &T);
    for(; i < T; i++){
        scanf("%d %d %d", &Gp, &Gc, &Gf); scanf("%d", &n);
        for(j = 0, k = 0; j < n; j++){
            scanf("%d %d %d", &p, &c, &f);
            if(p > Gp || c > Gc || f > Gf) continue;
            else { pp[k] = p, cc[k] = c, ff[k] = f; k++; }
        }
        hope = FALSE;
        for(j = 0; j < k; j++) if(search(Gp, Gc, Gf, pp, cc, ff, j, k)){ hope = TRUE; break; }
        printf("Case #%d: %s\n", i + 1, (hope ? "yes" : "no"));
    }
    return 0;
}
