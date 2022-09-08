from PIL import Image
import numpy as np

f = open("tiles.txt", 'w')

for counter in range(1,10):

	#Read image
	# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html		
	im = Image.open( 'apple_' + str(counter) + '.png')

	# APPLES
	# palette table: transparent, red, white, green
	'''	
	ppu.palette_table[1] = {
		glm::u8vec4(0x00, 0x00, 0x00, 0x00),
		glm::u8vec4(0xed, 0x1c, 0x24, 0xff),
		glm::u8vec4(0xff, 0xff, 0xff, 0xff),
		glm::u8vec4(0x0c, 0x66, 0x24, 0xff),
	};	
	'''
	w, h = im.size
	bitTable = np.zeros((w, h, 2))
	# Turn colors into bit0 and bit1
	# https://stackoverflow.com/questions/3971459/how-to-loop-all-image-pixels-and-tell-whether-they-are-black-or-white

	for j in range(im.size[1]):
		for i in range(im.size[0]):
			r, g, b, a = im.getpixel((i, j))
			# transparent
			if r == 0:
				bitTable[j][i][0] = 0
				bitTable[j][i][1] = 0
			# red
			elif r == 237:
				bitTable[j][i][0] = 1
				bitTable[j][i][1] = 0
			# white
			elif r == 255:
				bitTable[j][i][0] = 0
				bitTable[j][i][1] = 1
			# green
			else:
				bitTable[j][i][0] = 1
				bitTable[j][i][1] = 1
	# correct orientation for ppu tiles
	bitTable = np.flip(bitTable, 0)
	bitTable = np.flip(bitTable, 1)

	# print tables to make sure it looks like the png
	print(bitTable[:, :, 0])
	print(bitTable[:, :, 1])

	# split into 4 tiles
	bit0_0 = bitTable[0:8, 0:8, 0]
	bit1_0 = bitTable[0:8, 0:8, 1]
	bit0_1 = bitTable[0:8, 8:16, 0]
	bit1_1 = bitTable[0:8, 8:16, 1]
	bit0_2 = bitTable[8:16, 0:8, 0]
	bit1_2 = bitTable[8:16, 0:8, 1]
	bit0_3 = bitTable[8:16, 8:16, 0]
	bit1_3 = bitTable[8:16, 8:16, 1]
	# turn into string: https://stackoverflow.com/questions/32658322/concatenate-numpy-string-array-along-an-axis
	# tabs: https://stackoverflow.com/questions/7643579/modify-the-width-of-a-tab-in-a-format-string
	# top left tile

	str0_0 = '\tppu.tile_table[' + str(4 * counter + 0) + '].bit0 = {\n' + ',\n'.join('\t\t0b' + ''.join(str(int(bit)) for bit in row) for row in bit0_0) + '\n\t};'
	str0_0 = str0_0.expandtabs(4)
	str1_0 = '\tppu.tile_table[' + str(4 * counter + 0) + '].bit1 = {\n' + ',\n'.join('\t\t0b' + ''.join(str(int(bit)) for bit in row) for row in bit1_0) + '\n\t};'
	str1_0 = str1_0.expandtabs(4)
	# top right tile
	str0_1 = '\tppu.tile_table[' + str(4 * counter + 1) + '].bit0 = {\n' + ',\n'.join('\t\t0b' + ''.join(str(int(bit)) for bit in row) for row in bit0_1) + '\n\t};'
	str0_1 = str0_1.expandtabs(4)
	str1_1 = '\tppu.tile_table[' + str(4 * counter + 1) + '].bit1 = {\n' + ',\n'.join('\t\t0b' + ''.join(str(int(bit)) for bit in row) for row in bit1_1) + '\n\t};'
	str1_1 = str1_1.expandtabs(4)
	# bottom left tile
	str0_2 = '\tppu.tile_table[' + str(4 * counter + 2) + '].bit0 = {\n' + ',\n'.join('\t\t0b' + ''.join(str(int(bit)) for bit in row) for row in bit0_2) + '\n\t};'
	str0_2 = str0_2.expandtabs(4)
	str1_2 = '\tppu.tile_table[' + str(4 * counter + 2) + '].bit1 = {\n' + ',\n'.join('\t\t0b' + ''.join(str(int(bit)) for bit in row) for row in bit1_2) + '\n\t};'
	str1_2 = str1_2.expandtabs(4)
	# bottom right tile
	str0_3 = '\tppu.tile_table[' + str(4 * counter + 3) + '].bit0 = {\n' + ',\n'.join('\t\t0b' + ''.join(str(int(bit)) for bit in row) for row in bit0_3) + '\n\t};'
	str0_3 = str0_3.expandtabs(4)
	str1_3 = '\tppu.tile_table[' + str(4 * counter + 3) + '].bit1 = {\n' + ',\n'.join('\t\t0b' + ''.join(str(int(bit)) for bit in row) for row in bit1_3) + '\n\t};'
	str1_3 = str1_3.expandtabs(4)

	# print out so we can copy to playmode.cpp
	strings = [str0_0, str1_0, str0_1, str1_1, str0_2, str1_2, str0_3, str1_3]
	for s in strings:
		f.write(s)
		f.write('\n')
