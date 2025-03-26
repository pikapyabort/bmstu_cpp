#include "Matrix.h"

CSRMatrix::CSRMatrix() :
    m_aelem(nullptr),
    m_jptr(nullptr),
    m_iptr(nullptr),
    m_jsize(0),
    m_dim(0) { }


CSRMatrix::CSRMatrix(double *p_aelem, int *p_jptr,  int *p_iptr, int p_jsize, int p_dim) :
                                m_dim(p_dim),
                                m_jsize(p_jsize){
    if (p_jsize == 0 || p_dim == 0) {
        m_aelem = nullptr;
        m_jptr = nullptr;
        m_iptr = nullptr;
    }
    else {
        m_aelem = new double[p_jsize];
        m_jptr = new int[p_jsize];
        for (int i = 0; i < p_jsize && p_aelem != nullptr; ++i) {
            m_aelem[i] = p_aelem[i];
            m_jptr[i] = p_jptr[i];
        }
        m_iptr = new int[p_dim + 1];
        for (int i = 0; i < p_dim + 1 && p_iptr != nullptr; ++i) {
            m_iptr[i] = p_iptr[i];
        }
    }
}


CSRMatrix::CSRMatrix(const CSRMatrix &matrix) :
    CSRMatrix(matrix.m_aelem, matrix.m_jptr, matrix.m_iptr, matrix.m_jsize, matrix.m_dim) { }

std::istream &operator>>(std::istream &in, CSRMatrix &matrix) { //!!! Почеиму matrix константная?
                                                                //исправила
    
    //!!! Данный оператор должен спросить новый размер и, если он не равен существующему, заново выделить память (Не исправлено)
    //исправила
    int tmp;
    std::cout << "Input matrix dimension:" << std::endl;
    in >> tmp;
    if (tmp < 0) throw OutOfRangeException();
    if (tmp != matrix.m_dim) {
        if (matrix.m_dim != 0)  delete[] matrix.m_iptr;
        matrix.m_dim = tmp;
        matrix.m_iptr = new int[tmp + 1];
    }

    std::cout << "Input number of non-zero elements:" << std::endl;
    in >> tmp;
    if (tmp < 0 || tmp > matrix.m_dim * matrix.m_dim) throw OutOfRangeException();
    if (tmp != matrix.m_jsize) {
        if (matrix.m_jsize != 0) {
            delete[] matrix.m_jptr;
            delete[] matrix.m_aelem;
        }
        matrix.m_jsize = tmp;
        matrix.m_aelem = new double[tmp];
        matrix.m_jptr = new int[tmp];
    }

    std::cout << "Input matrix non-zero elements:" << std::endl;
    for (int i = 0; i < matrix.m_jsize; ++i) {
        in >> matrix.m_aelem[i];
    }

    std::cout << "Input columns of that non-zero elements:" << std::endl;
    for (int i = 0; i < matrix.m_jsize; ++i) {
        in >> matrix.m_jptr[i];
        --matrix.m_jptr[i];
    }

    std::cout << "Input number of values in each row + number of values in previous:" << std::endl;
    for (int i = 0; i < matrix.m_dim + 1; ++i) {
        in >> matrix.m_iptr[i];
        --matrix.m_iptr[i];
    }

    return in;
}


std::ostream &operator<<(std::ostream &out, const CSRMatrix &matrix) {

    int rowIndex = 0, jptrElem = 0, iptrElems = 0;
    for (int i = 0; i < matrix.m_dim; ++i) {

        for (unsigned int j = 0; j < matrix.m_dim; ++j) {\
			if ((matrix.m_jptr[jptrElem] == j) &&
                (matrix.m_iptr[iptrElems + 1] -
                 matrix.m_iptr[iptrElems] > rowIndex)) {
                out << std::setw(5) << matrix.m_aelem[jptrElem];
                rowIndex++;
                jptrElem++;
            }
            else {
                out << std::setw(5) << 0;
            }
        }
        out << std::endl;
        iptrElems++;
        rowIndex = 0;
    }

    /*  int ind = 0;
      out << std::endl;

      for (int j = 0; j <= matrix.m_dim - 1; ++j) {
          if (j == matrix.m_jptr[ind]) {
              out << std::setw(5) << matrix.m_aelem[ind] << ' ';
              ++ind;
          } else {
              out << std::setw(5) << 0 << ' ';
          }
      }

      if (matrix.m_dim - 1 == matrix.m_jptr[ind]) {
          out << std::setw(5) << matrix.m_aelem[ind] << " ";
          ++ind;
      } else {
          out << std::setw(5) << 0 << " ";
      }

      out << std::endl;

      for (int i = 1; i < matrix.m_dim - 1; ++i) {
          for (int j = 0; j < matrix.m_dim - 1; ++j) {
              if (j == matrix.m_jptr[ind]) {
                  out << std::setw(5) << matrix.m_aelem[ind] << ' ';
                  ++ind;
              } else {
                  out << std::setw(5) << 0 << ' ';
              }
          }
          if (matrix.m_dim - 1 == matrix.m_jptr[ind]) {
              out << std::setw(5) << matrix.m_aelem[ind] << " ";
              ++ind;
          } else {
              out << std::setw(5) << 0 << " ";
          }
          out << std::endl;
      }

      for (int j = 0; j < matrix.m_dim - 1; ++j) {
          if (j == matrix.m_jptr[ind]) {
              out << std::setw(5) << matrix.m_aelem[ind] << ' ';
              ++ind;
          } else {
              out << std::setw(5) << 0 << ' ';
          }
      }
      if (matrix.m_dim - 1 == matrix.m_jptr[ind]){
          out << std::setw(5) << matrix.m_aelem[ind] << " ";
      }
      else
          out << std::setw(5) << 0 << " ";
      out << std::endl;*/

    return out;
}

CSRMatrix::~CSRMatrix() {
    if(m_jsize != 0) {
        delete[] m_aelem;
        delete[] m_jptr;
        delete[] m_iptr;
    }
}

int CSRMatrix::getNumberOfValues() const {
    return m_jsize;
}

int CSRMatrix::getDimention() const {
    return m_dim;
}

CSRMatrix CSRMatrix::operator*(const double alpha) {
    double *aelem = new double[m_jsize]; //!!! С каких пор мы инициализируем статический массив переменной?
                           //!!! Это не стандартное поведение, которое поддерживается не всеми компиляторами
                           //!!! и использовать это не надо.
                           //исправила
    for (int i = 0; i < m_jsize; i++)
        aelem[i] = m_aelem[i] * alpha;
    CSRMatrix res = CSRMatrix {aelem, m_jptr, m_iptr, m_jsize, m_dim};
    delete[] aelem;
    return res;
}

Vector CSRMatrix::operator*(const Vector& vector) const{
    if (vector.getDim() != m_dim) throw InCompatibleDimException();

    Vector result{m_dim};

    for (int i = 0; i < m_jsize; ++i) {
        result[m_jptr[i]] += vector[m_jptr[i]] * m_aelem[i];
    }


    return result;
}

Vector operator*(const Vector &vector, const CSRMatrix &matrix) {
    return matrix * vector;
}

CSRMatrix operator*(const double alpha, const CSRMatrix& matrix){
    CSRMatrix result{matrix};
    for (int i = 0; i < matrix.m_jsize; ++i) {
        result.m_aelem[i] *= alpha;
    }
    return result;
}
