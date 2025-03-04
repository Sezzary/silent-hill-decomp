#include "common.h"

extern s16 D_8002BA04[5119]; // sinLut. 1.25 period.

s16 shRsin(s16 angle)
{
    s32 idx = angle & 4095;
    s16* value = (u8*)D_8002BA04 + (idx * 2);
    return *value;
    
    // Should be:
    /*s32 idx = (angle & 0xFFF);
    return D_8002BA04[idx];*/
}

s16 shRcos(s16 angle)
{
    s32 idx = angle & 4095;
    s16* value = (u8*)D_8002BA04 + (idx * 2);
    return *(value + 1024);
    
    // Should be:
    /*s32 idx = ((angle + 0x4000) & 0xFFF);
    return D_8002BA04[idx];*/
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_8009687C", shRotMatrixZ);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_8009687C", func_80096A5C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_8009687C", func_80096AA4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_8009687C", func_80096BA0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_8009687C", func_80096C4C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_8009687C", func_80096C94);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_8009687C", func_80096CE8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_8009687C", func_80096D2C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_8009687C", func_80096E78);
