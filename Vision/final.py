import cv2
import numpy as np
import serial
import time
from matplotlib import pyplot as plt
port = 'COM14' 
ard = serial.Serial(port,115200,timeout=10)

def main():
    print("main code")
    #Read gray image
    img_col = cv2.imread("imgs/maze3.png")
    img_gray = cv2.imread("imgs/maze3.png",0)
    [out1, out2] = get_Convolution(img_col, img_gray)
    # image = cv2.resize(out2,(960,540))
    # cv2.imshow('img',image)

    maze = EncodeMaze(out1, 9, 5, 250, 250)
    maze.getMap()

    #close port
    ard.close()
    # Q for quit
    while(1):
        key = cv2.waitKey(0) & 0xFF
        if key == ord("q"):
            break
        cv2.destroyAllWindows()
#---------------------------------------------------------------------------------------------
def get_Convolution(img_col, img_gray):
    #crop
    resize_col = cv2.resize(img_col,(960,540))
    resize_gray = cv2.resize(img_gray,(960,540))
    crop = resize_col[15:536 ,7:939]

    rows,cols,ch = crop.shape
    pts1 = np.float32([[0,0],[0,517],[927,0],[927,517]])
    pts2 = np.float32([[0,0],[0,1250],[2250,0],[2250,1250]])
    M = cv2.getPerspectiveTransform(pts1,pts2)
    img_crop_color = cv2.warpPerspective(crop,M,(2250,1250))
    img_crop_gray = cv2.cvtColor(img_crop_color,cv2.COLOR_BGR2GRAY)

    #OTSU
    ret, thresh = cv2.threshold(img_crop_gray,0,255,cv2.THRESH_BINARY_INV+cv2.THRESH_OTSU)
    # th, bw = cv2.threshold(img_gray, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)

    # #resize
    # img_crop_color = cv2.resize(img_crop_color,(960,540))
    # thresh = cv2.resize(thresh,(960,540))

    #---------------------------------------------------------------------------------------------
    #morph
    morph = img_crop_color.copy()

    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))
    morph = cv2.morphologyEx(morph, cv2.MORPH_CLOSE, kernel)
    morph = cv2.morphologyEx(morph, cv2.MORPH_OPEN, kernel)

    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (8, 8))

    # take morphological gradient
    gradient_image = cv2.morphologyEx(morph, cv2.MORPH_GRADIENT, kernel)

    #grayimg = cv2.cvtColor(gradient_image, cv2.COLOR_BGR2GRAY)
    #ret, thresh = cv2.threshold(grayimg,0,255,cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU)

    # split the gradient image into channels
    image_channels = np.split(np.asarray(gradient_image), 3, axis=2)

    channel_height, channel_width, _ = image_channels[0].shape

    # apply Otsu threshold to each channel
    for i in range(0, 3):
        _,image_channels[i] = cv2.threshold(~image_channels[i], 0, 255, cv2.THRESH_OTSU | cv2.THRESH_BINARY)
        image_channels[i] = np.reshape(image_channels[i], newshape=(channel_height, channel_width, 1))

    # merge the channels
    image_channels = np.concatenate((image_channels[0], image_channels[1], image_channels[2]), axis=2)

    # image_channels = cv2.resize(image_channels,(960,540))
    # cv2.imshow('img',image_channels)
    image_channels_b = ~image_channels
    image_channels_b*= np.array((0,0,1),np.uint8)
    out = np.bitwise_or(img_crop_color, image_channels_b)

    # info = np.iinfo(gradient_image.dtype) # Get the information of the incoming image type
    # gradient_image = gradient_image.astype(np.float64) / info.max # normalize the data to 0 - 1
    # gradient_image = 255 * gradient_image # Now scale by 255
    # gradient_image = gradient_image.astype(np.uint8)

    cv2.rectangle(image_channels_b, (0,0), (2250,1250), (0,0,255), 15)
    display_img = image_channels_b

    horizontal = np.copy(display_img)

    cols = horizontal.shape[1]
    horizontal_size = cols // 30

    horizontalStructure = cv2.getStructuringElement(cv2.MORPH_RECT, (horizontal_size,1))
    horizontal = cv2.erode(horizontal, horizontalStructure)
    horizontal = cv2.dilate(horizontal, horizontalStructure)
    # cv2.imshow('img',horizontal)
    vertical = np.copy(display_img)
    # Specify size on vertical axis
    rows = vertical.shape[0]
    verticalsize = rows // 30
    # Create structure element for extracting vertical lines through morphology operations
    verticalStructure = cv2.getStructuringElement(cv2.MORPH_RECT, (1, verticalsize))
    # Apply morphology operations
    vertical = cv2.erode(vertical, verticalStructure)
    vertical = cv2.dilate(vertical, verticalStructure)

    out1 = np.bitwise_or(horizontal, vertical)
    out2 = np.bitwise_or(out1,img_crop_color)
    return [out1,out2]
    # out3 = cv2.resize(out1,(960,540))
    # cv2.imshow('img',out3)
