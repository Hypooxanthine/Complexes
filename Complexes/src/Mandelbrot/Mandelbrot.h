#pragma once

#include <map>

#include "../UserInterface/Button.h"
#include "../UserInterface/Text.h"
#include <SFML/Graphics.hpp>

#include "../Math/Complex.h"

class Mandelbrot
{
public:
	Mandelbrot();

	void run();
	void manageEvents();
	void update();
	void render();

	void drawSet();
	void renderAnimation();
	int isFromSet(const Complex& z) const;
	Complex pixelToComplex(const sf::Vector2u& px) const;
	sf::Vector2u complexToPixel(const Complex& z) const;
	void setOrigin(const sf::Vector2u& origin, const bool& refresh);
	void zoom(const float& strength);

private:
	float m_Dt = 0.f;
	sf::Clock m_DtClock;

	std::shared_ptr<sf::RenderWindow> m_Window;
	sf::Vector2u m_WindowSize;
	sf::Vector2u m_WindowCenter;
	sf::Event m_Event;

	std::map<std::string, std::shared_ptr<Button>> m_Buttons;
	std::map<std::string, std::shared_ptr<Text>> m_Texts;
	std::map<std::string, sf::Color> m_ButtonColors;

	Complex m_Origin;

	uint32_t m_Iterations = 1000;
	long double m_PxPerUnit = 150;
	sf::Image m_Image;
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	bool m_Started = false;
};