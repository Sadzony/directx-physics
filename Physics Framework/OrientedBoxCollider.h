#pragma once
#include "Collider.h"
#include "SphereCollider.h"
class OrientedBoxCollider :
    public Collider
{
public:
    OrientedBoxCollider(Transform* p_transform, Vector3D dimensions);
    virtual bool Intersects(Collider* other) override;
protected:
    Vector3D dimensions;
};

