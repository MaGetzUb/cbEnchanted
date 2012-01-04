#ifndef DRAWING_PRIMITIVES_H
#define DRAWING_PRIMITIVES_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Line: public sf::Drawable {
	public:
		Line(float x1, float y1, float x2, float y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
        void Draw(sf::RenderTarget &target, sf::RenderStates states) const;
	private:
		float x1, y1, x2, y2;
};

class Circle: public sf::Drawable {
	public:
		Circle(float cx, float cy, float r, bool f) : cx(cx), cy(cy), r(r), fill(f) {}
        void Draw(sf::RenderTarget &target, sf::RenderStates states) const;
	private:
		float cx, cy, r;
		bool fill;
};

#endif
