#include <windows.h>
#include <cmath>

#include "aimbot.h"
#include "config.h"
#include "math.h"

void Aimbot::Tick(const Vec3& local, const Vec3& target, float fov, float smooth) {
    Vec3 delta = target - local;
    float dist = delta.Length();
    if (dist < 0.1f) return;

    Vec3 angles = Math::ToAngles(delta);
    float delta_yaw = Math::Normalize(angles.y - current.y);
    float delta_pitch = Math::Normalize(angles.x - current.x);

    if (std::hypot(delta_yaw, delta_pitch) > fov) return;

    current.y += delta_yaw / smooth;
    current.x += delta_pitch / smooth;
    Math::WriteViewAngles(current);
}

Vec3 Aimbot::PickBone(const Player& p, Bone bone) {
    switch (bone) {
        case Bone::Head:  return p.head;
        case Bone::Chest: return p.chest;
        default:          return p.nearest;
    }
}
