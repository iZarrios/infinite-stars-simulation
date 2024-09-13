#ifndef __STAR_HPP__
#define __STAR_HPP__

#include <vector>

#include "globals.hpp"

class Star {
   public:
	Star(f32 x, f32 y, f32 z) : _pos({x, y}), _z(z) {}

   public:
	sf::Vector2f _pos;
	f32 _z = 1.0f;
};

std::vector<Star> create_stars(const usize count, const f32 scale);

#endif	//__STAR_HPP__
