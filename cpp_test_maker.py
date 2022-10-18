# reference: https://maker.pro/raspberry-pi/tutorial/grid-detection-with-opencv-on-raspberry-pi
from statistics import median
import cv2
import numpy as np
import pytesseract
import os

# if on windows
if os.name == "nt":
    pytesseract.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"

# Read image
image = cv2.imread("board.png")
# cv2.imshow("Image", image)

# increase contrast so that the grid lines are more visible
alpha = 1.5  # Contrast control (1.0-3.0)
beta = 0  # Brightness control (0-100)
image = cv2.convertScaleAbs(image, alpha=alpha, beta=beta)

# We don't need color information, so convert to grayscale
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
# cv2.imshow("gray", gray)

# Blur the image to reduce noise
blur = cv2.GaussianBlur(gray, (5, 5), 0)
# cv2.imshow("blur", blur)

# Apply adaptive thresholding to get a binary image
thresh = cv2.adaptiveThreshold(blur, 255, 1, 1, 11, 2)
# cv2.imshow("thresh", thresh)

# Find contours
contours, _ = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

# find the biggest countour (c) by the area
# this is the outer border of the board
max_area = 0
c = 0
best_cnt = contours[0]
for i in contours:
    # calculate the area of each contour
    area = cv2.contourArea(i)
    if area > 1000:
        if area > max_area:
            max_area = area
            best_cnt = i
            # draw the biggest contour (c) in green
            image = cv2.drawContours(image, contours, c, (0, 255, 0), 3)
    c += 1

# cv2.imshow("contours", image)

""" create a mask with the biggest contour (c)
    the next thing to create is a mask image
    according to these borders so that we will
    only detect grids inside the borders."""
mask = np.zeros((gray.shape), np.uint8)
cv2.drawContours(mask, [best_cnt], 0, 255, -1)
cv2.drawContours(mask, [best_cnt], 0, 0, 2)
# cv2.imshow("mask", mask)

""" We create another image that is the same
    as the one we are processing and
    crop it according to the outer border"""
# gray is the image we are processing, but its an array
# zeros_like creates an array of zeros with the same shape as gray
out = np.zeros_like(gray)
# now we copy the pixels inside the biggest contour to out
# mask is a numpy array with the same shape as gray
# when we do `mask == 255` we get a numpy array
# that is True where mask is 255 and False everywhere else
# this will be used as an index to copy the pixels
# from gray to out
out[mask == 255] = gray[mask == 255]
# cv2.imshow("New image", out)

# Apply blur to the image to reduce noise
blur = cv2.GaussianBlur(out, (5, 5), 0)
# cv2.imshow("blur1", blur)

# Apply adaptive thresholding to get a binary image
thresh = cv2.adaptiveThreshold(blur, 255, 1, 1, 11, 2)
# cv2.imshow("thresh1", thresh)

# Find contours again, but this time on the inside of the board
contours, _ = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

masks = []
# keep only the contours that are inside the outer border
for cnt in contours:
    # create a mask for the contour
    mask = np.zeros((gray.shape), np.uint8)
    cv2.drawContours(mask, [cnt], 0, 255, -1)
    # calculate percentage of non-zero pixels in the mask
    # if it is inside the board, it should be > 50%
    # if it is outside the board, it will be < 50%
    p = cv2.countNonZero(mask) / mask.size
    if p < 0.5 and p > 0.025:
        masks.append(mask)

# if the coordinates of 2 contours are close, they are probably the same
# so we will merge them
for i in range(len(masks)):
    for j in range(i + 1, len(masks)):
        if np.sum(masks[i] & masks[j]) > 0:
            masks[i] = masks[i] | masks[j]
            masks[j] = np.zeros((gray.shape), np.uint8)
# remove empty masks
masks = [m for m in masks if np.count_nonzero(m) > 0]

# rotate the masks counter-clockwise by 90 degrees 2 times
# this is because the masks are in the wrong orientation
masks = [np.rot90(m) for m in masks]
masks = [np.rot90(m) for m in masks]

# for each mask, write the index of the cell on it
for i, mask in enumerate(masks):
    # find the center of the contour
    M = cv2.moments(mask)
    cX = int(M["m10"] / M["m00"])
    cY = int(M["m01"] / M["m00"])
    # write the index
    cv2.putText(image, str(i), (cX, cY), cv2.FONT_HERSHEY_SIMPLEX, 1, 255, 2)

# for each mask, mark a rectangle on the original image
for mask in masks:
    # find the bounding rectangle of the contour
    x, y, w, h = cv2.boundingRect(mask)
    # draw the rectangle on the original image
    cv2.rectangle(image, (x, y), (x + w, y + h), (0, 255, 255), 2)

# for each mask, find the number inside it
numbers = []
for mask in masks:
    # find the bounding rectangle of the contour
    x, y, w, h = cv2.boundingRect(mask)
    # crop the image to the bounding rectangle
    crop = out[y : y + h, x : x + w]
    string = pytesseract.image_to_string(crop, config="--psm 10")
    numbers.append(string)

for i, number in enumerate(numbers):
    number = [x for x in number if x.isdigit()]
    if len(number) > 0:
        number = int("".join(number))
        numbers[i] = number
    else:
        numbers[i] = 0

numbers = np.array(numbers).reshape(4, 4)
# format this like a c++ array when printing
# by using '{' and '}' instead of '[' and ']'
# and by adding a comma after each element
string_array = np.array2string(numbers, separator=", ").replace("[", "{").replace("]", "}")
print(f"{{{string_array}}}")

# show the image
# cv2.imshow("image", image)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
