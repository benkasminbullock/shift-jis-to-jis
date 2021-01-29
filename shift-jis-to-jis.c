#include "shift-jis-to-jis.h"

//#define DEBUG

int
shift_jis_to_jis (const unsigned char * may_be_shift_jis,
                  int * jis_first_ptr, int * jis_second_ptr)
{
    int status = 0;
    unsigned char first = may_be_shift_jis[0];
    unsigned char second = may_be_shift_jis[1];
    int jis_first = 0;
    int jis_second = 0;
    /* Check first byte is valid shift JIS. */
#ifdef DEBUG
    printf (":%X%X\n", first, second);
#endif
    if ((first >= 0x81 && first <= 0x84) || 
        (first >= 0x87 && first <= 0x9f)) {
        jis_first = 2 * (first - 0x70) - 1;
#ifdef DEBUG
        printf ("First choice: hex value is %X\n", jis_first);
#endif
        if (second >= 0x40 && second <= 0x9e) {
            jis_second = second - 31;
            if (jis_second > 95) {
                jis_second -= 1;
            }
#ifdef DEBUG
            printf ("Second is lower: hex value %X\n", jis_second);
#endif
            status = 1;
        }
        else if (second >= 0x9f && second <= 0xfc) {
            jis_second = second - 126;
            jis_first += 1;
            status = 1;
        }
        else {
#ifdef DEBUG
            printf ("Second byte not OK\n");
#endif
        }
    }
    else if (first >= 0xe0 && first <= 0xef) {
#ifdef DEBUG
        printf ("Second choice\n");
#endif
        jis_first = 2 * (first - 0xb0) - 1;
        if (second >= 0x40 && second <= 0x9e) {
#ifdef DEBUG
            printf ("Second is lower\n");
#endif
            jis_second = second - 31;
            if (jis_second > 95) {
                jis_second -= 1;
            }
            status = 1;
        }
        else if (second >= 0x9f && second <= 0xfc) {
            jis_second = second - 126;
            jis_first += 1;
            status = 1;
        }
    }
    else {
#ifdef DEBUG
        printf ("Fail on first byte\n");
#endif
    }
    * jis_first_ptr = jis_first;
    * jis_second_ptr = jis_second;
    return status;
}

