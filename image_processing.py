# reference: https://maker.pro/raspberry-pi/tutorial/grid-detection-with-opencv-on-raspberry-pi
from statistics import median
import cv2
import numpy as np
import pytesseract
import os

# if on windows
if os.name == "nt":
    pytesseract.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"


class ImageProcessing:
    def __init__(self, show_images=False):
        self.show_images = show_images
        self.image = None

    def load_image(self, image_path, name="Original Image", show_images=None):
        """Load image from path"""
        if show_images is None:
            show_images = self.show_images
        self.image = cv2.imread(image_path)
        if self.show_images:
            cv2.imshow(name, self.image)
        return self.image

    def increase_contrast(self, image, name="Increased Contrast", show_images=None):
        """Increase contrast of image"""
        if show_images is None:
            show_images = self.show_images
        image = cv2.convertScaleAbs(image, alpha=1.5, beta=0)
        if show_images:
            cv2.imshow(name, image)
        return image

    def convert_to_gray(self, image, name="Grayscale", show_images=None):
        """Convert image to grayscale"""
        if show_images is None:
            show_images = self.show_images
        image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        if show_images:
            cv2.imshow(name, image)
        return image

    def blur_image(self, image, name="Blurred Image", show_images=None):
        """Blur image"""
        if show_images is None:
            show_images = self.show_images
        image = cv2.GaussianBlur(image, (5, 5), 0)
        if show_images:
            cv2.imshow(name, image)
        return image

    def threshold_image(self, image, name="Threshold Image", show_images=None):
        """Threshold image"""
        if show_images is None:
            show_images = self.show_images
        image = cv2.adaptiveThreshold(image, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11, 2)
        if show_images:
            cv2.imshow(name, image)
        return image

    def find_contours(self, image, name="Contours", show_images=None):
        """Find contours"""
        if show_images is None:
            show_images = self.show_images
        contours, hierarchy = cv2.findContours(image, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        if show_images:
            cv2.drawContours(self.image, contours, -1, (0, 255, 0), 3)
            cv2.imshow(name, self.image)
        return contours

    def find_largest_contour(self, image, contours, name="Largest Contour", show_images=None):
        """Find largest contour"""
        if show_images is None:
            show_images = self.show_images
        largest_contour = max(contours, key=cv2.contourArea)
        if show_images:
            cv2.drawContours(self.image, largest_contour, -1, (0, 255, 0), 3)
            cv2.imshow(name, image)
        return largest_contour

    def create_mask(self, image, contour, name="Mask", show_images=None):
        """Create mask"""
        if show_images is None:
            show_images = self.show_images
        mask = np.zeros(image.shape, np.uint8)
        cv2.drawContours(mask, [contour], 0, 255, -1)
        if show_images:
            cv2.imshow(name, mask)
        return mask

    def find_similar_contours(self, image, contours, name="Similar Contours", show_images=None):
        """Find similar contours"""
        if show_images is None:
            show_images = self.show_images
        similar_contours = []
        for contour in contours:
            area = cv2.contourArea(contour)
            if area > 1000:
                similar_contours.append(contour)
        if show_images:
            for i, contour in enumerate(similar_contours):
                cv2.drawContours(self.image, [contour], -1, (0, 255, 0), 3)
                cv2.imshow(name + str(i), self.image)
        return similar_contours

    def merge_contours(self, contour1, countour2, name="Merged Contours", show_images=None):
        """Merge contours"""
        if show_images is None:
            show_images = self.show_images
        merged_contours = np.concatenate((contour1, countour2), axis=0)
        if show_images:
            cv2.drawContours(self.image, merged_contours, -1, (0, 255, 0), 3)
            cv2.imshow(name, self.image)
        return merged_contours

    def merge_similar_contours(self, similar_contours, name="Merged Similar Contours", show_images=None):
        """Merge similar contours"""
        if show_images is None:
            show_images = self.show_images

        # print the area of each contour
        areas = [cv2.contourArea(c) for c in similar_contours]
        areas.sort(reverse=True)

        # remove the contours that are too large
        similar_contours = [c for c in similar_contours if cv2.contourArea(c) < 10000]
        # remove the contours that are too small
        similar_contours = [c for c in similar_contours if cv2.contourArea(c) > 5000]

        if show_images:
            for i, contour in enumerate(similar_contours):
                cv2.drawContours(self.image, [contour], -1, (0, 255, 0), 3)
                cv2.imshow(name + str(i), self.image)

        return similar_contours

    def sort_contours(self, contours, name="Sorted Contours", show_images=None):
        """Sort contours"""
        if show_images is None:
            show_images = self.show_images

        centers = []
        for contour in contours:
            x, y, w, h = cv2.boundingRect(contour)
            center = [x + w / 2, y + h / 2]
            centers.append(center)

        # sort the centers by their x coordinate
        centers = sorted(centers, key=lambda x: x[0])
        row1 = centers[:4]
        row2 = centers[4:8]
        row3 = centers[8:12]
        row4 = centers[12:]
        # sort each row by their y coordinate
        row1 = sorted(row1, key=lambda x: x[1])
        row2 = sorted(row2, key=lambda x: x[1])
        row3 = sorted(row3, key=lambda x: x[1])
        row4 = sorted(row4, key=lambda x: x[1])
        centers = []
        for row in zip(row1, row2, row3, row4):
            for center in row:
                centers.append(center)

        if show_images:
            for i, center in enumerate(centers):
                cv2.putText(
                    self.image,
                    str(i),
                    (int(center[0]), int(center[1])),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    1,
                    (125, 125, 125),
                    2,
                )
                cv2.imshow(name, self.image)

        return centers

    def wait_for_key(self):
        """Wait for key press"""
        cv2.waitKey(0)
        cv2.destroyAllWindows()
