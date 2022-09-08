#include "PlayMode.hpp"

//for the GL_ERRORS() macro:
#include "gl_errors.hpp"

//for glm::value_ptr() :
#include <glm/gtc/type_ptr.hpp>

#include <random>
#include <iostream>

/*
Notes:
- One room
- Filled with x by y tiles all with a number associated with them
- tiles need a name to connect to a texture
- Tiles also probably need a pointer to connect between tiles? Could also just move the main sprite around
- 
*/


PlayMode::PlayMode() {
	//TODO:
	// you *must* use an asset pipeline of some sort to generate tiles.
	// don't hardcode them like this!
	// or, at least, if you do hardcode them like this,
	//  make yourself a script that spits out the code that you paste in here
	//   and check that script into your repository.

	//Also, *don't* use these tiles in your game:

	// MY CODE

	// palettes

	// slime
	// transparent - 0, 0, 0, 0
	// blue - 84, 135, 255
	// black - 0, 0, 0, 255
	// misc - 0, 0, 0, 255
	ppu.palette_table[0] = {
		glm::u8vec4(0x00, 0x00, 0x00, 0x00),
		glm::u8vec4(0x54, 0x87, 0xff, 0xff),
		glm::u8vec4(0x00, 0x00, 0x00, 0xff),
		glm::u8vec4(0x00, 0x00, 0x00, 0xff),
	};	

	// apples
	// transparent - 0, 0, 0, 0
	// red - 237, 28, 36, 255 
	// white - 255, 255, 255, 255
	// green - 12, 102, 36, 255
	ppu.palette_table[1] = {
		glm::u8vec4(0x00, 0x00, 0x00, 0x00),
		glm::u8vec4(0xed, 0x1c, 0x24, 0xff),
		glm::u8vec4(0xff, 0xff, 0xff, 0xff),
		glm::u8vec4(0x0c, 0x66, 0x24, 0xff),
	};	

	// walls
	// transparent - 0, 0, 0, 0
	// green - 30, 230, 86, 255 
	// misc - 0, 0, 0, 255
	// misc - 0, 0, 0, 255
	ppu.palette_table[2] = {
		glm::u8vec4(0x00, 0x00, 0x00, 0x00),
		glm::u8vec4(0x1e, 0xe6, 0x56, 0xff),
		glm::u8vec4(0x00, 0x00, 0x00, 0xff),
		glm::u8vec4(0x00, 0x00, 0x00, 0xff),
	};	

	// tiles

	// need four for each apple - 36 tiles
	// need four for slime - 4 tiles
	// generate code from script.py and paste here

	// player from slime.py: tiles 0 - 3
    ppu.tile_table[0].bit0 = {
        0b00011111,
        0b00111111,
        0b01111111,
        0b11111000,
        0b11110111,
        0b11111111,
        0b11111111,
        0b11111111
    };

    ppu.tile_table[0].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000111,
        0b00001000,
        0b00000000,
        0b00000000,
        0b00000000
    };

    ppu.tile_table[1].bit0 = {
        0b11111000,
        0b11111100,
        0b11111110,
        0b00011111,
        0b11101111,
        0b11111111,
        0b11111111,
        0b11111111
    };

    ppu.tile_table[1].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b11100000,
        0b00010000,
        0b00000000,
        0b00000000,
        0b00000000
    };

    ppu.tile_table[2].bit0 = {
        0b11110111,
        0b11110111,
        0b01111111,
        0b00111111,
        0b00000111,
        0b00000011,
        0b00000001,
        0b00000001
    };

    ppu.tile_table[2].bit1 = {
        0b00001000,
        0b00001000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };

    ppu.tile_table[3].bit0 = {
        0b11101111,
        0b11101111,
        0b11111110,
        0b11111100,
        0b11100000,
        0b11000000,
        0b10000000,
        0b10000000
    };

    ppu.tile_table[3].bit1 = {
        0b00010000,
        0b00010000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };

	// apples from apples.py: tiles 4 - 39
    ppu.tile_table[4].bit0 = {
        0b00001111,
        0b00011111,
        0b00111111,
        0b01111000,
        0b11111000,
        0b11111110,
        0b11111110,
        0b11111110
    };
    ppu.tile_table[4].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000111,
        0b00000111,
        0b00000001,
        0b00000001,
        0b00000001
    };
    ppu.tile_table[5].bit0 = {
        0b11110000,
        0b11111000,
        0b11111100,
        0b00011110,
        0b00011111,
        0b01111111,
        0b01111111,
        0b01111111
    };
    ppu.tile_table[5].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b11100000,
        0b11100000,
        0b10000000,
        0b10000000,
        0b10000000
    };
    ppu.tile_table[6].bit0 = {
        0b11111110,
        0b01111110,
        0b00111110,
        0b00011111,
        0b00001111,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[6].bit1 = {
        0b00000001,
        0b00000001,
        0b00000001,
        0b00000000,
        0b00000000,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[7].bit0 = {
        0b00011111,
        0b00111110,
        0b01111100,
        0b11111000,
        0b11110000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[7].bit1 = {
        0b11100000,
        0b11000000,
        0b10000000,
        0b00000000,
        0b00000000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[8].bit0 = {
        0b00001111,
        0b00011111,
        0b00111111,
        0b01111000,
        0b11111000,
        0b11111111,
        0b11111000,
        0b11111000
    };
    ppu.tile_table[8].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000111,
        0b00000111,
        0b00000000,
        0b00000111,
        0b00000111
    };
    ppu.tile_table[9].bit0 = {
        0b11110000,
        0b11111000,
        0b11111100,
        0b00011110,
        0b00011111,
        0b10011111,
        0b00011111,
        0b00011111
    };
    ppu.tile_table[9].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b11100000,
        0b11100000,
        0b01100000,
        0b11100000,
        0b11100000
    };
    ppu.tile_table[10].bit0 = {
        0b11111001,
        0b01111000,
        0b00111000,
        0b00011111,
        0b00001111,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[10].bit1 = {
        0b00000110,
        0b00000111,
        0b00000111,
        0b00000000,
        0b00000000,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[11].bit0 = {
        0b11111111,
        0b00011110,
        0b00011100,
        0b11111000,
        0b11110000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[11].bit1 = {
        0b00000000,
        0b11100000,
        0b11100000,
        0b00000000,
        0b00000000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[12].bit0 = {
        0b00001111,
        0b00011111,
        0b00111111,
        0b01111000,
        0b11111000,
        0b11111001,
        0b11111000,
        0b11111000
    };
    ppu.tile_table[12].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000111,
        0b00000111,
        0b00000110,
        0b00000111,
        0b00000111
    };
    ppu.tile_table[13].bit0 = {
        0b11110000,
        0b11111000,
        0b11111100,
        0b00011110,
        0b00011111,
        0b11111111,
        0b00011111,
        0b00011111
    };
    ppu.tile_table[13].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b11100000,
        0b11100000,
        0b00000000,
        0b11100000,
        0b11100000
    };
    ppu.tile_table[14].bit0 = {
        0b11111001,
        0b01111000,
        0b00111000,
        0b00011111,
        0b00001111,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[14].bit1 = {
        0b00000110,
        0b00000111,
        0b00000111,
        0b00000000,
        0b00000000,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[15].bit0 = {
        0b11111111,
        0b00011110,
        0b00011100,
        0b11111000,
        0b11110000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[15].bit1 = {
        0b00000000,
        0b11100000,
        0b11100000,
        0b00000000,
        0b00000000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[16].bit0 = {
        0b00001111,
        0b00011111,
        0b00111111,
        0b01111001,
        0b11111001,
        0b11111001,
        0b11111000,
        0b11111000
    };
    ppu.tile_table[16].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000110,
        0b00000110,
        0b00000110,
        0b00000111,
        0b00000111
    };
    ppu.tile_table[17].bit0 = {
        0b11110000,
        0b11111000,
        0b11111100,
        0b11111110,
        0b11111111,
        0b11111111,
        0b00011111,
        0b00011111
    };
    ppu.tile_table[17].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b11100000,
        0b11100000
    };
    ppu.tile_table[18].bit0 = {
        0b11111001,
        0b01111001,
        0b00111001,
        0b00011111,
        0b00001111,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[18].bit1 = {
        0b00000110,
        0b00000110,
        0b00000110,
        0b00000000,
        0b00000000,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[19].bit0 = {
        0b10011111,
        0b10011110,
        0b10011100,
        0b11111000,
        0b11110000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[19].bit1 = {
        0b01100000,
        0b01100000,
        0b01100000,
        0b00000000,
        0b00000000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[20].bit0 = {
        0b00001111,
        0b00011111,
        0b00111111,
        0b01111000,
        0b11111000,
        0b11111001,
        0b11111000,
        0b11111000
    };
    ppu.tile_table[20].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000111,
        0b00000111,
        0b00000110,
        0b00000111,
        0b00000111
    };
    ppu.tile_table[21].bit0 = {
        0b11110000,
        0b11111000,
        0b11111100,
        0b00011110,
        0b00011111,
        0b11111111,
        0b00011111,
        0b00011111
    };
    ppu.tile_table[21].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b11100000,
        0b11100000,
        0b00000000,
        0b11100000,
        0b11100000
    };
    ppu.tile_table[22].bit0 = {
        0b11111111,
        0b01111000,
        0b00111000,
        0b00011111,
        0b00001111,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[22].bit1 = {
        0b00000000,
        0b00000111,
        0b00000111,
        0b00000000,
        0b00000000,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[23].bit0 = {
        0b10011111,
        0b00011110,
        0b00011100,
        0b11111000,
        0b11110000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[23].bit1 = {
        0b01100000,
        0b11100000,
        0b11100000,
        0b00000000,
        0b00000000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[24].bit0 = {
        0b00001111,
        0b00011111,
        0b00111111,
        0b01111000,
        0b11111000,
        0b11111001,
        0b11111000,
        0b11111000
    };
    ppu.tile_table[24].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000111,
        0b00000111,
        0b00000110,
        0b00000111,
        0b00000111
    };
    ppu.tile_table[25].bit0 = {
        0b11110000,
        0b11111000,
        0b11111100,
        0b00011110,
        0b00011111,
        0b10011111,
        0b00011111,
        0b00011111
    };
    ppu.tile_table[25].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b11100000,
        0b11100000,
        0b01100000,
        0b11100000,
        0b11100000
    };
    ppu.tile_table[26].bit0 = {
        0b11111111,
        0b01111000,
        0b00111000,
        0b00011111,
        0b00001111,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[26].bit1 = {
        0b00000000,
        0b00000111,
        0b00000111,
        0b00000000,
        0b00000000,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[27].bit0 = {
        0b10011111,
        0b00011110,
        0b00011100,
        0b11111000,
        0b11110000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[27].bit1 = {
        0b01100000,
        0b11100000,
        0b11100000,
        0b00000000,
        0b00000000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[28].bit0 = {
        0b00001111,
        0b00011111,
        0b00111111,
        0b01111001,
        0b11111001,
        0b11111001,
        0b11111001,
        0b11111001
    };
    ppu.tile_table[28].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000110,
        0b00000110,
        0b00000110,
        0b00000110,
        0b00000110
    };
    ppu.tile_table[29].bit0 = {
        0b11110000,
        0b11111000,
        0b11111100,
        0b11111110,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111
    };
    ppu.tile_table[29].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };
    ppu.tile_table[30].bit0 = {
        0b11111001,
        0b01111000,
        0b00111000,
        0b00011111,
        0b00001111,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[30].bit1 = {
        0b00000110,
        0b00000111,
        0b00000111,
        0b00000000,
        0b00000000,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[31].bit0 = {
        0b10011111,
        0b00011110,
        0b00011100,
        0b11111000,
        0b11110000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[31].bit1 = {
        0b01100000,
        0b11100000,
        0b11100000,
        0b00000000,
        0b00000000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[32].bit0 = {
        0b00001111,
        0b00011111,
        0b00111111,
        0b01111000,
        0b11111000,
        0b11111001,
        0b11111000,
        0b11111000
    };
    ppu.tile_table[32].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000111,
        0b00000111,
        0b00000110,
        0b00000111,
        0b00000111
    };
    ppu.tile_table[33].bit0 = {
        0b11110000,
        0b11111000,
        0b11111100,
        0b00011110,
        0b00011111,
        0b10011111,
        0b00011111,
        0b00011111
    };
    ppu.tile_table[33].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b11100000,
        0b11100000,
        0b01100000,
        0b11100000,
        0b11100000
    };
    ppu.tile_table[34].bit0 = {
        0b11111001,
        0b01111000,
        0b00111000,
        0b00011111,
        0b00001111,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[34].bit1 = {
        0b00000110,
        0b00000111,
        0b00000111,
        0b00000000,
        0b00000000,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[35].bit0 = {
        0b10011111,
        0b00011110,
        0b00011100,
        0b11111000,
        0b11110000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[35].bit1 = {
        0b01100000,
        0b11100000,
        0b11100000,
        0b00000000,
        0b00000000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[36].bit0 = {
        0b00001111,
        0b00011111,
        0b00111111,
        0b01111000,
        0b11111000,
        0b11111001,
        0b11111000,
        0b11111000
    };
    ppu.tile_table[36].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000111,
        0b00000111,
        0b00000110,
        0b00000111,
        0b00000111
    };
    ppu.tile_table[37].bit0 = {
        0b11110000,
        0b11111000,
        0b11111100,
        0b00011110,
        0b00011111,
        0b11111111,
        0b00011111,
        0b00011111
    };
    ppu.tile_table[37].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b11100000,
        0b11100000,
        0b00000000,
        0b11100000,
        0b11100000
    };
    ppu.tile_table[38].bit0 = {
        0b11111001,
        0b01111000,
        0b00111000,
        0b00011111,
        0b00001111,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[38].bit1 = {
        0b00000110,
        0b00000111,
        0b00000111,
        0b00000000,
        0b00000000,
        0b00000011,
        0b00000011,
        0b00000111
    };
    ppu.tile_table[39].bit0 = {
        0b10011111,
        0b00011110,
        0b00011100,
        0b11111000,
        0b11110000,
        0b11000000,
        0b11000000,
        0b10000000
    };
    ppu.tile_table[39].bit1 = {
        0b01100000,
        0b11100000,
        0b11100000,
        0b00000000,
        0b00000000,
        0b11000000,
        0b11000000,
        0b10000000
    };

	// player but sad

	ppu.tile_table[41].bit0 = {
        0b00011111,
        0b00111111,
        0b01110111,
        0b11111000,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111
    };

    ppu.tile_table[41].bit1 = {
        0b00000000,
        0b00000000,
        0b00001000,
        0b00000111,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };

    ppu.tile_table[42].bit0 = {
        0b11111000,
        0b11111100,
        0b11101110,
        0b00011111,
        0b11111111,
        0b11111111,
        0b11111111,
        0b11111111
    };

    ppu.tile_table[42].bit1 = {
        0b00000000,
        0b00000000,
        0b00010000,
        0b11100000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };

    ppu.tile_table[43].bit0 = {
        0b11110111,
        0b11110111,
        0b01111111,
        0b00111111,
        0b00000111,
        0b00000011,
        0b00000001,
        0b00000001
    };

    ppu.tile_table[43].bit1 = {
        0b00001000,
        0b00001000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };

    ppu.tile_table[44].bit0 = {
        0b11101111,
        0b11101111,
        0b11111110,
        0b11111100,
        0b11100000,
        0b11000000,
        0b10000000,
        0b10000000
    };

    ppu.tile_table[44].bit1 = {
        0b00010000,
        0b00010000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };

	// background

    ppu.tile_table[40].bit0 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };
    ppu.tile_table[40].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };

	// walls from walls.py
    ppu.tile_table[45].bit0 = {
        0b11100000,
        0b11100000,
        0b11100000,
        0b11100000,
        0b11100000,
        0b11100000,
        0b11100000,
        0b11100000
    };
    ppu.tile_table[45].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };
    ppu.tile_table[46].bit0 = {
        0b11111111,
        0b11111111,
        0b11111111,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };
    ppu.tile_table[46].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };
    ppu.tile_table[47].bit0 = {
        0b00000111,
        0b00000111,
        0b00000111,
        0b00000111,
        0b00000111,
        0b00000111,
        0b00000111,
        0b00000111
    };
    ppu.tile_table[47].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };
    ppu.tile_table[48].bit0 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b11111111,
        0b11111111,
        0b11111111
    };
    ppu.tile_table[48].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };

	// corners
    ppu.tile_table[49].bit0 = {
        0b11111111,
        0b11111111,
        0b11111111,
        0b11100000,
        0b11100000,
        0b11100000,
        0b11100000,
        0b11100000
    };
    ppu.tile_table[49].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };
    ppu.tile_table[50].bit0 = {
        0b11100000,
        0b11100000,
        0b11100000,
        0b11100000,
        0b11100000,
        0b11111111,
        0b11111111,
        0b11111111
    };
    ppu.tile_table[50].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };
    ppu.tile_table[51].bit0 = {
        0b11111111,
        0b11111111,
        0b11111111,
        0b00000111,
        0b00000111,
        0b00000111,
        0b00000111,
        0b00000111
    };
    ppu.tile_table[51].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };
    ppu.tile_table[52].bit0 = {
        0b00000111,
        0b00000111,
        0b00000111,
        0b00000111,
        0b00000111,
        0b11111111,
        0b11111111,
        0b11111111
    };
    ppu.tile_table[52].bit1 = {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    };

	// make background transparent
	for (uint32_t y = 0; y < PPU466::BackgroundHeight; ++y) {
		for (uint32_t x = 0; x < PPU466::BackgroundWidth; ++x) {
			ppu.background[x+PPU466::BackgroundWidth*y] = 40;
		}
	}
	// draw walls
	for(uint32_t x = 10; x < 22; x++) {
		ppu.background[x+PPU466::BackgroundWidth*10] = (2 << 8) | (46);
	}
	for(uint32_t x = 10; x < 22; x++) {
		ppu.background[x+PPU466::BackgroundWidth*21] = (2 << 8) | (48);
	}
	for(uint32_t y = 10; y < 22; y++) {
		ppu.background[10+PPU466::BackgroundWidth*y] = (2 << 8) | (47);
	}
	for(uint32_t y = 10; y < 22; y++) {
		ppu.background[21+PPU466::BackgroundWidth*y] = (2 << 8) | (45);
	}

	ppu.background[10+PPU466::BackgroundWidth*10] = (2 << 8) | (51);
	ppu.background[21+PPU466::BackgroundWidth*10] = (2 << 8) | (49);
	ppu.background[10+PPU466::BackgroundWidth*21] = (2 << 8) | (52);
	ppu.background[21+PPU466::BackgroundWidth*21] = (2 << 8) | (50);

	// apples
	// https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, 9); // define the range
	uint8_t j = 0;
	for(uint8_t i = 0; i < 16; ++i) {
		if(i == 9) {
			i = i + 1;
		}
		// update apple values
		uint8_t val = (uint8_t)(distr(gen) & 0xff);
		apples[j].value = val;
		apples[j].apple_at = glm::vec2(92 + 24 * (i % 4), 164 - 24 * (i / 4));
		apples[j].alive = true;
		apples[j].sprite_idx = i * 4;

		// update corresponding 4 sprites
		ppu.sprites[i * 4 + 0].x = int8_t(apples[j].apple_at.x);
		ppu.sprites[i * 4 + 0].y = int8_t(apples[j].apple_at.y - 8);
		ppu.sprites[i * 4 + 0].index = val * 4 + 0;
		ppu.sprites[i * 4 + 0].attributes = 1;

		ppu.sprites[i * 4 + 1].x = int8_t(apples[j].apple_at.x - 8);
		ppu.sprites[i * 4 + 1].y = int8_t(apples[j].apple_at.y - 8);
		ppu.sprites[i * 4 + 1].index = val * 4 + 1;
		ppu.sprites[i * 4 + 1].attributes = 1;

		ppu.sprites[i * 4 + 2].x = int8_t(apples[j].apple_at.x);
		ppu.sprites[i * 4 + 2].y = int8_t(apples[j].apple_at.y);
		ppu.sprites[i * 4 + 2].index = val * 4 + 2;
		ppu.sprites[i * 4 + 2].attributes = 1;

		ppu.sprites[i * 4 + 3].x = int8_t(apples[j].apple_at.x - 8);
		ppu.sprites[i * 4 + 3].y = int8_t(apples[j].apple_at.y);
		ppu.sprites[i * 4 + 3].index = val * 4 + 3;
		ppu.sprites[i * 4 + 3].attributes = 1;

		// increment other counter
		j = j + 1;
	}	
	// draw player
	ppu.sprites[36].x = int8_t(user.player_at.x);
	ppu.sprites[36].y = int8_t(user.player_at.y - 8);
	ppu.sprites[36].index = 0;
	ppu.sprites[36].attributes = 0;

	ppu.sprites[37].x = int8_t(user.player_at.x - 8);
	ppu.sprites[37].y = int8_t(user.player_at.y - 8);
	ppu.sprites[37].index = 1;
	ppu.sprites[37].attributes = 0;

	ppu.sprites[38].x = int8_t(user.player_at.x);
	ppu.sprites[38].y = int8_t(user.player_at.y);
	ppu.sprites[38].index = 2;
	ppu.sprites[38].attributes = 0;

	ppu.sprites[39].x = int8_t(user.player_at.x - 8);
	ppu.sprites[39].y = int8_t(user.player_at.y);
	ppu.sprites[39].index = 3;
	ppu.sprites[39].attributes = 0;
}

PlayMode::~PlayMode() {
}

void PlayMode::game_over() {
	// set apples to be nothing
	uint8_t j = 0;
	for(uint8_t i = 0; i < 16; ++i) {
		if(i == 9) {
			i = i + 1;
		}
		apples[j].alive = false;

		// update corresponding 4 sprites
		ppu.sprites[i * 4 + 0].index = 40;
		ppu.sprites[i * 4 + 1].index = 40;
		ppu.sprites[i * 4 + 2].index = 40;
		ppu.sprites[i * 4 + 3].index = 40;

		// increment other counter
		j = j + 1;
	}
	// set player to be sad and stuck wherever they are
	ppu.sprites[36].index = 41;
	ppu.sprites[37].index = 42;
	ppu.sprites[38].index = 43;
	ppu.sprites[39].index = 44;
	go = true;

	// set movement to false
	left.pressed = false;
	right.pressed = false;
	down.pressed = false;
	up.pressed = false;
	move = false;
	space.pressed = false;
}

// https://stackoverflow.com/questions/20925818/algorithm-to-check-if-two-boxes-overlap
bool PlayMode::overlap(glm::vec2 box1x, glm::vec2 box1y, glm::vec2 box2x, glm::vec2 box2y) {
	return (box1x.y >= box2x.x) && (box2x.y >= box1x.x) && (box1y.y >= box2y.x) && (box2y.y >= box1y.x);
}

bool PlayMode::handle_event(SDL_Event const &evt, glm::uvec2 const &window_size) {

	if (evt.type == SDL_KEYDOWN && !go) {
		if (evt.key.keysym.sym == SDLK_LEFT) {
			left.downs += 1;
			left.pressed = true;
			move = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_RIGHT) {
			right.downs += 1;
			right.pressed = true;
			move = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_UP) {
			up.downs += 1;
			up.pressed = true;
			move = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_DOWN) {
			down.downs += 1;
			down.pressed = true;
			move = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_SPACE) {
			// https://stackoverflow.com/questions/48994893/sdl-keydown-not-recognizing-some-keystrokes-a-z-0-9-space
			space.downs += 1;
			space.pressed = true;
			return true;
		}
	} else if (evt.type == SDL_KEYUP && !go) {
		if (evt.key.keysym.sym == SDLK_LEFT) {
			left.pressed = false;
			move = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_RIGHT) {
			right.pressed = false;
			move = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_UP) {
			up.pressed = false;
			move = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_DOWN) {
			down.pressed = false;
			move = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_SPACE) {
			space.pressed = false;
			return true;
		}
	}

	return false;
}


void PlayMode::update(float elapsed) {
	timer += elapsed;
	if((timer > 30.f) && (num_apples_dead < 15)) {
		if(text_flag) {
			std::cout << "You ran out of time :(\n";
		}
		text_flag = false;
		game_over();
	}
	else if (num_apples_dead == 15) {
		if(text_flag) {
			std::cout << "Congrats, you cleared the board!\n";
		}
		text_flag = false;
		left.pressed = false;
		right.pressed = false;
		down.pressed = false;
		up.pressed = false;
		move = false;
		space.pressed = false;
		go = true;
	}
	constexpr float PlayerSpeed = 60.0f;
	if (left.pressed) user.player_at.x = std::min(std::max(user.player_at.x - PlayerSpeed * elapsed, 92.0f), 164.0f);
	if (right.pressed) user.player_at.x = std::min(std::max(user.player_at.x + PlayerSpeed * elapsed, 92.0f), 164.0f);
	if (down.pressed) user.player_at.y = std::min(std::max(user.player_at.y - PlayerSpeed * elapsed, 92.0f), 164.0f);
	if (up.pressed) user.player_at.y = std::min(std::max(user.player_at.y + PlayerSpeed * elapsed, 92.0f), 164.0f);

	if (move) {
		glm::vec2 playerx = glm::vec2(user.player_at.x - 8, user.player_at.x + 8);
		glm::vec2 playery = glm::vec2(user.player_at.y - 8, user.player_at.y + 8);

		for(Apple &apple : apples) {
			if(apple.alive) {
				glm::vec2 applex = glm::vec2(apple.apple_at.x - 8, apple.apple_at.x + 8);
				glm::vec2 appley = glm::vec2(apple.apple_at.y - 8, apple.apple_at.y + 8);
				if(overlap(playerx, playery, applex, appley)) {
					user.value += apple.value;
					ppu.sprites[apple.sprite_idx + 0].index = 40;
					ppu.sprites[apple.sprite_idx + 1].index = 40;
					ppu.sprites[apple.sprite_idx + 2].index = 40;
					ppu.sprites[apple.sprite_idx + 3].index = 40;
					apple.alive = false;
					user.num_apples += 1;
					num_apples_dead += 1;
				}
			}
		}
		if(user.num_apples > 5) {
			if(text_flag) {
				std::cout << "You ate too many apples :(\n";
			}
			text_flag = false;
			game_over();
		}
	}
	if(space.pressed) {
		// check player value
		// if good then keep playing
		bool check = false;

		for(uint8_t i = 0; i < primes.size(); ++i) {
			if(primes[i] == user.value) {
				check = true;
				break;
			}
		}
		if(check && (user.num_apples <= 5)) {
			std::cout << "Nice, you ate " << (uint32_t)user.value << " apples!\n";
			user.value = 0;
			user.num_apples = 0;
		}
		else {
			if(text_flag) {
				std::cout << "Not a prime number!\n";
			}
			text_flag = false;
			game_over();
		}
		space.pressed = false;
	}
	//reset button press counters:
	left.downs = 0;
	right.downs = 0;
	up.downs = 0;
	down.downs = 0;
	space.downs = 0;
}

void PlayMode::draw(glm::uvec2 const &drawable_size) {
	//--- set ppu state based on game state ---

	//background color will be some hsv-like fade:
	ppu.background_color = glm::u8vec4(0x00, 0x00, 0x00, 0xff);

	// No background scroll:
	// ppu.background_position.x = int32_t(-0.5f * player_at.x);
	// ppu.background_position.y = int32_t(-0.5f * player_at.y);

	//player sprite 36-39:
	ppu.sprites[36].x = int8_t(user.player_at.x);
	ppu.sprites[36].y = int8_t(user.player_at.y - 8);

	ppu.sprites[37].x = int8_t(user.player_at.x - 8);
	ppu.sprites[37].y = int8_t(user.player_at.y - 8);

	ppu.sprites[38].x = int8_t(user.player_at.x);
	ppu.sprites[38].y = int8_t(user.player_at.y);

	ppu.sprites[39].x = int8_t(user.player_at.x - 8);
	ppu.sprites[39].y = int8_t(user.player_at.y);


	//--- actually draw ---
	ppu.draw(drawable_size);
}
