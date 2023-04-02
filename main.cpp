/*
    By Geekious (Rhitt C)
    I have written this program mostly to test out my C++ skills.
    For this reason, I have used double pointers to make the matrices dynamic
        instead of the various other more efficient methods.
    
    Please enjoy!
*/


#include <iostream>
#include <fstream>
#include "matrices.h"

int main()
{
    std::cout << "\n\n";
    std::ifstream linux_ascii_art("linux_tux.txt");
    std::string line;
    while(getline(linux_ascii_art, line))
        std::cout << line << '\n';
    
    
    test_matrix("A", "square");
    std::cout << "\n\n\n";
    test_matrices("B", "C");
    std::cout << "\n\n\n";
    test_matrix("D");

    
    std::cout << "\n\n\nThat's all, comrades!\n"
        << " In your unrelenting pursuit of mathematics,\n"
        << " May you BOLDLY GO WHERE NO MAN HAS GONE BEFORE!\n\n";

    std::ifstream elephant_ascii_art("elephant.txt");
    while(getline(elephant_ascii_art, line))
        std::cout << line << '\n';
    
    return 0;
}


void test_matrix(const std::string name, const std::string type)
{
    std::cout << "Performing opperations on Matrix " << name << ":\n\n\n";
    Matrix m = {name, type};

    // Inputting everything before outputting
    int c;        // Scalar
    std::cout << "Input Scalar for multiplying with Matrix "
        << m.get_name() << ": ";
    std::cin >> c;
    std::cout << "\n\n\n";

    
    // Matrix M
    m.cout();
    std::cout << "\n\n\n";
    
    // Determinant
    try
    {
        std::cout << '|' << m.get_name() << "|: " << m.determinant();
    }
    catch(int no_solution)
    {
        std::cout << "Matrix " << m.get_name() << " has no Determinant";
    }
    std::cout << "\n\n\n\n";
    
    // Scalar Multiplication
    m.scalar_multiply(c).cout();
    std::cout << "\n\n\n";

    // Trace
    try
    {
        std::cout << "Tr(" << m.get_name() << "): " << m.trace();
    }
    catch(int no_solution)
    {
        std::cout << "Matrix " << m.get_name() << " has no Trace";
    }
    std::cout << "\n\n\n\n";

    // Transpose
    m.transpose().cout();
    std::cout << "\n\n\n";
}

Matrix::Matrix(const std::string name, const std::string type): name{name}
{
    try
    {
        cin_row_col(type);
    }
    catch(int error)
    {
        std::cout << "\nError: Invalid argument in Matrix::cin_row_col()\n";
        exit(0);
    }
    
    cin_val();
}

Matrix::~Matrix()
{
    for(unsigned int i = 0; i < row; i++)
        delete(a[i]);
}

void Matrix::cin_row_col(const std::string type)
{
    if(type == "square")
    {
        std::cout <<  name << " is a square matrix\n"
            << "Input Number of Dimensions: ";
        std::cin >> row;
        col = row;
    }
    else if(type == "rectangular")
    {
        std::cout << name << " is a rectangular matrix\n"
            << "Input Number of Rows and Columns: ";
        std::cin >> row >> col;
    }
    else
        throw 0;

    if(row < 2 || col < 2)
    {
        std::cout << "Error: Please input at least a 2x2 Matrix:\n\n\n";
        cin_row_col(type);
    }
    
    std::cout << "\n\n";
}

