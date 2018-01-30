#include "CompositeNode.h"
#include "Blackboard.h"

CompositeNode::CompositeNode(const std::string& name, ENodeStatus defaultStatus) :
	MultipleChildNode(name), m_DefaultStatus(defaultStatus){}

CompositeNode::~CompositeNode() {}

ENodeStatus CompositeNode::Tick(Entity* entity, Blackboard* blackboard) const
{	
	for (auto startNodeIt = GetNodeIterator(blackboard); startNodeIt != m_Nodes.end(); startNodeIt++)
	{
		ENodeStatus childStatus = (*startNodeIt)->Tick(entity, blackboard);
		if (childStatus != m_DefaultStatus)
		{
			if (childStatus == ENodeStatus::RUNNING)
				SaveNode((*startNodeIt), blackboard);
			
			return childStatus;
		}
	}

	return m_DefaultStatus;
}

void CompositeNode::SaveNode(const Node* node, Blackboard* blackboard) const
{	
	blackboard->SetNode(this->GetName(), node);
}

const std::vector<const Node*>::const_iterator CompositeNode::GetNodeIterator(Blackboard* blackboard) const
{	
	auto nodeIt = m_Nodes.begin();
	const Node* node = blackboard->GetNode(this->GetName());
	if (node)
	{
		blackboard->SetNode(this->GetName(), nullptr);
		nodeIt = std::find(m_Nodes.begin(), m_Nodes.end(), node);
		assert(nodeIt != m_Nodes.end());
	}
	return nodeIt;
}
