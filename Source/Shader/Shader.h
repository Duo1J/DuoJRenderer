#pragma once

#include <Core.h>

#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

enum class ShaderType
{
	VERTEX,
	FRAGMENT,
	GEOMETRY
};

class Shader
{
public:
	unsigned int programID;

public:
	Shader();

	Shader& Attach(const char* shaderPath, ShaderType shaderType);

	void Link();

	void Use();

	void Delete();

	void SetBool(const std::string& name, bool value) const;

	void SetInt(const std::string& name, int value) const;

	void SetFloat(const std::string& name, float value) const;

	void SetMat4(const std::string& name, glm::mat4 value) const;

	void SetMat3(const std::string& name, glm::mat3 value) const;

	void SetVec4(const std::string& name, glm::vec4 value) const;

	void SetVec3(const std::string& name, glm::vec3 value) const;

	void SetVec2(const std::string& name, glm::vec2 value) const;

private:
	bool linked = false;

	static unsigned int ShaderTypeToGLType(ShaderType shaderType);
};
