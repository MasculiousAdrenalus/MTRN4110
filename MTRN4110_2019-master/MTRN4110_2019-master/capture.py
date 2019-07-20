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

cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FPS, 30)
fourcc = cv2.VideoWriter_fourcc(*'mp4v')
out = cv2.VideoWriter('output.mp4', fourcc, 30.0, (640,480))
while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()
    fps = cap.get(cv2.CAP_PROP_FPS)
    width = cap.get(cv2.CAP_PROP_FRAME_WIDTH)
    height = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)
    print('FPS:',fps, 'Width:', width, 'Height:', height)
    # Our operations on the frame come here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    out.write(frame)
    # Display the resulting frame
    cv2.imshow('frame',gray)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
out.release()
cv2.destroyAllWindows()
