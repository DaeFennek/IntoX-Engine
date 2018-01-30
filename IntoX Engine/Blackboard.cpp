#include "Blackboard.h"
#include <unordered_map>

Blackboard::Blackboard(){}

float Blackboard::GetFloat(const std::string & key) const
{
	auto pos = m_floatMap.find(key);
	if (pos != m_floatMap.end())
		return pos->second;
	return 0.0f;
}

void Blackboard::SetFloat(const std::string & key, float value)
{
	m_floatMap[key] = value;
}

double Blackboard::GetDouble(const std::string & key) const
{
	auto pos = m_doubleMap.find(key);
	if (pos != m_doubleMap.end())
		return pos->second;
	return 0.0;
}

void Blackboard::SetDouble(const std::string & key, double value)
{
	m_doubleMap[key] = value;
}

const Node * Blackboard::GetNode(const std::string & key) const
{
	auto pos = m_nodeMap.find(key);
	if (pos != m_nodeMap.end())
		return pos->second;
	return nullptr;
}

void Blackboard::SetNode(const std::string & key, const Node * node)
{
	m_nodeMap[key] = node;
}
