#pragma once

#include "CompositeNode.h"

class SelectorNode : public CompositeNode
{
public:
	SelectorNode(const std::string& name) : CompositeNode(name, ENodeStatus::FAILURE) {}
	virtual ~SelectorNode() {}
	SelectorNode(const SelectorNode&) = delete;
};

