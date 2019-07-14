import cv2
import numpy as np
from matplotlib import pyplot as plt

#Read gray image
img = cv2.imread("maze.jpg",0)
# img_blur = cv2.bilateralFilter(img,8,150,150)
img_blur = cv2.GaussianBlur(img, (5, 5), 0)
img_laplacian = cv2.Laplacian(img,cv2.CV_64F)
abs_dst = cv2.convertScaleAbs(img_laplacian)
#Create default parametrization LSD
lsd = cv2.createLineSegmentDetector(0)

#Detect lines in the image
lines = lsd.detect(abs_dst)[0] #Position 0 of the returned tuple are the detected lines

#Draw detected lines in the image
drawn_img = lsd.drawSegments(img,lines)
print(lines[0])
print(img_laplacian[0])
#Show image
cv2.imshow("LSD",drawn_img )
cv2.waitKey(0)
