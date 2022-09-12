#include "stdafx.h"
#include "SpriteAgent.h"



// Constructors
CSpriteAgent::CSpriteAgent(float x, float y, char* pFileBitmap, Uint32 time) : CSprite(x, y, pFileBitmap, time) 
{ wanderTarget = CVector(0, 1); }

CSpriteAgent::CSpriteAgent(float x, float y, char* pFileBitmap, CColor colorKey, Uint32 time) : CSprite(x, y, pFileBitmap, colorKey, time)
{ wanderTarget = CVector(0, 1); }

CSpriteAgent::CSpriteAgent(float x, float y, float w, float h, char* pFileBitmap, Uint32 time) : CSprite(x, y, w, h, pFileBitmap, time)
{ wanderTarget = CVector(0, 1); }

CSpriteAgent::CSpriteAgent(float x, float y, float w, float h, char* pFileBitmap, CColor colorKey, Uint32 time) : CSprite(x, y, w, h, pFileBitmap, colorKey, time)
{ wanderTarget = CVector(0, 1); }

CSpriteAgent::~CSpriteAgent()  
{ }

// Behaviour Steerings


CVector CSpriteAgent::hide(CVector obstaclePos, double targetRadius, CVector targetPos)

{
	float DistanceFromBoundary = 30.0f;
	float distanceAway = targetRadius + DistanceFromBoundary;           //Hiding behaviour
	CVector toOb = Normalize(obstaclePos - targetPos);
	return (toOb * distanceAway) + obstaclePos;

}
CVector CSpriteAgent::seek(CVector targetPos, float speed)
{
	
	CVector desiredVelocity, steering; 
	desiredVelocity = targetPos  - GetPosition(); 
	desiredVelocity = Normalize(desiredVelocity) * speed; 
	steering = desiredVelocity  - GetVelocity();

	return steering;

	
}

CVector CSpriteAgent::flee(CVector targetPos, float speed)
{
	CVector desiredVelocity, steering; 
	desiredVelocity = GetPosition() - targetPos; 
	desiredVelocity = Normalize(desiredVelocity) * speed; 
	steering = desiredVelocity - GetVelocity();

	return steering;
}

float random()
{
	return ((float)rand() / (float)RAND_MAX);
}

CVector CSpriteAgent::wander(float speed, float wanderDist, float wanderRadius)
{
	CVector realTarget;
	
	wanderTarget += CVector(random() -0.5, random() -0.5);
	wanderTarget = Normalize(wanderTarget);
	realTarget = GetPosition() + Normalize(GetVelocity()) * wanderDist + wanderTarget * wanderRadius;

	return seek(realTarget, speed);


}

// Screen functions

void CSpriteAgent::wrapToScreen(int width, int height)
{
	if (GetX() < 0) SetX((float)width);
	if (GetX() > width) SetX(0);
	if (GetY() < 0) SetY((float)height);
	if (GetY() > height) SetY(0);

}
