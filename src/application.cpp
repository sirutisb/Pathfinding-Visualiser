#include "Application.h"
#include "Config.h"

Application::Application(const char* windowName)
	: m_window{sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), windowName}
	, m_grid{0, 0}
	, m_camera{m_window}
	, m_menu{m_grid}
{
	ImGui::SFML::Init(m_window);
	m_window.setFramerateLimit(Config::FPS_LIMIT);
	m_window.setKeyRepeatEnabled(false);
}

void Application::Run()
{
	while (m_window.isOpen()) {
		handleEvents();
		m_camera.update();
		render();
	}
	ImGui::SFML::Shutdown();
}
 
void Application::handleEvents()
{
	sf::Event ev;
	while (m_window.pollEvent(ev)) {
		if (m_menu.isOpen())
			ImGui::SFML::ProcessEvent(m_window, ev);
		m_camera.handleEvent(ev);
		switch (ev.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Insert)
				m_menu.toggle();
			break;

		case sf::Event::MouseButtonPressed:
			if (ev.mouseButton.button == sf::Mouse::Left)
				// left mouse
			break;
		case sf::Event::MouseButtonReleased:
			if (ev.mouseButton.button == sf::Mouse::Left)
				// left mouse released
			break;
		case sf::Event::MouseMoved:
		{
			sf::Vector2i mousePos = *reinterpret_cast<sf::Vector2i*>(&ev.mouseMove); // hacky type punning
			sf::Vector2f worldPos = m_window.mapPixelToCoords(mousePos);

		}
			break;
		default:
			break;
		}
	}
	if (m_menu.isOpen())
		ImGui::SFML::Update(m_window, m_deltaClock.restart());
}


void Application::render()
{
	m_window.clear(sf::Color(18, 33, 43));
	m_grid.render(m_window);
	m_menu.render(m_window);
	m_window.display();
}

