import PIL

img = PIL.Image.open('red.ico')
pix = img.load()

for i in range(img.size[0]):
    for j in range(img.size[1]):
        if pix[i,j] != (255, 0, 0):
            # change to black if not red
            pix[i,j] = (0, 0 ,0)