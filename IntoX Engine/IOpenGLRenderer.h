#pragma once
class IOpenGLRenderer
{
public:
	IOpenGLRenderer();
	~IOpenGLRenderer();

	virtual bool Init();
	virtual void Render() = 0;
};

