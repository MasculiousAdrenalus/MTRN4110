# UNSW Australia
# Author(s): Annie Xu Wang (annie.xu.wang7@gmail.com)
# Github: https://github.com/annie7777
# Date: 15 April 2019
# === Description ===
# Capture videos via Logitech Brio
# Tested Environment: USB 3.0
#                     Python 3.7
#                     Windows 10 + Ubuntu 18.04 Desktop
# Outputs: output.mp4
# Required packages: opencv 

import numpy as np
import cv2
import matplotlib.pyplot as plt

# set plot to show inside jupyter notebook.
# delete the line below when run in python.%matplotlib inline

# check opencv version
print(cv2.__version__)


#video shit
# img_counter = 0
# cap = cv2.VideoCapture(0)
# cap.set(cv2.CAP_PROP_FPS, 30)
# fourcc = cv2.VideoWriter_fourcc(*'mp4v')
# out = cv2.VideoWriter('output.mp4', fourcc, 30.0, (640,480))

#loads image
maze_orig = cv2.imread('maze.JPG')
# Check the image have been opened successfully
if maze_orig is not None:
    print('Loading image successfully!')
    h, w = maze_orig.shape[:2]
    print('Image type: {}'.format(maze_orig.dtype))
    print('Image width: {}'.format(w), 'Image height: {}'.format(h))

    # Index image(left-upper is (0,0), right bottom is (h,w))
    # Check the pixel value of row 1 and 2, column 1 and 2.
    print(maze_orig[:2, :2, :])
    #display an image using matplotlib

    # Convert image to rgb order
    img_rgb = cv2.cvtColor(maze_orig, cv2.COLOR_BGR2RGB)

    # # Create a figure with 2 plots. Plot size is set to 10inches wide x 8 inches high.
    # # fig is a handle to the figure, ax1 is handle to plot no 1, ax2 is handle to plot no 2.
    fig, (ax1, ax2) = plt.subplots(figsize=(10, 8), ncols=2)

    # ax1.imshow(maze_orig)
    # ax1.set_title("BGR")
    # # ax1.show()
    # img_rgb = cv2.cvtColor(maze_orig, cv2.COLOR_BGR2RGB)
    fig.show(img_rgb)

    # # plt.subplot(2,2)
    # ax2.imshow(img_rgb)
    # ax2.set_title("RGB")
    # #ax2.show()
    # fig.canvas.draw()
    # plt.draw()
else:
    assert("Loading error");
    print('Loading error!')
    
print("loop started")
while(True):
    # # Capture frame-by-frame
    # ret, frame = cap.read()
    # fps = cap.get(cv2.CAP_PROP_FPS)
    # width = cap.get(cv2.CAP_PROP_FRAME_WIDTH)
    # height = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)
    # print('FPS:',fps, 'Width:', width, 'Height:', height)
    # # Our operations on the frame come here
    # gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # #out.write(frame)
    # # Display the resulting frame
    # cv2.imshow('PhaseB Part4 B.Gossling z3424655',gray)

    #KeyboardInterruptS
    k = cv2.waitKey(1)
    #SPACE BAR
    if k & 0xFF == ord(' '):
        print("Saving frame %2d \n" %k)
        # img_name = "opencv_frame_{}.png".format(img_counter)
        # cv2.imwrite(img_name, frame)
        # print("{} written!".format(img_name))
        # img_counter += 1

	#QUIT
    if k & 0xFF == ord('q'):
        break


# When everything done, release the capture
cap.release()
# ############out.release()
cv2.destroyAllWindows()



