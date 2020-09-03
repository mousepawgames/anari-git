#include "anari/static_layer.hpp"
// White Object
StaticLayer::StaticLayer(/* args */)
{
}

StaticLayer::~StaticLayer() {}

Color& StaticLayer::get_color() { return object_color; }

FlexArray<Coordinate> StaticLayer::get_transformation_points()
{
	return transformation_points;
}

FlexArray<Coordinate> StaticLayer::get_object_points() { return object_points; }
