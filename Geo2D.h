#pragma once
#include <glm.hpp>
namespace Geo2D
{
    class Edge2
    {
    public:
        glm::vec2 m_point[2];
        Edge2(glm::vec2 _point0 = glm::vec2(0,0), glm::vec2 _point1 = glm::vec2(0,0));
        ~Edge2();
    };
    
    class Tri2
    {
    public:
        Edge2 m_edge[3];
        Tri2(Edge2 _edge0, Edge2 _edge1, Edge2 _edge2);
        ~Tri2();
    };
    
    
};
