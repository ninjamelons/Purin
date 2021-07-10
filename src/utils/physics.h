#if !defined(BULLET_PHYSICS)
#define BULLET_PHYSICS

#include "btBulletDynamicsCommon.h"

class Physics
{
public:
    btDynamicsWorld* dynamicsWorld;
    Physics(/* args */);
    ~Physics();
};

Physics::Physics(/* args */)
{
    /// collision configuration contains default setup for memory , collision setup . Advanced users can create their own configuration .
    btDefaultCollisionConfiguration* collisionConfiguration
        = new btDefaultCollisionConfiguration () ;
    
    /// use the default collision dispatcher . For parallel processing you can use a diffent dispatcher (see Extras / BulletMultiThreaded )
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher( collisionConfiguration );

    /// btDbvtBroadphase is a good general purpose broadphase . You can also try out btAxis3Sweep .
    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
    
    /// the default constraint solver . For parallel processing you can use a different solver (see Extras / BulletMultiThreaded )
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
    
    dynamicsWorld->setGravity( btVector3 (0 , -10 ,0) ) ;
}

Physics::~Physics()
{
    btAlignedObjectArray<btCollisionObject*> objArr
        = dynamicsWorld->getCollisionObjectArray();
    for(int i = objArr.size() - 1; i >= 0; i--)
    {
        btCollisionObject* obj = objArr[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if(body && body->getMotionState()) {
            delete body->getMotionState();
        }
        dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }

    delete dynamicsWorld;
}


#endif // BULLET_PHYSICS
