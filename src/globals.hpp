#ifndef __GLOBALS_HPP__
#define __GLOBALS_HPP__

#include <SFML/Graphics.hpp>
#include <cstddef>
#include <cstdint>

// Unsigned integer types
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

// Signed integer types
using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

// Floating point types
using f32 = float;
using f64 = double;

// Pointer-size types
using usize = std::size_t;
using isize = std::ptrdiff_t;

namespace Globals {

const sf::Vector2u window_size = {1920, 1080};
const sf::Vector2f window_size_f = static_cast<sf::Vector2f>(window_size);
const u32 max_frame_rate = 144;
const f32 dt = 1.0f / static_cast<f32>(max_frame_rate);

/// Star specific globals
const usize count = 10'000;
const f32 radius = 30.0f;
const f32 near = 0.01f;
const f32 far = 10.0f;
const f32 speed = 5.0f;

};	// namespace Globals

#endif	//__GLOBALS_HPP__
