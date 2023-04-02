#include <string>
#include <cmath>

void test_matrix(const std::string, const std::string = "rectangular");
unsigned int extra_chars(const int);
int** dupplicate(const unsigned int, const unsigned int, int**);

class Matrix
{
    int** a;
    unsigned int row, col;
    const std::string name;

    void cin_row_col(const std::string);
    void cin_val();

public:
    Matrix(const std::string, const std::string = "rectangular");

    Matrix(const unsigned int row, const unsigned int col, 
            const std::string name)
            : row{row}, col{col}, name{name} {    cin_val();    }

    // Initialising to the pointer itself would allow change outside the object
    Matrix(const unsigned int row, const unsigned int col, 
        const std::string name, int** a)
        : row{row}, col{col}, name{name}, a{dupplicate(row, col, a)} {        }

    ~Matrix();


    // Get functions
    // Returning the pointer itself would allow change outside the object
    int** get() const {    return dupplicate(row, col, a);    }
    unsigned int get_row() const {    return row;    }
    unsigned int get_col() const {    return col;    }
    std::string get_name() const {    return name;    }

    // Any Matrix
    Matrix scalar_multiply(const int) const;
    Matrix transpose() const;
    void cout() const;

    // Square Matrix
    int determinant() const;
    int trace() const;
};