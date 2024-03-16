#include "Mesh.h"
#include "Data.h"

Mesh::Mesh() : vao(0), vertexBuffer(0), indexBuffer(0), vertexCount(0) {}

bool Mesh::load(std::string filename)
{
    // массив вершин полигональной сетки
    std::vector<Vertex> vertices;
    // массив индексов
    std::vector<GLuint> indices;

    std::ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error '" << filename << "' mesh file\n";
        return false;
    }
    else {
        cout << "Mesh file '" << filename << "' open\n";
    }


    std::vector<glm::vec3> v;
    std::vector<glm::vec3> n;
    std::vector<glm::vec2> t;
    vector<ivec3> fPoints;

    int i = 0;
    int key_int = 0;

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v")
        {
            float x, y, z;
            iss >> x >> y >> z;
            v.push_back({ x, y, z });
        }
        else if (prefix == "vn")
        {
            float nx, ny, nz;
            iss >> nx >> ny >> nz;
            n.push_back({ nx, ny, nz });
        }
        else if (prefix == "vt")
        {
            float u, v;
            iss >> u >> v;
            t.push_back({ u, v });
        }
        else if (prefix == "f")
        {
            std::vector<int> vertexIndices;
            std::vector<int> normalIndices;
            std::vector<int> texCoordIndices;

            std::string indexStr;
            while (iss >> indexStr)
            {
                std::istringstream indexIss(indexStr);
                std::string vertexIndexStr, texCoordIndexStr, normalIndexStr;

                getline(indexIss, vertexIndexStr, '/');
                getline(indexIss, texCoordIndexStr, '/');
                getline(indexIss, normalIndexStr, '/');

                string key_str = vertexIndexStr + '/' + texCoordIndexStr + '/' + normalIndexStr;

                indices.push_back(key_int);




                key_int++;
                int vertexIndex = std::stoi(vertexIndexStr) - 1;
                int texCoordIndex = std::stoi(texCoordIndexStr) - 1;
                int normalIndex = std::stoi(normalIndexStr) - 1;

                vertexIndices.push_back(vertexIndex);
                texCoordIndices.push_back(texCoordIndex);
                normalIndices.push_back(normalIndex);
                fPoints.push_back({ vertexIndices[vertexIndices.size() - 1],texCoordIndices[vertexIndices.size() - 1], normalIndices[vertexIndices.size() - 1] });

            }
        }
    }
    Vertex vertex;
    for (int i = 0; i < fPoints.size(); i++)
    {
        vertex.coord[0] = v[fPoints[i].x].x;
        vertex.coord[1] = v[fPoints[i].x].y;
        vertex.coord[2] = v[fPoints[i].x].z;

        vertex.texCoord[0] = t[fPoints[i].y].x;
        vertex.texCoord[1] = t[fPoints[i].y].y;

        vertex.normal[0] = n[fPoints[i].z].x;
        vertex.normal[1] = n[fPoints[i].z].y;
        vertex.normal[2] = n[fPoints[i].z].z;

        vertices.push_back(vertex);
    }
    vertexCount = vertices.size();

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
        &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (GLvoid*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (GLvoid*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (GLvoid*)offsetof(Vertex, texCoord));

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()
        * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

    return true;
}

void Mesh::drawOne() {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
}