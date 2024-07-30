
#include "MenuManager.h"

MenuManager::MenuManager(Grid& grid)
	: m_grid{ grid }
	, show{true}
{
}

void MenuManager::render(sf::RenderWindow& window)
{
	if (!show) return;
	ImGui::Begin("Options", &show);
	ImGui::SliderInt2("Grid Size", (int*)&menuData.gridSize, 4, 32);
	ImGui::SliderFloat("Node Size", &menuData.nodeSize, 10.0f, 100.0f);
	if (ImGui::Button("Create Grid")) {
		m_grid.resize(menuData.gridSize[0], menuData.gridSize[1]);
		// todo: center view on the new grid creater (aka move the camera)
	}
	if (ImGui::Button("Clear Grid")) {
	}
	if (ImGui::Button("Save Grid")) {
	}
	if (ImGui::Button("Load Grid")) {
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

bool MenuManager::isOpen()
{
	return show;
}

void MenuManager::toggle()
{
	show = !show;
}
