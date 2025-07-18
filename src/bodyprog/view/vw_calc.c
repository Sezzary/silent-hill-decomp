#include "game.h"

#include "bodyprog/vw_system.h"
#include "bodyprog/math.h"

extern MATRIX D_800C3868;

void vwRenewalXZVelocityToTargetPos(s32* velo_x, s32* velo_z, VECTOR3* now_pos, VECTOR3* tgt_pos, s32 tgt_r,
                                    s32 accel, s32 total_max_spd, s32 dec_forwd_lim_spd, s32 dec_accel_side) // 0x80048F28
{
// SH2 locals
#if 0
    /* 0x1d */ float vec_xz[4];
    /* 0x1d */ float lim_spd;
    /* 0x1d */ float to_tgt_dist;
    /* 0x16 */ float to_tgt_ang_y;
    /* 0x18 */ float ang_y;
    /* 0x1d */ float spd;
    /* 0x2 */ float add_spd;
    /* 0x1d */ float cam2tgt_dir_vec[4];
    /* 0x1d */ float cam_mv_ang_y;
    /* 0x1d */ float cam2tgt_ang_y;
#endif

    SVECTOR unused; // `cam2tgt_dir_vec`?
    s16     temp_v0;
    s32     ang_y;
    s32     temp_s0;
    s32     to_tgt_ang_y;
    s32     add_spd;
    s32     temp_s1_2;
    s32     temp_s1_3;
    s32     temp_v0_2;
    s32     var_s1;

    temp_v0 = ratan2(tgt_pos->vx - now_pos->vx, tgt_pos->vz - now_pos->vz);

    // `shSinCosV` is called in SH2 while SH just calls `shRsin`/`shRcos` and does nothing with result.
    unused.vx = shRsin(temp_v0);
    unused.vy = shRcos(temp_v0);

    ratan2(*velo_x, *velo_z);

    add_spd = Math_MulFixed(accel, g_DeltaTime0, Q12_SHIFT);
    *velo_x += FP_MULTIPLY(add_spd, shRsin(temp_v0), Q12_SHIFT);
    *velo_z += FP_MULTIPLY(add_spd, shRcos(temp_v0), Q12_SHIFT);

    temp_v0_2 = Math_VectorMagnitude(*velo_x, 0, *velo_z);
    if (total_max_spd < temp_v0_2)
    {
        temp_s1_2 = temp_v0_2 - total_max_spd;
        ang_y = ratan2(*velo_x, *velo_z);
        *velo_x -= Math_MulFixed(temp_s1_2, shRsin(ang_y), Q12_SHIFT);
        *velo_z -= Math_MulFixed(temp_s1_2, shRcos(ang_y), Q12_SHIFT);
    }

    temp_s1_3    = tgt_pos->vx - now_pos->vx;
    temp_s0      = tgt_pos->vz - now_pos->vz;
    to_tgt_ang_y = ratan2(temp_s1_3, temp_s0);
    var_s1       = Math_MulFixed(dec_forwd_lim_spd, Math_VectorMagnitude(temp_s1_3, 0, temp_s0) - tgt_r, Q12_SHIFT);

    if (var_s1 < 0)
    {
        var_s1 = 0;
    }

    vwLimitOverLimVector(velo_x, velo_z, var_s1, to_tgt_ang_y);
    vwDecreaseSideOfVector(velo_x, velo_z, Math_MulFixed(dec_accel_side, g_DeltaTime0, Q12_SHIFT), var_s1 >> 1, to_tgt_ang_y);
}

