#include "Box2D_Constraint_Joint.h"
#include "World.h"

Box2D_Constraint_Joint::Box2D_Constraint_Joint(World* world, b2Body* bodyA, b2Body* bodyB) : Box2D_Constraint(world)
{
	this->bodyA = bodyA;
	this->bodyB = bodyB;
}

Box2D_Constraint_Joint::Box2D_Constraint_Joint(World* world, Box2D_Shape* bodyA, Box2D_Shape* bodyB) : Box2D_Constraint(world)
{
	this->bodyA = bodyA->getBody();
	this->bodyB = bodyB->getBody();
}

Box2D_Constraint_Joint::~Box2D_Constraint_Joint(void)
{
}

bool Box2D_Constraint_Joint::update(float timeStep)
{
	if (joint == NULL) return false;
	if (!breakable) return false;
	b2Vec2 reactionForce = joint->GetReactionForce(1 / timeStep);
	float forceModuleSq = reactionForce.LengthSquared();
	if (abs(forceModuleSq) > breakForce)
	{
		physicsWorld->DestroyJoint(joint);
		joint = NULL;
		return true;
	}
	return false;
}

void Box2D_Constraint_Joint::create(b2JointType type, b2Vec2& posA, b2Vec2& posB, float distance, bool collideAnchor, bool useAngleLimits, b2Vec2& angleLimits, bool breakable, float breakForce, float motorTorque, float motorSpeed)
{
	this->breakable = breakable;
	this->breakForce = breakForce;
	this->type = type;
	switch (type)
	{
		case b2JointType::e_distanceJoint:
			jointDef = new b2DistanceJointDef();
			((b2DistanceJointDef*)jointDef)->bodyA = bodyA;
			((b2DistanceJointDef*)jointDef)->bodyB = bodyB;
			((b2DistanceJointDef*)jointDef)->length = distance;
			((b2DistanceJointDef*)jointDef)->localAnchorA = posA;
			((b2DistanceJointDef*)jointDef)->localAnchorB = posB;
			break;
		case b2JointType::e_ropeJoint:
			jointDef = new b2RopeJointDef();
			((b2RopeJointDef*)jointDef)->bodyA = bodyA;
			((b2RopeJointDef*)jointDef)->bodyB = bodyB;
			((b2RopeJointDef*)jointDef)->maxLength = distance;
			((b2RopeJointDef*)jointDef)->localAnchorA = posA;
			((b2RopeJointDef*)jointDef)->localAnchorB = posB;
			break;
		case b2JointType::e_weldJoint:
			jointDef = new b2WeldJointDef();
			((b2WeldJointDef*)jointDef)->bodyA = bodyA;
			((b2WeldJointDef*)jointDef)->bodyB = bodyB;
			((b2WeldJointDef*)jointDef)->referenceAngle = distance;
			((b2WeldJointDef*)jointDef)->localAnchorA = posA;
			((b2WeldJointDef*)jointDef)->localAnchorB = posB;
			break;
		case b2JointType::e_revoluteJoint:
			jointDef = new b2RevoluteJointDef();
			((b2RevoluteJointDef*)jointDef)->bodyA = bodyA;
			((b2RevoluteJointDef*)jointDef)->bodyB = bodyB;
			((b2RevoluteJointDef*)jointDef)->localAnchorA = posA;
			((b2RevoluteJointDef*)jointDef)->localAnchorB = posB;
			if (useAngleLimits)
			{
				((b2RevoluteJointDef*)jointDef)->enableLimit = true;
				((b2RevoluteJointDef*)jointDef)->lowerAngle = glm::radians(angleLimits.x);
				((b2RevoluteJointDef*)jointDef)->upperAngle = glm::radians(angleLimits.y);
				((b2RevoluteJointDef*)jointDef)->referenceAngle = 0;
			}
			if (motorSpeed != 0.0f && motorTorque > 0.0f)
			{
				((b2RevoluteJointDef*)jointDef)->enableLimit = false;
				((b2RevoluteJointDef*)jointDef)->enableMotor = true;
				((b2RevoluteJointDef*)jointDef)->maxMotorTorque = motorTorque;
				((b2RevoluteJointDef*)jointDef)->motorSpeed = motorSpeed;
			}
			break;
		default:
			return;
	}
	jointDef->collideConnected = collideAnchor;
	joint = physicsWorld->CreateJoint(jointDef);
}

void Box2D_Constraint_Joint::render(void)
{

}

void Box2D_Constraint_Joint::dispose(void)
{

}

b2JointType Box2D_Constraint_Joint::getType(void)
{
	return type;
}