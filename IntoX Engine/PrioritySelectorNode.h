#pragma once

#include "SelectorNode.h"

class PrioritySelectorNode : public SelectorNode
{
public:
	PrioritySelectorNode(const std::string& name) : SelectorNode(name) {};
	~PrioritySelectorNode() {}

	const std::vector<const Node*>::const_iterator GetNodeIterator(Blackboard* blackboard) const override
	{
		return m_Nodes.begin();
	}

	virtual void SaveNode(const Node* node, Blackboard* blackboard) const override
	{
		// do nothing
	}
};

