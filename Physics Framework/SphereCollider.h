#pragma once
#include "Collider.h"
#include "OrientedBoxCollider.h"
class SphereCollider :
    public Collider
{
public:
    SphereCollider(Transform* p_transform, float p_radius);
    virtual bool Intersects(Collider* other) override;
protected:
    float radius;
};

