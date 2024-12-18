#include "menu.h"
#include <imgui.h>
#include <imgui-SFML.h>

Menu::Menu()
	: show(false)
{
}

void Menu::render(sf::RenderWindow& window)
{
	if (!show) return;
	ImGui::Begin("Options", &show);
	if (ImGui::Button("Create Grid")) {
	}

	ImGui::End();
	ImGui::SFML::Render(window);
}

void Menu::toggle()
{
	show = !show;
}

bool Menu::isOpen() const
{
	return show;
}