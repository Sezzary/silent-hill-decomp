#include "game.h"

#include <libcd.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "bodyprog/vw_system.h"
#include "main/fsqueue.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

void func_80035338(s32 arg0, s8 arg1, u32 arg2, s32 arg3); // arg3 type assumed.
void func_8003D5B4(s8 arg0);
void func_8003D6E0(s32 arg0, s32 arg1, s32 arg2, void* arg3);

void func_80085D78(s32 arg0)
{
    if (arg0 != 0)
    {
        g_SysWork.timer_2C = 0;
        g_SysWork.field_14 = 0;
        g_SysWork.field_10++;
        return;
    }

    g_SysWork.field_28 = 0;
    g_SysWork.field_10 = 0;
    g_SysWork.timer_2C = 0;
    g_SysWork.field_14 = 0;
    g_SysWork.sysStateStep_C++;
}

void func_80085DC0(s32 arg0, s32 sysStateStep)
{
    if (arg0 != 0)
    {
        g_SysWork.field_10 = sysStateStep;
        g_SysWork.timer_2C = 0;
        g_SysWork.field_14 = 0;
    }
    else
    {
        g_SysWork.sysStateStep_C = sysStateStep;
        g_SysWork.field_28 = 0;
        g_SysWork.field_10 = 0;
        g_SysWork.timer_2C = 0;
        g_SysWork.field_14 = 0;
    }
}

void func_80085DF0()
{
    g_SysWork.timer_2C += g_DeltaTime1;

    if (g_MapOverlayHeader.func_EC() != 0 || g_SysWork.timer_2C > 4096)
    {
        g_SysWork.field_28 = 0;
        g_SysWork.field_10 = 0;
        g_SysWork.timer_2C = 0;
        g_SysWork.field_14 = 0;
        g_SysWork.sysStateStep_C++;
    }
}

void func_80085E6C(s32 arg0, s32 arg1)
{
    s32 unkTime;

    unkTime = g_SysWork.timer_2C + g_DeltaTime1;
    g_SysWork.timer_2C = unkTime;

    if (arg0 < unkTime)
    {
        func_80085D78(arg1);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80085EB8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008605C);

void func_800860B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 sysStateStep, s32 arg5)
{
    s32 ret;

    ret = func_800365B8(arg1);
    if (ret <= 0)
    {
        return;
    }
    
    if (arg0 == 0)
    {
        func_80085D78(arg5);
        return;
    }

    if (ret == 1)
    {
        func_80085DC0(arg5, arg2);
    }
    if (ret == 2)
    {
        func_80085DC0(arg5, arg3);
    }
    if (ret == 3)
    {
        func_80085DC0(arg5, sysStateStep);
    }
}

// TODO: Get rid of gotos.
void func_8008616C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 caseVar;
    s32 var0;
    s32 var1;

    if (arg0 != 2)
    {
        caseVar = arg0;
    }
    else
    {
        caseVar = g_SysWork.field_14;
    }

    switch (caseVar)
    {
        case 0:
            if (arg2 != 2)
            {
                D_800B5C30 = arg3;
            }

            if (arg1 != 0)
            {
                if (arg2 == 0)
                {
                    D_800BCD0C = 3;
                }
                else if (arg2 == 1)
                {
                    D_800BCD0C = 11;
                }
                else
                {
                    g_SysWork.field_30 = 18;

                    if (arg2 == 3)
                    {
                        g_SysWork.flags_22A4 |= 1 << 3;
                    }
                }
            }
            else if (arg2 == 0)
            {
                D_800BCD0C = 7;
            }
            else if (arg2 == 1)
            {
                D_800BCD0C = 15;
            }
            else
            {
                g_SysWork.field_30 = 22;
            }

            if (arg0 != 0)
            {
                g_SysWork.field_14++;
                break;
            }
            break;

        case 1:
            if (arg2 < 2)
            {
                if (arg1 != 0 || D_800BCD0C != caseVar)
                {
                    if (arg1 == caseVar)
                    {
                        var1 = 5;
                        var0 = D_800BCD0C & 0x7;

                        if (var1 == var0)
                        {
                            func_80085D78(arg4);
                        }
                    }
                }
                else
                {
                    goto block_32;
                }
            }
            else if (arg1 != 0 || g_SysWork.field_30 != caseVar)
            {
                if (arg1 == caseVar)
                {
                    var1 = g_SysWork.field_30;
                    var0 = 21;
                    
                    if (var1 == var0)
                    {
                        goto block_32;
                    }
                }
            }
            else
            {
block_32:
                func_80085D78(arg4);
            }
            break;
    }
}

void func_800862F8(s32 arg0, s32 arg1, s32 arg2) // 0x800862F8
{
    s32 switchVar;

    if (arg0 == 7)
    {
        switchVar = g_SysWork.field_14;
    }
    else
    {
        switchVar = arg0;
        if (switchVar == 8)
        {
            switchVar = 1;
            if (g_SysWork.field_14 == 0)
            {
                switchVar = 4;
            }
        }
    }

    switch (switchVar)
    {
        case 0:
            Fs_QueueStartReadTim(arg1, FS_BUFFER_1, &D_800A902C);

            if (arg0 != 0)
            {
                g_SysWork.field_14++;
                
                if (Fs_QueueDoThingWhenEmpty() != 0)
                {
                    func_80085D78(arg2);
                }
            }
            break;

        case 1:
            if (Fs_QueueDoThingWhenEmpty() != 0)
            {
                func_80085D78(arg2);
            }
            break;

        case 2:
            func_80031AAC(&D_800A902C);
            break;

        case 3:
            DrawSync(0);
            StoreImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(0);
            break;

        case 4:
            Fs_QueueStartReadTim(arg1, FS_BUFFER_1, &D_800A9A04);

            if (arg0 == 8)
            {
                g_SysWork.field_14 = 1;
            }
            break;

        case 5:
            func_80031AAC(&D_800A9A04);
            break;

        case 6:
            LoadImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(0);
            break;

        default:
            break;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80086470);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800865FC);

void func_800866D4(s32 arg0, s32 arg1, s32 arg2) // 0x800866D4
{
    if (g_MapOverlayHeader.func_D0(arg0, &D_800C4640, D_800C4700, arg1) == 1)
    {
        func_80085D78(arg2);
    }
}

void func_80086728(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x80086728
{
    if (g_MapOverlayHeader.func_13C(arg0, arg1, &D_800C46A0, D_800C4702, arg2) == 1)
    {
        func_80085D78(arg3);
    }
}

void func_8008677C(s32 arg0, s32 arg1, s32 arg2) // 0x8008677C
{
    g_MapOverlayHeader.func_13C(arg0, arg1, &D_800C46A0, D_800C4702, arg2);
}

void func_800867B4(s32 caseParam, s32 idx) // 0x800867B4
{
    switch (caseParam)
    {
        case 0:
            DrawSync(0);
            StoreImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(0);

            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + D_800A99B4[idx], FS_BUFFER_2, &D_800A901C);
            Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + D_800A99CC[idx], FS_BUFFER_1, &D_800A9024);

            Gfx_Init(SCREEN_WIDTH, 1);
            GsSwapDispBuff();
            Fs_QueueWaitForEmpty();
            break;

        case 1:
            Gfx_BackgroundSpriteDraw(&D_800A901C);
            break;

        case 2:
            LoadImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(0);
            Gfx_Init(SCREEN_WIDTH, 0);
            break;

        default:
            break;
    }
}

