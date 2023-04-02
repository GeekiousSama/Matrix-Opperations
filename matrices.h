#include "matrix.h"

void test_matrices(const std::string, const std::string);

class Matrices
{
public:
    Matrix x, y;


    Matrices(const std::string nameA, const std::string nameB, 
            const std::string type = "rectangular")
            : x{nameA, type}, y{nameB, type} {        }

    Matrices(const std::string nameA, const std::string nameB, 
            const std::string typeA, const std::string typeB)
            : x{nameA, typeA}, y{nameB, typeB} {        }

    Matrices(const unsigned int rowA, const unsigned int rowB,
            const unsigned int colA, const unsigned int colB,
            const std::string nameA, const std::string nameB)
            : x{rowA, colA, nameA}, y{rowB, colB, nameB} {        }

    Matrices(const unsigned int rowA, const unsigned int rowB,
            const unsigned int colA, const unsigned int colB,
            const std::string nameA, const std::string nameB, int** a, int** b)
            : x{rowA, colA, nameA, a}, y{rowB, colB, nameB, b} {        }

    Matrix matrix_multiply() const;
    Matrix add() const;
};