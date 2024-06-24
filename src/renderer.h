#pragma once
#include "utils.h"

struct MenuData
{
	bool showMenu = true;
	Vec2i gridSize = { 16,16 };
	bool animatePath = false;
	float animationDelay = 0.1f;
};

class Renderer
{
public:
	Renderer(sf::RenderTarget& target) : m_target(target) {}

	void render() const {};

	void renderMenu() {
		if (!m_menuData.showMenu) return;
		ImGui::Begin("Options", &m_menuData.showMenu); //ImGuiWindowFlags_ for options
		ImGui::SliderInt2("Grid Size", (int*)&m_menuData.gridSize, 4, 32);
		if (ImGui::Button("Create Grid")) {
			// Create grid logic
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

	MenuData& getMenuData() { return m_menuData; }

private:
	sf::RenderTarget& m_target;
	MenuData m_menuData{};
};