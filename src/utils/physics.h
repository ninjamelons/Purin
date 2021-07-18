#if !defined(BULLET_PHYSICS)
#define BULLET_PHYSICS

#include "btBulletDynamicsCommon.h"

#include <memory>

class Physics
{
public:
    btDynamicsWorld* _dynamicsWorld;
    Physics(/* args */);
    ~Physics();
};

Physics::Physics(/* args */)
{
    /// collision configuration contains default setup for memory , collision setup . Advanced users can create their own configuration .
    std::shared_ptr<btDefaultCollisionConfiguration> collisionConfiguration(new btDefaultCollisionConfiguration());
    
    /// use the default collision dispatcher . For parallel processing you can use a diffent dispatcher (see Extras / BulletMultiThreaded )
    std::shared_ptr<btCollisionDispatcher> dispatcher(new btCollisionDispatcher(collisionConfiguration.get()));

    /// btDbvtBroadphase is a good general purpose broadphase . You can also try out btAxis3Sweep .
    std::shared_ptr<btBroadphaseInterface> broadphase(new btDbvtBroadphase());
    
    /// the default constraint solver . For parallel processing you can use a different solver (see Extras / BulletMultiThreaded )
    std::shared_ptr<btSequentialImpulseConstraintSolver> solver(new btSequentialImpulseConstraintSolver());

    _dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher.get(), broadphase.get(), solver.get(), collisionConfiguration.get());
    
    _dynamicsWorld->setGravity( btVector3 (0 , -10 ,0) ) ;
}

Physics::~Physics()
{
    btAlignedObjectArray<btCollisionObject*> objArr
        = _dynamicsWorld->getCollisionObjectArray();
    for(int i = objArr.size() - 1; i >= 0; i--)
    {
        btCollisionObject* obj = objArr[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if(body && body->getMotionState()) {
            delete body->getMotionState();
        }
        _dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }

    delete _dynamicsWorld;
}


#endif // BULLET_PHYSICS
