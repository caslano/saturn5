//
//  Copyright (c) 2000-2010
//  Joerg Walter, Mathias Koch, David Bellot
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef _BOOST_UBLAS_IO_
#define _BOOST_UBLAS_IO_

// Only forward definition required to define stream operations
#include <iosfwd>
#include <sstream>
#include <boost/numeric/ublas/matrix_expression.hpp>


namespace boost { namespace numeric { namespace ublas {

    /** \brief output stream operator for vector expressions
     *
     * Any vector expressions can be written to a standard output stream
     * as defined in the C++ standard library. For example:
     * \code
     * vector<float> v1(3),v2(3);
     * for(size_t i=0; i<3; i++)
     * {
     *       v1(i) = i+0.2;
     *       v2(i) = i+0.3;
     * }
     * cout << v1+v2 << endl;
     * \endcode
     * will display the some of the 2 vectors like this:
     * \code
     * [3](0.5,2.5,4.5)
     * \endcode
     *
     * \param os is a standard basic output stream
     * \param v is a vector expression
     * \return a reference to the resulting output stream
     */
    template<class E, class T, class VE>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    std::basic_ostream<E, T> &operator << (std::basic_ostream<E, T> &os,
                                           const vector_expression<VE> &v) {
        typedef typename VE::size_type size_type;
        size_type size = v ().size ();
        std::basic_ostringstream<E, T, std::allocator<E> > s;
        s.flags (os.flags ());
        s.imbue (os.getloc ());
        s.precision (os.precision ());
        s << '[' << size << "](";
        if (size > 0)
            s << v () (0);
        for (size_type i = 1; i < size; ++ i)
            s << ',' << v () (i);
        s << ')';
        return os << s.str ().c_str ();
    }

    /** \brief input stream operator for vectors
     *
     * This is used to feed in vectors with data stored as an ASCII representation
     * from a standard input stream.
     *
     * From a file or any valid stream, the format is: 
     * \c [<vector size>](<data1>,<data2>,...<dataN>) like for example:
     * \code
     * [5](1,2.1,3.2,3.14,0.2)
     * \endcode
     *
     * You can use it like this
     * \code
     * my_input_stream >> my_vector;
     * \endcode
     *
     * You can only put data into a valid \c vector<> not a \c vector_expression
     *
     * \param is is a standard basic input stream
     * \param v is a vector
     * \return a reference to the resulting input stream
     */
    template<class E, class T, class VT, class VA>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    std::basic_istream<E, T> &operator >> (std::basic_istream<E, T> &is,
                                           vector<VT, VA> &v) {
        typedef typename vector<VT, VA>::size_type size_type;
        E ch;
        size_type size;
        if (is >> ch && ch != '[') {
            is.putback (ch);
            is.setstate (std::ios_base::failbit);
        } else if (is >> size >> ch && ch != ']') {
            is.putback (ch);
            is.setstate (std::ios_base::failbit);
        } else if (! is.fail ()) {
            vector<VT, VA> s (size);
            if (is >> ch && ch != '(') {
                is.putback (ch);
                is.setstate (std::ios_base::failbit);
            } else if (! is.fail ()) {
                for (size_type i = 0; i < size; i ++) {
                    if (is >> s (i) >> ch && ch != ',') {
                        is.putback (ch);
                        if (i < size - 1)
                            is.setstate (std::ios_base::failbit);
                        break;
                    }
                }
                if (is >> ch && ch != ')') {
                    is.putback (ch);
                    is.setstate (std::ios_base::failbit);
                }
            }
            if (! is.fail ())
                v.swap (s);
        }
        return is;
    }