void vwLimitOverLimVector(s32* vec_x, s32* vec_z, s32 lim_vec_len, s16 lim_vec_ang_y) // 0x8004914C
{
    s32 over_spd;
    s32 lim_spd_dir_x;
    s32 lim_spd_dir_z;

    lim_spd_dir_x = shRsin(lim_vec_ang_y);
    lim_spd_dir_z = shRcos(lim_vec_ang_y);

    over_spd = (Math_MulFixed(*vec_x, lim_spd_dir_x, Q12_SHIFT) + Math_MulFixed(*vec_z, lim_spd_dir_z, Q12_SHIFT)) - lim_vec_len;
    if (over_spd > 0)
    {
        *vec_x -= Math_MulFixed(over_spd, lim_spd_dir_x, Q12_SHIFT);
        *vec_z -= Math_MulFixed(over_spd, lim_spd_dir_z, Q12_SHIFT);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", vwDecreaseSideOfVector);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", vwRetNewVelocityToTargetVal);

s32 vwRetNewAngSpdToTargetAng(s32 now_ang_spd, s16 now_ang, s16 tgt_ang, s32 accel_spd, s32 total_max_ang_spd, s32 dec_val_lim_spd) // 0x80049464
{
    return vwRetNewVelocityToTargetVal(now_ang_spd, 0, ((tgt_ang - now_ang) << 20) >> 20, accel_spd, total_max_ang_spd, dec_val_lim_spd);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_800494B0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_80049530);

void vwMatrixToAngleYXZ(SVECTOR* ang, MATRIX* mat) // 0x800495D4
{
    s32 r_xz = SquareRoot0((mat->m[0][2] * mat->m[0][2]) + (mat->m[2][2] * mat->m[2][2]));
    ang->vx  = ratan2(-mat->m[1][2], r_xz);

    if (ang->vx == FP_ANGLE(90.0f))
    {
        ang->vz = 0;
        ang->vy = ratan2(mat->m[0][1], mat->m[2][1]);
    }
    else if (ang->vx == FP_ANGLE(-90.0f))
    {
        ang->vz = 0;
        ang->vy = ratan2(-mat->m[0][1], -mat->m[2][1]);
    }
    else
    {
        ang->vz = ratan2(mat->m[1][0], mat->m[1][1]);
        ang->vy = ratan2(mat->m[0][2], mat->m[2][2]);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_800496AC);

void vbSetWorldScreenMatrix(GsCOORDINATE2* coord) // 0x800497E4
{
    MATRIX work;
    VECTOR sp30;

    func_80049984(coord, &D_800C3868);
    TransposeMatrix(&D_800C3868, &work);
    MulMatrix0(&work, &GsIDMATRIX2, &VbWvsMatrix);

    VbWvsMatrix.t[2] = 0;
    VbWvsMatrix.t[1] = 0;
    VbWvsMatrix.t[0] = 0;

    GsWSMATRIX.m[0][0] = VbWvsMatrix.m[0][0];
    GsWSMATRIX.m[0][1] = VbWvsMatrix.m[0][1];
    GsWSMATRIX.m[0][2] = VbWvsMatrix.m[0][2];
    GsWSMATRIX.m[1][0] = VbWvsMatrix.m[1][0];
    GsWSMATRIX.m[1][1] = VbWvsMatrix.m[1][1];
    GsWSMATRIX.m[1][2] = VbWvsMatrix.m[1][2];
    GsWSMATRIX.m[2][0] = VbWvsMatrix.m[2][0];
    GsWSMATRIX.m[2][1] = VbWvsMatrix.m[2][1];
    GsWSMATRIX.m[2][2] = VbWvsMatrix.m[2][2];

    sp30.vx = -D_800C3868.t[0];
    sp30.vy = -D_800C3868.t[1];
    sp30.vz = -D_800C3868.t[2];
    ApplyMatrixLV(&VbWvsMatrix, &sp30, (VECTOR*)&GsWSMATRIX.t);
}

void vbSetRefView(VbRVIEW* rview) // 0x800498D8
{
    GsCOORDINATE2 sp10;
    SVECTOR       sp60;
    SVECTOR       sp68;

    sp10.flg   = 0;
    sp10.super = rview->super;
    sp68.vx    = rview->vr.vx - rview->vp.vx;
    sp68.vy    = rview->vr.vy - rview->vp.vy;
    sp68.vz    = rview->vr.vz - rview->vp.vz;
    vwVectorToAngle(&sp60, &sp68);
    func_80096E78(&sp60, &sp10.coord);

    sp10.coord.t[0] = rview->vp.vx;
    sp10.coord.t[1] = rview->vp.vy;
    sp10.coord.t[2] = rview->vp.vz;
    vbSetWorldScreenMatrix(&sp10);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_80049984);

void func_80049AF8(GsCOORDINATE2* coord, SVECTOR* vec)
{
    MATRIX mat;

    func_80049984(coord, &mat);

    mat.t[0] -= D_800C3868.t[0];
    mat.t[1] -= D_800C3868.t[1];
    mat.t[2] -= D_800C3868.t[2];

    func_800496AC(&VbWvsMatrix, &mat, vec);
}

void func_80049B6C(GsCOORDINATE2* coord, MATRIX* mat, SVECTOR* vec)
{
    func_80049984(coord, mat);
    mat->t[0] -= D_800C3868.t[0];
    mat->t[1] -= D_800C3868.t[1];
    mat->t[2] -= D_800C3868.t[2];

    func_800496AC(&VbWvsMatrix, mat, vec);
    mat->t[0] += D_800C3868.t[0];
    mat->t[1] += D_800C3868.t[1];
    mat->t[2] += D_800C3868.t[2];
}

void func_80049C2C(MATRIX* mat, s32 x, s32 y, s32 z)
{
    VECTOR input;
    VECTOR output;

    input.vx = FP_FROM(x, Q4_SHIFT);
    input.vy = FP_FROM(y, Q4_SHIFT);
    input.vz = FP_FROM(z, Q4_SHIFT);
    ApplyMatrixLV(&GsWSMATRIX, &input, &output);

    // Copies matrix fields as 32-bit words, maybe an inlined CopyMatrix func?
    *(u32*)&mat->m[0][0] = *(u32*)&GsWSMATRIX.m[0][0];
    *(u32*)&mat->m[0][2] = *(u32*)&GsWSMATRIX.m[0][2];
    *(u32*)&mat->m[1][1] = *(u32*)&GsWSMATRIX.m[1][1];
    *(u32*)&mat->m[2][0] = *(u32*)&GsWSMATRIX.m[2][0];
    mat->m[2][2]         = GsWSMATRIX.m[2][2];

    mat->t[0] = output.vx + GsWSMATRIX.t[0];
    mat->t[1] = output.vy + GsWSMATRIX.t[1];
    mat->t[2] = output.vz + GsWSMATRIX.t[2];
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_80049D04);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_80049F38);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_8004A54C);

