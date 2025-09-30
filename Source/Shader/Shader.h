#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <Core.h>;
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

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

	inline void Use();

	inline void Delete();

	inline void SetBool(const std::string& name, bool value) const;

	inline void SetInt(const std::string& name, int value) const;

	inline void SetFloat(const std::string& name, float value) const;

	inline void SetMat4(const std::string& name, glm::mat4 value) const;

	inline void SetMat3(const std::string& name, glm::mat3 value) const;

	inline void SetVec4(const std::string& name, glm::vec4 value) const;

	inline void SetVec3(const std::string& name, glm::vec3 value) const;

	inline void SetVec2(const std::string& name, glm::vec2 value) const;

private:
	static unsigned int ShaderTypeToGLType(ShaderType shaderType);
};
