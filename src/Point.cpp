#include <ostream>
#include <SDL3pp/Point.hpp>
#include <SDL3pp/Rect.hpp>

namespace SDL3pp {

class Rect;

Point Point::get_clamped(const Rect& rect) const {
	Point p = *this;
	p.clamp(rect);
	return p;
}

Point& Point::clamp(const Rect& rect) {
	if (x < rect.get_x())
		x = rect.get_x();
	if (x > rect.get_x2())
		x = rect.get_x2();
	if (y < rect.get_y())
		y = rect.get_y();
	if (y > rect.get_y2())
		y = rect.get_y2();
	return *this;
}

Point Point::get_wrapped(const Rect& rect) const {
	Point p = *this;
	p.wrap(rect);
	return p;
}

Point& Point::wrap(const Rect& rect) {
	if (x < rect.get_x())
		x = rect.get_x() + rect.get_width() - 1 
			- (rect.get_x() - x + rect.get_width() - 1)
			 % rect.get_width();
	else if (x >= rect.get_x() + rect.get_width())
		x = rect.get_x() + (x - rect.get_x() - rect.get_width())
		 % rect.get_width();

	if (y < rect.get_y())
		y = rect.get_y() + rect.get_height() - 1 
		- (rect.get_y() - y + rect.get_height() - 1) 
		% rect.get_height();
	else if (y >= rect.get_y() + rect.get_height())
		y = rect.get_y() + (y - rect.get_y() - rect.get_height()) 
		% rect.get_height();

	return *this;
}

}

std::ostream& operator<<(std::ostream& stream, const SDL3pp::Point& point) {
	stream << "[x:" << point.get_x() << ",y:" << point.get_y() << "]";
	return stream;
}
