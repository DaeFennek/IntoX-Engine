#include "BehaviorTree.h"

BehaviorTree::BehaviorTree()
{
	m_rootNode = new SingleChildNode("rootNode");
}

BehaviorTree::~BehaviorTree()
{
	delete m_rootNode;
}

void BehaviorTree::Execute(Entity * entity, Blackboard * blackboard)
{
	m_rootNode->Tick(entity, blackboard);
}

Node* BehaviorTree::AddChild(Node* node)
{
	m_rootNode->AddChild(node);
	return node;
}
