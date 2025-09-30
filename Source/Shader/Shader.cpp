#include "Shader.h"

Shader::Shader()
{
	programID = glCreateProgram();
}

Shader& Shader::Attach(const char* shaderPath, ShaderType shaderType)
{
	unsigned int glShaderType = ShaderTypeToGLType(shaderType);
	if (glShaderType == 0)
	{
		return *this;
	}

	std::string shaderCode;

	try
	{
		if (shaderPath != nullptr)
		{
			std::ifstream shaderFile;
			shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			shaderFile.open(shaderPath);

			std::stringstream shaderStream;
			shaderStream << shaderFile.rdbuf();
			shaderFile.close();

			shaderCode = shaderStream.str();
		}
	}
	catch (std::ifstream::failure e)
	{
		LogError("Failed to load shader file: ", shaderPath);
		return *this;
	}

	if (!shaderCode.empty())
	{
		int success;
		char info[512];

		const char* shaderCodeCStr = shaderCode.c_str();
		unsigned int shaderID = glCreateShader(glShaderType);

		glShaderSource(shaderID, 1, &shaderCodeCStr, NULL);
		glCompileShader(shaderID);

		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderID, 512, NULL, info);
			LogError("Shader compile failed! ProgramID: ", std::to_string(programID), ", ShaderID: ", shaderID, ", ShaderType: ", shaderType, "\nInfo: ", info);
		};

		glAttachShader(programID, shaderID);
		glDeleteShader(shaderID);
	}

	return *this;
}

void Shader::Link()
{
	int success;
	char info[512];

	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, info);
		LogError("Shader program link failed! ProgramID: ", std::to_string(programID), "\nInfo: ", info);
	}
}

inline void Shader::Use()
{
	glUseProgram(programID);
}

inline void Shader::Delete()
{
	glDeleteProgram(programID);
}

inline void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

inline void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

inline void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

inline void Shader::SetMat4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

inline void Shader::SetMat3(const std::string& name, glm::mat3 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

inline void Shader::SetVec4(const std::string& name, glm::vec4 value) const
{
	glUniform4f(glGetUniformLocation(programID, name.c_str()), value.x, value.y, value.z, value.w);
}

inline void Shader::SetVec3(const std::string& name, glm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(programID, name.c_str()), value.x, value.y, value.z);
}

inline void Shader::SetVec2(const std::string& name, glm::vec2 value) const
{
	glUniform2f(glGetUniformLocation(programID, name.c_str()), value.x, value.y);
}

unsigned int Shader::ShaderTypeToGLType(ShaderType shaderType)
{
	switch (shaderType)
	{
	case ShaderType::VERTEX:
		return GL_VERTEX_SHADER;
	case ShaderType::FRAGMENT:
		return GL_FRAGMENT_SHADER;
	case ShaderType::GEOMETRY:
		return GL_GEOMETRY_SHADER;
	default:
		LogError("Undefined shader type: ", shaderType);
		return 0;
	}
}
