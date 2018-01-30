#pragma once

#include "CompositeNode.h"

class SequenceNode : public CompositeNode
{
public:
	SequenceNode(const std::string& name) : CompositeNode(name, ENodeStatus::SUCCESS) {}
	virtual ~SequenceNode() {}
	SequenceNode(const SequenceNode&) = delete;
};