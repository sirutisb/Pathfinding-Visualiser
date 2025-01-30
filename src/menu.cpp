#include "menu.h"
#include <imgui.h>
#include <imgui-SFML.h>

Menu::Menu()
	: show(false)
	, gridSize{ 8, 8 }
	, algorithmIndex(0)
	, algorithms{ "Dijkstra's", "A*" }
	, showAnimation(false)
	, animationDelay(1.0f)
{
}

void Menu::render(sf::RenderWindow& window, Grid& grid) {
	if (!show) return;
	ImGui::Begin("Options", &show);
	ImGui::SeparatorText("Grid Options");
	ImGui::SliderInt2("Grid Size", gridSize, 5, 200);
	if (ImGui::Button("Create Grid")) {
		grid.resize(gridSize[0], gridSize[1]);
	}
	if (ImGui::Button("Clear Grid")) {
		grid.clear();
	}
	if (ImGui::Button("Save Grid")) {
	}
	if (ImGui::Button("Load Grid")) {
	}
	ImGui::SeparatorText("Algorithm");
	ImGui::Combo("Algorithm", &algorithmIndex, algorithms, IM_ARRAYSIZE(algorithms));
	ImGui::Checkbox("Show Path Animation", &showAnimation);
	if (showAnimation) {
		ImGui::SliderFloat("Animation Delay", &animationDelay, 0.0f, 1.0f);
	}
	if (ImGui::Button("Find Path")) {
	}

	ImGui::End();
	ImGui::SFML::Render(window);
}

void Menu::toggle() {
	show = !show;
}

bool Menu::isOpen() const {
	return show;
}