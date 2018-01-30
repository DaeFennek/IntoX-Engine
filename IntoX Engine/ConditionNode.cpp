#include "ConditionNode.h"


ConditionNode::ConditionNode(const std::string& name) : SingleChildNode(name) {}

ConditionNode::~ConditionNode(){}

ENodeStatus ConditionNode::Tick( Entity* entity, Blackboard* blackboard) const
{
	if (ConditionReached(entity, blackboard))
	{
		return SingleChildNode::Tick(entity, blackboard);
	}

	return ENodeStatus::FAILURE;
}