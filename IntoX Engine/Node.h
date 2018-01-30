#pragma once

#include <string>
#include "Entity.h"

enum class ENodeStatus : unsigned char
{
	FAILURE = 0,
	SUCCESS = 1,
	RUNNING = 2
};

class Node
{	

public:
	virtual ~Node() {}
	virtual ENodeStatus Tick( Entity* entity, class Blackboard* blackboard) const = 0;
	inline const std::string& GetName() const { return m_Name; }

protected:
	Node(const std::string& name) : m_Name(name) {}	

	std::string m_Name;
};

