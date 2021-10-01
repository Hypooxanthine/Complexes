#include "Button.h"

Button::Button(std::shared_ptr<sf::RenderWindow> window) : Widget(window)
{
	m_Shapes["Normal"] = sf::RectangleShape();
	m_Shapes["Hovered"] = sf::RectangleShape();
	m_Shapes["Pressed"] = sf::RectangleShape();

	m_ActiveShape = &m_Shapes["Normal"];
}

void Button::setPosition(const sf::Vector2f& pos)
{
	Widget::setPosition(pos);

	for (std::pair<const std::string, sf::RectangleShape>& rs : m_Shapes)
		rs.second.setPosition(getAbsolutePosition());
}

void Button::setShapeColor(sf::Color col, std::string key)
{
	try {
		m_Shapes.at(key).setFillColor(col);
	}
	catch (std::out_of_range) {
		LOG_ERROR(key + " does not match any key from m_Shapes map.");
	}
}

void Button::setCallbackFn(const CallbackFn& fn)
{
	m_Callback = fn;
}

void Button::update(const float& dt)
{
	Widget::update(dt);
	updateActiveShape();
}

void Button::onClicked()
{
	if(m_Callback != NULL)
		m_Callback();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(m_ActiveShape != nullptr)
		target.draw(*m_ActiveShape);
}

void Button::updateActiveShape()
{
	switch (m_CursorState)
	{
	case CursorState::StateNormal:
		m_ActiveShape = &m_Shapes["Normal"];
		break;
	case CursorState::StateHovered:
		m_ActiveShape = &m_Shapes["Hovered"];
		break;
	case CursorState::StatePressed:
		m_ActiveShape = &m_Shapes["Pressed"];
		break;
	default:
		m_ActiveShape = &m_Shapes["Normal"];
		break;
	}
}

void Button::setSize(sf::Vector2f size)
{	
	for (std::pair<const std::string, sf::RectangleShape>& rs : m_Shapes)
		rs.second.setSize(size);

	m_Bounds.width = size.x;
	m_Bounds.height = size.y;
}
