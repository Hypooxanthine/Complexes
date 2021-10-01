#pragma once

#include <map>

#include "Widget.h"
#include <functional>

#define BIND_BUTTON_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

class Button : public Widget
{
	using CallbackFn = std::function<void()>;
public: //Constructors
	Button(std::shared_ptr<sf::RenderWindow> window);

public: //Public methods
	void setSize(sf::Vector2f size);

	virtual void update(const float& dt) override;

	virtual void setPosition(const sf::Vector2f& pos) override;
	void setShapeColor(sf::Color col, std::string key);

	void setCallbackFn(const CallbackFn& fn);

protected: //Protected attributes
	std::map<std::string, sf::RectangleShape> m_Shapes;
	sf::RectangleShape* m_ActiveShape;

	CallbackFn m_Callback;
	virtual void onClicked() override;

protected: //Protected methods
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void updateActiveShape();
};

