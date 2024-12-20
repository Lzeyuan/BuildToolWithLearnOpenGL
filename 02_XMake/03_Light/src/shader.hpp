#ifndef SHADER_H
#define SHADER_H

#include <stdafx.hpp>

class Shader {
public:
  unsigned int ID;
  // constructor generates the shader on the fly
  // ------------------------------------------------------------------------
  Shader(const char *vertexPath, const char *fragmentPath) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
      // open files
      vShaderFile.open(vertexPath);
      fShaderFile.open(fragmentPath);
      printf("vertexPath = %s, fragmentPath = %s\n", vertexPath, fragmentPath);
      std::stringstream vShaderStream, fShaderStream;
      // read file's buffer contents into streams
      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();
      // close file handlers
      vShaderFile.close();
      fShaderFile.close();
      // convert stream into string
      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure &e) {
      std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what()
                << std::endl;
    }
    const char *vShaderCode = vertexCode.data();
    const char *fShaderCode = fragmentCode.data();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer
    // necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }
  // activate the shader
  // ------------------------------------------------------------------------
  void use() const { glUseProgram(ID); }
  // utility uniform functions
  // ------------------------------------------------------------------------
  void setBool(std::string_view name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.data()), (int)value);
  }
  // ------------------------------------------------------------------------
  void setInt(std::string_view name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.data()), value);
  }
  // ------------------------------------------------------------------------
  void setFloat(std::string_view name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.data()), value);
  }
  // ------------------------------------------------------------------------
  void setVec2(std::string_view name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(ID, name.data()), 1, &value[0]);
  }
  void setVec2(std::string_view name, float x, float y) const {
    glUniform2f(glGetUniformLocation(ID, name.data()), x, y);
  }
  // ------------------------------------------------------------------------
  void setVec3(std::string_view name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(ID, name.data()), 1, &value[0]);
  }
  void setVec3(std::string_view name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, name.data()), x, y, z);
  }
  // ------------------------------------------------------------------------
  void setVec4(std::string_view name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(ID, name.data()), 1, &value[0]);
  }
  void setVec4(std::string_view name, float x, float y, float z,
               float w) const {
    glUniform4f(glGetUniformLocation(ID, name.data()), x, y, z, w);
  }
  // ------------------------------------------------------------------------
  void setMat2(std::string_view name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(ID, name.data()), 1, GL_FALSE,
                       &mat[0][0]);
  }
  // ------------------------------------------------------------------------
  void setMat3(std::string_view name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.data()), 1, GL_FALSE,
                       &mat[0][0]);
  }
  // ------------------------------------------------------------------------
  void setMat4(std::string_view name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.data()), 1, GL_FALSE,
                       &mat[0][0]);
  }

private:
  // utility function for checking shader compilation/linking errors.
  // ------------------------------------------------------------------------
  void checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout
            << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
            << infoLog
            << "\n -- --------------------------------------------------- -- "
            << std::endl;
      }
    } else {
      glGetProgramiv(shader, GL_LINK_STATUS, &success);
      if (!success) {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        std::cout
            << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
            << infoLog
            << "\n -- --------------------------------------------------- -- "
            << std::endl;
      }
    }
  }
};
#endif