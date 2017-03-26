#include "Geo2D.h"
using namespace Geo2D;
Edge2::Edge2(glm::vec2 _point0, glm::vec2 _point1)
{
    m_point[0] = _point0;
    m_point[1] = _point1;
}

Edge2::~Edge2()
{
}

Tri2::Tri2(Edge2 _edge0, Edge2 _edge1,Edge2 _edge2)
{
    m_edge[0] = _edge0;
    m_edge[1] = _edge1;
    m_edge[2] = _edge2;
}

Geo2D::Tri2::~Tri2()
{
}

