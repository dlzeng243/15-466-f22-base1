from PIL import Image
import numpy as np

f = open("walls.txt", 'w')

for counter in range(1,5):
    # Read image
    # https://pillow.readthedocs.io/en/stable/handbook/tutorial.html
    im = Image.open( 'wall' + str(counter) +'.png' )


    # WALL BACKGROUND
    # palette table: transparent, green, misc, misc
    '''	
        ppu.palette_table[2] = {
            glm::u8vec4(0x00, 0x00, 0x00, 0x00),
            glm::u8vec4(0x1e, 0xe6, 0x56, 0xff),
            glm::u8vec4(0x00, 0x00, 0x00, 0xff),
            glm::u8vec4(0x00, 0x00, 0x00, 0xff),
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
            if a == 0:
                bitTable[j][i][0] = 0
                bitTable[j][i][1] = 0
            # green
            else:
                bitTable[j][i][0] = 1
                bitTable[j][i][1] = 0
    # correct orientation for ppu tiles
    bitTable = np.flip(bitTable, 0)
    bitTable = np.flip(bitTable, 1)

    # print tables to make sure it looks like the png
    # print(bitTable[:, :, 0])
    # print(bitTable[:, :, 1])

    # turn into string: https://stackoverflow.com/questions/32658322/concatenate-numpy-string-array-along-an-axis
    # tabs: https://stackoverflow.com/questions/7643579/modify-the-width-of-a-tab-in-a-format-string

    str0_0 = '\tppu.tile_table[' + str(44 + counter) + '].bit0 = {\n' + ',\n'.join('\t\t0b' + ''.join(str(int(bit)) for bit in row) for row in bitTable[:, :, 0]) + '\n\t};'
    str0_0 = str0_0.expandtabs(4)
    str1_0 = '\tppu.tile_table[' + str(44 + counter) + '].bit1 = {\n' + ',\n'.join('\t\t0b' + ''.join(str(int(bit)) for bit in row) for row in bitTable[:, :, 1]) + '\n\t};'
    str1_0 = str1_0.expandtabs(4)


    # print out so we can copy to playmode.cpp
    strings = [str0_0, str1_0]
    for s in strings:
        f.write(s)
        f.write('\n')