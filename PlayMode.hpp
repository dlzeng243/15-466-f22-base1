#include "PPU466.hpp"
#include "Mode.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up, space;


	//player position:
	struct Player {
		// center of 16 x 16, can use this to compute the four positions of the sprite
		glm::vec2 player_at = glm::vec2(116.0f, 116.0f);

		// value of apples eaten this interval
		uint8_t value = 0;

		// number of apples eaten this interval
		uint8_t num_apples = 0;

		// bbox can be computed from player location
	} user;

	struct Apple {
		// center of 16 x 16, can use this to compute the four positions of the sprite
		glm::vec2 apple_at = glm::vec2(128.0f, 120.0f);

		// value of apple
		uint8_t value = 0;

		// bbox can be computed from apple location
		bool alive = false;
		uint8_t sprite_idx = 0;
	};
	// array of 60 / 4 = 15 apples
	std::array< Apple, 15> apples;

	// game over function
	void game_over();
	bool go = false;

	// overlap function
	bool overlap(glm::vec2 box1x, glm::vec2 box1y, glm::vec2 box2x, glm::vec2 box2y);
	bool move = false;

	// primes to check (max apples eaten is 45)
	std::array<uint8_t, 14> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 43, 47};

	//global timer
	float timer = 0.f;
	uint8_t num_apples_dead = 0;

	bool text_flag = true;
	//----- drawing handled by PPU466 -----

	PPU466 ppu;
};
