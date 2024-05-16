#pragma once 

#include "../SDk/client.h"
#include "../SDk/offset.h"

#include "../math/vector.h"
#include "../memory/memory.h"

namespace aimbot {
    inline uintptr_t module_base;
    inline uintptr_t procID;

    float distance(vec3 p1, vec3 p2);
    void frame();

    
}