void func_800868DC(s32 idx)
{
    D_800C4710[idx] = 0;
}

s32 func_800868F4(s32 arg0, s32 arg1, s32 idx)
{
    D_800C4710[idx] += g_DeltaTime0;
    D_800C4710[idx] = (arg1 < D_800C4710[idx]) ? arg1 : D_800C4710[idx];

    return (arg0 * D_800C4710[idx]) / arg1;
}

s32 func_8008694C(s32 arg0, s16 arg1, s16 arg2, s32 arg3, s32 idx)
{
    D_800C4710[idx] += g_DeltaTime0;
    D_800C4710[idx] = (arg3 < D_800C4710[idx]) ? arg3 : D_800C4710[idx];
    return (arg0 * shRsin(arg1 + ((arg2 * D_800C4710[idx]) / arg3))) >> 12;
}

void func_800869E4(u8* arg0, u8* arg1, u16* arg2) // 0x800869E4
{
    s32 ret;

    g_SysWork.field_22A0 |= 1 << 5;

    ret = func_800365B8();
    if (ret == 1)
    {
        g_SysWork.field_28 = 0;
        g_SysWork.field_10 = 0;
        g_SysWork.timer_2C = 0;
        g_SysWork.field_14 = 0;
        g_SysWork.sysStateStep_C++;
    }
    else if (ret == NO_VALUE)
    {
        Sd_EngineCmd(arg2[*arg1]);
        *arg1 += 1;
    }
}

void Camera_SetTranslation(VECTOR3* pos, s32 xPosOffset, s32 yPosOffset, s32 zPosOffset,
                           s32 xzAccel, s32 yAccel, s32 xzSpeedMax, s32 ySpeedMax, s32 warpCamFlag) // 0x80086A94
{
    VECTOR3         posTarget;
    VC_CAM_MV_PARAM camTranslationParams;

    // Set position target.
    if (pos != NULL)
    {
        posTarget.vx = pos->vx + xPosOffset;
        posTarget.vy = pos->vy + yPosOffset;
        posTarget.vz = pos->vz + zPosOffset;
    }
    else
    {
        posTarget.vx = xPosOffset;
        posTarget.vy = yPosOffset;
        posTarget.vz = zPosOffset;
    }

    // Set acceleration on XZ plane.
    if (xzAccel == 0)
    {
        camTranslationParams.accel_xz = cam_mv_prm_user.accel_xz;
    }
    else
    {
        camTranslationParams.accel_xz = xzAccel;
    }

    // Set acceleration on Y axis.
    if (yAccel == 0)
    {
        camTranslationParams.accel_y = cam_mv_prm_user.accel_y;
    }
    else
    {
        camTranslationParams.accel_y = yAccel;
    }

    // Set max speed on XZ plane.
    if (xzSpeedMax == 0)
    {
        camTranslationParams.max_spd_xz = cam_mv_prm_user.max_spd_xz;
    }
    else
    {
        camTranslationParams.max_spd_xz = xzSpeedMax;
    }

    // Set max speed on Y axis.
    if (ySpeedMax == 0)
    {
        camTranslationParams.max_spd_y = cam_mv_prm_user.max_spd_y;
    }
    else
    {
        camTranslationParams.max_spd_y = ySpeedMax;
    }

    // Set camera position target.
    vcUserCamTarget(&posTarget, &camTranslationParams, warpCamFlag);
}

void Camera_SetRotation(VECTOR3* lookAt, s32 xLookAtOffset, s32 yLookAtOffset, s32 zLookAtOffset,
                        s32 xAngularAccel, s32 yAngularAccel, s32 xAngularSpeedMax, s32 yAngularSpeedMax, s32 warpLookAtFlag) // 0x80086B70
{
    VECTOR3           lookAtTarget;
    VC_WATCH_MV_PARAM camRotParams;

    // Set look-at target.
    if (lookAt != NULL)
    {
        lookAtTarget.vx = lookAt->vx + xLookAtOffset;
        lookAtTarget.vy = lookAt->vy + yLookAtOffset;
        lookAtTarget.vz = lookAt->vz + zLookAtOffset;
    }
    else
    {
        lookAtTarget.vx = xLookAtOffset;
        lookAtTarget.vy = yLookAtOffset;
        lookAtTarget.vz = zLookAtOffset;
    }

    // Set angular acceleration on X axis.
    if (xAngularAccel == 0)
    {
        camRotParams.ang_accel_x = deflt_watch_mv_prm.ang_accel_x;
    }
    else
    {
        camRotParams.ang_accel_x = xAngularAccel;
    }

    // Set angular acceleration on Y axis.
    if (yAngularAccel == 0)
    {
        camRotParams.ang_accel_y = deflt_watch_mv_prm.ang_accel_y;
    }
    else
    {
        camRotParams.ang_accel_y = yAngularAccel;
    }

    // Set max angular speed on X axis.
    if (xAngularSpeedMax == 0)
    {
        camRotParams.max_ang_spd_x = deflt_watch_mv_prm.max_ang_spd_x;
    }
    else
    {
        camRotParams.max_ang_spd_x = xAngularSpeedMax;
    }
    
    // Set max angular speed on Y axis.
    if (yAngularSpeedMax == 0)
    {
        camRotParams.max_ang_spd_y = deflt_watch_mv_prm.max_ang_spd_y;
    }
    else
    {
        camRotParams.max_ang_spd_y = yAngularSpeedMax;
    }

    // Set camera flags and rotation target.
    vcWorkSetFlags(0, VC_VISIBLE_CHARA_F);
    vcUserWatchTarget(&lookAtTarget, &camRotParams, warpLookAtFlag);
}

void func_80086C58(s32 arg0, s32 arg1)
{
    switch (g_SysWork.field_10)
    {
        case 0:
            func_80085EB8(0, arg0, arg1, 0);

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
            break;

        case 1:
            func_80085EB8(1, arg0, 0, 1);
            break;

        default:
            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.sysStateStep_C++;
            break;
    }
}

void func_80086D04(s32 arg0)
{
    switch (g_SysWork.field_10)
    {
        case 0:
            func_80085EB8(3, arg0, 0, 0);
            
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
            break;

        case 1:
            func_80085EB8(1, arg0, 0, 1);
            break;

        default:
            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.sysStateStep_C++;
            break;
    }
}

void func_80086DA8(s32 arg0, s32 arg1)
{
    switch (g_SysWork.field_10)
    {
        case 0:
            func_8008616C(0, 1, 0, arg1, 0);
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_800862F8(7, arg0, 1);
            break;

        default:
            func_8008616C(1, 1, 0, 0, 0);
            break;
    }
}

