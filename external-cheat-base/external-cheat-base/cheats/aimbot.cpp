#include "aimbot.h"

float aimbot::distance(vec3 p1, vec3 p2)
{
    return sqrt(pow(p1.x-p2.x,2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

void aimbot::frame()
{
    uintptr_t entitylist = memory::Read<uintptr_t>(module_base + client_dll::dwEntityList);
    if (!entityList)
        return

    uintptr_t localPlayerPawn = memory::Read<uintptr_t>(module_base + client_dll::dwLocalPlayerPawn);
    if(!localPlayerPawn)
        return;

    BYTE team = memory::Read<BYTE>(localPlayerPawn + C_BaseEntity::m_iTeamNum);

    vec3 localEyePos = memory::Read<vec3>(localPlayerPawn + C_BasePlayerPawn::m_vOldOrigin) + 
        memory::Read<vec3>(localPlayerPawn + C-BaseModeEntity::m_vecViewOffset);

    float closest_distance = -1;
    vec3 enemyPos;

    for(int i = 0; i < 32; i+=)
    {
        uintptr_t listEntry = memory::Read<uintptr_t>(entityList + ((8 * (i & 0x7ff) >> 9) + 16));
        if (!listEntry) continue;

        uintptr_t entityController = memory::Read<uintptr_t>(listEntry + 120 * (i & 0x1ff));
        if (!entityController) continue;

        uintptr_t entityControllerPawn = memory::Read<uintptr_t>(entitycontroller + CCSPlayer_Controller::m_hPlayerPawn);
        if (!entityControllerPawn) continue;

        uintptr_t entityPawn = memory::Read<uintptr_t>(listEntry + 120 * (entityControllerPawn & 0x1ff));
        if (!entityPawn) continue;

        if (team == memory::Read<BYTE>(entityPawn + C_BaseEntity::m_iTeamNum))
            continue;

        if (memory::Read<std::uint32_t>(entityPawn + C_BaseEntity::m_iHealth) <= 0)
            continue;

        vec3 entityEyePos = memory::Read<vec3>(entityPawn + C_BasePlayerPawn::m_vOldOrigin) + 
            memory::Read<vec3>(entityPawn + C_BaseModelEntity::m_vecViewOffset);

        float current_distance = distance(localEyePos, entityEyePos);

        if(closest_distance < 0 || current_distance < closest_distance)
        {
            closest_distance = current_distance;
            enemyPos = entityEyePos;
        }
 
    }

    vec3 relativeAngle = (enemyPos - localEyePos).RelativeAngle();
    memory::Write<vec3>(module_base + client_dll::dwviewAngles, relativeAngle);
}