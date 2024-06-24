#include "renderer.h"

Renderer::Renderer(sf::RenderTarget& target, Grid& grid) : m_target(target), m_grid(grid)
{
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
	ImGui::Button("Clear Grid");
	ImGui::Button("Save Grid");
	ImGui::Button("Load Grid");
	ImGui::Button("Find Path");
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


