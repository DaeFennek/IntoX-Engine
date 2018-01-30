#pragma once

#include "Node.h"

class ActionNode : public Node
{
public:
	ActionNode(const std::string& name) : Node(name) {}
	virtual ~ActionNode() {}

	virtual ENodeStatus Tick( Entity* entity, Blackboard* blackboard) const = 0;

	ActionNode(const ActionNode&) = delete;
};

