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