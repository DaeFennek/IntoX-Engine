#include "RepeaterDecoratorNode.h"

RepeaterDecoratorNode::RepeaterDecoratorNode(const std::string& name) : SingleChildNode(name) {}

RepeaterDecoratorNode::~RepeaterDecoratorNode() {}

ENodeStatus RepeaterDecoratorNode::Tick(Entity * entity, Blackboard * blackboard) const
{
	assert(m_ConditionNode != nullptr);
	do
	{
		SingleChildNode::Tick(entity, blackboard);

	} while (!m_ConditionNode->ConditionReached(entity, blackboard));

	return ENodeStatus::SUCCESS;
}
