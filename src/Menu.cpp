
#include "Menu.h"

Menu::Menu(Grid& grid)
	: m_grid{grid}
	, show{true}
{
}

void Menu::render(sf::RenderWindow& window)
{
	if (!show) return;
	ImGui::Begin("Options", &show);
	ImGui::SliderInt2("Grid Size", (int*)&menuData.gridSize, 5, 50);
	//ImGui::SliderFloat("Node Size", &menuData.nodeSize, 10.0f, 100.0f); // don't think this is necessary because we can just pan around anyway
	if (ImGui::Button("Create Grid")) {
		m_grid.resize(menuData.gridSize.x, menuData.gridSize.y);
		// todo: center view on the new grid creater (aka move the camera)
	}
	if (ImGui::Button("Clear Grid")) {
		m_grid.clear();
	}
	if (ImGui::Button("Save Grid")) {
		m_grid.save("test.map");
	}
	if (ImGui::Button("Load Grid")) {
		m_grid.load("test.map");
	}

	if (ImGui::Button("Find Path")) {
		// pathfinding logic
		// renderer must render this path with its animation etc
	}
	ImGui::Checkbox("Animate Path", &menuData.animatePath);
	if (menuData.animatePath)
		ImGui::SliderFloat("Animation Delay", &menuData.animationDelay, 0.0f, 1.0f);
	ImGui::End();
	ImGui::SFML::Render(window);
}

bool Menu::isOpen() const
{
	return show;
}

void Menu::toggle()
{
	show = !show;
}
