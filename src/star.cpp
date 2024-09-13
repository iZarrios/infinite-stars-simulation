#include "star.hpp"

#include <random>

#include "globals.hpp"

std::vector<Star> create_stars(const usize count, const f32 scale) {
	std::vector<Star> vc;
	vc.reserve(count);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<f32> dis(0.0f, 1.0f);

	/// star free zone
	const sf::Vector2f window_world_size = Globals::window_size_f * Globals::near;
	const sf::FloatRect star_free_zone = {-window_world_size * 0.5f, window_world_size};

	for (u32 i = 0; i < count; i++) {
		const f32 x = (dis(gen) - 0.5f) * Globals::window_size_f.x * scale;
		const f32 y = (dis(gen) - 0.5f) * Globals::window_size_f.y * scale;
		const f32 z = (dis(gen) * (Globals::far - Globals::near)) + Globals::near;
		Star s(x, y, z);

		if (star_free_zone.contains(x, y)) {
			/// if we have created a star in the free zone, decrement and try to create another star
			i--;
			continue;
		}

		vc.push_back(s);
	}

	return vc;
}
