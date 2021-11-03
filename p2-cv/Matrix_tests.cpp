// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----

// Initialize a 2x3 Matrix and checks
// that Matrix's width and height equal to the paramenters.
TEST(test_matrix_init) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
  Matrix_init(mat, 2, 3);
  int width=2;
  int height=3;
  ASSERT_TRUE(Matrix_height(mat)==height&&Matrix_width(mat)==width);
    
  Matrix *mat1 = new Matrix; // create a Matrix in dynamic memory
  Matrix_init(mat1, 500, 500);
  int width1=500;
  int height1=500;
  ASSERT_TRUE(Matrix_height(mat1)==height1&&Matrix_width(mat1)==width1);
  delete mat; // delete the Matrix
  delete mat1; // delete the Matrix
}

// Initialize a 2x3 Matrix and checks
// that Matrix_print outputs that correct format for the matrix.
TEST(test_matrix_print) {
  Matrix *mat=new Matrix;
  Matrix_init(mat,2,1);
  ostringstream expected;
  expected  << "2 1\n"
            << "0 0 \n";
  Matrix_fill(mat, 0);
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
    
  Matrix *mat1 = new Matrix; // create a Matrix in dynamic memory
  Matrix_init(mat1, 2, 1);
  *Matrix_at(mat1, 0, 0) = 42;
  *Matrix_at(mat1, 0, 1) = 42;
  ostringstream expected1;
  expected1  << "2 1\n"
              << "42 42 \n";
  ostringstream actual1;
  Matrix_print(mat1, actual1);
  ASSERT_EQUAL(expected1.str(), actual1.str());
    
  Matrix *mat2=new Matrix;
  Matrix_init(mat2,3,2);
  *Matrix_at(mat2, 0, 0) = 42;
  *Matrix_at(mat2, 0, 1) = 41;
  *Matrix_at(mat2, 0, 2) = 40;
  *Matrix_at(mat2, 1, 0) = 39;
  *Matrix_at(mat2, 1, 1) = 38;
  *Matrix_at(mat2, 1, 2) = 37;
  ostringstream expected2;
  expected2  << "3 2\n"
               <<"42 41 40 \n"
               <<"39 38 37 \n";
  ostringstream actual2;
  Matrix_print(mat2, actual2);
  ASSERT_EQUAL(expected2.str(), actual2.str());

  delete mat1;
  delete mat2;
  delete mat;
}

// Initialize a 2x3 Matrix and checks
// that Matrix_width outputs the correct width for the matrix.
TEST(test_matrix_width_height) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
  Matrix_init(mat, 2, 500);
  ASSERT_EQUAL(Matrix_width(mat), 2);
  ASSERT_EQUAL(Matrix_height(mat), 500);
  delete mat; // delete the Matrix
}

// Initialize a 2x3 Matrix with a value and checks
// that Matrix_row outputs the correct row for a certain data poiner.
TEST(test_matrix_row_column) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
  Matrix_init(mat, 5, 3);
  const int *ptr=Matrix_at(mat,1,0);
  int row=Matrix_row(mat, ptr);
  int column=Matrix_column(mat,ptr);
  ASSERT_EQUAL(row, 1);
  ASSERT_EQUAL(column,0);
    
  const int *ptr1=Matrix_at(mat,2,4);
  int row1=Matrix_row(mat,ptr1);
  int column1=Matrix_column(mat,ptr1);
  ASSERT_EQUAL(row1, 2);
  ASSERT_EQUAL(column1,4);
  
  const int *ptr2=Matrix_at(mat,2,2);
  int row2=Matrix_row(mat,ptr2);
  int column2=Matrix_column(mat,ptr2);
  ASSERT_EQUAL(row2, 2);
  ASSERT_EQUAL(column2,2);
    
  const int *ptr3=Matrix_at(mat,1,4);
  int row3=Matrix_row(mat,ptr3);
  int column3=Matrix_column(mat,ptr3);
  ASSERT_EQUAL(row3, 1);
  ASSERT_EQUAL(column3,4);
  delete mat; // delete the Matrix
}

// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);
//test if every element filled equals to the same element being passed in Matrix_fill
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }
    
  Matrix_fill_border(mat, 40);
    for(int column=0;column<Matrix_width(mat);++column){
        ASSERT_EQUAL(*Matrix_at(mat,0,column), 40);
        ASSERT_EQUAL(*Matrix_at(mat,Matrix_height(mat)-1,column),40);}
        
    for(int row=1;row<Matrix_height(mat)-1;++row){
        for (int column=0;column<Matrix_width(mat);++column){
            if(column==0||column==Matrix_width(mat)-1){
                ASSERT_EQUAL(*Matrix_at(mat,row,column),40);}
        }
    }
  Matrix *mat1 = new Matrix;
  const int width1 = 100;
  const int height1 = 100;
  const int value1 = 0;
  Matrix_init(mat1, 100, 100);
  Matrix_fill(mat1, value1);
  for(int r = 0; r < height1; ++r){
    for(int c = 0; c < width1; ++c){
      ASSERT_EQUAL(*Matrix_at(mat1, r, c), value1);
    }
  }
  delete mat; // delete the Matrix
  delete mat1;
}

TEST(test_min_row_and_column){
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory
    Matrix_init(mat, 3, 5);
    Matrix_fill(mat, -100);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 1, 3),1);
    *Matrix_at(mat,1,1)=-101;
    *Matrix_at(mat,1,2)=-102;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 1, 3),2);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 1, 2),1);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 1, 2),-101);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 1, 3),-102);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 1, 2),-100);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 4, 0, 3),-100);
    delete mat;
}

TEST(test_max){
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory
    Matrix_init(mat, 3, 5);
    Matrix_fill(mat, -100);
    ASSERT_EQUAL(Matrix_max(mat),-100);
    *Matrix_at(mat,1,1)=-101;
    ASSERT_EQUAL(Matrix_max(mat),-100);
    *Matrix_at(mat,1,2)=-99;
    *Matrix_at(mat,2,2)=-98;
    ASSERT_EQUAL(Matrix_max(mat),-98);
    delete mat;
}
    
    
    















// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