    /** \brief output stream operator for matrix expressions
     *
     * it outpus the content of a \f$(M \times N)\f$ matrix to a standard output 
     * stream using the following format:
     * \c[<rows>,<columns>]((<m00>,<m01>,...,<m0N>),...,(<mM0>,<mM1>,...,<mMN>))
     *
     * For example:
     * \code
     * matrix<float> m(3,3) = scalar_matrix<float>(3,3,1.0) - diagonal_matrix<float>(3,3,1.0);
     * cout << m << endl;
     * \encode
     * will display
     * \code
     * [3,3]((0,1,1),(1,0,1),(1,1,0))
     * \endcode
     * This output is made for storing and retrieving matrices in a simple way but you can
     * easily recognize the following: 
     * \f[ \left( \begin{array}{ccc} 1 & 1 & 1\\ 1 & 1 & 1\\ 1 & 1 & 1 \end{array} \right) - \left( \begin{array}{ccc} 1 & 0 & 0\\ 0 & 1 & 0\\ 0 & 0 & 1 \end{array} \right) = \left( \begin{array}{ccc} 0 & 1 & 1\\ 1 & 0 & 1\\ 1 & 1 & 0 \end{array} \right) \f]
     *
     * \param os is a standard basic output stream
     * \param m is a matrix expression
     * \return a reference to the resulting output stream
     */
    template<class E, class T, class ME>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    std::basic_ostream<E, T> &operator << (std::basic_ostream<E, T> &os,
                                           const matrix_expression<ME> &m) {
        typedef typename ME::size_type size_type;
        size_type size1 = m ().size1 ();
        size_type size2 = m ().size2 ();
        std::basic_ostringstream<E, T, std::allocator<E> > s;
        s.flags (os.flags ());
        s.imbue (os.getloc ());
        s.precision (os.precision ());
        s << '[' << size1 << ',' << size2 << "](";
        if (size1 > 0) {
            s << '(' ;
            if (size2 > 0)
                s << m () (0, 0);
            for (size_type j = 1; j < size2; ++ j)
                s << ',' << m () (0, j);
            s << ')';
        }
        for (size_type i = 1; i < size1; ++ i) {
            s << ",(" ;
            if (size2 > 0)
                s << m () (i, 0);
            for (size_type j = 1; j < size2; ++ j)
                s << ',' << m () (i, j);
            s << ')';
        }
        s << ')';
        return os << s.str ().c_str ();
    }

    /** \brief input stream operator for matrices
     *
     * This is used to feed in matrices with data stored as an ASCII representation
     * from a standard input stream.
     *
     * From a file or any valid standard stream, the format is:
     * \c[<rows>,<columns>]((<m00>,<m01>,...,<m0N>),...,(<mM0>,<mM1>,...,<mMN>))
     *
     * You can use it like this
     * \code
     * my_input_stream >> my_matrix;
     * \endcode
     *
     * You can only put data into a valid \c matrix<> not a \c matrix_expression
     *
     * \param is is a standard basic input stream
     * \param m is a matrix
     * \return a reference to the resulting input stream
     */
    template<class E, class T, class MT, class MF, class MA>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    std::basic_istream<E, T> &operator >> (std::basic_istream<E, T> &is,
                                           matrix<MT, MF, MA> &m) {
        typedef typename matrix<MT, MF, MA>::size_type size_type;
        E ch;
        size_type size1, size2;
        if (is >> ch && ch != '[') {
            is.putback (ch);
            is.setstate (std::ios_base::failbit);
        } else if (is >> size1 >> ch && ch != ',') {
            is.putback (ch);
            is.setstate (std::ios_base::failbit);
        } else if (is >> size2 >> ch && ch != ']') {
            is.putback (ch);
            is.setstate (std::ios_base::failbit);
        } else if (! is.fail ()) {
            matrix<MT, MF, MA> s (size1, size2);
            if (is >> ch && ch != '(') {
                is.putback (ch);
                is.setstate (std::ios_base::failbit);
            } else if (! is.fail ()) {
                for (size_type i = 0; i < size1; i ++) {
                    if (is >> ch && ch != '(') {
                        is.putback (ch);
                        is.setstate (std::ios_base::failbit);
                        break;
                    }
                    for (size_type j = 0; j < size2; j ++) {
                        if (is >> s (i, j) >> ch && ch != ',') {
                            is.putback (ch);
                            if (j < size2 - 1) {
                                is.setstate (std::ios_base::failbit);
                                break;
                            }
                        }
                    }
                    if (is >> ch && ch != ')') {
                        is.putback (ch);
                        is.setstate (std::ios_base::failbit);
                        break;
                    }
                    if (is >> ch && ch != ',') {
                       is.putback (ch);
                       if (i < size1 - 1) {
                            is.setstate (std::ios_base::failbit);
                            break;
                       }
                    }
                }
                if (is >> ch && ch != ')') {
                    is.putback (ch);
                    is.setstate (std::ios_base::failbit);
                }
            }
            if (! is.fail ())
                m.swap (s);
        }
        return is;
    }

