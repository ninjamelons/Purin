#if !defined(BULLET_PHYSICS)
#define BULLET_PHYSICS

#include "btBulletDynamicsCommon.h"

#include <memory>

class Physics
{
public:
    btDefaultCollisionConfiguration* _collisionConfiguration;
    btCollisionDispatcher* _dispatcher;
    btBroadphaseInterface* _broadphase;
    btSequentialImpulseConstraintSolver* _solver;
    btDynamicsWorld* _dynamicsWorld;

    void addRigidBody(btScalar mass, btVector3 inertia, btVector3 origin, btCollisionShape* shape);

    Physics(/* args */);
    ~Physics();
};

void Physics::addRigidBody(btScalar mass, btVector3 inertia, btVector3 origin, btCollisionShape* shape)
{
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0, -56, 0));

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    if (isDynamic)
        shape->calculateLocalInertia(mass, inertia);

    //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, inertia);
    btRigidBody* body = new btRigidBody(rbInfo);

    //add the body to the dynamics world
    _dynamicsWorld->addRigidBody(body);
}

Physics::Physics(/* args */)
{
    /// collision configuration contains default setup for memory , collision setup . Advanced users can create their own configuration .
    _collisionConfiguration = new btDefaultCollisionConfiguration();
    
    /// use the default collision dispatcher . For parallel processing you can use a diffent dispatcher (see Extras / BulletMultiThreaded )
    _dispatcher = new btCollisionDispatcher(_collisionConfiguration);

    /// btDbvtBroadphase is a good general purpose broadphase . You can also try out btAxis3Sweep .
    _broadphase = new btDbvtBroadphase();
    
    /// the default constraint solver . For parallel processing you can use a different solver (see Extras / BulletMultiThreaded )
    _solver = new btSequentialImpulseConstraintSolver();

    _dynamicsWorld = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfiguration);
    
    _dynamicsWorld->setGravity( btVector3 (0 , -10 ,0) );
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
