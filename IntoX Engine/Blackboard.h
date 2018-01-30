#pragma once

#include <map>
#include "Node.h"

class Blackboard
{
public:
	Blackboard();
	float GetFloat(const std::string& key) const;
	void SetFloat(const std::string& key, float value);

	double GetDouble(const std::string& key) const;
	void SetDouble(const std::string& key, double value);

	const Node* GetNode(const std::string& key) const;
	void SetNode(const std::string& key, const Node* node);	

	Blackboard(const Blackboard&) = delete;

private:
	std::map<const std::string, float> m_floatMap;
	std::map<const std::string, double> m_doubleMap;
	std::map<const std::string, const Node*> m_nodeMap;	
};