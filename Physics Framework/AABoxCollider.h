#pragma once
#include "Collider.h"
#include <algorithm>
class SphereCollider;
class AABoxCollider :
    public Collider
{
public:
    AABoxCollider(Transform* p_transform, Vector3D dimensions, ParticlePhysics* p_particlePhysics);
    virtual bool Intersects(Collider* other) override;
    bool IntersectsBox(AABoxCollider* thisCol, AABoxCollider* other);
    bool IntersectsSphere(AABoxCollider* thisCol, SphereCollider* other);
    virtual void ResolveCollision(Collider* other) override;
    void ResolveCollisionBox(AABoxCollider* thisCol, AABoxCollider* other);
    void ResolveCollisionSphere(AABoxCollider* thisCol, SphereCollider* other);
    Vector3D dimensions;
    Vector3D extents;
};

