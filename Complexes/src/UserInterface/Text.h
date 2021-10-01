#pragma once

#include <SFML/Graphics.hpp>

#include "Widget.h"

class Text : public Widget
{
public: //Constructors
	Text(std::shared_ptr<sf::RenderWindow> window);

public: //Public methods
	virtual void update(const float& dt) override;

	void setFont(const char* path);
	void setText(const char* text);
	void setColor(const sf::Color& col);
	void setSize(const unsigned int & size);

protected: //Protected attributes
	sf::Font m_Font;
	sf::Text m_Text;

protected: //Protected methods
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void updateRelativeParent() override;

	void updateBounds();
};

