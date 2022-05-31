#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>

_Static_assert(__SIZEOF_POINTER__ == 8, "");

#define BITMASK_SHL(n, shl) (((1LU << (n)) - 1) << (shl))
#define BITMASK(n) BITMASK_SHL(n, 0)

#define MAX_INPUT_SIZE (uint64_t)1e7
#define BUFF_SIZE (uint64_t)11e6

static  uint8_t S[256], _in[BUFF_SIZE], _out[BUFF_SIZE];
static uint32_t M[256], a[3 << 22], b[1 << 21];

#define fin(stop) for (ssize_t i = -1, _stop = stop; ++i < _stop;)
#define fix(start, stop, increment) for (ssize_t i = start, _stop = stop; i < _stop; i += increment)

static void init_SM() {
    fin(128)         S[i] = 1, M[i] = BITMASK( 8);
    fix(192, 224, 1) S[i] = 2, M[i] = BITMASK(16);
    fix(224, 240, 1) S[i] = 3, M[i] = BITMASK(24);
    fix(240, 248, 1) S[i] = 4, M[i] = BITMASK(32);
}

typedef struct sym_freq { uint8_t char_size; uint32_t sym, freq; } sym_freq;
static sym_freq plt[1 << 15];

static inline int cmp(const void *a, const void *b) {
    return (((const sym_freq *)a)->freq < ((const sym_freq *)b)->freq) -
           (((const sym_freq *)a)->freq > ((const sym_freq *)b)->freq);
}

static inline uint32_t* get_dp(uint8_t char_size, uint32_t c) {
    return (char_size < 4) ? a + c :
            b + ((c & BITMASK(3)) | ((c & BITMASK_SHL(6,  8)) >> 5)
                                  | ((c & BITMASK_SHL(6, 16)) >> 7)
                                  | ((c & BITMASK_SHL(6, 24)) >> 9));
}

int main(int argc, char **argv) {
    
    if (argc != 4 || !(!strcmp(argv[1], "-c") || !strcmp(argv[1], "-d"))) {
        
        printf("\n"
            
        "\tkek -c some.txt some.kek\n"
        "\tkek -d some.kek some.txt\n"
            
        "\n"); return 1;
    }
    
    FILE *inf = fopen(argv[2], "rb"), *of; struct stat instat;
    if (inf == NULL || fstat(fileno(inf), &instat) != 0) return 1;
    const uint64_t insize = instat.st_size; init_SM(); uint8_t *o;
    if (!strcmp(argv[1], "-d")) goto d;
    if (insize < 1 || insize > MAX_INPUT_SIZE) {
        puts("\n\tInput size must be between 1 and 1e7 bytes.\n"); fclose(inf); return 1;
    }
    if (fread(_in, 1, insize, inf) != insize || fclose(inf)) return 1;
    
    const uint8_t *p = _in, *const P = p + insize; uint32_t N = 0;
    
    while (p < P) {
        uint8_t char_size = S[*p]; if (char_size == 0) return 1;
        uint32_t register c = *(uint32_t *)p & M[*p];
        fix (1, char_size, 1) if ((p[i] >> 6) != 2) return 1;
        p += char_size;
        uint32_t *const dp = get_dp(char_size, c);
        if (*dp == 0) {
            if (N == (1 << 15)) return 1;
            plt[N].char_size = char_size;
            plt[N].sym = c;
            N++;
        }
        *dp += 1;
    }
    
    if (p != P) return 1;
    fin(N) plt[i].freq = *get_dp(plt[i].char_size, plt[i].sym);
    qsort(plt, N, sizeof(sym_freq), cmp);
    uint64_t tsz = 2, csz = 0;
    if (N <= 256)
        fin(N)
            tsz += plt[i].char_size, csz += plt[i].freq,
            *get_dp(plt[i].char_size, plt[i].sym) = i;
    else {
        fin(128)
            tsz += plt[i].char_size, csz += plt[i].freq,
            *get_dp(plt[i].char_size, plt[i].sym) = (i << 1) + 1;
        fix(128, N, 1)
            tsz += plt[i].char_size, csz += 2 * plt[i].freq,
            *get_dp(plt[i].char_size, plt[i].sym) = i << 1;
    }
    
    of = fopen(argv[3], "wb"); if (of == NULL) return 1;
    
    if (tsz + csz >= insize) {
        uint8_t type = 0;
        return (int)(fwrite(&type, 1, 1, of) != 1 ||
                     fwrite(_in, 1, insize, of) != insize || fclose(of));
    }
    
    o = _out, *o++ = 1, *(uint16_t *)o = N, o += 2, tsz++;
    fin(N) *(uint32_t *)o = plt[i].sym, o += plt[i].char_size;
    if (fwrite(_out, 1, tsz, of) != tsz) return 1;
    o = _out, p = _in;
    
    if (N <= 256)
        while (p < P) {
            uint8_t char_size = S[*p];
            uint32_t register c = *(uint32_t *)p & M[*p];
            p += char_size;
            *o++ = *get_dp(char_size, c);
        }
    else
        while (p < P) {
            uint8_t char_size = S[*p];
            uint32_t register c = *(uint32_t *)p & M[*p];
            p += char_size;
            const uint32_t index = *get_dp(char_size, c);
            if (index < 256)
                *o++ = index;
            else
                *(uint16_t *)o = index, o += 2;
        }
    
    return (int)(fwrite(_out, 1, csz, of) != csz || fclose(of));
    
d:  if (insize < 2 || insize > MAX_INPUT_SIZE + 1) {
        puts("\n\tInput size must be between (1 + 1) and (1e7 + 1) bytes.\n"); fclose(inf); return 1;
    }
    if (fread(_in, 1, insize, inf) != insize || fclose(inf)) return 1;
    
    const uint8_t *x = _in, *const X = x + insize; if (*x > 1) return 1;
    
    if (*x++ == 0) {
        of = fopen(argv[3], "wb"); if (of == NULL) return 1;
        return (int)(fwrite(x, 1, insize - 1, of) != insize - 1 || fclose(of));
    }
    
    uint32_t tab_size = *(uint16_t *)x; x += 2;
    if (tab_size < 1 || tab_size > (1 << 15)) return 1;
    fin(tab_size) {
        uint8_t char_size = S[*x]; if (char_size == 0) return 1;
        fix (1, char_size, 1) if ((x[i] >> 6) != 2) return 1;
        plt[i].sym = *(uint32_t *)x, x += plt[i].char_size = char_size;
    }
    if (x > X) return 1;
    
    o = (void *)a;
    
    if (tab_size <= 256)
        while (x < X) {
            uint32_t register index = *x++;
            if (index >= tab_size) return 1;
            *(uint32_t *)o = plt[index].sym, o += plt[index].char_size;
        }
    else
        while (x < X) {
            uint32_t register index;
            if (*x & 1) index = *x++ >> 1; else index = *(uint16_t *)x >> 1, x += 2;
            if (index >= tab_size) return 1;
            *(uint32_t *)o = plt[index].sym, o += plt[index].char_size;
        }
    
    uint64_t outsize = o - (uint8_t *)a;
    if (outsize == 0 || x != X) return 1;
    of = fopen(argv[3], "wb"); if (of == NULL) return 1;
    
    return (int)(fwrite(a, 1, outsize, of) != outsize || fclose(of));
}
