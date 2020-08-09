// convpng v7.3
#include <stdint.h>
#include "SCRSPT.h"

#include <fileioc.h>
uint8_t *SCRSPT[35] = {
 (uint8_t*)0,
 (uint8_t*)246,
 (uint8_t*)752,
 (uint8_t*)817,
 (uint8_t*)1106,
 (uint8_t*)1257,
 (uint8_t*)1481,
 (uint8_t*)1550,
 (uint8_t*)1624,
 (uint8_t*)1974,
 (uint8_t*)2250,
 (uint8_t*)2611,
 (uint8_t*)2861,
 (uint8_t*)3198,
 (uint8_t*)4160,
 (uint8_t*)4681,
 (uint8_t*)5892,
 (uint8_t*)7095,
 (uint8_t*)8438,
 (uint8_t*)10209,
 (uint8_t*)13785,
 (uint8_t*)15761,
 (uint8_t*)18606,
 (uint8_t*)23195,
 (uint8_t*)26945,
 (uint8_t*)27089,
 (uint8_t*)27173,
 (uint8_t*)27257,
 (uint8_t*)27620,
 (uint8_t*)27737,
 (uint8_t*)27765,
 (uint8_t*)27796,
 (uint8_t*)27818,
 (uint8_t*)27896,
 (uint8_t*)28116,
};

bool SCRSPT_init(void) {
    unsigned int data, i;
    ti_var_t appvar;

    ti_CloseAll();

    appvar = ti_Open("SCRSPT", "r");
    data = (unsigned int)ti_GetDataPtr(appvar) - (unsigned int)SCRSPT[0];
    for (i = 0; i < SCRSPT_num; i++) {
        SCRSPT[i] += data;
    }

    ti_CloseAll();

    return (bool)appvar;
}
