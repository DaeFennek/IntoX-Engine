#pragma once

#include "SingleChildNode.h"

class InverterDecoratorNode : public SingleChildNode
{
public:
	InverterDecoratorNode(const std::string& name) : SingleChildNode(name) {}
	virtual ~InverterDecoratorNode() {}

	virtual ENodeStatus Tick( Entity* entity, Blackboard* blackboard) const override
	{
		return (SingleChildNode::Tick(entity, blackboard) == ENodeStatus::FAILURE) ? (ENodeStatus::SUCCESS) : (ENodeStatus::FAILURE);
	}

	InverterDecoratorNode(const InverterDecoratorNode&) = delete;
};

