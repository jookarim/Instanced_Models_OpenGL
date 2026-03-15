#pragma once

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <cstdint>

class Mesh
{
private:

    std::vector<glm::vec3> m_positions{};
    std::vector<glm::vec2> m_texCoords{};
    std::vector<glm::vec3> m_normals{};
    std::vector<uint32_t>  m_indices{};

private:

    GLuint m_VAO{};
    GLuint m_positionsVBO{};
    GLuint m_texCoordsVBO{};
    GLuint m_normalsVBO{};
    GLuint m_EBO{};

private:

    void createVertexArray() noexcept;
    void destroyVertexArray() noexcept;

    void createBuffers() noexcept;
    void destroyBuffers() noexcept;

public:

    Mesh(std::vector<glm::vec3>&& positions,
        std::vector<glm::vec2>&& texCoords,
        std::vector<glm::vec3>&& normals,
        std::vector<uint32_t>&& indices);

    ~Mesh() noexcept;

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

public:

    const std::vector<glm::vec3>& getPositions() const noexcept;
    const std::vector<glm::vec2>& getTexCoords() const noexcept;
    const std::vector<glm::vec3>& getNormals() const noexcept;
    const std::vector<uint32_t>& getIndices() const noexcept;

    void setData(
        std::vector<glm::vec3>&& positions,
        std::vector<glm::vec2>&& texCoords,
        std::vector<glm::vec3>&& normals,
        std::vector<uint32_t>&& indices) noexcept;

};