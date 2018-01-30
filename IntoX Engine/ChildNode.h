#pragma once

#include "Node.h"

class ChildNode : public Node
{
public:	
	virtual Node* AddChild(Node* node) = 0;

protected:
	ChildNode(const std::string& name) : Node(name) {}
	virtual ~ChildNode() {}
};

