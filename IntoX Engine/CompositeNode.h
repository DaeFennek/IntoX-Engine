#pragma once

#include "MultipleChildNode.h"


class CompositeNode : public MultipleChildNode
{
public:
	CompositeNode(const std::string& name, ENodeStatus defaultStatus);
	virtual ~CompositeNode();
	virtual ENodeStatus Tick(Entity* entity, Blackboard* blackboard) const override;

protected:	
	virtual void SaveNode(const Node* node, Blackboard* blackboard) const;
	virtual const std::vector<const Node*>::const_iterator GetNodeIterator(Blackboard* blackboard) const;
	ENodeStatus m_DefaultStatus;
};

