#pragma once

#include "SingleChildNode.h"
#include "Entity.h"
#include "Blackboard.h"

class BehaviorTree
{
public:
	BehaviorTree();
	~BehaviorTree();

	void Execute(Entity* entity, Blackboard* blackboard);
	Node* AddChild(Node* node);

	BehaviorTree(const BehaviorTree&) = delete;

private:
	SingleChildNode* m_rootNode = nullptr;
};