void vwAngleToVector(SVECTOR* vec, SVECTOR* ang, s32 r) // 0x8004A66C
{
    s32 entou_r;
    
    entou_r = FP_MULTIPLY(r, shRcos(ang->vx), Q12_SHIFT);
    vec->vy = FP_MULTIPLY(-r, shRsin(ang->vx), Q12_SHIFT);
    vec->vx = FP_MULTIPLY(entou_r, shRsin(ang->vy), Q12_SHIFT);
    vec->vz = FP_MULTIPLY(entou_r, shRcos(ang->vy), Q12_SHIFT);
}

s32 vwVectorToAngle(SVECTOR* ang, SVECTOR* vec) // 0x8004A714
{
    VECTOR localVec;
    s32    ret_r;

    localVec.vx = vec->vx;
    localVec.vy = vec->vy;
    localVec.vz = vec->vz;
    Square0(&localVec, &localVec);
    ret_r = SquareRoot0(localVec.vx + localVec.vy + localVec.vz);

    ang->vx = ratan2(-vec->vy, SquareRoot0(localVec.vx + localVec.vz));
    ang->vy = ratan2(vec->vx, vec->vz);
    ang->vz = 0;
    return ret_r;
}

s32 vwOresenHokan(s32* y_ary, s32 y_suu, s32 input_x, s32 min_x, s32 max_x) // 0x8004A7C8
{
    s32 amari;    // Remainder when calculating position within interval.
    s32 kukan_w;  // Width of each interval between Y values.
    s32 kukan_no; // Index of the interval containing input_x.
    s32 output_y; // Interpolated output Y value.

    if (input_x >= max_x)
    {
        output_y = y_ary[y_suu - 1];
    }
    else
    {
        if (input_x < min_x)
        {
            output_y = y_ary[0];
        }
        else
        {
            kukan_w  = (max_x - min_x) / (y_suu - 1);
            amari    = (input_x - min_x) % kukan_w;
            kukan_no = (input_x - min_x) / kukan_w;
            if (kukan_no >= (y_suu - 1))
            {
                output_y = y_ary[y_suu - 1];
            }
            else
            {
                if (kukan_no < 0)
                {
                    output_y = y_ary[0];
                }
                else
                {
                    output_y = ((y_ary[kukan_no] * (kukan_w - amari)) + (y_ary[kukan_no + 1] * amari)) / kukan_w;
                }
            }
        }
    }

    return output_y;
}
