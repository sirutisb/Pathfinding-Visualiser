#include "grid.h"

void Grid::createGrid(sf::Vector2i size, float nodeSize)
{
	m_size = size;
	m_nodeSize = nodeSize;
	delete m_nodes; // makes sure to free memory if an instance of nodes already exist
	m_nodes = new Node[size.x * size.y];
}

void Grid::clearGrid()
{
}

void Grid::saveGrid(const std::string& filename)
{
}

void Grid::loadGrid(const std::string& filename)
{
}
