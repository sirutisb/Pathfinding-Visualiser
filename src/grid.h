#pragma once
#include "utils.h"
#include <string>

enum class NodeType
{
	Empty,
	Wall,
	Start,
	End
};

struct Node
{
	NodeType type;
};

class Grid
{
public:
	Grid() = default;

	Grid(Vec2i size, float nodeSize) {
		createGrid(size, nodeSize);
	}

	~Grid() { delete[] m_nodes; }
	void createGrid(sf::Vector2i size, float nodeSize);
	Node& getNode(int x, int y) { return m_nodes[y * m_size.x + x]; }
	Node& getNode(Vec2i pos) { return getNode(pos.x, pos.y); }
	Vec2i getSize() const { return m_size; }
	float getNodeSize() const { return m_nodeSize; }
	void clearGrid();
	void saveGrid(const std::string& filename);
	void loadGrid(const std::string& filename);

private:
	Node* m_nodes{};
	Vec2i m_size{};
	float m_nodeSize{};
};