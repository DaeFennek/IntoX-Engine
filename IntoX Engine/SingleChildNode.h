#pragma once

#include "ChildNode.h"

class SingleChildNode : public ChildNode
{
public:
	SingleChildNode(const std::string& name) : ChildNode(name) {}
	virtual ~SingleChildNode() 
	{
		delete m_Child;
		m_Child = nullptr;
	}
	
	virtual ENodeStatus Tick(Entity* entity, Blackboard* blackboard) const override
	{
		assert(m_Child != nullptr);
		return m_Child->Tick(entity, blackboard);
	}

	virtual Node* AddChild(Node * node) override
	{
		m_Child = node;
		return node;
	}

	SingleChildNode(const SingleChildNode&) = delete;
	
protected:
	Node* m_Child = nullptr;
};

