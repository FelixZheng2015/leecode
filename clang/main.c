#include <stdio.h>
#include <math.h>
extern int test_dailyTemperatures();
extern void test_zero_even_odd();
extern void test_add_binary();

int main()
{
//    test_dailyTemperatures();

//    test_zero_even_odd();

//    test_add_binary();

    int ideal_hashrate_per_chip = 825 * 40 / 681;
    int low_freq_flag = ideal_hashrate_per_chip * 120 / pow(2, (0x10-10)) * 0.85;
    printf("low freq %d\n", low_freq_flag);
    return 0;
}