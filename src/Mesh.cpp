#include "Mesh.h"

void Mesh::createVertexArray() noexcept
{
    glCreateVertexArrays(1, &m_VAO);
}

void Mesh::destroyVertexArray() noexcept
{
    if (m_VAO)
        glDeleteVertexArrays(1, &m_VAO);
}

void Mesh::createBuffers() noexcept
{
    glCreateBuffers(1, &m_positionsVBO);
    glCreateBuffers(1, &m_texCoordsVBO);
    glCreateBuffers(1, &m_normalsVBO);
    glCreateBuffers(1, &m_EBO);

    glNamedBufferData(
        m_positionsVBO,
        sizeof(glm::vec3) * m_positions.size(),
        m_positions.data(),
        GL_STATIC_DRAW);

    glNamedBufferData(
        m_texCoordsVBO,
        sizeof(glm::vec2) * m_texCoords.size(),
        m_texCoords.data(),
        GL_STATIC_DRAW);

    glNamedBufferData(
        m_normalsVBO,
        sizeof(glm::vec3) * m_normals.size(),
        m_normals.data(),
        GL_STATIC_DRAW);

    glNamedBufferData(
        m_EBO,
        sizeof(uint32_t) * m_indices.size(),
        m_indices.data(),
        GL_STATIC_DRAW);

    glVertexArrayVertexBuffer(m_VAO, 0, m_positionsVBO, 0, sizeof(glm::vec3));
    glVertexArrayVertexBuffer(m_VAO, 1, m_texCoordsVBO, 0, sizeof(glm::vec2));
    glVertexArrayVertexBuffer(m_VAO, 2, m_normalsVBO, 0, sizeof(glm::vec3));

    glVertexArrayElementBuffer(m_VAO, m_EBO);

    glEnableVertexArrayAttrib(m_VAO, 0);
    glVertexArrayAttribBinding(m_VAO, 0, 0);
    glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

    glEnableVertexArrayAttrib(m_VAO, 1);
    glVertexArrayAttribBinding(m_VAO, 1, 1);
    glVertexArrayAttribFormat(m_VAO, 1, 2, GL_FLOAT, GL_FALSE, 0);

    glEnableVertexArrayAttrib(m_VAO, 2);
    glVertexArrayAttribBinding(m_VAO, 2, 2);
    glVertexArrayAttribFormat(m_VAO, 2, 3, GL_FLOAT, GL_FALSE, 0);
}

void Mesh::destroyBuffers() noexcept
{
    glDeleteBuffers(1, &m_positionsVBO);
    glDeleteBuffers(1, &m_texCoordsVBO);
    glDeleteBuffers(1, &m_normalsVBO);
    glDeleteBuffers(1, &m_EBO);
}

Mesh::Mesh(std::vector<glm::vec3>&& positions,
    std::vector<glm::vec2>&& texCoords,
    std::vector<glm::vec3>&& normals,
    std::vector<uint32_t>&& indices)
    :
    m_positions(std::move(positions)),
    m_texCoords(std::move(texCoords)),
    m_normals(std::move(normals)),
    m_indices(std::move(indices))
{
    createVertexArray();
    createBuffers();
}

Mesh::~Mesh() noexcept
{
    destroyBuffers();
    destroyVertexArray();
}

Mesh::Mesh(Mesh&& other) noexcept
{
    m_VAO = other.m_VAO;

    m_positionsVBO = other.m_positionsVBO;
    m_texCoordsVBO = other.m_texCoordsVBO;
    m_normalsVBO = other.m_normalsVBO;
    m_EBO = other.m_EBO;

    m_positions = std::move(other.m_positions);
    m_texCoords = std::move(other.m_texCoords);
    m_normals = std::move(other.m_normals);
    m_indices = std::move(other.m_indices);

    other.m_VAO = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
    if (this == &other)
        return *this;

    destroyBuffers();
    destroyVertexArray();

    m_VAO = other.m_VAO;

    m_positionsVBO = other.m_positionsVBO;
    m_texCoordsVBO = other.m_texCoordsVBO;
    m_normalsVBO = other.m_normalsVBO;
    m_EBO = other.m_EBO;

    m_positions = std::move(other.m_positions);
    m_texCoords = std::move(other.m_texCoords);
    m_normals = std::move(other.m_normals);
    m_indices = std::move(other.m_indices);

    other.m_VAO = 0;

    return *this;
}

const std::vector<glm::vec3>& Mesh::getPositions() const noexcept
{
    return m_positions;
}

const std::vector<glm::vec2>& Mesh::getTexCoords() const noexcept
{
    return m_texCoords;
}

const std::vector<glm::vec3>& Mesh::getNormals() const noexcept
{
    return m_normals;
}

const std::vector<uint32_t>& Mesh::getIndices() const noexcept
{
    return m_indices;
}

void Mesh::setData(
    std::vector<glm::vec3>&& positions,
    std::vector<glm::vec2>&& texCoords,
    std::vector<glm::vec3>&& normals,
    std::vector<uint32_t>&& indices) noexcept
{
    m_positions = std::move(positions);
    m_texCoords = std::move(texCoords);
    m_normals = std::move(normals);
    m_indices = std::move(indices);
}