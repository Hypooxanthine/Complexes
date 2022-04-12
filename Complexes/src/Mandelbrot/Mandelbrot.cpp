#include "Mandelbrot.h"
#include "Util.h"

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
				if (m_Started)
				{
					m_Iterations = (size_t)((double)m_Iterations * 1.5);
					drawSet();
					std::cout << "New value for m_Iterations : " << m_Iterations << std::endl;
				}
				break;
			case sf::Keyboard::Subtract:
				if (m_Started)
				{
					m_Iterations = (size_t)((double)m_Iterations / 1.5);
					if (m_Iterations < 2) m_Iterations = 2;
					drawSet();
					std::cout << "New value for m_Iterations : " << m_Iterations << std::endl;
				}
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
		case sf::Event::MouseWheelMoved:
			if (m_Started)
			{
				if(m_Iterations + m_Event.mouseWheel.delta * 10)
					m_Iterations += m_Event.mouseWheel.delta * 10;
				drawSet();
				std::cout << "New value for m_Iterations : " << m_Iterations << std::endl;
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

	for (uint16_t x = 0; x < m_WindowSize.x; x++)
	{
		for (uint16_t y = 0; y < m_WindowSize.y; y++)
		{
			size_t i = mandelCheck(pixelToComplex(sf::Vector2u(x, y)));
			
			HsvColor hsvCol =
			{
				(unsigned char)(255.0 * (double)i / (double)m_Iterations),
				255,
				(i < m_Iterations ? 255 : 0)
			};

			RgbColor unitRgb = HsvToRgb(hsvCol);

			sf::Color color(sf::Uint8(unitRgb.r), sf::Uint8(unitRgb.g), sf::Uint8(unitRgb.b));

			m_Image.setPixel(x, y, color);
		}
	}

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

size_t Mandelbrot::mandelCheck(const Complex& z) const
{
	Complex z_n = 0;

	for (size_t i = 0; i < m_Iterations; i++)
	{
		z_n *= z_n;
		z_n += z;

		if (z_n.module() > 2)
			return i;
	}

	return m_Iterations;
}

Complex Mandelbrot::pixelToComplex(const sf::Vector2u& px) const
{
	Complex out;

	out.setReal(((double)px.x - (double)m_WindowCenter.x) / (double)m_PxPerUnit);
	out.setImaginary(((double)px.y - (double)m_WindowCenter.y) / (double)m_PxPerUnit);

	out += m_Origin;

	return out;
}

void Mandelbrot::setOrigin(const sf::Vector2u& origin, const bool& refresh = false)
{
	m_Origin = pixelToComplex(origin);
	std::cout << "Setting origin to complex : Re = " << m_Origin.getReal() << " Im = " << m_Origin.getImaginary() << std::endl;

	if (refresh)
		drawSet();
}

void Mandelbrot::zoom(const float& strength)
{
	m_PxPerUnit = (size_t)((float)m_PxPerUnit * strength);
	std::cout << "Pixels per Unit : " << m_PxPerUnit << std::endl;
}
