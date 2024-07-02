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
		m_gridVertex = createGridVertex(m_menuData.gridSize, m_menuData.nodeSize);
		// todo: center view on the new grid creater (aka move the camera)
	}
	if (ImGui::Button("Clear Grid")) {
		m_grid.clearGrid();
		m_gridVertex = createGridVertex(m_menuData.gridSize, m_menuData.nodeSize);
	}
	if (ImGui::Button("Save Grid")) {
		m_grid.saveGrid("test.dat");
	}
	if (ImGui::Button("Load Grid")) {
		m_grid.loadGrid("test.dat");
		//m_gridVertex = createGridVertex(m_gri) To be implemented
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

sf::VertexArray Renderer::createGridVertex(const sf::Vector2i& gridSize, float cellSize) {
	sf::VertexArray grid(sf::Lines);

	// Create horizontal lines
	for (unsigned int i = 0; i <= gridSize.y; i++) {
		float y = i * cellSize;
		grid.append(sf::Vertex(sf::Vector2f(0, y), sf::Color::White));
		grid.append(sf::Vertex(sf::Vector2f(gridSize.y * cellSize, y), sf::Color::White));
	}

	// Create vertical lines
	for (unsigned int j = 0; j <= gridSize.x; j++) {
		float x = j * cellSize;
		grid.append(sf::Vertex(sf::Vector2f(x, 0), sf::Color::White));
		grid.append(sf::Vertex(sf::Vector2f(x, gridSize.x * cellSize), sf::Color::White));
	}
	return grid;
}

void Renderer::renderGrid()
{
	const sf::Vector2i gridSize = m_grid.getSize();
	const float nodeSize = m_grid.getNodeSize();
	//sf::VertexArray grid = createGridVertex(gridSize, nodeSize);

	sf::RectangleShape gridBackground(sf::Vector2f(gridSize.x * nodeSize, gridSize.y * nodeSize));
	gridBackground.setFillColor(sf::Color::Cyan);
	m_target.draw(gridBackground);
	m_target.draw(m_gridVertex);
}


