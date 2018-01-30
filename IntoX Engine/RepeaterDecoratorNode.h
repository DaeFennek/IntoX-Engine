#pragma once

#include <assert.h>
#include "SingleChildNode.h"
#include "IConditionNode.h"

class RepeaterDecoratorNode : public SingleChildNode
{
public:
	RepeaterDecoratorNode(const std::string& name);
	virtual ~RepeaterDecoratorNode();

	virtual ENodeStatus Tick(Entity* entity, Blackboard* blackboard) const override;
	inline void SetCondition(IConditionNode* conditionNode) { m_ConditionNode = conditionNode; }
	RepeaterDecoratorNode(const RepeaterDecoratorNode&) = delete;

protected:
	IConditionNode* m_ConditionNode = nullptr;
};

