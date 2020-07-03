#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char * addBinary(char * a, char * b){
    int aint = strtol(a, NULL, 2);
    int bint = strtol(b, NULL, 2);

    printf("aint %d, bint %d\n", aint, bint);
    int cint = aint + bint;
    int target = 0;
    int step = 1;

    while(cint > 0)
    {
        int flag = cint & 1;
        target += flag * step;
        step = 10 * step;
        cint = cint >> 1;
    }

    printf("target = %d\n", target);
    char *buf = malloc(256);
    sprintf(buf, "%d", target);
    return buf;
}

char * addBinary2(char *a, char *b)
{
    int alen = strlen(a);
    int blen = strlen(b);

    int max_len = (alen > blen) ? alen : blen;
    max_len++;

    char *pa = malloc(max_len);
    memset(pa, '0', max_len);
    char *pb = malloc(max_len);
    memset(pb, '0', max_len);

    printf("pa = %s, pb = %s, len %d\n", pa, pb, max_len);
    int tmp_max_len = max_len;
    pa[--tmp_max_len] = 0;
    for (int i=alen-1; i>=0; i--)
    {
        pa[--tmp_max_len] = a[i];
    }

    tmp_max_len = max_len;
    pb[--tmp_max_len] = 0;
    for (int i=blen-1; i>=0; i--)
    {
        pb[--tmp_max_len] = b[i];
    }

    char *target = malloc(max_len+1);   //probable the highest carry bit + body + \0
    memset(target, '0', max_len+1);

    unsigned char carry_bit = 0;
    target[max_len] = 0;
    for (int i=max_len-2; i>=0; i--)
    {
        unsigned char tar = pa[i] - '0' + pb[i] - '0' + carry_bit;
        printf("tar %d\n", tar);
        if (tar > 1){
            carry_bit = 1;
        } else {
            carry_bit = 0;
        }

        if (tar % 2 == 0) {
            target[i+1] = 0 + '0';
        } else {
            target[i+1] = 1 + '0';
        }
    }
    target[0] = carry_bit + '0';

    free(pa);
    free(pb);

    if (carry_bit > 0)
        return target;
    return &target[1];
}

void test_add_binary()
{
    char *a = "0";
    char *b = "0";

    char *p = addBinary2(a, b);
    printf("ptarget = %s\n", p);
    free(p);
}