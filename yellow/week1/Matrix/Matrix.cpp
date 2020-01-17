#include "Matrix.h"

/**
 * @brief Construct a new Matrix:: Matrix object
 * Constructs an empty Matrix with 0 rows and cols
 */
    Matrix::Matrix()
    {
        m_num_cols = 0;
        m_num_rows = 0;
    }

/**
 * @brief Construct a new Matrix:: Matrix object
 *
 * @param num_rows number of rows
 * @param num_cols number of cols
 *
 * @throw std::out_of_range exception when num_row or num_cols is negative
 */
    Matrix::Matrix(int num_rows, int num_cols): m_num_rows(num_rows), m_num_cols(num_rows) {

        if(isNegative(m_num_rows) || isNegative(m_num_cols))
        {
            throw std::out_of_range("Unable to create a matrix with negative nr of elements!");
        }

        if(NOT(IsEmpty()))
        {
            createMatrixArray();
            eraseMatrixElements();
        }
    }

/**
 * @brief Destroy the Matrix:: Matrix object
 *
 */
    Matrix::~Matrix()
    {
        if(NOT(IsEmpty()))
        {
            destroyMatrixArray();
        }
    }

/**
 * @brief Create a new matrix in the current Matrix object
 *
 * Re-create a new matrix based on new number of rows and cols.
 * The old matrix items will be erased.
 *
 * @param num_rows new number of rows
 * @param num_cols new number of cols
 *
 * @throw std::out_of_range exception when num_row or num_cols is negative
 */
    void Matrix::Reset(int num_rows, int num_cols)
    {
        if(isNegative(num_rows) || isNegative(num_cols))
        {
            throw std::out_of_range("Unable to create a matrix with negative nr of elements!");
        }

        m_num_rows = num_rows;
        m_num_cols = num_cols;

        destroyMatrixArray();
        if(NOT(IsEmpty()))
        {
            createMatrixArray();
            eraseMatrixElements();
        }
    }

/**
 * @brief Get a matrix element by row and col
 *
 * @param row_nr number of row
 * @param col_nr number of col
 * @return int new value from the matrix
 */
    int Matrix::At(int row_nr, int col_nr) const {
        return m_matrix[row_nr][col_nr];
    }

/**
 * @brief Get a reference to matrix element by row and col
 *
 * @param row_nr number of row
 * @param col_nr number of col
 * @return int& reference into matrix
 */
    int& Matrix::At(int row_nr, int col_nr){
        return m_matrix[row_nr][col_nr];
    }

/**
 * @brief Get number of rows in the matrix
 *
 * @return int number of rows
 */
    int Matrix::GetNumRows() const{
        return m_num_rows;
    }

/**
 * @brief Get number of cols in the matrix
 *
 * @return int number of cols
 */
    int Matrix::GetNumColumns() const{
        return m_num_cols;
    }

/**
 * @brief Check that input number is negative
 *
 * @param check_nr parameter to verify
 * @return true if input number is negative
 * @return false if input number is positive
 */
    bool Matrix::isNegative(int check_nr)
    {
        return check_nr < 0;
    }

/**
 * @brief Check that matrix is empty
 *
 * @return true matrix is empty
 * @return false matrix does not empty
 */
    bool Matrix::IsEmpty() const
    {
        return (m_num_rows == 0) || (m_num_cols == 0);
    }

/**
 * @brief Allocate a matrix array with member values
 *
 */
    void Matrix::createMatrixArray()
    {
        m_matrix = new int*[m_num_rows];
        for(int i = 0; i < m_num_rows; i++)
        {
            m_matrix[i] = new int[m_num_cols];
        }
    }
/**
 * @brief Destroy a matrix array
 *
 */
    void Matrix::destroyMatrixArray()
    {
        for(int i = 0; i < m_num_rows; i++)
        {
            if(m_matrix[i] != NULL)
                delete[] m_matrix[i];
        }
        if(m_matrix != NULL)
            delete[] m_matrix;
    }

/**
 * @brief Zero each matrix element
 *
 */
    void Matrix::eraseMatrixElements()
    {
        for(int i = 0; i < m_num_rows; i++)
            for(int j = 0; j < m_num_cols; j++)
                m_matrix[i][j] = 0;
    }

    std::ostream& operator<< (std::ostream &out, const Matrix &matrix)
    {
        out << matrix.m_num_rows <<" "<< matrix.m_num_cols<<"\n";

        if(NOT(matrix.IsEmpty()))
        {
            for(int i = 0; i < matrix.m_num_rows; i++)
            {
                for(int j = 0; j < matrix.m_num_cols; j++)
                {
                    out << matrix.m_matrix[i][j] << " ";
                }
                out << "\n";
            }
        }
        return out;
    }

    std::istream& operator>> (std::istream &in, Matrix &matrix){
        in >> matrix.m_num_rows;
        in >> matrix.m_num_cols;
        if(NOT(matrix.IsEmpty()))
        {
            matrix.createMatrixArray();
            for(int i = 0; i < matrix.m_num_rows; i++)
                for(int j = 0; j < matrix.m_num_cols; j++)
                    in >> matrix.m_matrix[i][j];
        }
        return in;
    }

    bool operator==(const Matrix& lhs, const Matrix& rhs){
        if(lhs.m_num_rows != rhs.m_num_rows)
            return false;
        if(lhs.m_num_cols != rhs.m_num_cols)
            return false;
        for(int i = 0; i < lhs.m_num_rows; i++)
            for(int j = 0; j < lhs.m_num_cols; j++)
                if(lhs.m_matrix[i][j] != rhs.m_matrix[i][j])
                    return false;
        return true;
    }

    Matrix& operator+(Matrix lhs, const Matrix& rhs){
        if((lhs.m_num_rows != rhs.m_num_rows) || (lhs.m_num_cols != rhs.m_num_cols))
            throw std::invalid_argument("Unable to add matrix with different sizes");

        Matrix *result = new Matrix(lhs.m_num_rows, lhs.m_num_cols);

        for(int i = 0; i < lhs.m_num_rows; i++)
            for(int j = 0; j < lhs.m_num_cols; j++)
                result->m_matrix[i][j] = lhs.m_matrix[i][j] + rhs.m_matrix[i][j];

        return *result;
    }