void Matrix::cin_val()
{
    /*
        n is the last row    index, the variable row - 1
        m is the last column index, the variable col - 1


        How int** a becomes a 2d array:

        *a, the int*[]'s are the rows and can be thought of like this:
            a[  0] =    int*[  0]
            a[  1] =    int*[  1]
            a[  i] =    int*[  i]
            a[i+1] =    int*[i+1]
            a[row] =    int*[  n]

        Within this int*[], each int is a column, so *a can be thought of as:
            a[  0][  0]    a[  0][1]    a[  0][j]    a[  0][j+1]    a[  0][m]
            a[  1][  0]    a[  1][1]    a[  1][j]    a[  1][j+1]    a[  1][m]
            a[  i][  0]    a[  i][1]    a[  i][j]    a[  i][j+1]    a[  i][m]
            a[i+1][  0]    a[i+1][1]    a[i+1][j]    a[i+1][j+1]    a[i+1][m]
            a[  n][  0]    a[  n][1]    a[  n][j]    a[  n][j+1]    a[  n][m]

        [] in c++ already dereferences the pointer.
        In fact, that's how arrays work under the hood

        Also note that the data is not stored contiguously.
        If that bothers you, you can simply use triple pointers instead.
        However, for these purposes, it's not neccesary.
    */
    
    unsigned int i, j;
    
    std::cout << "Input Matrix " << name << ":\n";
    // Initialising
    a = new int*[row];    // Allocate array of int pointers
    for(i = 0; i < row; i++)
    {
        a[i] = new int[col];
        for(j = 0; j < col; j++)
        {
            std::cout << "Element " << name 
                << " sub " << i + 1 << ' ' << j + 1 << ": ";
            std::cin >> a[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

int** dupplicate(const unsigned int row, const unsigned int col, int** a)
{
    unsigned int i, j;
    
    int** getA = new int*[row];
    for(i = 0; i < row; i++)
    {
        getA[i] = new int[col];
        for(j = 0; j < col; j++)
            getA[i][j] = a[i][j];
    }
    
    return getA;
}

Matrix Matrix::scalar_multiply(const int c) const
{
    unsigned int i, j;
    
    int** cA = new int*[row];
    for(i = 0; i < row; i++)
    {
        cA[i] = new int[col];
        for(j = 0; j < col; j++)
            cA[i][j] = c * a[i][j];
    }

    Matrix c_a = {row, col, std::to_string(c) + name, cA};
    return c_a;
}

Matrix Matrix::transpose() const
{
    unsigned int i, j;
    
    int** aT = new int*[col];    // col in place of row
    for(i = 0; i < col; i++)
    {
        aT[i] = new int[row];    // row in place of col
        for(j = 0; j < row; j++)
            aT[i][j] = a[j][i];
    }
    
    Matrix a_t = {col, row, name + "^T", aT};    // col and row are inverted
    return a_t;
}

unsigned int extra_chars(const int num)
{
    unsigned int extraChars = 0;
    
    if(num < 0 || num > 9)
        extraChars++;
    if(num < -9 || num > 99)
        extraChars++;
    if(num < -99 || num > 999)
        extraChars++;
    if(num < -999 || num > 9999)
        extraChars++;
    if(num < -9999 || num > 99999)
        extraChars++;
    if(num < -99999 || num > 999999)
        extraChars++;
    if(num < -999999 || num > 9999999)
        extraChars++;
    if(num < -9999999 || num > 99999999)
        extraChars++;
    if(num < -99999999 || num > 999999999)
        extraChars++;
    if(num < -999999999)        // Max Digits of int is 10
        extraChars++;
    // Remove some if() blocks if you want

    return extraChars;    // Digits (+ 1 if negative) - 1
}

void Matrix::cout() const
{
    unsigned int i, j, k;
    unsigned int spaces = col * 2 - 2;

    
    // Accounting for extra chars due to multiple digits or negatives
    unsigned int extraChars[col];
    for(i = 0; i < col; i++)    // Initialising
        extraChars[i] = 0;

    // Note that i and j are swapped. This is because we are looking at the cols
    // The num of extra chars in each col is recorded for future reference
    unsigned int maxJ = 0;    // This is also why I named this int as such
    for(i = 0; i < col; i++)
    {
        for(j = 0; j < row; j++)
        {
            int temp = extra_chars(a[j][i]);
            if(temp > extraChars[i])
                extraChars[i] = temp;
        }
        spaces += extraChars[i];
    }
    //std::cout << extraChars[maxI];

    // Actually Outputting
    std::cout << "Matrix " << name << ": \n";
    
    std::cout << " _";
    for(i = 0; i <= spaces; i++)
        std::cout << ' ';
    std::cout << "_\n";
    
    std::cout << '|';
    for(i = 0; i <= spaces + 2; i++)
        std::cout << ' ';
    std::cout << "|\n";
    
    for(i = 0; i < row; i++)
    {
        std::cout << "| ";
        for(j = 0; j < col; j++)
        {
            if(extraChars[j] > 0)
                for(k = 0; k < extraChars[j] - extra_chars(a[i][j]); k++)
                    std::cout << ' ';
            std::cout << a[i][j] << ' ';
        }
        std::cout << "|\n";
    }
    
    std::cout << "|_";
    for(i = 0; i <= spaces; i++)
        std::cout << ' ';
    std::cout << "_|\n";
}

int Matrix::determinant() const
{
    if(row != col)
        throw 0;
    
    int detA = 0;
    if(row == 2)
        detA = a[0][0] * a[1][1] - a[1][0] * a[0][1];
    else
    {
        //Recursion with Submatrix
        unsigned int k, i, j;

        for(k = 0; k < row; k++)    // Removing this column
        {
            /*
                The following submatrix is created:                

                                           skipped
                                         |         |
                a[  0][0]    a[  0][1]   |a[  0][j]|   a[  0][j+1]    a[  0][n]
                a[  1][0]    a[  1][1]   |a[  ~][j]|   a[  1][j+1]    a[  1][n]
                _________________________|         |_________________________
    skipped     a[i+0][~]    a[i+0][~]    a[i+0][j]    a[i+0][  ~]    a[i+0][~]
                __________________________         ____________________________
                a[i+1][0]    a[i+1][1]   |a[  ~][j]|   a[i+1][j+1]    a[i+1][n]
                a[  n][0]    a[  n][1]   |a[  ~][j]|   a[  n][j+1]    a[  n][n]
                                         |         |
                

                a[  0][0]    a[  0][1]    a[  0][j+1]    a[  0][n]
                a[  1][0]    a[  1][1]    a[  1][j+1]    a[  1][n]
                a[i+1][0]    a[i+1][1]    a[i+1][j+1]    a[i+1][n]
                a[  n][0]    a[  n][1]    a[  n][j+1]    a[  n][n]


                From here, it's easy to use recursion to find any determinant
            */
            int** aSub = new int*[row - 1];
            
            for(i = 0; i < row - 1; i++)
            {
                aSub[i] = new int[col - 1];
                unsigned int subJ = 0;
                for(j = 0; j < col; j++)
                    if(j != k)
                        aSub[i][subJ++] = a[i + 1][j];
            }
            
            Matrix a_sub = 
            {
                row - 1, col - 1,
                "submatrix " + std::to_string(k + 1) + " of " + name,
                aSub
            };
            //a_sub.cout();
            
            detA += std::pow(-1, k) * a[0][k] * a_sub.determinant();
        }
    }
    
    return detA;
}

int Matrix::trace() const
{
    if(row != col)
        throw 0;
    
    int trA = 0;
    for(unsigned int i = 0; i < row; i++)
        trA += a[i][i];
    
    return trA;
}


void test_matrices(const std::string nameV, const std::string nameW)
{
    std::cout << "Performing operations on Matrices "
        << nameV << " and " << nameW << ":\n\n\n";
    Matrices vw = {nameV, nameW};
    vw.x.cout();
    std::cout << "\n\n\n";
    vw.y.cout();
    std::cout << "\n\n\n";

    // Matrix Multiplication
    try
    {
        vw.matrix_multiply().cout();
    }
    catch(int no_solution)
    {
        std::cout << "Cannot Multiply Matrices "
            << vw.x.get_name() << " and " << vw.y.get_name() << "\n";
    }
    std::cout << "\n\n\n";

    // Matrix Addition
    try
    {
        vw.add().cout();
    }
    catch(int no_solution)
    {
        std::cout << "Cannot Add Matrices "
            << vw.x.get_name() << " and " << vw.y.get_name() << "\n";
    }
    std::cout << "\n\n\n";
}

Matrix Matrices::matrix_multiply() const
{
    if(x.get_row() != y.get_col() && x.get_col() != y.get_row())
        throw 0;
    unsigned int i, j, k;

    // Initialise Matrix XY
    int** xy = new int*[x.get_row()];
    for(i = 0; i < x.get_row(); i++)
    {
        xy[i] = new int[y.get_col()];
        for(j = 0; j < y.get_col(); j++)
            xy[i][j] = 0;
    }

    // Multiply
    for(i = 0; i < x.get_row(); i++)
        for(j = 0; j < y.get_col(); j++)
            for(k = 0; k < x.get_col(); k++)
                xy[i][j] += x.get()[i][k] * y.get()[k][j];

    Matrix x_y = {x.get_row(), y.get_col(), x.get_name() + y.get_name(), xy};
    return x_y;
}

Matrix Matrices::add() const
{
    if(x.get_row() != y.get_row() && x.get_col() != y.get_col())
        throw 0;
    
    unsigned int i, j;

    int** xPlusY = new int*[x.get_row()];
    for(i = 0; i < x.get_row(); i++)
    {
        xPlusY[i] = new int[x.get_col()];
        for(j = 0; j < x.get_col(); j++)
            xPlusY[i][j] = x.get()[i][j] + y.get()[i][j];
    }

    Matrix x_plus_y = 
    {
        x.get_row(), y.get_col(), x.get_name() + " + " + y.get_name(), xPlusY
    };
    
    return x_plus_y;
}