void func_80086E50(s32 arg0, s32 arg1, s32 arg2)
{
    switch (g_SysWork.field_10)
    {
        case 0:
            func_8008616C(0, 1, 0, arg1, 0);
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_800862F8(7, arg0, 1);
            break;

        case 2:
            func_8008616C(1, 1, 0, 0, 1);
            break;

        default:
            func_800862F8(2, 0, 0);
            func_8008616C(2, 0, 0, arg2, 0);
    }
}

void func_80086F44(s32 arg0, s32 arg1) // 0x80086F44
{
    if (g_SysWork.field_10 == 0)
    {
        func_800862F8(2, 0, 0);
        func_8008616C(2, 1, 0, arg1, 1);
        return;
    }

    func_8008616C(0, 0, 0, arg0, 0);
    g_SysWork.field_28 = 0;
    g_SysWork.field_10 = 0;
    g_SysWork.timer_2C = 0;
    g_SysWork.field_14 = 0;
    g_SysWork.sysStateStep_C++;
}

void func_80086FE8(s32 arg0, s32 arg1, s32 arg2) // 0x80086FE8
{
    s32 i;
    
    if (!(g_SysWork.flags_22A4 & (1 << 5)))
    {
        // Run through NPCs.
        for (i = 0; i < NPC_COUNT_MAX; i++)
        {
            // NPC type is >=24 or health is 0.
            if ((u32)((u8)g_SysWork.npcs_1A0[i].model_0.charaId_0 - 1) >= 24 ||
                g_SysWork.npcs_1A0[i].health_B0 <= 0)
            {
                continue;
            }

            break;
        }

        if (i != NPC_COUNT_MAX)
        {
            g_DeltaTime0 = 0;
        }
    }

    switch (g_SysWork.field_10)
    {
        case 0:
            g_MapOverlayHeader.func_C8();
            func_8005DC1C(arg1, arg2, 0x80, 0);
            
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_80085E6C(0x333, 1);
            break;
        
        case 2:
            func_800860B0(0, arg0, 0, 0, 0, 1);
            break;

        default:
            g_MapOverlayHeader.func_CC(0);

            g_SysWork.sysState_8 = 0;
            g_SysWork.timer_24 = 0;
            g_SysWork.sysStateStep_C = 0;
            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            break;
    }
}

void func_8008716C(s32 arg0, s32 arg1, s32 arg2) // 0x8008716C
{
    s32 var;

    switch (g_SysWork.field_10)
    {
        case 0:
            g_MapOverlayHeader.func_C8();
            func_8008616C(0, 1, 0, arg1, 0);
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_800862F8(7, arg0, 1);
            break;

        case 2:
            func_8008616C(1, 1, 0, 0, 1);
            break;

        case 3:
            func_800862F8(2, 0, 0);

            var = 0;
            func_8008616C(2, var, 0, arg2, 1);
            break;

        case 4:
            func_800862F8(2, 0, 0);
            if (g_ControllerPtr0->btns_new_10 & (g_GameWorkPtr1->config_0.controllerBinds_0.enter | g_GameWorkPtr1->config_0.controllerBinds_0.cancel))
            {
                g_SysWork.timer_2C = 0;
                g_SysWork.field_14 = 0;
                g_SysWork.field_10++;
            }
            break;

        case 5:
            func_800862F8(2, 0, 0);

            var = 1;
            func_8008616C(2, var, 0, arg2, 1);
            break;

        default:
            func_8008616C(0, 0, 0, arg1, 0);
            g_MapOverlayHeader.func_CC(0);

            g_SysWork.sysState_8 = 0;
            g_SysWork.timer_24 = 0;
            g_SysWork.sysStateStep_C = 0;
            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            break;
    }
}

