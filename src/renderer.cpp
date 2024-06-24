#include "renderer.h"
#include "DijkstraPathfinder.h"

Renderer::Renderer(sf::RenderTarget& target, Grid& grid) : m_target(target), m_grid(grid), m_pathfinder(new DijkstraPathfinder(grid))
{
}

Renderer::~Renderer()
{
	delete m_pathfinder; // weird rn
}

void Renderer::render()
{
	renderGrid();
	renderMenu();
}

void Renderer::renderMenu()
{
	if (!m_menuData.showMenu) return;
	ImGui::Begin("Options", &m_menuData.showMenu); //ImGuiWindowFlags_ for options
	ImGui::SliderInt2("Grid Size", (int*)&m_menuData.gridSize, 4, 32);
	ImGui::SliderFloat("Node Size", &m_menuData.nodeSize, 10.0f, 100.0f);
	if (ImGui::Button("Create Grid")) {
		m_grid.createGrid(m_menuData.gridSize, m_menuData.nodeSize);
	}
	if (ImGui::Button("Clear Grid")) {
		m_grid.clearGrid();
	}
	if (ImGui::Button("Save Grid")) {
		m_grid.saveGrid("test.dat");
	}
	if (ImGui::Button("Load Grid")) {
		m_grid.loadGrid("test.dat");
	}

	if (ImGui::Button("Find Path")) {
		sf::Vector2i start(0, 0);
		sf::Vector2i end(m_grid.getSize().x - 1, m_grid.getSize().y - 1);
		std::vector<sf::Vector2i> path = m_pathfinder->findPath(start, end);
		// pathfinding logic
		// renderer must render this path with its animation etc
	}
	ImGui::Checkbox("Animate Path", &m_menuData.animatePath);
	if (m_menuData.animatePath)
		ImGui::SliderFloat("Animation Delay", &m_menuData.animationDelay, 0.0f, 1.0f);
	ImGui::End();
}

MenuData& Renderer::getMenuData()
{
	return m_menuData;
}

void Renderer::renderGrid()
{
	const sf::Vector2i gridSize = m_grid.getSize();
	const float nodeSize = m_grid.getNodeSize();
	//sf::RectangleShape rect(sf::Vector2f(nodeSize - 1, nodeSize - 1)); // -1 for a small gap between nodes
	sf::RectangleShape rect(sf::Vector2f(nodeSize - 4, nodeSize - 4)); // -1 for a small gap between nodes
	rect.setFillColor(sf::Color::Cyan); // change depending on the node state
	for (int y = 0; y < gridSize.y; y++) {
		for (int x = 0; x < gridSize.x; x++) {
			Node& node = m_grid.getNode(x, y);
			sf::Vector2f nodePos(x * nodeSize, y * nodeSize);
			rect.setPosition(nodePos);
			m_target.draw(rect);
		}
	}
}


