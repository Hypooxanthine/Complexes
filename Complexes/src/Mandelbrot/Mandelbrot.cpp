#include "Mandelbrot.h"

Mandelbrot::Mandelbrot()
	: m_Window(std::make_shared<sf::RenderWindow>()), m_Event(sf::Event()), m_WindowSize(sf::Vector2u(600, 600)),
	m_Origin(Complex(0, 0))
{
	m_WindowCenter.x = m_WindowSize.x / 2;
	m_WindowCenter.y = m_WindowSize.y / 2;
}

void Mandelbrot::run()
{
	/* User Interface */
	m_ButtonColors["Normal"] = sf::Color(50, 50, 50);
	m_ButtonColors["Hovered"] = sf::Color(70, 70, 70);
	m_ButtonColors["Pressed"] = sf::Color(40, 40, 40);

	m_Buttons["Start"] = std::make_shared<Button>(m_Window);
	m_Buttons["Render"] = std::make_shared<Button>(m_Window);
	m_Texts["Start"] = std::make_shared<Text>(m_Window);
	m_Texts["Render"] = std::make_shared<Text>(m_Window);

	m_Buttons["Render"]->setSize(sf::Vector2f(150.f, 50.f));
	m_Buttons["Render"]->setShapeColor(m_ButtonColors["Normal"], "Normal");
	m_Buttons["Render"]->setShapeColor(m_ButtonColors["Hovered"], "Hovered");
	m_Buttons["Render"]->setShapeColor(m_ButtonColors["Pressed"], "Pressed");
	m_Buttons["Render"]->setPosition(sf::Vector2f(400, 500));
	m_Buttons["Render"]->setCallbackFn(BIND_BUTTON_FN(Mandelbrot::renderAnimation));

	m_Buttons["Start"]->setSize(sf::Vector2f(150.f, 50.f));
	m_Buttons["Start"]->setShapeColor(m_ButtonColors["Normal"], "Normal");
	m_Buttons["Start"]->setShapeColor(m_ButtonColors["Hovered"], "Hovered");
	m_Buttons["Start"]->setShapeColor(m_ButtonColors["Pressed"], "Pressed");
	m_Buttons["Start"]->setPosition(sf::Vector2f(400, 430));
	m_Buttons["Start"]->setCallbackFn(BIND_BUTTON_FN(Mandelbrot::drawSet));

	m_Texts["Start"]->setFont("Resources/fonts/Chocolate_Cookies.ttf");
	m_Texts["Start"]->setText("Start");
	m_Texts["Start"]->setColor(sf::Color::White);
	m_Texts["Start"]->setSize(30);
	m_Texts["Start"]->setPosition(sf::Vector2f(0, -5.f));
	m_Texts["Start"]->setParent(m_Buttons["Start"]);

	m_Texts["Render"]->setFont("Resources/fonts/Chocolate_Cookies.ttf");
	m_Texts["Render"]->setText("Render");
	m_Texts["Render"]->setColor(sf::Color::White);
	m_Texts["Render"]->setSize(30);
	m_Texts["Render"]->setPosition(sf::Vector2f(0, -5.f));
	m_Texts["Render"]->setParent(m_Buttons["Render"]);

	m_Window->create(sf::VideoMode(m_WindowSize.x, m_WindowSize.y, 32), "Mandelbrot set");
	
	// Main loop
	while (m_Window->isOpen())
	{
		manageEvents();
		update();
		render();

		m_Dt = m_DtClock.restart().asSeconds();
	}
}

void Mandelbrot::manageEvents()
{
	while (m_Window->pollEvent(m_Event))
	{
		switch (m_Event.type)
		{
		case sf::Event::Closed:
			m_Window->close();
			break;
		case sf::Event::KeyPressed:
			switch (m_Event.key.code)
			{
			case sf::Keyboard::Escape:
				m_Window->close();
				break;
			case sf::Keyboard::Add:
				m_Iterations *= 1.5f;
				drawSet();
				std::cout << "New value for m_Iterations : " << m_Iterations << std::endl;
				break;
			case sf::Keyboard::Subtract:
				m_Iterations /= 1.5f;
				drawSet();
				std::cout << "New value for m_Iterations : " << m_Iterations << std::endl;
				break;
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (m_Event.mouseButton.button == sf::Mouse::Left)
			{
				if (m_Started)
				{
					zoom(2.f);
					setOrigin(sf::Vector2u(m_Event.mouseButton.x, m_Event.mouseButton.y), true);
				}
			}
			else if (m_Event.mouseButton.button == sf::Mouse::Right)
			{
				if (m_Started)
				{
					zoom(1.f / 2.f);
					setOrigin(sf::Vector2u(m_Event.mouseButton.x, m_Event.mouseButton.y), true);
				}
			}
			break;
		}
	}
}

void Mandelbrot::update()
{
	for (std::pair p : m_Buttons)
		p.second->update(m_Dt);
	for (std::pair p : m_Texts)
		p.second->update(m_Dt);
}

void Mandelbrot::render()
{
	m_Window->clear();

	m_Window->draw(m_Sprite);

	for (std::pair p : m_Buttons)
		m_Window->draw(*p.second);
	for (std::pair p : m_Texts)
		m_Window->draw(*p.second);

	m_Window->display();
}

void Mandelbrot::drawSet()
{
	m_Started = true;

	// Resetting image pixels
	m_Image.create(m_WindowSize.x, m_WindowSize.y);

	for (uint32_t x = 0; x < m_WindowSize.x; x++)
	{
		for (uint32_t y = 0; y < m_WindowSize.y; y++)
		{
			int color = isFromSet(pixelToComplex(sf::Vector2u(x, y)));
			m_Image.setPixel(x, y, sf::Color(color, color, 127));
		}
	}

	sf::Texture texture;
	m_Texture.loadFromImage(m_Image);
	m_Sprite.setTexture(m_Texture);
}

void Mandelbrot::renderAnimation()
{
	m_Origin = Complex(-0.747156, -0.087601);

	uint32_t frames = 150;

	for (uint32_t i = 0; i < frames; i++)
	{

		m_Window->clear();

		std::cout << "Drawing Mandelbrot set " << (i + 1) << "/" << frames << ".\n";
		drawSet();
		std::cout << "Drawn.\n";

		m_Window->draw(m_Sprite);
		m_Window->display();

		m_Image.saveToFile(std::to_string(i) + ".png");
		zoom(1.1f);
	}
}

int Mandelbrot::isFromSet(const Complex& z) const
{
	Complex z_n = 0;

	for (uint32_t i = 0; i < m_Iterations; i++)
	{
		z_n *= z_n;
		z_n += z;

		if (z_n.module() >= 2)
			return i + 1;
	}

	return 0;
}

Complex Mandelbrot::pixelToComplex(const sf::Vector2u& px) const
{
	Complex out;

	out.setReal(((long double)px.x - (long double)m_WindowCenter.x) / m_PxPerUnit);
	out.setImaginary(((long double)px.y - (long double)m_WindowCenter.y) / m_PxPerUnit);

	out += m_Origin;

	return out;
}

sf::Vector2u Mandelbrot::complexToPixel(const Complex& z) const
{
	sf::Vector2u out;
	return out;
}

void Mandelbrot::setOrigin(const sf::Vector2u& origin, const bool& refresh = false)
{
	m_Origin = pixelToComplex(origin);
	std::cout << "Setting origin to complex : " << m_Origin << std::endl;

	if (refresh)
		drawSet();
}

void Mandelbrot::zoom(const float& strength)
{
	m_PxPerUnit *= strength;
}
