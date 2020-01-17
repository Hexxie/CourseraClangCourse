#include <iostream>
#include <vector>

#define NOT !

class Matrix
{
public:
    Matrix();
    Matrix(int num_rows, int num_cols);

    void Reset(int num_rows, int num_cols);
    int At(int row_nr, int col_nr) const;
    int& At(int row_nr, int col_nr);
    int GetNumRows() const;
    int GetNumColumns() const;

    friend std::ostream& operator<< (std::ostream &out, const Matrix &matrix);
    friend std::istream& operator>> (std::istream &in, Matrix &matrix);
    friend bool operator==(const Matrix& lhs, const Matrix& rhs);
    friend Matrix& operator+(Matrix lhs, const Matrix& rhs);

private:
    int m_num_rows;
    int m_num_cols;
    std::vector<std::vector<int>> m_matrix;

    bool isNegative(int check_nr);

};