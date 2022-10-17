# reference: https://maker.pro/raspberry-pi/tutorial/grid-detection-with-opencv-on-raspberry-pi
# reference: https://stackoverflow.com/questions/9413216/simple-digit-recognition-ocr-in-opencv-python
import cv2
import numpy as np
import pytesseract

pytesseract.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"

# Read image
image = cv2.imread("board.png")
cv2.imshow("Image", image)

# We don't need color information, so convert to grayscale
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
cv2.imshow("gray", gray)

# Blur the image to reduce noise
blur = cv2.GaussianBlur(gray, (5, 5), 0)
cv2.imshow("blur", blur)

# Apply adaptive thresholding to get a binary image
thresh = cv2.adaptiveThreshold(blur, 255, 1, 1, 11, 2)
cv2.imshow("thresh", thresh)

# Find contours
contours, _ = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

# find the biggest countour (c) by the area
# this is the outer border of the board
max_area = 0
c = 0
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

cv2.imshow("contours", image)

""" create a mask with the biggest contour (c)
    the next thing to create is a mask image
    according to these borders so that we will
    only detect grids inside the borders."""
mask = np.zeros((gray.shape), np.uint8)
cv2.drawContours(mask, [best_cnt], 0, 255, -1)
cv2.drawContours(mask, [best_cnt], 0, 0, 2)
cv2.imshow("mask", mask)

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
cv2.imshow("New image", out)

# Apply blur to the image to reduce noise
blur = cv2.GaussianBlur(out, (5, 5), 0)
cv2.imshow("blur1", blur)

# Apply adaptive thresholding to get a binary image
thresh = cv2.adaptiveThreshold(blur, 255, 1, 1, 11, 2)
cv2.imshow("thresh1", thresh)

# Find contours again, but this time on the inside of the board
contours, _ = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

masks = []
for c, i in enumerate(contours):
    area = cv2.contourArea(i)
    # if the area is too small, it is probably just noise (or in this case a number)
    if area > 1000 / 2:
        # cv2.drawContours(image, contours, c, (0, 255, 0), 3)
        # create a mask for the contour
        mask = np.zeros((gray.shape), np.uint8)
        cv2.drawContours(mask, [i], 0, 255, -1)
        cv2.drawContours(mask, [i], 0, 0, 2)
        masks.append(mask)

# coordinates in [(x1, y1, x2, y2), ...] format
coordinates = []
for i, mask in enumerate(masks):
    # find the coordinates of the grid
    # we do this by finding the min and max x and y values
    # that are not 0
    ys, xs = np.nonzero(mask)
    x1, x2 = xs.min(), xs.max()
    y1, y2 = ys.min(), ys.max()
    coordinates.append((x1, y1, x2, y2))

# sort the coordinates from left to right
# and remove the first element (the outer border)
# and the second element (the inner border)
coordinates = sorted(coordinates, key=lambda x: x[0])
coordinates = coordinates[2:]

# check for similar coordinates and merge them
new_cords = []
for i, coord in enumerate(coordinates):
    x1, y1, x2, y2 = coord
    for j, coord2 in enumerate(coordinates):
        x3, y3, x4, y4 = coord2
        if x1 < x3 < x2 and y1 < y3 < y2:
            x1, y1, x2, y2 = min(x1, x3), min(y1, y3), max(x2, x4), max(y2, y4)
            new_cords.append((x1, y1, x2, y2))

# remove duplicates
coordinates = list(set(coordinates) - set(new_cords))

values = []
# draw the coordinates on the image
for x1, y1, x2, y2 in coordinates:
    # create a mask inside the coordinate
    mask = np.zeros((gray.shape), np.uint8)
    cv2.rectangle(mask, (x1, y1), (x2, y2), 255, -1)
    cv2.rectangle(mask, (x1, y1), (x2, y2), 0, 2)
    inside_img = np.zeros_like(gray)
    inside_img[mask == 255] = gray[mask == 255]
    # blur the image to reduce noise
    inside_img = cv2.GaussianBlur(inside_img, (5, 5), 0)
    # apply adaptive thresholding to get a binary image
    inside_img = cv2.adaptiveThreshold(inside_img, 255, 1, 1, 11, 2)
    # find contours
    contours, _ = cv2.findContours(inside_img, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    digit = 0
    if (cv2.countNonZero(inside_img) / inside_img.size) * 10000 > 90:
        [x, y, w, h] = cv2.boundingRect(contours[0])
        if h > 28:
            cv2.rectangle(image, (x1, y1), (x2, y2), (0, 255, 0), 2)
            roi = inside_img[y : y + h, x : x + w]
            roismall = cv2.resize(roi, (10, 10))
            roismall = roismall.reshape((1, 100))
            roismall = np.float32(roismall)
            text = pytesseract.image_to_string(roi, config="--psm 6")
            # find the digits in text
            digit = ""
            for i in text:
                if i.isdigit():
                    digit += i
                    break
            digit = int(digit)

    values.append(digit)
    # there should be a number inside this contour
    # find the number and append it to the values list

    cv2.rectangle(image, (x1, y1), (x2, y2), (100, 100, 100), 2)
# make values into a 4x4 array
values = np.array(values).reshape((4, 4))
print(values)


cv2.imshow("Final Image", image)
cv2.waitKey(0)
cv2.destroyAllWindows()
