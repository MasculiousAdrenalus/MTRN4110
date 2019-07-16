import cv2
import numpy as np

while(1):
# load color image
	Imaze1 = cv2.imread('maze3.png')
	Imaze = cv2.imread('maze3.png',0)
	resize1 = cv2.resize(Imaze1,(960,540))
	resize = cv2.resize(Imaze,(960,540))
	crop = resize1[15:536 ,7:939]

	Gray_Imaze = cv2.cvtColor(crop,cv2.COLOR_BGR2GRAY)
	ret, thresh = cv2.threshold(resize,0,255,cv2.THRESH_BINARY_INV+cv2.THRESH_OTSU)
	th, bw = cv2.threshold(Imaze, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)


	rows,cols,ch = crop.shape
	pts1 = np.float32([[0,0],[0,517],[927,0],[927,517]])
	pts2 = np.float32([[0,0],[0,1250],[2250,0],[2250,1250]])
	M = cv2.getPerspectiveTransform(pts1,pts2)
	dst = cv2.warpPerspective(crop,M,(2250,1250))

	cv2.imwrite('imagedst.png',dst)
	Gray_Imaze = cv2.cvtColor(dst,cv2.COLOR_BGR2GRAY)
	imageg = cv2.imread('imagedst.png',0)
	image_rgb = cv2.imread('imagedst.png')
	# smooth the image with alternative closing and opening
	# with an enlarging kernel
	gray = cv2.cvtColor(image_rgb,cv2.COLOR_BGR2GRAY)
	edges = cv2.Canny(gray,50,150,apertureSize = 3)


	morph = image_rgb.copy()

	kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))
	morph = cv2.morphologyEx(morph, cv2.MORPH_CLOSE, kernel)
	morph = cv2.morphologyEx(morph, cv2.MORPH_OPEN, kernel)

	kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (8, 8))

	# take morphological gradient
	gradient_image = cv2.morphologyEx(morph, cv2.MORPH_GRADIENT, kernel)

	# split the gradient image into channels
	image_channels = np.split(np.asarray(gradient_image), 3, axis=2)

	channel_height, channel_width, _ = image_channels[0].shape

	# apply Otsu threshold to each channel
	for i in range(0, 3):
		_,image_channels[i] = cv2.threshold(~image_channels[i], 0, 255, cv2.THRESH_OTSU | cv2.THRESH_BINARY)
		image_channels[i] = np.reshape(image_channels[i], newshape=(channel_height, channel_width, 1))

	# merge the channels
	image_channels = np.concatenate((image_channels[0], image_channels[1], image_channels[2]), axis=2)
	image_channels_b = ~image_channels
	image_channels_b*= np.array((0,0,1),np.uint8)
	out = np.bitwise_or(image_rgb, image_channels_b)
	#output_img = cv2.resize(out,(960,540))
	

	#display_img = cv2.resize(image_channels_b,(960,540))
	cv2.rectangle(image_channels_b, (0,0), (2250,1250), (0,0,255), 15)
	display_img = image_channels_b

	horizontal = np.copy(display_img)

	cols = horizontal.shape[1]
	horizontal_size = cols // 30

	horizontalStructure = cv2.getStructuringElement(cv2.MORPH_RECT, (horizontal_size,1))
	horizontal = cv2.erode(horizontal, horizontalStructure)
	horizontal = cv2.dilate(horizontal, horizontalStructure)

	vertical = np.copy(display_img)
	# Specify size on vertical axis
	rows = vertical.shape[0]
	verticalsize = rows // 30
	# Create structure element for extracting vertical lines through morphology operations
	verticalStructure = cv2.getStructuringElement(cv2.MORPH_RECT, (1, verticalsize))
	# Apply morphology operations
	vertical = cv2.erode(vertical, verticalStructure)
	vertical = cv2.dilate(vertical, verticalStructure)

	out1 = np.bitwise_or(horiz	ontal, vertical)
	out2 = np.bitwise_or(out1,image_rgb)

	out3 = cv2.resize(out2,(960,540))
	cv2.imshow('img',out3)


	key = cv2.waitKey(0) & 0xFF
	if key == ord("q"):
		break

	cap.release()
	cv2.destroyAllWindows()