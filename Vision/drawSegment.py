import cv2
import numpy as np
from matplotlib import pyplot as plt

#Read gray image
img = cv2.imread("maze1.png",0)

img_blurBilat = cv2.bilateralFilter(img,8,75,150)
abs_img_blurBilat = cv2.convertScaleAbs(img_blurBilat)

img_blurG = cv2.GaussianBlur(img, (5, 5), 0)
abs_img_blurG = cv2.convertScaleAbs(img_blurG)

img_laplacian = cv2.Laplacian(img,cv2.CV_64F)
abs_img_laplacian = cv2.convertScaleAbs(img_laplacian)

#Create default parametrization LSD
lsd = cv2.createLineSegmentDetector(0)

#Detect lines in the image
lines = lsd.detect(abs_img_laplacian)[0] #Position 0 of the returned tuple are the detected lines

#Draw detected lines in the image
drawn_img = lsd.drawSegments(img,lines)
for i in range(0,len(lines)):
    print(lines[i][0])

# print(lines[1](1))

# print(x1)
# print(y1)
# print(img_laplacian[0])
#Show image
cv2.imshow("LSD",drawn_img )
cv2.waitKey(0)
