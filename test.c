#include <stdio.h>
#include <stdlib.h>
#include "c-tap-test.h"
#include "shift-jis-to-jis.h"

int main()
{
    int first, second;
    const unsigned char * sj = (const unsigned char *) "\x93\xE0";
    shift_jis_to_jis (sj, &first, &second);
    TAP_TEST_EQUAL (first, 0x46);
    TAP_TEST_EQUAL (second, 0x62);

    TAP_PLAN;
    exit (0);
}
