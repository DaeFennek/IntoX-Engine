#pragma once

class IConditionNode
{
public:
	virtual bool ConditionReached(const class Entity* entity, class Blackboard* blackboard) const = 0;
};