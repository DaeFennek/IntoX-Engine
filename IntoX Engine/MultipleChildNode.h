#pragma once

#include <vector>
#include "ChildNode.h"

class MultipleChildNode : public ChildNode
{
public:
	virtual ~MultipleChildNode()
	{
		for (auto it = m_Nodes.begin(); it != m_Nodes.end(); it++)
		{
			delete (*it);
		}
		m_Nodes.clear();
	}

	Node* AddChild(Node * node) override
	{
		m_Nodes.emplace_back(node);
		return node;
	}

	MultipleChildNode(const MultipleChildNode&) = delete;

protected:
	MultipleChildNode(const std::string& name) : ChildNode(name) {}	

	std::vector<const Node*> m_Nodes;
};