void func_80087360(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x80087360
{
    s32 var;

    switch (g_SysWork.field_10)
    {
        case 0:
            g_MapOverlayHeader.func_C8();
            func_8008616C(0, 1, 0, arg1, 0);

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_800862F8(7, arg0, 1);
            break;

        case 2:
            func_8008616C(1, 1, 0, 0, 1);
            break;

        case 3:
            func_800862F8(2, 0, 0);

            var = 0;
            func_8008616C(2, var, 0, arg2,1);
            break;

        case 4:
            func_800862F8(2, 0, 0);
            func_800860B0(0, arg3, 0, 0, 0, 1);
            break;
        
        case 5:
            func_800862F8(2, 0, 0);

            var = 1;
            func_8008616C(2, var, 0, arg2, 1);
            break;

        default:
            func_8008616C(0, 0, 0, arg1, 0);
            g_MapOverlayHeader.func_CC(0);

            g_SysWork.sysState_8 = 0;
            g_SysWork.timer_24 = 0;
            g_SysWork.sysStateStep_C = 0;
            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            break;
    }
}

void func_80087540(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) // 0x80087540
{
    s32 var;

    switch (g_SysWork.field_10)
    {
        case 0:
            g_MapOverlayHeader.func_C8();
            func_8008616C(0, 1, 0, arg1, 0);

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_800862F8(7, arg0, 1);
            break;

        case 2:
            func_8008616C(1, 1, 0, 0, 1);
            break;

        case 3:
            func_800862F8(2, 0, 0);
            func_8008616C(2, 0, 0, arg2, 1);
            break;

        case 4:
            func_800862F8(2, 0, 0);
            
            if (arg3 != 0)
            {
                var = arg3;
                func_800860B0(0, var, 0, 0, 0, 1);
                break;
            }

            if (g_ControllerPtr0->btns_new_10 & (g_GameWorkPtr1->config_0.controllerBinds_0.enter | g_GameWorkPtr1->config_0.controllerBinds_0.cancel))
            {
                g_SysWork.timer_2C = 0;
                g_SysWork.field_14 = 0;
                g_SysWork.field_10++;
            }
            break;

        case 5:
            D_800A8E58 = 0x30;
            func_800862F8(2, 0, 0);

            var = arg4;
            func_800860B0(0, var, 0, 0, 0, 1);
            break;

        case 6:
            D_800A8E58 = 0x30;

            func_800862F8(2, 0, 0);
            func_8008616C(2, 1, 0, arg2, 1);
            break;

        default:
            func_8008616C(0, 0, 0, arg1, 0);
            g_MapOverlayHeader.func_CC(0);

            g_SysWork.sysState_8 = 0;
            g_SysWork.timer_24 = 0;
            g_SysWork.sysStateStep_C = 0;
            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            break;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800877B8);

void func_800879FC(u32 arg0, s32 arg1) // 0x800879FC
{
    s32 var0;
    s32 var1;
    s32 var2;
    s32 newBulletAdjust;
    s32 var4;

    newBulletAdjust = g_GameWork.config_0.optBulletAdjust_2D + 1;
    if ((g_SaveGamePtr->field_260 >> 28) == NO_VALUE)
    {
        var4 = 2;
        if (newBulletAdjust >= var4)
        {
            var4 = newBulletAdjust;
        }

        newBulletAdjust = var4;
    }

    switch (arg0)
    {
        case 0:
            var0 = 33;
            var1 = 1;
            var2 = 5;
            func_800877B8(var0, var1, arg1, var2);
            break;

        case 1:
            var0 = 32;
            var1 = 1;
            var2 = 6;
            func_800877B8(var0, var1, arg1, var2);
            break;

        case 2:
            var0 = 34;
            var1 = 1;
            var2 = 7;

            func_800877B8(var0, var1, arg1, var2);
            break;

        case 3:
            var0 = 192;
            var1 = newBulletAdjust * 15;
            var2 = 8;
            func_800877B8(var0, var1, arg1, var2);
            break;

        case 5:
            var0 = 194;
            var1 = newBulletAdjust * 6;
            var2 = 10;
            func_800877B8(var0, var1, arg1, var2);
            break;

        case 4:
            var0 = 193;
            var1 = newBulletAdjust * 6;
            var2 = 9;
            func_800877B8(var0, var1, arg1, var2);
            break;

        default:
            break;
    }
}

// TODO: Requires jump table.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80087AF4);

void func_80087EA8(s32 arg0)
{
    if (func_800358A8() == 0)
    {
        return;
    }
    
    func_800358DC(arg0);
}

void func_80087EDC(s32 arg0)
{
    if (func_80045B28() || Fs_QueueDoThingWhenEmpty() == 0)
    {
        return;
    }
    
    switch (g_SysWork.field_10)
    {
        case 0:
            if (func_800358A8(arg0) == 0)
            {
                g_SysWork.field_10 = 3;
                g_SysWork.timer_2C = 0;
                g_SysWork.field_14 = 0;
                return;
            }
            
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_22A0 |= 1 << 7;
            g_SysWork.field_10++;
            return;
        
        case 1:
            g_SysWork.field_22A0 |= 1 << 7;
            Sd_EngineCmd(23);
            
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
            return;
        
        case 2:
            g_SysWork.field_22A0 |= 1 << 7;
            
            if (!(func_80045BC8() & 0xFFFF))
            {
                func_800358DC(arg0);
                
                g_SysWork.timer_2C = 0;
                g_SysWork.field_14 = 0;
                g_SysWork.field_10++;
            }
            break;
        
        case 3:
            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.sysStateStep_C++;
            break;

        default:
            break;
    }
}

void func_80088028()
{
    func_80087EDC(0);
}

void func_80088048()
{
    if (func_80045B28())
    {
        return;
    }

    switch (g_SysWork.field_10)
    {
        case 0:
            func_80035E1C();
            Sd_EngineCmd(18);
            
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
            break;

        case 1:
            if (!(func_80045BC8() & 0xFFFF))
            {
                g_SysWork.field_28 = 0;
                g_SysWork.field_10 = 0;
                g_SysWork.timer_2C = 0;
                g_SysWork.field_14 = 0;
                g_SysWork.sysStateStep_C++;
            }
            break;

        default:
            break;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800880F0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800881B8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80088370);

s32 Chara_Load(s32 arg0, s8 arg1, s32 arg2, s8 arg3, s32 arg4, s32 arg5) // 0x80088C7C
{
    func_80035338(arg0 + 1, arg1, 0, arg2);
    func_8003D5B4(arg3);
    func_8003D6E0(arg1, arg0, arg4, arg5);
    return 1;
}

s32 func_80088D0C()
{
    Fs_QueueWaitForEmpty();
    func_8003D95C();
    return 1;
}

void func_80088D34(s32 idx)
{
    idx++; 
    func_800445A4(D_800A992C[idx].field_8, D_800A992C[idx].field_14);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Chara_Spawn);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80088F94);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80088FF4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089034);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089090);

void func_800890B8() // 0x800890B8
{
    func_8009E198(&g_SysWork.field_2514[0], 0);
    func_8009E310(&g_SysWork.field_2514[0], &g_SysWork.field_2514[8], 2);
    func_8009EBB8(&g_SysWork.field_2514[0], &g_SysWork.field_2514[12], 16);

    g_SysWork.field_2510 = func_8009E4F8();

    func_8009E7D8(g_SysWork.field_2510);
    func_8009E97C(g_SysWork.field_2510);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089128);

void func_800892A4(s32 idx) // 0x800892A4
{
    func_800895E4(g_SysWork.field_2514, &D_8002AC04[idx], 0x80);
}

void func_800892DC(s32 idx, s32 arg1) // 0x800892DC
{
    func_800895E4(g_SysWork.field_2514, &D_8002AC04[idx], arg1 & 0xFF, idx * sizeof(s_8002AC04));
}

void func_80089314(s32 arg0) // 0x80089314
{
    s32 var0;
    s32 var1;

    var0 = 24;
    D_800AFD05 += g_VBlanks;
    
    if (arg0 != 0)
    {
        var0 = 6;
    }
    
    if ((s32)D_800AFD05 >= var0)
    {
        var0 = func_80080514();
        if (arg0 != 0)
        {
            var1 = ((var0 * 16) >> 12) + 20;
        }
        else
        {
            var1 = ((var0 * 20) >> 12) + 60;
        }
        
        D_800AFD04 = (D_800AFD04 + var1) & 0x7F;
    }
    
    func_800892DC(0x15, (D_800AFD04 + 32) & 0xFF);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800893D0);

void func_8008944C() // 0x8008944C
{
    func_800892DC(19, 0xA0);
}

void func_80089470() // 0x80089470
{
    func_800892DC(19, 0xA0);
}

void func_80089494() // 0x80089494
{
    func_800892DC(9, 0xA0);
}

void func_800894B8(s32 arg0) // 0x800894B8
{
    func_800892DC(9, arg0 & 0xFF);
}

void func_800894DC() // 0x800894DC
{
    func_800892DC(9, 0xE0);
}

void func_80089500() // 0x80089500
{
    func_800892DC(9, 0xA0);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089524);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800895E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089644);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008973C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089840);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008989C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008992C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800899BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089A30);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089BB8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089D0C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089DF0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A058);

s32 func_8008A0CC()
{
    return 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A0D4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A0E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A270);

// TODO: Has match on decomp.me, some issues getting it to build.
/** It uses jump table, even though it matches it applies weirdly. The
address where the jump table is defined on the *.yaml file, but it
is commented so uncomment it onces we figure out how to apply this one.
*/
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A2E0);
/*u8 func_8008A2E0(s32 arg0)
{
    if (g_SysWork.field_275C > 0x100000)
    {
        switch (arg0)
        {
            case 5:
            case 25:
                return 0x12;

            case 15:
                return 15;

            case 2:
            case 12:
            case 22:
                return 13;

            default:
                break;
        }
    }

    return D_800AD4C8[arg0].field_F;
}*/

