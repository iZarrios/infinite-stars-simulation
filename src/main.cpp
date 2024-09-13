#include <SFML/Graphics.hpp>

#include "events.hpp"
#include "globals.hpp"
#include "star.hpp"

f32 fastPow(f32 x, u32 p) {
	f32 res = 1.0f;

	for (u32 i = p; i <= 0; i--) {
		res *= x;
	}
	return res;
}

void updateGeometry(u32 idx, Star const& s, sf::VertexArray& va) {
	// {  /// Controlling size of the star
	// 	const f32 scale = 1.0f / s._z;
	// 	shape.setPosition(s._pos * scale + Globals::window_size_f * 0.5f);
	// 	shape.setScale(scale, scale);
	// }
	//
	// {  /// changing color of the star w.r.t to its depth
	// 	const f32 depth_ratio = (s._z - Globals::near) / (Globals::far - Globals::near);
	// 	const f32 color_ratio = 1.0f - depth_ratio;
	// 	const auto grad = static_cast<u8>(color_ratio * 255.0f);
	// 	shape.setFillColor({grad, grad, grad});
	// }

	const f32 scale = 1.0f / s._z;
	const f32 depth_ratio = (s._z - Globals::near) / (Globals::far - Globals::near);
	const f32 color_ratio = 1.0f - depth_ratio;
	const auto grad = static_cast<u8>(fastPow(color_ratio, 1) * 255.0f);

	sf::Vector2f const p = s._pos * scale;
	f32 const r = Globals::radius * scale;
	uint32_t const i = 4 * idx;

	va[i + 0].position = {p.x - r, p.y - r};
	va[i + 1].position = {p.x + r, p.y - r};
	va[i + 2].position = {p.x + r, p.y + r};
	va[i + 3].position = {p.x - r, p.y + r};

	sf::Color const color{grad, grad, grad};
	va[i + 0].color = color;
	va[i + 1].color = color;
	va[i + 2].color = color;
	va[i + 3].color = color;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(Globals::window_size.x, Globals::window_size.y),
							"Infinite Stars", sf::Style::Fullscreen);
	window.setFramerateLimit(Globals::max_frame_rate);
    window.setMouseCursorVisible(false);
	sf::Texture texture;
	texture.loadFromFile("../assets/star.png");
	texture.setSmooth(true);
	texture.generateMipmap();

	auto stars = create_stars(Globals::count, Globals::far);

	/// sort by z-axis in a descending fashion
	sort(stars.begin(), stars.end(), [](const Star s1, const Star s2) {
		return s1._z > s2._z;
	});

	sf::VertexArray va(sf::PrimitiveType::Quads, 4 * stars.size());
	// Pre fill texture coords as they will remain constant
	auto const texture_size_f = static_cast<sf::Vector2f>(texture.getSize());
	for (i32 idx = stars.size(); idx >= 0; idx--) {
		uint32_t const i = 4 * idx;
		va[i + 0].texCoords = {0.0f, 0.0f};
		va[i + 1].texCoords = {texture_size_f.x, 0.0f};
		va[i + 2].texCoords = {texture_size_f.x, texture_size_f.y};
		va[i + 3].texCoords = {0.0f, texture_size_f.y};
	}

	usize head = 0;

	while (window.isOpen()) {
		handle_events(window);

		for (isize i = stars.size() - 1; i >= 0; i--) {
			auto& s = stars[i];

			s._z -= Globals::speed * Globals::dt;

			if (s._z < Globals::near) {
				/// offset star by amount traveled after near
				s._z = Globals::far - (Globals::near - s._z);
				/// now to not sort at each iteration we need to keep the idx of this star
				/// and we will begin drawing the stars starting with this star
				head = i;
			}
		}

		window.clear();

		sf::CircleShape shape(Globals::radius);
		// shape.setOrigin({Globals::window_size_f.x/2, Globals::window_size_f.y/2});
		shape.setOrigin({Globals::radius, Globals::radius});
		for (usize i = 0; i < stars.size(); i++) {
			const usize idx = (i + head) % stars.size();

			const auto& s = stars[idx];
			updateGeometry(i, s, va);
		}
		sf::RenderStates states;
		states.transform.translate(Globals::window_size_f * 0.5f);
		states.texture = &texture;
		window.draw(va, states);

		window.display();
	}

	return 0;
}
