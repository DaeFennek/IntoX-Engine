#pragma once

#include "SequenceNode.h"

class PrioritySequenceNode : public SequenceNode
{
public:
	PrioritySequenceNode(const std::string& name) : SequenceNode(name) {}
	~PrioritySequenceNode() {}

	const std::vector<const Node*>::const_iterator GetNodeIterator(Blackboard* blackboard) const override
	{
		return m_Nodes.begin();
	}

	virtual void SaveNode(const Node* node, Blackboard* blackboard) const override
	{
		// do nothing
	}
};

