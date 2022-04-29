#pragma once
#include "Collider.h"
class AABoxCollider;
class SphereCollider :
    public Collider
{
public:
    SphereCollider(Transform* p_transform, float p_radius);
    virtual bool Intersects(Collider* other) override;
    bool IntersectsBox(SphereCollider* thisCol, AABoxCollider* other);
    bool IntersectsSphere(SphereCollider* thisCol, SphereCollider* other);
    float radius;
};