#---------------------------------------------------------------------------------------------
class Cords:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class EncodeMaze:
    map_size = Cords(0,0)
    pt1 = Cords(0,0)
    pt2 = Cords(0,0) #//rectangular section to check
    var_x = 25 #mm
    var_y1 = 50
    var_y2 = 200
    #------------------------------------------------------------
    def __init__(self, img, maze_x, maze_y, cell_x, cell_y):
        self.img = img
        self.maze = Cords(maze_x,maze_y)
        self.cell = Cords(cell_x, cell_y)
        self.map_size.x = self.maze.x*self.cell.x
        self.map_size.y = self.maze.y*self.cell.y
    #------------------------------------------------------------    
    def getMap(self):
        first= 0xab01 #np.uint64(0xAB)
        second= 0xab02
        temp = 0
        temp_h = 0
        temp_l = 0
        flag = 0
        data_high = []
        data_low = []
        data_high.append(0xab)
        data_high.append(0x01)
        # data_low.append(0xab)
        # data_low.append(0x02)
        #traps vertical
        print("\t\t ---Vertical Walls---")
        for y in range(0,self.maze.y):
            c=250*y+50
            d=250*y+200
            for x in range(1,self.maze.x):
                flag = 0
                a=250*x-25
                b=250*x+25
                # print('x,y')
                # print(x,y)
                cv2.rectangle(self.img, (a,c), (b,d), (255,255,0), 2)
                for i in range(c,d):
                    if (flag == 0):
                        for j in range(a,b):
                            px = self.img[i,j,2]
                            if px > 0:
                                # print('WALL',x,y)
                                second <<= 1
                                second |= 1
                                temp_l <<= 1
                                temp_l |= 1
                                # data_low.append(1)
                                flag = 1
                                break
                    else: 
                        break
                if flag ==0:
                    # print('no wall')
                    second <<= 1
                    temp_l <<= 1
                    # data_low.append(0)

                #align to 8 bits
                temp+=1           
                # print(temp)     
                # print(hex(temp_l))
                if temp == 8:
                    # print(hex())
                    # print(temp)
                    # print(temp_h)
                    data_low.append(temp_l)
                    temp_l=0    
                    temp = 0
            # if x==self.maze.x-1:
            #     data_low.append(temp_l)
        #traps horizontal
        print("\t\t ---Horizontal Walls---")
        for y in range(1,self.maze.y):
            g=250*(y)-25
            h=250*(y)+25
            for x in range(0,self.maze.x):
                flag = 0
                e=250*(x)+50
                f=250*(x)+200
                cv2.rectangle(self.img, (e,g), (f,h), (255,255,0), 2)
                for i in range(e,f):
                    if (flag == 0):
                        for j in range(g,h):
                            px = self.img[j,i,2]
                            if px > 0:
                                #wall
                                # print('WALL',x,y)
                                flag = 1
                                first <<= 1
                                first |= 1
                                temp_h <<= 1
                                temp_h |= 1
                                # data_high.append(1)
                                break
                            else:
                                pass
                #no wall
                if flag ==0:
                    # print("no wall")
                    first <<= 1
                    temp_h <<= 1
                    # data_high.append(0)
 
                #align to 8 bits
                temp+=1           
                # print(temp)     
                # print(hex(temp_h))
                if temp == 8:
                    # print(hex())
                    # print(temp)
                    # print(temp_h)
                    data_high.append(temp_h)
                    temp_h=0    
                    temp = 0
        if y==self.maze.y-1:
            data_high.append(temp_h)
            
        #------------------------------------------------------------
        
        print("horiz walls")
        print(data_high)
        print(hex(first))
        print("verticle walls")
        print(data_low)
        print(hex(second))
        # self.img = cv2.resize(self.img,(960,540))
        # cv2.imshow('img',self.img)

        # time.sleep(3)
        # ard.flush()
        # ard.write(b'transmission started')     
        # ard.write(b'first')
        data_print = []
        data_print.append(0xab)
        data_print.append(0x03)
        # arr_test = bytearray((first))
        arr_l= bytearray((data_low))
        arr_h = bytearray((data_high))
        arr_print = bytearray(data_print)

        print((arr_h))
        print((arr_l))
        #ard.write(arr_h)
        time.sleep(3)
        ard.flush()
        ard.write(arr_h)
        # ard.flush()
        # # ard.flush()
        # # time.sleep(10)
        # # ard.flush()
        ard.write(arr_l)
        ard.flush()
        # # time.sleep(10)
        # # ard.flush()        
        # ard.write(data_print)
        # ard.flush()


        image = cv2.resize(self.img,(960,540))
        cv2.imshow('img',image)
        # # ard.write(arr[0])
        # i=0
        # while (i < 8):
        #     ard.flush()
        #     print('here')
        #     #ard.write(b'________loops')
        #     #ard.write((first).to_bytes(2, byteorder='big'))

        #     time.sleep(1)
        #     i+=1

        
        
#---------------------------------------------------------------------------------------------
class SerialComms:
    def __init__():
        pass
    def SerialComms():
        pass
    
#---------------------------------------------------------------------------------------------
if __name__ == "__main__":main()
#---------------------------------------------------------------------------------------------
