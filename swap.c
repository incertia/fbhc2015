#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int BOOL;
#define TRUE    1
#define FALSE   0

BOOL canswap(char *s, int a, int b){ return (a != b ? (a == 0 ? (s[b] != '0') : TRUE) : TRUE); }

int swap(char *s, int a, int b){
    int r;
    if(a == b) return atoi(s);
    s[a] ^= s[b]; s[b] ^= s[a]; s[a] ^= s[b];
    r = atoi(s);
    s[a] ^= s[b]; s[b] ^= s[a]; s[a] ^= s[b];
    return r;
}

int main(int argc, char **argv){
    int T, l, max, min;
    int i = 0;
    int a, b;
    char s[100000];
    scanf("%d", &T);
    for(; i < T; i++){
        scanf("%s", s);
        l = strlen(s);
        max = min = swap(s, 0, 0);
        for(a = 0; a < l - 1; a++){
            for(b = a + 1; b < l; b++){
                if(canswap(s, a, b) && min > swap(s, a, b)) min = swap(s, a, b);
                if(canswap(s, a, b) && max < swap(s, a, b)) max = swap(s, a, b);
            }
        }
        printf("Case #%d: %d %d\n", i + 1, min, max);
    }
    return 0;
}
