import os
from image_processor import ImageProcessor
import numpy as np

TEST_TEMPLATE = """
TEST(Test1, Move{PYTHON_MOVE}{CPP_MOVE}) {{
    Logic logic = Logic();


    logic.board = {{
    {PYTHON_BEFORE}
    }};

    logic.move{PYTHON_MOVE}();

    std::array<std::array<int, GRID_COLS>, GRID_ROWS> board = {{
    {PYTHON_AFTER}
    }};

    ASSERT_EQ(logic.board, board);
}
"""


class CppTestMaker:
    def __init__(self, directory):
        images = []
        for x in os.listdir(directory):
            # if its a directory
            if os.path.isdir(os.path.join(directory, x)):
                for y in os.listdir(os.path.join(directory, x)):
                    # if its a file
                    if os.path.isfile(os.path.join(directory, x, y)):
                        # if its a png
                        if y.endswith(".png"):
                            # add it to the list
                            images.append(os.path.join(directory, x, y))
            # self.sorted_images should look like this:
            # [("Test 1", ("start.png", "end.png")), ...]
            start_images = []
            end_images = []
            for image in images:
                if image.endswith("start.png"):
                    start_images.append(image)
                else:
                    end_images.append(image)
            self.sorted_images = list(zip(start_images, end_images))
            # sort by the number in 'tests/testNUMBER/*.png'
            if os.name == "nt":
                self.sorted_images.sort(key=lambda x: int(x[0].split("\\")[-2].split("test")[-1]))
            else:
                self.sorted_images.sort(key=lambda x: int(x[0].split("/")[-2].split(" ")[-1]))

    def process_image(self, image, quiet=False):
        if not quiet:
            print(f"Processing '{image}' ...")
        processor = ImageProcessor()
        processor.load_image(image)
        numbers = processor.get_list()
        return (
            np.array2string(numbers, separator=", ")
            .replace("[", "{")
            .replace("]", "}")
            .replace("{{", "{")
            .replace("}}", "}")
            .replace("{", "\t{")
        )

    def make_test(self, image, start_list, end_list):
        if os.name == "nt":
            move = image[1].split("\\")[-1].split(".")[0].title()
            cpp = image[1].split("\\")[-2].split("test")[-1]
        else:
            move = image[1].split("/")[-1].split(".")[0].title()
            cpp = image[1].split("/")[-2].split("test")[-1]
        return (
            TEST_TEMPLATE.replace("{PYTHON_BEFORE}", start_list)
            .replace("{PYTHON_AFTER}", end_list)
            .replace("{PYTHON_MOVE}", move)
            .replace("{CPP_MOVE}", cpp)
        )


if __name__ == "__main__":
    cpp_test_maker = CppTestMaker("tests")
    for image in cpp_test_maker.sorted_images:
        before = cpp_test_maker.process_image(image[0], quiet=True)
        after = cpp_test_maker.process_image(image[1], quiet=True)
        print(cpp_test_maker.make_test(image, before, after))
