from image_processing import ImageProcessing

images = ["board.png", "board2.png"]

for image in images:
    image_process = ImageProcessing(show_images=False)
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
    sorted_contours = image_process.sort_contours(merged_contours, show_images=True)

    image_process.wait_for_key()
