#画像を作る工場。
# from PIL import Image, ImageDraw
#手始めにデバッグ用連番画像を作るぞ（個別に作る、アトラスを作るそれはどうせならplist付きで）

from PIL import Image, ImageDraw, ImageFont

from collections import namedtuple
Vector2 = namedtuple('Vector2', ('x','y'))

# MySystemUtilitiesに移動
import os
def should_make_dir(dir_name):
	if not os.path.isdir(dir_name) :
		os.mkdir(dir_name)


# とりあえず定数
OUTPUT_DIR = "./output"

def create_checkered_pattern(image_size, x_num, y_num, filename):
	"""
	@breif: 市松模様を作る。これは英語でチェックだったと思い追加。
	"""
	create_itimatsu_pattern(image_size, x_num, y_num, filename)

def create_itimatsu_pattern(Vector2, x_num, y_num, filename):
	"""
	@breif: 市松模様を作る。
	"""
	im = Image.new("RGBA", Vector2)
	imDraw = ImageDraw.Draw(im)
	color_switch = True
	black = (0,0,0)
	white = (255,255,255)
	color = black
	width = Vector2.x / x_num
	height = Vector2.y / y_num
	start_pos = (0,0)
	end_pos = (width, height)
	for i in range(10):
		color_switch = i % 2 == 0 if True else False 
		for j in range(10):
			if (i+j) & 1: #ビット演算で偶奇判定できた。
				color = black
			else:
				color = white
			imDraw.rectangle([start_pos, end_pos], color, color)
			start_pos = (width * j, height * i)
			end_pos = (start_pos[0] + width, start_pos[1] + height) 
	should_make_dir(OUTPUT_DIR)
	im.save(OUTPUT_DIR + "/" + filename)
	# im.show()
	return


def create_dummy_image(mode, imagesize, num):
	"""
	@brief:ナンバリングした画像を連番で生成。（ダミー用
	@param:mode、イメージ全体サイズ、個数、
	"""
	should_make_dir(OUTPUT_DIR)

	im = Image.new(mode, imagesize)
	draw = ImageDraw.Draw(im)
	font = ImageFont.load_default()
	for i in range(num):
		s = font.getsize(str(i)) # テキストサイズ補正
		im.save(OUTPUT_DIR + "/" + "name_" + str(i) + ".png")

def create_dummy_atlas_image(imagesize, col, row):
	"""
	@brief:ナンバリングしたアトラス画像を作成。（ダミー用
	@param:mode、イメージ全体サイズ、行、列
	"""
	im = Image.new("RGB", imagesize).convert("RGBA")
	im2 = Image.new("RGBA", imagesize)
	draw = ImageDraw.Draw(im2)
	width = imagesize[0] / col
	height = imagesize[1] / row
	x = width * 0.5
	y = height * 0.5
	cnt = 0
	for i in range(row):
		for j in range(col):
			# font = ImageFont.load_default()
			font = ImageFont.truetype("/Users/D3/Documents/_private_resource/Callie Hegstrom/Magnolia Merchant Font Family/Font Family/Web Fonts/Script/MagnoliaMerchant-Script.ttf", 150)
			s = font.getsize(str(cnt)) # テキストサイズ補正
			adjust = (s[0] * 0.5, s[1] * 0.5)
			draw.text(( j * width + x - adjust[0], i * height + y - adjust[1]), str(cnt), font=font)
			cnt += 1
	out = Image.alpha_composite(im, im2)
	# out.show()
	im.save(OUTPUT_DIR + "/" + 'ttttt01.png')
	im2.save(OUTPUT_DIR + "/" + 'ttttt02.png')
	out.save(OUTPUT_DIR + "/" + 'ttttt03.png')
	return im

create_dummy_image("RGB", (128,128), 3)
create_dummy_atlas_image( (1024,1024), 5, 5)
create_checkered_pattern(Vector2(128,128), 3, 10, "ITIMATSU.png")

# if __name__ == main():
