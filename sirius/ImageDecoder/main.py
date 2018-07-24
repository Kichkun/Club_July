from tkinter.filedialog import askopenfilenames
from PIL import Image
import tkinter
import os

root = tkinter.Tk()
root.withdraw()
filenames = askopenfilenames(parent=root, initialdir="/home/petr/Documents/sirius/ImageDecoder", title='Select images to decode')

id = 0
for f in filenames:
    w, h = (320, 240)
    img = Image.new('L', (w, h))

    try:
        filedata = open(f, 'rb').read()
        print(filedata)
        for i in range(w * h):
            print(i)
            now = filedata[i]
            img.putpixel((i // h, i % h), now)
        img.show()
        img.save('results/%d.png' % id)
    except Exception as ex:
        print(ex)
    id += 1
