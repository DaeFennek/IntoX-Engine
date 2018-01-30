#pragma once

#include "SingleChildNode.h"
#include "IConditionNode.h"

class ConditionNode : public SingleChildNode, public IConditionNode
{
public:
	ConditionNode(const std::string& name);
	virtual ~ConditionNode();
	virtual ENodeStatus Tick( Entity* entity, Blackboard* blackboard) const override;	

	ConditionNode(const ConditionNode&) = delete;		
};

