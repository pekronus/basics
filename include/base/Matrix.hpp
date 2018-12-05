#ifndef __Matrix_H__
#define __Matrix_H__

#include <vector>
#include <memory>
#include <string.h>

namespace pekronus
{
    template <class T>
    class Matrix
    {
      public:
        //!ctor
        Matrix();
        //! ctor with dimensions and initializer
        Matrix(const int i, const int j, const T v = 0.0);
        //! resize
        void resize(const int i, const int j, const T v = 0.0);
        //! get reference to value
        T& operator()(const int i, const int j)
          {return _data[i*_cols + j];}
        //! const version of get element
        const T& operator()(const int i, const int j) const
          {return _data[i*_cols + j];}
        //! multiply by vector A*v
        void multiply(const std::vector<T>& v, std::vector<T>& out) const;
        //! transpose
        void transpose();
        //! return number of columns
        size_t cols() const
          {return _cols;}
        //! return number of rows
        size_t rows() const
          {return _rows;}
    
      protected:
        size_t _rows;
        size_t _cols;
        std::unique_ptr<T> _data;
    };

    template <class T>
    void
    Matrix<T>::transpose()
    {
        const int sz = _rows*_cols;
        // create copy of the data (not efficient)
        std::unique_ptr<T> ta(new T(sz));
        memcpy(ta.get(), _data.get(), sz*sizeof(T));
          
        for (int i = 0; i < _rows; ++i)
        {
            for (int j = 0; j < _cols; ++j)
            {
                // find the new position
                int np = j*_rows + i;
                _data[np] = ta[i*_cols + j];
            }
        }

        int t = _cols;
        _cols = _rows;
        _rows = t;
    }

    template <class T>
    void
    Matrix<T>::multiply(const std::vector<T>& v, std::vector<T>& out) const
    {
        auto sz = v.size();
        if (sz != _cols)
            throw std::exception("Sizes do not match");

        out.assign(_rows, 0.0);
        for (size_t i = 0; i < _rows; ++i)
            for (size_t j = 0; j < _cols; ++j)
                out[i] += (*this)(i,j)*v[j];
    }
}

#endif
