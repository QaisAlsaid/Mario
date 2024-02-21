from PIL import Image

def wrietInfoToFile(string, xy):
    size = "64 64"
    f = open("test.txt","a")
    if(string != "cloud"):
        f.write("Tile " + string +" "+ str(xy[0]) +" "+ str(xy[1]) +" "+size+"\n")
    elif(string == "cloud"):
        f.write("Dec " + string +" "+ str(xy[0]) +" "+ str(xy[1]) + "\n")
    else:
        pass
    f.close()

def translatePixelColor(z,x,y):
    if(z[0] == z[1] == z[2] == 255):
        return ("ground",(x, y))
    elif(z[0] == 255 and z[1] == z[2] == 0):
        return ("lava",(x, y))
    elif(z[1] == 255 and z[0] == z[2]== 0):
        return ("stairs",(x, y))
    elif(z[2] == 255 and z[1] == z[0]== 0):
        return ("block",(x, y))
    elif(z[0] == z[1] == z[2]== 0):
        return ("blockb",(x, y))
    elif(z[0] == z[1] == 255 and z[2]== 0):
        return ("cloud",(x, y))
    elif(z[1] == z[2] == 255 and z[0] == 0):
        return ("spike",(x, y))
    elif(z[0] == 200 and z[1] == 100 and z[2] == 0):
        return ("qblock",(x, y))
    elif(z[2] == 200 and z[1] == 100 and z[0] == 0):
        return ("castel",(x, y))

def getPixelColorAndPos(im, x, y):
    r,g,b,a = im.getpixel((x,y))
    c = (r, g, b)
    pos = (x,im.size[1] - y)
    return (c, pos)
string = input()
im = Image.open(string)
open("string","w").close()
for i in range(im.size[0]):
    for j in range(im.size[1]):
        if(im.getpixel((i, j))[3] != 0):
            wrietInfoToFile(translatePixelColor(getPixelColorAndPos(im,i,j)[0], getPixelColorAndPos(im,i,j)[1][0], getPixelColorAndPos(im,i,j)[1][1])[0],
                            translatePixelColor(getPixelColorAndPos(im,i,j)[0], getPixelColorAndPos(im,i,j)[1][0], getPixelColorAndPos(im,i,j)[1][1])[1])