s32 func_8008A35C(s_8008A35C* arg0, s32 arg1) // 0x8008A35C
{
    s32 var;
    s32 res;

    var = arg0->field_E + arg0->field_F;
    res = 0;
    if (arg1 >= arg0->field_E)
    {
        res = (arg1 < var);
    }

    return res;
}

void func_8008A384(s_SubCharacter* chara) // 0x8008A384
{
    chara->field_3E &= ~(1 << 7);
}

void func_8008A398(s_SubCharacter* chara) // 0x8008A398
{
    chara->field_3E |= 1 << 7;
}

void func_8008A3AC(s_SubCharacter* chara) // 0x8008A3AC
{
    if (!(chara->field_3E & (1 << 7)))
    {
        chara->field_44 = 0;
        func_8008A3E0();
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A3E0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B15C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B1DC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B398);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B3E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B40C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B438);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B474);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B664);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B714);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008BF84);

void DmsHeader_FixOffsets(s_DmsHeader* header) // 0x8008C9A0
{
    s_DmsEntry* chara;

    if (header->isLoaded_0)
    {
        return;
    }

    header->isLoaded_0 = 1;

    // Add memory addr of DMS header to offsets in header.
    header->intervalPtr_8 = (u8*)header->intervalPtr_8 + (u32)header;
    header->characters_18 = (u8*)header->characters_18 + (u32)header;

    DmsEntry_FixOffsets(&header->camera_1C, header);

    for (chara = header->characters_18;
         chara < &header->characters_18[header->characterCount_1];
         chara++)
    {
        DmsEntry_FixOffsets(chara, header);
    }
}

void DmsEntry_FixOffsets(s_DmsEntry* entry, s_DmsHeader* header) // 0x8008CA44
{
    entry->keyframes_C.character = (u32)entry->keyframes_C.character + (u32)header;
    entry->svectorPtr_8 = (u32)entry->svectorPtr_8 + (u32)header;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008CA60);

void Dms_CharacterGetPosRot(VECTOR3* pos, SVECTOR* rot, char* charName, s32 time, s_DmsHeader* header) // 0x8008CA74
{
    s32 charIdx;

    charIdx = Dms_CharacterFindIndexByName(charName, header);
    if (charIdx == NO_VALUE)
    {
        // Character not found in DMS.
        Math_Vector3Zero(pos);
        Math_SVectorZero(rot);

        Gfx_DebugStringPosition(SCREEN_POSITION_X(15.75f), SCREEN_POSITION_Y(37.5f));

#ifdef DEBUG
        // Only seen in prototypes.
        Gfx_DebugStringDraw(charName);
        Gfx_DebugStringDraw(" doesn't exist in dms.");
#endif
    }
    else
    {
        Dms_CharacterGetPosRotByIndex(pos, rot, charIdx, time, header);
    }
}

s32 Dms_CharacterFindIndexByName(char* name, s_DmsHeader* header) // 0x8008CB10
{
    s32 i;

    for (i = 0; i < header->characterCount_1; i++)
    {
        if (!strncmp(name, header->characters_18[i].name_4, 4))
        {
            return i;
        }
    }

    return NO_VALUE;
}

void Dms_CharacterGetPosRotByIndex(VECTOR3* pos, SVECTOR3* rot, s32 charaIdx, s32 time, s_DmsHeader* header) // 0x8008CB90
{
    s_DmsEntry*             charaEntry;
    s32                     keyframePrev;
    s32                     keyframeNext;
    s32                     alpha;
    s_DmsKeyframeCharacter* keyframes;
    s_DmsKeyframeCharacter  curFrame;

    charaEntry = &header->characters_18[charaIdx];
    func_8008D1D0(&keyframePrev, &keyframeNext, &alpha, time, charaEntry, header);

    keyframes = charaEntry->keyframes_C.character;
    Dms_CharacterKeyframeInterpolate(&curFrame, &keyframes[keyframePrev], &keyframes[keyframeNext], alpha);

    pos->vx = FP_TO(curFrame.position_0.vx + header->origin_C.vx, Q4_SHIFT);
    pos->vy = FP_TO(curFrame.position_0.vy + header->origin_C.vy, Q4_SHIFT);
    pos->vz = FP_TO(curFrame.position_0.vz + header->origin_C.vz, Q4_SHIFT);
    rot->vx = curFrame.rotation_6.vx;
    rot->vy = curFrame.rotation_6.vy;
    rot->vz = curFrame.rotation_6.vz;
}

void Dms_CharacterKeyframeInterpolate(s_DmsKeyframeCharacter* result, s_DmsKeyframeCharacter* frame0, s_DmsKeyframeCharacter* frame1, s32 alpha) // 0x8008CC98
{
    // Low-precision lerp between positions?
    result->position_0.vx = frame0->position_0.vx + FP_MULTIPLY(frame1->position_0.vx - frame0->position_0.vx, (s64)alpha, Q12_SHIFT);
    result->position_0.vy = frame0->position_0.vy + FP_MULTIPLY(frame1->position_0.vy - frame0->position_0.vy, (s64)alpha, Q12_SHIFT);
    result->position_0.vz = frame0->position_0.vz + FP_MULTIPLY(frame1->position_0.vz - frame0->position_0.vz, (s64)alpha, Q12_SHIFT);

    // Higher-precision lerp between rotations?
    result->rotation_6.vx = Math_LerpFixed12(frame0->rotation_6.vx, frame1->rotation_6.vx, alpha);
    result->rotation_6.vy = Math_LerpFixed12(frame0->rotation_6.vy, frame1->rotation_6.vy, alpha);
    result->rotation_6.vz = Math_LerpFixed12(frame0->rotation_6.vz, frame1->rotation_6.vz, alpha);
}

s16 func_8008CDBC(s16 angle) // 0x8008CDBC
{
    return (96 * shRcos(angle / 2)) / shRsin(angle / 2);
}

s32 Dms_CameraGetTargetPos(VECTOR3* posTarget, VECTOR3* lookAtTarget, u16* arg2, s32 time, s_DmsHeader* header) // 0x8008CE1C
{
    s_DmsEntry*         camEntry;
    s32                 keyframePrev;
    s32                 keyframeNext;
    s32                 alpha;
    s_DmsKeyframeCamera curFrame;
    s32                 camProjValue;

    camEntry = &header->camera_1C;

    func_8008D1D0(&keyframePrev, &keyframeNext, &alpha, time, camEntry, header);
    camProjValue = Dms_CameraKeyframeInterpolate(&curFrame, &camEntry->keyframes_C.camera[keyframePrev], &camEntry->keyframes_C.camera[keyframeNext], alpha);

    posTarget->vx = FP_TO(curFrame.posTarget_0.vx + header->origin_C.vx, Q4_SHIFT);
    posTarget->vy = FP_TO(curFrame.posTarget_0.vy + header->origin_C.vy, Q4_SHIFT);
    posTarget->vz = FP_TO(curFrame.posTarget_0.vz + header->origin_C.vz, Q4_SHIFT);

    lookAtTarget->vx = FP_TO(curFrame.lookAtTarget_6.vx + header->origin_C.vx, Q4_SHIFT);
    lookAtTarget->vy = FP_TO(curFrame.lookAtTarget_6.vy + header->origin_C.vy, Q4_SHIFT);
    lookAtTarget->vz = FP_TO(curFrame.lookAtTarget_6.vz + header->origin_C.vz, Q4_SHIFT);

    if (arg2 != NULL)
    {
        *arg2 = curFrame.field_C[0];
    }

    // `camProjValue` comes from `curFrame.field_C[1]`, return value is passed to `vcChangeProjectionValue`.
    return camProjValue;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008CF54);

