import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread('maze.jpg',0)

x = 1
y = 2
# #needs blurring
# #img_blur = cv2.medianBlur(img,5)
# img_blur = cv2.bilateralFilter(img,9,150,150)
# plt.subplot(x,y,1),plt.imshow(img, cmap ='gray')
# plt.title('img_gausThres')
# plt.xticks([]),plt.yticks([])
# #-----------------------------------------------------------------------------------
# #ADAPTIVE_THRESH_GAUSSIAN_
# img_gausThres = cv2.adaptiveThreshold(img_blur,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,\
            # cv2.THRESH_BINARY,11,2)
# #-----------------------------------------------------------------------------------
# plt.subplot(x,y,2),plt.imshow(img_gausThres, cmap ='gray')
# plt.title('img_gausThres')
# plt.xticks([]),plt.yticks([])
# #-----------------------------------------------------------------------------------
# #laplacian

# img = cv2.imread('maze.jpg',0)
# img_laplacian = cv2.Laplacian(img,cv2.CV_64F)
# plt.subplot(x,y,3),plt.imshow(img_laplacian, cmap = 'gray')
# plt.title('Laplacian'), plt.xticks([]), plt.yticks([])


#-----------------------------------------------------------------------------------
#canny
edges = cv2.Canny(img,50,150)
plt.subplot(x,y,1),plt.imshow(edges, cmap = 'gray')
plt.title('canny'), plt.xticks([]), plt.yticks([])
#-----------------------------------------------------------------------------------
#watershed
img = cv2.imread('maze.jpg')
gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
ret, thresh = cv2.threshold(gray,0,255,cv2.THRESH_BINARY_INV+cv2.THRESH_OTSU)

# noise removal
kernel = np.ones((3,3),np.uint8)
opening = cv2.morphologyEx(thresh,cv2.MORPH_OPEN,kernel, iterations = 2)

# sure background area
sure_bg = cv2.dilate(opening,kernel,iterations=3)

# Finding sure foreground area
dist_transform = cv2.distanceTransform(opening,cv2.DIST_L2,5)
ret, sure_fg = cv2.threshold(dist_transform,0.7*dist_transform.max(),255,0)

# Finding unknown region
sure_fg = np.uint8(sure_fg)
unknown = cv2.subtract(sure_bg,sure_fg)

# Marker labelling
ret, markers = cv2.connectedComponents(sure_fg)

# Add one to all labels so that sure background is not 0, but 1
markers = markers+1

# Now, mark the region of unknown with zero
markers[unknown==255] = 0

markers = cv2.watershed(img,markers)
img[markers == -1] = [255,0,0]
plt.subplot(x,y,2),plt.imshow(img, cmap = 'gray')
plt.title('watershed_canny'), plt.xticks([]), plt.yticks([])
#-----------------------------------------------------------------------------------



plt.show()
