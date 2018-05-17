# Pillowを使って画像を処理するよ

from PIL import Image

def createImage(mode, size):
    return Image.new(mode, size)

def convertImage(im, mode):
    im.convert(mode)

def saveImage(im, filepath):
    im.save(filepath)

if __name__ == '__main__':
    im = createImage("RGB", (128,128))
    saveImage(im, "test.jpg")