s32 Dms_CameraKeyframeInterpolate(s_DmsKeyframeCamera* result, s_DmsKeyframeCamera* frame0, s_DmsKeyframeCamera* frame1, s32 alpha) // 0x8008CFEC
{
    result->posTarget_0.vx = frame0->posTarget_0.vx + FP_MULTIPLY(frame1->posTarget_0.vx - frame0->posTarget_0.vx, (s64)alpha, Q12_SHIFT);
    result->posTarget_0.vy = frame0->posTarget_0.vy + FP_MULTIPLY(frame1->posTarget_0.vy - frame0->posTarget_0.vy, (s64)alpha, Q12_SHIFT);
    result->posTarget_0.vz = frame0->posTarget_0.vz + FP_MULTIPLY(frame1->posTarget_0.vz - frame0->posTarget_0.vz, (s64)alpha, Q12_SHIFT);

    result->lookAtTarget_6.vx = frame0->lookAtTarget_6.vx + FP_MULTIPLY(frame1->lookAtTarget_6.vx - frame0->lookAtTarget_6.vx, (s64)alpha, Q12_SHIFT);
    result->lookAtTarget_6.vy = frame0->lookAtTarget_6.vy + FP_MULTIPLY(frame1->lookAtTarget_6.vy - frame0->lookAtTarget_6.vy, (s64)alpha, Q12_SHIFT);
    result->lookAtTarget_6.vz = frame0->lookAtTarget_6.vz + FP_MULTIPLY(frame1->lookAtTarget_6.vz - frame0->lookAtTarget_6.vz, (s64)alpha, Q12_SHIFT);

    result->field_C[0] = Math_LerpFixed12(frame0->field_C[0], frame1->field_C[0], alpha);
    result->field_C[1] = frame0->field_C[1] + FP_MULTIPLY(frame1->field_C[1] - frame0->field_C[1], (s64)alpha, Q12_SHIFT);

    return result->field_C[1];
}

void func_8008D1D0(s32* keyframePrev, s32* keyframeNext, s32* alpha, s32 time, s_DmsEntry* camEntry, s_DmsHeader* header) // 0x8008D1D0
{
    s32 prevVal;
    s32 nextVal;

    prevVal = 0;
    nextVal = 0;
    
    switch (func_8008D2C4(time, header))
    {
        case 0:
            prevVal = FP_FROM(time, Q12_SHIFT);
            nextVal = prevVal + 1;
            *alpha = time & 0xFFF;
            break;

        case 1:
            prevVal = FP_FROM(time, Q12_SHIFT);
            nextVal = prevVal;
            *alpha = 0;
            break;

        case 2:
            prevVal = FP_FROM(time, Q12_SHIFT) - 1;
            nextVal = prevVal + 1;
            *alpha = (time & 0xFFF) + 0x1000;
            break;

        default:
            break;
    }

    *keyframePrev = func_8008D330(prevVal, camEntry);
    *keyframeNext = func_8008D330(nextVal, camEntry);
}

// Dms_IntervalGetStatus?
u32 func_8008D2C4(s32 time, s_DmsHeader* header)
{
    s_DmsInterval* interval;

    time = FP_FROM(time, Q12_SHIFT);

    for (interval = header->intervalPtr_8;
         interval < &header->intervalPtr_8[header->intervalCount_2];
         interval++)
    {
        if (time != ((interval->start + interval->duration) - 1))
        {
            continue;
        }

        if (interval->duration > 1)
        {
            return 2;
        }

        return 1;
    }

    return 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D330);

s32 Math_LerpFixed12(s16 from, s16 to, s32 alpha) // 0x8008D3D4
{
    // TODO: Shifts are similar to `shAngleRegulate`, but that doesn't seem to work here.
    return ((s32)(FP_MULTIPLY((((to - from) << 20) >> 20), (s64)alpha, 12) + from) << 20) >> 20;
}

void func_8008D41C() // 0x8008D41C
{
    D_800C4818.field_0 = 0;
    D_800C4818.field_1 = 0;
    D_800C4818.field_2 = 0;
    D_800C4818.field_A = 0;
}

void func_8008D438() // 0x8008D438
{
    D_800C4818.field_0 = 1;
}

void func_8008D448() // 0x8008D448
{
    D_800C4818.field_0 = 0;
}

void func_8008D454() // 0x8008D454
{
    D_800C4818.field_1 = 1;
}

void func_8008D464() // 0x8008D464
{
    D_800C4818.field_1 = 0;
}

