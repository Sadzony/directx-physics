#pragma once
#include "Collider.h"
class SphereCollider;
class AABoxCollider :
    public Collider
{
public:
    AABoxCollider(Transform* p_transform, Vector3D dimensions);
    virtual bool Intersects(Collider* other) override;
    bool IntersectsBox(AABoxCollider* thisCol, AABoxCollider* other);
    bool IntersectsSphere(AABoxCollider* thisCol, SphereCollider* other);
    Vector3D dimensions;
    Vector3D extents;
};

