#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "../Log.h"

class Widget : public sf::Drawable
{
public: //Enums
	enum class CursorState { StateNormal = 0, StateHovered, StatePressed, StatePressedUnhovered, StatePressedHovered};

public: //Constructors
	Widget(std::shared_ptr<sf::RenderWindow> window);

public: //Public methods
	virtual void update(const float& dt);

	void setParent(std::shared_ptr<Widget> parent, bool center = true);

	sf::Vector2f getAbsolutePosition();
	sf::Vector2f getRelativePosition();
	virtual void setPosition(const sf::Vector2f& pos);

	sf::Vector2f getCenter();

protected: //Protected attributes
	std::shared_ptr<sf::RenderWindow> m_Window;

	sf::Vector2i m_MousePosScreen;
	CursorState m_CursorState;
	bool m_Clicked;

	sf::FloatRect m_Bounds;

	sf::Vector2f m_Position;

	std::shared_ptr<Widget> m_ParentWidget;
	bool m_Center;

protected: //Protected methods
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void onHovered();
	virtual void onStopHovered();
	virtual void onPressed();
	virtual void onReleased();
	virtual void onClicked();

	bool isHovered();
	void updateState();
	virtual void updateRelativeParent();

	sf::Vector2i getMousePosScreen();
};

