// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <fstream>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

TEST(image_width_height){
    Image *img=new Image;
    Image_init(img,3,2);
    ASSERT_EQUAL(Image_height(img),2);
    ASSERT_EQUAL(Image_width(img),3);
    delete img;
}
TEST(fill_and_get_pixel){
    Image *img=new Image;
    Image_init(img,3,2);
    Pixel color={255,100,200};
    Image_fill(img, color);
    for (int row=0;row<Image_height(img);++row){
        for (int col=0;col<Image_width(img);++col){
            ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,row,col), color));
        }
    }
    Image *img1=new Image;
    Image_init(img1,500,500);
    Pixel color1={100,103,209};
    Image_fill(img1, color1);
    for (int row=0;row<Image_height(img1);++row){
        for (int col=0;col<Image_width(img1);++col){
            ASSERT_TRUE(Pixel_equal(Image_get_pixel(img1,row,col), color1));
        }
    }
    delete img;
    delete img1;
}

TEST(test_image_from_and_to_stream){
    Image* img=new Image;
    string input = "P3 2 3\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n 100 37 49 100\n 100 105";
    std::istringstream ss_input(input);
    Image_init(img, ss_input);
    string output_correct = "P3\n2 3\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n100 37 49 100 100 105 \n";
    std::ostringstream ss_output;
    Image_print(img, ss_output);
    string actual = ss_output.str();
    ASSERT_EQUAL(actual, output_correct);

    Image* img1=new Image;
    std::ifstream file;
    file.open("dog.ppm");
    std::stringstream strStream;
    strStream << file.rdbuf(); //read the file
    std::string str = strStream.str(); //str holds the content of the fill
    std::istringstream ss_input1(str);
      
    Image_init(img1, ss_input1);
    
    std::ostringstream ss_output1;
    Image_print(img1, ss_output1);
    string actual1 = ss_output1.str();
    string output_correct1="P3\n5 5\n255\n0 0 0 0 0 0 255 255 250 0 0 0 0 0 0 \n255 255 250 126 66 0 126 66 0 126 66 0 255 255 250 \n126 66 0 0 0 0 255 219 183 0 0 0 126 66 0 \n255 219 183 255 219 183 0 0 0 255 219 183 255 219 183 \n255 219 183 0 0 0 134 0 0 0 0 0 255 219 183 \n";

    ASSERT_EQUAL(actual1, output_correct1);
    
    delete img;
    delete img1;
}
// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
