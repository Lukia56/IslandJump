#include "GoalObject.h"
#include "GoalTrigger.h"

GoalObject::GoalObject() :
	mTrigger(nullptr)
{
	mTrigger = CreateToChild<GoalTrigger>();
}

void GoalObject::Init()
{
	
}

void GoalObject::Update()
{

}