void func_8008D470(s16 arg0, SVECTOR* rot, VECTOR3* pos, s32 arg3) // 0x8008D470
{
    s_8008E51C* ptr;
    s32 var;

    if (D_800C4818.field_0 == 0)
    {
        func_800410D8(&D_800C4818.field_C, &D_800C4818.field_1C, &D_800C4818.field_20, rot, pos);

        if ((ReadGeomScreen() >> 1) < D_800C4818.field_C.vz)
        {
            D_800C4818.field_2 = 1;
            D_800C4818.field_8 = func_8008D8C0(arg0, D_800C4818.field_C.vz, D_800C4818.field_20);
            func_8008D5A0(&D_800C4818.field_C, D_800C4818.field_20);
        }
        else
        {
            return;
        }
    }

    if (D_800C4818.field_1 == 0)
    {
        ptr = func_8008E51C(FP_FROM(pos->vx, Q8_SHIFT), FP_FROM(pos->vz, Q8_SHIFT), arg3);
        if (ptr != NULL)
        {
            func_8008E5B4();

            if (ptr->field_0 == 1)
            {
                var = FP_TO(ptr->field_2, Q8_SHIFT);
                func_8008E794(pos, D_800C4818.field_20, var);
                func_8008EA68(rot, pos, var);
            }
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D5A0);

void func_8008D78C()
{
    s32 var0;
    s32 var1;

    if (D_800C4818.field_2 == 0)
    {
        return;
    }

    D_800C4818.field_2 = 0;

    if (D_800C4818.field_0 != 0)
    {
        return;
    }

    var1 = func_8008D850();
    if (var1 != 0)
    {
        var0 = D_800C4818.field_8 - D_800C4818.field_A;
    }
    else
    {
        var0 = -D_800C4818.field_A;
    }

    D_800C4818.field_A += var0 >> 1;

    if (vcRetCamMvSmoothF() == 0)
    {
        D_800C4818.field_A = 0;
        var1 = 0;
    }

    func_8008D990(var1, D_800C4818.field_A, &D_800C4818.field_C, D_800C4818.field_1C, D_800C4818.field_20);
}

s32 func_8008D850() // 0x8008D850
{
    s16 rectX;
    RECT rect;
    s_8008D850 unk; 

    rectX = 784;
    if (g_ObjectTableIdx == 0)
    {
        rectX = 792;
    }

    rect.y = 112;
    rect.w = 2;
    rect.x = rectX;
    rect.h = 1;
    
    DrawSync(0);
    StoreImage2(&rect, &unk.field_0);
    DrawSync(0);

    return (unk.field_0 & 0x7FFF) == 0x7FFF;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D8C0);

// Large function.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D990);

void func_8008E4EC(s32 arg) // 0x8008E4EC
{
    func_80056504(arg, &D_8002B2CC, &D_800AFD9C, 1);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E51C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E5B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E794);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008EA68);

void func_8008EF18() {}

s32 Demo_SequenceAdvance(s32 incrementAmt)
{
    g_Demo_DemoId += incrementAmt;

    while (true)
    {
        // Cycle demo ID between 0 - `DEMO_FILE_COUNT_MAX` (5)
        while (g_Demo_DemoId < 0)
        {
            g_Demo_DemoId += DEMO_FILE_COUNT_MAX;
        }

        while ((u32)g_Demo_DemoId >= DEMO_FILE_COUNT_MAX)
        {
            g_Demo_DemoId -= DEMO_FILE_COUNT_MAX;
        }

        // Call optional funcptr associated with this demo.
        // If funcptr is set, returns whether demo is eligible to play, possibly based on game progress or other conditions.
        // In retail demos this pointer is always `NULL`.
        if (g_Demo_FileIds[g_Demo_DemoId].canPlayDemo_4 == NULL || g_Demo_FileIds[g_Demo_DemoId].canPlayDemo_4() == 1)
        {
            break;
        }

        // If funcptr is set and returned false, skip to next demo.
        // Direction to skip depends on sign of `incrementAmt` (forward or backward).
        if (incrementAmt >= 0)
        {
            g_Demo_DemoId++;
        }
        else
        {
            g_Demo_DemoId--;
        }
    }

    g_Demo_DemoFileIdx = g_Demo_FileIds[g_Demo_DemoId].demoFileId_0;
    g_Demo_PlayFileIdx = g_Demo_FileIds[g_Demo_DemoId].playFileId_2;
    return 1;
}

void Demo_DemoDataRead() // 0x8008F048
{
    if (g_Demo_DemoFileIdx != NO_VALUE)
    {
        Fs_QueueStartRead(g_Demo_DemoFileIdx, DEMO_WORK());
    }
}

void Demo_PlayDataRead() // 0x8008F07C
{
    Demo_SequenceAdvance(0);

    if (g_Demo_PlayFileIdx != NO_VALUE)
    {
        Fs_QueueStartRead(g_Demo_PlayFileIdx, g_Demo_PlayFileBufferPtr);
    }
}

s32 Demo_PlayFileBufferSetup() // 0x8008F0BC
{
    s32 mapOverlaySize;
    s32 playFileSize;

    // Get map overlay size used in demo.
    mapOverlaySize = Fs_GetFileSize(FILE_VIN_MAP0_S00_BIN + DEMO_WORK()->saveGame_100.mapOverlayIdx_A4);

    // Get play file size, rounded up to next 0x800-byte boundary.
    playFileSize = (Fs_GetFileSize(g_Demo_PlayFileIdx) + 0x7FF) & ~0x7FF;

    // Try placing play file buffer just before `DEMO_WORK` in memory.
    g_Demo_PlayFileBufferPtr = (void*)((s32)DEMO_WORK() - playFileSize);

    // If play file or map overlay is too large, buffer ptr may overlap with map.
    // Return 1 if buffer fits (no overlap with map overlay); otherwise, return 0.
    return ((u32)g_Demo_PlayFileBufferPtr >= (u32)(g_OvlDynamic + mapOverlaySize));
}

void Demo_DemoFileSaveGameUpdate() // 0x8008F13C
{
    g_GameWork.saveGame_30C = DEMO_WORK()->saveGame_100;
}

void Demo_GameGlobalsUpdate() // 0x8008F1A0
{
    // Backup current user config.
    g_Demo_UserConfigBackup = g_GameWork.config_0;

    // Update `Demo_RandSeed`.
    g_Demo_RandSeed = DEMO_WORK()->randSeed_7FC;

    // Replace user config with config from demo file.
    g_GameWork.config_0 = DEMO_WORK()->config_0;

    // Restore users system settings over demo values.
    g_GameWork.config_0.screenPosX_1C          = g_Demo_UserConfigBackup.screenPosX_1C;
    g_GameWork.config_0.screenPosY_1D          = g_Demo_UserConfigBackup.screenPosY_1D;
    g_GameWork.config_0.optSoundType_1E        = g_Demo_UserConfigBackup.optSoundType_1E;
    g_GameWork.config_0.optVolumeBgm_1F        = OPT_SOUND_VOLUME_MIN;                     // Disable BGM during demo.
    g_GameWork.config_0.optVolumeSe_20         = g_Demo_UserConfigBackup.optVolumeSe_20;
    g_GameWork.config_0.optVibrationEnabled_21 = OPT_VIBRATION_DISABLED;                   // Disable vibration during demo.
    g_GameWork.config_0.optBrightness_22       = g_Demo_UserConfigBackup.optBrightness_22;

    Sd_SetVolume(OPT_SOUND_VOLUME_MIN, OPT_SOUND_VOLUME_MIN, g_GameWork.config_0.optVolumeSe_20);
}

void Demo_GameGlobalsRestore() // 0x8008F2BC
{
    g_GameWork.config_0 = g_Demo_UserConfigBackup;

    Sd_SetVolume(OPT_SOUND_VOLUME_MAX, g_GameWork.config_0.optVolumeBgm_1F, g_GameWork.config_0.optVolumeSe_20);
}

void Demo_GameRandSeedUpdate() // 0x8008F33C
{
    g_Demo_PrevRandSeed = Rng_GetSeed();
    Rng_SetSeed(g_Demo_RandSeed);
}

void Demo_GameRandSeedRestore() // 0x8008F370
{
    Rng_SetSeed(g_Demo_PrevRandSeed);
}

void Demo_Start() // 0x8008F398
{
    D_800AFDEC = 1;
    g_SysWork.flags_22A4 |= 1 << 1;

    Demo_GameGlobalsUpdate();
    Demo_GameRandSeedUpdate();

    g_GameWork.field_5A8 = 1;
    g_GameWork.field_5AC = 1;
}

void Demo_Stop() // 0x8008f3f0
{
    D_800AFDEC = 0;
    g_SysWork.flags_22A4 &= ~(1 << 1);

    Demo_GameGlobalsRestore(-3);
    Demo_GameRandSeedRestore();
}

s32 func_8008F434(s32 arg0)
{
    s32 caseVar = arg0 & ~1;

    switch (caseVar)
    {
        case 2:
        case 3:
        case 4:
        case 5:
        case 10:
        case 11:
        case 12:
        case 13:
            return 0;

        default:
            break;
    }

    return 1;
}

s32 func_8008F470(s32 caseArg)
{
    switch (caseArg)
    {
        case 11:
            if (g_SysWork.sysState_8 == SysState_GameOver)
            {
                return -1;
            }
            else if (g_GameWork.gameStatePrev_590 == GameState_Unk10)
            {
                return -1;
            }

        case 12:
        case 13:
        case 14:
        case 15:
            return 1;

        case 18:
            return 1;

        default:
            break;
    }

    return 0;
}

void Demo_ExitDemo() // 0x8008F4E4
{
    D_800A9768 = 0xEA24;
    g_Demo_CurFrameData = NULL;
    g_Demo_DemoStep = 0;
    g_SysWork.flags_22A4 |= 1 << 8;
}

void func_8008F518() {}

s32 func_8008F520()
{
    return 0;
}

void Demo_DemoRandSeedBackup() // 0x8008F528
{
    if (g_SysWork.flags_22A4 & (1 << 1))
    {
        g_Demo_RandSeedBackup = Rng_GetSeed();
    }
}

void Demo_DemoRandSeedRestore() // 0x8008F560
{
    if (g_SysWork.flags_22A4 & (1 << 1))
    {
        Rng_SetSeed(g_Demo_RandSeedBackup);
    }
}

void Demo_DemoRandSeedAdvance() // 0x8008F598
{
    #define SEED_OFFSET 0x3C6EF35F

    if (g_SysWork.flags_22A4 & (1 << 1))
    {
        Rng_SetSeed(g_Demo_RandSeedBackup + SEED_OFFSET);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_Update);

// TODO: Move this to header if any other funcs have same code.
static inline void ControllerData_Reset(s_ControllerData* controller, u16 btns)
{
    *(u16*)&controller->analogPad_0.status  = 0x7300;
    controller->analogPad_0.digitalButtons  = btns;
    *(u32*)&controller->analogPad_0.right_x = 0x80808080;
}

s32 Demo_ControllerDataUpdate() // 0x8008F7CC
{
    u32 btns;

    if (!(g_SysWork.flags_22A4 & (1 << 1)))
    {
        return 0;
    }

    btns = g_ControllerPtr0->analogPad_0.digitalButtons;
    if (btns != 0xFFFF)
    {
        Demo_ExitDemo();
        return 1;
    }

    D_800A9768 = 0; // `Demo_FrameCnt`

    if (g_Demo_CurFrameData != NULL)
    {
        g_ControllerPtr0->analogPad_0 = g_Demo_CurFrameData->analogPad_0;
        return 1;
    }

    ControllerData_Reset(g_ControllerPtr0, btns);
    return 1;
}

s32 Demo_PresentIntervalUpdate() // 0x8008F87C
{
    g_Demo_VideoPresentInterval = 1;

    if (g_Demo_CurFrameData == NULL)
    {
        return 0;
    }

    g_Demo_VideoPresentInterval = g_Demo_CurFrameData->videoPresentInterval_9;
    return 1;
}

s32 Demo_GameRandSeedSet() // 0x8008F8A8
{
    if (!(g_SysWork.flags_22A4 & (1 << 1)))
    {
        return 1;
    }
    else if (g_Demo_CurFrameData == NULL)
    {
        Rng_SetSeed(g_Demo_RandSeed);
        return 0;
    }
    else
    {
        Rng_SetSeed(g_Demo_CurFrameData->randSeed_C);
        return 1;
    }
}

s32 func_8008F914()
{
    if (g_SysWork.flags_22A4 & (1 << 1))
    {
        return func_8004393C();
    }

    return 1;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008F94C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800904F4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80090664);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8009134C);

void func_80091380() {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80091388);

void func_80091464() {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8009146C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800914C4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8009151C);

void GameFs_StfRollBinLoad() // 0x80091778
{
    if (D_800A909C.tPage != 0)
    {
    }

    Fs_QueueStartRead(FILE_VIN_STF_ROLL_BIN, FS_BUFFER_1);

    func_800917C0(FONT24_BUFFER, 1, &D_800A909C);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800917C0);

void func_8009185C(s16 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) // 0x8009185C
{
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_4;
    s32 temp_lo_7;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_v0;
    u16 temp_t0 = 24;

    temp_t1   = arg2 << 22;
    temp_lo   = temp_t1 / (arg6 >> 2);
    temp_lo_2 = arg9 * temp_t0;
    temp_lo_4 = (arg6 + (s32)FP_MULTIPLY((s64)arg3, temp_lo_2, Q12_SHIFT)) >> 2;
    temp_lo_4 = temp_t1 / temp_lo_4;

    D_800AFE24.field_0  = 0;
    D_800AFE24.field_2  = 0;
    D_800AFE24.field_4  = 0;
    D_800AFE24.field_6  = 24;
    D_800AFE24.field_7  = 0;
    D_800AFE24.field_8  = 0x2CFFFFFF;
    D_800AFE24.field_18 = D_800AFE08.field_18;
    D_800AFE24.field_16 = D_800AFE08.field_16;
    D_800AFE24.field_14 = D_800AFE08.field_14;
    D_800AFE24.field_1C = arg3;
    D_800AFE24.field_20 = arg0;
    D_800AFE24.field_22 = arg1;
    D_800AFE24.field_24 = arg2;
    D_800AFE24.field_28 = arg4;
    D_800AFE24.field_2C = arg5;
    D_800AFE24.field_30 = arg6;
    D_800AFE24.field_34 = arg7;
    D_800AFE24.field_38 = arg8;
    D_800AFE24.field_3C = arg9;
    D_800AFE24.field_40 = FP_MULTIPLY((s64)temp_lo, arg4, Q12_SHIFT);
    D_800AFE24.field_44 = FP_MULTIPLY((s64)temp_lo_4, arg4, Q12_SHIFT);

    temp_v0             = arg4 + FP_MULTIPLY((s64)arg3, arg7, Q12_SHIFT);
    D_800AFE24.field_48 = FP_MULTIPLY((s64)temp_lo, temp_v0, Q12_SHIFT) - D_800AFE24.field_40;
    D_800AFE24.field_4C = FP_MULTIPLY((s64)temp_lo_4, temp_v0, Q12_SHIFT) - D_800AFE24.field_44;
    D_800AFE24.field_50 = FP_MULTIPLY((s64)temp_lo, arg5, Q12_SHIFT);

    temp_lo_7           = arg8 * temp_t0;
    temp_t2             = arg5 + FP_MULTIPLY((s64)arg3, temp_lo_7, Q12_SHIFT);
    D_800AFE24.field_54 = FP_MULTIPLY((s64)temp_lo_4, temp_t2, Q12_SHIFT);
}
