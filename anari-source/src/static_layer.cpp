#include "anari/static_layer.hpp"
// White Object
StaticLayer::StaticLayer(/* args */) {}

StaticLayer::~StaticLayer() {}

const Color& StaticLayer::get_stroke_color() const noexcept
{
	return this->stroke_color;
}

const Color& StaticLayer::get_fill_color() const noexcept
{
	return this->fill_color;
}

const Curve& StaticLayer::get_geometry() const noexcept { return this->curve; }
