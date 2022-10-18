import os
from image_processor import ImageProcessor
from test_maker import TestMaker

directories = []
for directory in os.listdir("tests"):
    directories.append(directory)

for directory in directories:
    print("Processing directory " + directory)
    image_processor = ImageProcessor(directory)
    image_processor.process_images()
    test_maker = TestMaker(directory)
    test_maker.make_test()
"""
for image in images:
    image_process = ImageProcessor(show_images=False)
    image = image_process.load_image(image)

    # pre-process image
    increased_contrast = image_process.increase_contrast(image)
    grayscale = image_process.convert_to_gray(increased_contrast)
    blur = image_process.blur_image(grayscale)
    threshold = image_process.threshold_image(blur)

    # make "largest contour" mask
    contours = image_process.find_contours(threshold)
    largest_contour = image_process.find_largest_contour(threshold, contours)
    mask = image_process.create_mask(image, largest_contour)

    # find similar contours and merge them
    similar_contours = image_process.find_similar_contours(threshold, contours)
    merged_contours = image_process.merge_similar_contours(similar_contours)

    # sort contours
    sorted_contours = image_process.sort_contours(merged_contours)

    # find numbers
    numbers = image_process.find_numbers_in_contours(sorted_contours)

    # print numbers
    # test_maker = TestMaker(image, numbers)
    # test_maker.make_test()

    image_process.wait_for_key()
"""
