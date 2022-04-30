#pragma once
#include "Collider.h"
class AABoxCollider;
class SphereCollider :
    public Collider
{
public:
    SphereCollider(Transform* p_transform, float p_radius, ParticlePhysics* p_particlePhysics);
    virtual bool Intersects(Collider* other) override;
    bool IntersectsBox(SphereCollider* thisCol, AABoxCollider* other);
    bool IntersectsSphere(SphereCollider* thisCol, SphereCollider* other);
    virtual void ResolveCollision(Collider* other) override;
    void ResolveCollisionBox(SphereCollider* thisCol, AABoxCollider* other);
    void ResolveCollisionSphere(SphereCollider* thisCol, SphereCollider* other);
    float radius;
};