    /** \brief special input stream operator for symmetric matrices
     *
     * This is used to feed in symmetric matrices with data stored as an ASCII 
     * representation from a standard input stream.
     *
     * You can simply write your matrices in a file or any valid stream and read them again 
     * at a later time with this function. The format is the following:
     * \code [<rows>,<columns>]((<m00>,<m01>,...,<m0N>),...,(<mM0>,<mM1>,...,<mMN>)) \endcode
     *
     * You can use it like this
     * \code
     * my_input_stream >> my_symmetric_matrix;
     * \endcode
     *
     * You can only put data into a valid \c symmetric_matrix<>, not in a \c matrix_expression
     * This function also checks that input data form a valid symmetric matrix
     *
     * \param is is a standard basic input stream
     * \param m is a \c symmetric_matrix
     * \return a reference to the resulting input stream
     */
    template<class E, class T, class MT, class MF1, class MF2, class MA>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    std::basic_istream<E, T> &operator >> (std::basic_istream<E, T> &is,
                                           symmetric_matrix<MT, MF1, MF2, MA> &m) {
        typedef typename symmetric_matrix<MT, MF1, MF2, MA>::size_type size_type;
        E ch;
        size_type size1, size2;
        MT value;
        if (is >> ch && ch != '[') {
            is.putback (ch);
            is.setstate (std::ios_base::failbit);
        } else if (is >> size1 >> ch && ch != ',') {
            is.putback (ch);
            is.setstate (std::ios_base::failbit);
        } else if (is >> size2 >> ch && (size2 != size1 || ch != ']')) { // symmetric matrix must be square
            is.putback (ch);
            is.setstate (std::ios_base::failbit);
        } else if (! is.fail ()) {
            symmetric_matrix<MT, MF1, MF2, MA> s (size1, size2);
            if (is >> ch && ch != '(') {
                is.putback (ch);
                is.setstate (std::ios_base::failbit);
             } else if (! is.fail ()) {
                for (size_type i = 0; i < size1; i ++) {
                    if (is >> ch && ch != '(') {
                        is.putback (ch);
                        is.setstate (std::ios_base::failbit);
                        break;
                    }
                    for (size_type j = 0; j < size2; j ++) {
                        if (is >> value >> ch && ch != ',') {
                            is.putback (ch);
                            if (j < size2 - 1) {
                                is.setstate (std::ios_base::failbit);
                                break;
                            }
                        }
                        if (i <= j) { 
                             // this is the first time we read this element - set the value
                            s(i,j) = value;
                        }
                        else if ( s(i,j) != value ) {
                            // matrix is not symmetric
                            is.setstate (std::ios_base::failbit);
                            break;
                        }
                     }
                     if (is >> ch && ch != ')') {
                         is.putback (ch);
                         is.setstate (std::ios_base::failbit);
                         break;
                     }
                     if (is >> ch && ch != ',') {
                        is.putback (ch);
                        if (i < size1 - 1) {
                             is.setstate (std::ios_base::failbit);
                             break;
                        }
                     }
                }
                if (is >> ch && ch != ')') {
                    is.putback (ch);
                    is.setstate (std::ios_base::failbit);
                }
            }
            if (! is.fail ())
                m.swap (s);
        }
        return is;
    }
 

}}}

#endif

/* io.hpp
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
*/