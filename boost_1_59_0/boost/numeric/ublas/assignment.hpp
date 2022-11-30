//
//  Copyright (c) 2010 Athanasios Iliopoulos
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASSIGNMENT_HPP
#define ASSIGNMENT_HPP

#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>

/*! \file assignment.hpp
    \brief uBlas assignment operator <<=.
*/

namespace boost { namespace numeric { namespace ublas {

/** \brief A CRTP and Barton-Nackman trick index manipulator wrapper class.
 *
 * This class is not meant to be used directly.
 */
template <class TV>
class index_manipulator {
public:
    typedef TV type;
    BOOST_UBLAS_INLINE
    const type &operator () () const {
        return *static_cast<const type *> (this);
    }
    BOOST_UBLAS_INLINE
    type &operator () () {
        return *static_cast<type *> (this);
    }
};

/** \brief A move_to vector index manipulator.
 *
 * When member function \c manip is called the referenced
 * index will be set to the manipulators' index.
 *
 * \sa move_to(T i)
 */
template <typename T>
class vector_move_to_manip: public index_manipulator<vector_move_to_manip<T> > {
public:
    BOOST_UBLAS_INLINE
    vector_move_to_manip(const T &k): i(k) { }

    template <typename V>
    BOOST_UBLAS_INLINE
    void manip(V &k) const { k=i; }
private:
    T i;
};

/** \brief An object generator that returns a move_to vector index manipulator
 *
 * \param i The element number the manipulator will move to when \c manip member function is called
 * \return A move_to vector manipulator
 *
 * Example usage:
 * \code
 * vector<double> a(6, 0);
 * a <<= 1, 2, move_to(5), 3;
 * \endcode
 * will result in:
 * \code
 * 1 2 0 0 0 3
 * \endcode
 *
 * \tparam T Size type
 * \sa move_to()
 */
template <typename T>
BOOST_UBLAS_INLINE vector_move_to_manip<T>  move_to(T i) {
    return vector_move_to_manip<T>(i);
}

/** \brief A static move to vector manipulator.
 *
 * When member function \c manip is called the referenced
 * index will be set to the manipulators' index
 *
 * \sa move_to(T i) and move_to()
*/
template <std::size_t I>
class static_vector_move_to_manip: public index_manipulator<static_vector_move_to_manip<I> > {
public:
    template <typename V>
    BOOST_UBLAS_INLINE
    void manip(V &k) const { k=I; }
};

/** \brief An object generator that returns a static move_to vector index  manipulator.
 *
 * Typically faster than the dynamic version, but can be used only when the
 * values are known at compile time.
 *
 * \return A static move_to vector manipulator
 *
 * Example usage:
 * \code
 * vector<double> a(6, 0);
 * a <<= 1, 2, move_to<5>(), 3;
 * \endcode
 * will result in:
 * \code
 * 1 2 0 0 0 3
 * \endcode
 *
 * \tparam I The number of elements the manipulator will traverse the index when \c manip function is called
 */
template <std::size_t I>
BOOST_UBLAS_INLINE static_vector_move_to_manip<I>  move_to() {
    return static_vector_move_to_manip<I>();
}

/** \brief A move vector index manipulator.
 *
 * When member function traverse is called the manipulators'
 * index will be added to the referenced index.
 *
 * \see move(T i)
 */
template <typename T>
class vector_move_manip: public index_manipulator<vector_move_manip<T> > {
public:
    BOOST_UBLAS_INLINE
    vector_move_manip(const T &k): i(k) { }

    template <typename V>
    BOOST_UBLAS_INLINE void manip(V &k) const { k+=i; }
private:
    T i;
};

/**
* \brief  An object generator that returns a move vector index manipulator
*
* \tparam T Size type
* \param i The number of elements the manipulator will traverse the index when \c manip
* member function is called. Negative values can be used.
* \return A move vector manipulator
*
* Example usage:
* \code
* vector<double> a(6, 0);
* a <<= 1, 2, move(3), 3;
* \endcode
* will result in:
* \code
* 1 2 0 0 0 3
* \endcode
*
*/
template <typename T>
BOOST_UBLAS_INLINE vector_move_manip<T>  move(T i) {
    return vector_move_manip<T>(i);
}

/**
* \brief A static move vector manipulator
*
* When member function \c manip is called the manipulators
* index will be added to the referenced index
*
* \sa move()
*
* \todo Doxygen has some problems with similar template functions. Correct that.
*/
template <std::ptrdiff_t I>
class static_vector_move_manip: public index_manipulator<static_vector_move_manip<I> > {
public:
    template <typename V>
    BOOST_UBLAS_INLINE void manip(V &k) const {
        // With the equivalent expression using '+=' operator, mscv reports waring C4245:
        // '+=' : conversion from 'ptrdiff_t' to 'unsigned int', signed/unsigned mismatch
        k = k + I;
    }
};

/**
* \brief An object generator that returns a static move vector index manipulator.
*
* Typically faster than the dynamic version, but can be used only when the
* values are known at compile time.
* \tparam I The Number of elements the manipulator will traverse the index when \c manip
* function is called.Negative values can be used.
* \return A static move vector manipulator
*
* Example usage:
* \code
* vector<double> a(6, 0);
* a <<= 1, 2, move<3>(), 3;
* \endcode
* will result in:
* \code
* 1 2 0 0 0 3
* \endcode
*
* \todo Doxygen has some problems with similar template functions. Correct that.
*/
template <std::ptrdiff_t I>
static_vector_move_manip<I>  move() {
    return static_vector_move_manip<I>();
}

/**
* \brief A move_to matrix manipulator
*
* When member function \c manip is called the referenced
* index will be set to the manipulators' index
*
* \sa move_to(T i, T j)
*
* \todo Doxygen has some problems with similar template functions. Correct that.
*/
template <typename T>
class matrix_move_to_manip: public index_manipulator<matrix_move_to_manip<T> > {
public:
    BOOST_UBLAS_INLINE
    matrix_move_to_manip(T k, T l): i(k), j(l) { }

    template <typename V1, typename V2>
    BOOST_UBLAS_INLINE
    void manip(V1 &k, V2 &l) const {
        k=i;
        l=j;
    }
private:
    T i, j;
};

/**
* \brief  An object generator that returns a "move_to" matrix index manipulator
*
* \tparam size type
* \param i The row number the manipulator will move to when \c manip
* member function is called
* \param j The column number the manipulator will move to when \c manip
* member function is called
* \return A move matrix manipulator
*
* Example usage:
* \code:
* matrix<double> A(3, 3, 0);
* A <<= 1, 2, move_to(A.size1()-1, A.size1()-1), 3;
* \endcode
* will result in:
* \code
* 1 2 0
* 0 0 0
* 0 0 3
* \endcode
* \sa move_to(T i, T j) and static_matrix_move_to_manip
*
* \todo Doxygen has some problems with similar template functions. Correct that.
*/
template <typename T>
BOOST_UBLAS_INLINE matrix_move_to_manip<T>  move_to(T i, T j) {
    return matrix_move_to_manip<T>(i, j);
}


/**
* \brief A static move_to matrix manipulator
* When member function traverse is called the referenced
* index will be set to the manipulators' index
*
* \sa move_to()
*
* \todo Doxygen has some problems with similar template functions. Correct that.
*/
template <std::size_t I,std::size_t J>
class static_matrix_move_to_manip: public index_manipulator<static_matrix_move_to_manip<I, J> > {
public:
    template <typename V, typename K>
    BOOST_UBLAS_INLINE
    void manip(V &k, K &l) const {
        k=I;
        l=J;
    }
};

/**
* \brief  An object generator that returns a static move_to matrix index manipulator.
*
* Typically faster than the dynamic version, but can be used only when the
* values are known at compile time.
* \tparam I The row number the manipulator will set the matrix assigner index to.
* \tparam J The column number the manipulator will set the matrix assigner index to.
* \return A static move_to matrix manipulator
*
* Example usage:
* \code:
* matrix<double> A(3, 3, 0);
* A <<= 1, 2, move_to<2,2>, 3;
* \endcode
* will result in:
* \code
* 1 2 0
* 0 0 0
* 0 0 3
* \endcode
* \sa move_to(T i, T j) and static_matrix_move_to_manip
*/
template <std::size_t I, std::size_t J>
BOOST_UBLAS_INLINE static_matrix_move_to_manip<I, J>  move_to() {
    return static_matrix_move_to_manip<I, J>();
}

/**
* \brief A move matrix index manipulator.
*
* When member function \c manip is called the manipulator's
* index will be added to the referenced' index.
*
* \sa move(T i, T j)
*/
template <typename T>
class matrix_move_manip: public index_manipulator<matrix_move_manip<T> > {
public:
    BOOST_UBLAS_INLINE
    matrix_move_manip(T k, T l): i(k), j(l) { }

    template <typename V, typename K>
    BOOST_UBLAS_INLINE
    void manip(V &k, K &l) const {
        k+=i;
        l+=j;
    }
private:
    T i, j;
};

/**
* \brief  An object generator that returns a move matrix index manipulator
*
* \tparam size type
* \param i The number of rows the manipulator will traverse the index when "manip"
* member function is called
* \param j The number of columns the manipulator will traverse the index when "manip"
* member function is called
* \return A move matrix manipulator
*
* Example:
* \code:
* matrix<double> A(3, 3, 0);
* A <<= 1, 2, move(1,0),
*            3,;
* \endcode
* will result in:
* \code
* 1 2 0
* 0 0 3
* 0 0 0
* \endcode
*/
template <typename T>
BOOST_UBLAS_INLINE matrix_move_manip<T>  move(T i, T j) {
    return matrix_move_manip<T>(i, j);
}

/**
* \brief A static move matrix index manipulator.
*
* When member function traverse is called the manipulator's
* index will be added to the referenced' index.
*
* \sa move()
*
* \todo Doxygen has some problems with similar template functions. Correct that.
*/
template <std::ptrdiff_t I, std::ptrdiff_t J>
class static_matrix_move_manip: public index_manipulator<static_matrix_move_manip<I, J> > {
public:
    template <typename V, typename K>
    BOOST_UBLAS_INLINE
    void manip(V &k, K &l) const {
        // With the equivalent expression using '+=' operator, mscv reports waring C4245:
        // '+=' : conversion from 'ptrdiff_t' to 'unsigned int', signed/unsigned mismatch
        k = k + I;
        l = l + J;
    }
};

/**
* \brief  An object generator that returns a static "move" matrix index manipulator.
*
* Typically faster than the dynamic version, but can be used only when the
* values are known at compile time. Negative values can be used.
* \tparam I The number of rows the manipulator will trasverse the matrix assigner index.
* \tparam J The number of columns the manipulator will trasverse the matrix assigner index.
* \tparam size type
* \return A static move matrix manipulator
*
* Example:
* \code:
* matrix<double> A(3, 3, 0);
* A <<= 1, 2, move<1,0>(),
*            3,;
* \endcode
* will result in:
* \code
* 1 2 0
* 0 0 3
* 0 0 0
* \endcode
*
* \sa move_to()
*
* \todo Doxygen has some problems with similar template functions. Correct that.
*/
template <std::ptrdiff_t I, std::ptrdiff_t J>
BOOST_UBLAS_INLINE static_matrix_move_manip<I, J>  move() {
    return static_matrix_move_manip<I, J>();
}

/**
* \brief A begining of row manipulator
*
* When member function \c manip is called the referenced
* index will be be set to the begining of the row (i.e. column = 0)
*
* \sa begin1()
*/
class begin1_manip: public index_manipulator<begin1_manip > {
public:
    template <typename V, typename K>
    BOOST_UBLAS_INLINE
    void manip(V & k, K &/*l*/) const {
        k=0;
    }
};

/**
* \brief  An object generator that returns a begin1 manipulator.
*
* The resulted manipulator will traverse the index to the begining
* of the current column when its' \c manip member function is called.
*
* \return A begin1 matrix index manipulator
*
* Example usage:
* \code:
* matrix<double> A(3, 3, 0);
* A <<= 1, 2, next_row(),
*      3, 4, begin1(), 1;
* \endcode
* will result in:
* \code
* 1 2 1
* 3 4 0
* 0 0 0
* \endcode
* \sa begin2()
*/
inline begin1_manip  begin1() {
    return begin1_manip();
}

/**
* \brief A begining of column manipulator
*
* When member function \c manip is called the referenced
* index will be be set to the begining of the column (i.e. row = 0).
*
*
* \sa begin2()
*/
class begin2_manip: public index_manipulator<begin2_manip > {
public:
    template <typename V, typename K>
    BOOST_UBLAS_INLINE
    void manip(V &/*k*/, K &l) const {
        l=0;
    }
};

/**
* \brief  An object generator that returns a begin2 manipulator to be used to traverse a matrix.
*
* The resulted manipulator will traverse the index to the begining
* of the current row when its' \c manip member function is called.
*
* \return A begin2 matrix manipulator
*
* Example:
* \code:
* matrix<double> A(3, 3, 0);
* A <<= 1, 2, move<1,0>(),
*      3, begin2(), 1;
* \endcode
* will result in:
* \code
* 1 2 0
* 1 0 3
* 0 0 0
* \endcode
* \sa begin1() begin2_manip
*/
inline begin2_manip  begin2() {
    return begin2_manip();
}


/**
* \brief A next row matrix manipulator.
*
* When member function traverse is called the referenced
* index will be traveresed to the begining of next row.
*
* \sa next_row()
*/
class next_row_manip: public index_manipulator<next_row_manip> {
public:
    template <typename V, typename K>
    BOOST_UBLAS_INLINE
    void manip(V &k, K &l) const {
        k++;
        l=0;
    }
};

/**
* \brief  An object generator that returns a next_row manipulator.
*
* The resulted manipulator will traverse the index to the begining
* of the next row when it's manip member function is called.
*
* \return A next_row matrix manipulator.
*
* Example:
* \code:
* matrix<double> A(3, 3, 0);
* A <<= 1, 2, next_row(),
*      3, 4;
* \endcode
* will result in:
* \code
* 1 2 0
* 3 4 0
* 0 0 0
* \endcode
* \sa next_column()
*/
inline next_row_manip  next_row() {
    return next_row_manip();
}

/**
* \brief A next column matrix manipulator.
*
* When member function traverse is called the referenced
* index will be traveresed to the begining of next column.
*
* \sa next_column()
*/
class next_column_manip: public index_manipulator<next_column_manip> {
public:
    template <typename V, typename K>
    BOOST_UBLAS_INLINE
    void manip(V &k, K &l) const {
        k=0;
        l++;
    }
};

/**
* \brief  An object generator that returns a next_row manipulator.
*
* The resulted manipulator will traverse the index to the begining
* of the next column when it's manip member function is called.
*
* \return A next_column matrix manipulator.
*
* Example:
* \code:
* matrix<double> A(3, 3, 0);
* A <<= 1, 2, 0,
*      3, next_column(), 4;
* \endcode
* will result in:
* \code
* 1 2 4
* 3 0 0
* 0 0 0
* \endcode
*
*/
inline next_column_manip next_column() {
    return next_column_manip();
}

/**
* \brief  A wrapper for fill policy classes
*
*/
template <class T>
class fill_policy_wrapper {
public:
    typedef T type;
};

// Collection of the fill policies
namespace fill_policy {

    /**
    * \brief  An index assign policy
    *
    * This policy is used to for the simplified ublas assign through
    * normal indexing.
    *
    *
    */
    class index_assign :public fill_policy_wrapper<index_assign> {
    public:
        template <class T, typename S, typename V>
        BOOST_UBLAS_INLINE
        static void apply(T &e, const S &i, const V &v) {
            e()(i) = v;
        }
        template <class T, typename S, typename V>
        BOOST_UBLAS_INLINE
        static void apply(T &e, const S &i, const S &j, const V &v) {
            e()(i, j) = v;
        }
    };

    /**
    * \brief  An index plus assign policy
    *
    * This policy is used when the assignment is desired to be followed
    * by an addition.
    *
    *
    */
    class index_plus_assign :public fill_policy_wrapper<index_plus_assign> {
    public:
        template <class T, typename S, typename V>
        BOOST_UBLAS_INLINE
        static void apply(T &e, const S &i, const V &v) {
            e()(i) += v;
        }
        template <class T, typename S, typename V>
        BOOST_UBLAS_INLINE
        static void apply(T &e, const S &i, const S &j, const V &v) {
            e()(i, j) += v;
        }
    };

    /**
    * \brief  An index minus assign policy
    *
    * This policy is used when the assignment is desired to be followed
    * by a substraction.
    *
    *
    */
    class index_minus_assign :public fill_policy_wrapper<index_minus_assign> {
    public:
        template <class T, typename S, typename V>
        BOOST_UBLAS_INLINE
        static void apply(T &e, const S &i, const V &v) {
            e()(i) -= v;
        }
        template <class T, typename S, typename V>
        BOOST_UBLAS_INLINE
        static void apply(T &e, const S &i, const S &j, const V &v) {
            e()(i, j) -= v;
        }
    };

    /**
    * \brief  The sparse push_back fill policy.
    *
    * This policy is adequate for sparse types, when fast filling is required, where indexing
    * assign is pretty slow.

    * It is important to note that push_back assign cannot be used to add elements before elements
    * already existing in a sparse container. To achieve that please use the sparse_insert fill policy.
    */
    class sparse_push_back :public fill_policy_wrapper<sparse_push_back > {
    public:
        template <class T, class S, class V>
        BOOST_UBLAS_INLINE
        static void apply(T &e, const S &i, const V &v) {
            e().push_back(i, v);
        }
        template <class T, class S, class V>
        BOOST_UBLAS_INLINE
        static void apply(T &e, const S &i, const S &j, const V &v) {
            e().push_back(i,j, v);
        }
    };

    /**
    * \brief  The sparse insert fill policy.
    *
    * This policy is adequate for sparse types, when fast filling is required, where indexing
    * assign is pretty slow. It is slower than sparse_push_back fill policy, but it can be used to
    * insert elements anywhere inside the container.
    */
    class sparse_insert :public fill_policy_wrapper<sparse_insert> {
    public:
        template <class T, class S, class V>
        BOOST_UBLAS_INLINE
        static void apply(T &e, const S &i, const V &v) {
            e().insert_element(i, v);
        }
        template <class T, class S, class V>
        BOOST_UBLAS_INLINE
        static void apply(T &e, const S &i, const S &j, const V &v) {
            e().insert_element(i,j, v);
        }
    };

}

/** \brief A wrapper for traverse policy classes
*
*/
template <class T>
class traverse_policy_wrapper {
public:
    typedef T type;
};

// Collection of the traverse policies
namespace traverse_policy {


    /**
    * \brief  The no wrap policy.
    *
    * The no wrap policy does not allow wrapping when assigning to a matrix
    */
    struct no_wrap {
        /**
        * \brief  Element wrap method
        */
        template <class S1, class S2, class S3>
        BOOST_UBLAS_INLINE
        static void apply1(const S1 &/*s*/, S2 &/*i*/, S3 &/*j*/) {
        }

        /**
        * \brief  Matrix block wrap method
        */
        template <class S1, class S2, class S3>
        BOOST_UBLAS_INLINE
        static void apply2(const S1 &/*s1*/, const S1 &/*s2*/, S2 &/*i1*/, S3 &/*i2*/) {
        }
    };

    /**
    * \brief  The wrap policy.
    *
    * The wrap policy enables element wrapping when assigning to a matrix
    */
    struct wrap {
        /**
        * \brief  Element wrap method
        */
        template <class S1, class S2, class S3>
        BOOST_UBLAS_INLINE
        static void apply1(const S1 &s, S2 &i1, S3 &i2) {
            if (i2>=s) {
                i1++;
                i2=0;
            }
        }

        /**
        * \brief  Matrix block wrap method
        */
        template <class S1, class S2, class S3>
        BOOST_UBLAS_INLINE
        static void apply2(const S1 &s1, const S1 &s2, S2 &i1, S3 &i2) {
            if (i2>=s2) i2=0;   // Wrap to the next block
            else i1-=s1;        // Move up (or right) one block
        }
    };

    /**
    * \brief  The row_by_row traverse policy
    *
    * This policy is used when the assignment is desired to happen
    * row_major wise for performance or other reasons.
    *
    * This is the default behaviour. To change it globally please define BOOST_UBLAS_DEFAULT_ASSIGN_BY_COLUMN
    * in the compilation options or in an adequate header file.
    *
    * Please see EXAMPLES_LINK for usage information.
    *
    * \todo Add examples link
    */
    template <class Wrap = wrap>
    class by_row_policy :public traverse_policy_wrapper<by_row_policy<Wrap> > {
    public:
        template <typename S1, typename S2>
        BOOST_UBLAS_INLINE
        static void advance(S1 &/*i*/, S2 &j) { j++;}

        template <class E1, class E2, typename S1, typename S2, typename S3, typename S4, typename S5>
        BOOST_UBLAS_INLINE
        static bool next(const E1 &e, const E2 &me, S1 &i, S2 &j, const S3 &/*i0*/, const S3 &j0, S4 &k, S5 &l) {
            l++; j++;
            if (l>=e().size2()) {
                l=0; k++; j=j0; i++;
                // It is assumed that the iteration starts from 0 and progresses only using this function from within
                // an assigner object.
                // Otherwise (i.e. if it is called outside the assigner object) apply2 should have been
                // outside the if statement.
                if (k>=e().size1()) {
                    j=j0+e().size2();
                    Wrap::apply2(e().size1(), me().size2(), i, j);
                    return false;
                }
            }
            return true;
        }

        template <class E, typename S1, typename S2>
        BOOST_UBLAS_INLINE
        static void apply_wrap(const E& e, S1 &i, S2 &j) {
            Wrap::apply1(e().size2(), i, j);
        }
    };

    /**
    * \brief  The column_by_column traverse policy
    *
    * This policy is used when the assignment is desired to happen
    * column_major wise, for performance or other reasons.
    *
    * This is the NOT the default behaviour. To set this as the default define BOOST_UBLAS_DEFAULT_ASSIGN_BY_COLUMN
    * in the compilation options or in an adequate header file.
    *
    * Please see EXAMPLES_LINK for usage information.
    *
    * \todo Add examples link
    */
    template <class Wrap = wrap>
    class by_column_policy :public traverse_policy_wrapper<by_column_policy<Wrap> > {
    public:
        template <typename S1, typename S2>
        BOOST_UBLAS_INLINE
        static void advance(S1 &i, S2 &/*j*/) { i++;}

        template <class E1, class E2, typename S1, typename S2, typename S3, typename S4, typename S5>
        BOOST_UBLAS_INLINE
        static bool next(const E1 &e, const E2 &me, S1 &i, S2 &j, const S3 &i0, const S3 &/*j0*/, S4 &k, S5 &l) {
            k++; i++;
            if (k>=e().size1()) {
                k=0; l++; i=i0; j++;
                // It is assumed that the iteration starts from 0 and progresses only using this function from within
                // an assigner object.
                // Otherwise (i.e. if it is called outside the assigner object) apply2 should have been
                // outside the if statement.
                if (l>=e().size2()) {
                    i=i0+e().size1();
                    Wrap::apply2(e().size2(), me().size1(), j, i);
                    return false;
                }
            }
            return true;
        }

        template <class E, typename S1, typename S2>
        BOOST_UBLAS_INLINE
        static void apply_wrap(const E& e, S1 &i, S2 &j) {
            Wrap::apply1(e().size1(), j, i);
        }
    };
}
#ifndef BOOST_UBLAS_DEFAULT_NO_WRAP_POLICY
    typedef traverse_policy::wrap DEFAULT_WRAP_POLICY;
#else
    typedef traverse_policy::no_wrap DEFAULT_WRAP_POLICY;
#endif

#ifndef BOOST_UBLAS_DEFAULT_ASSIGN_BY_COLUMN
    typedef traverse_policy::by_row_policy<DEFAULT_WRAP_POLICY> DEFAULT_TRAVERSE_POLICY;
#else
    typedef traverse_policy::by_column<DEFAULT_WRAP_POLICY> DEFAULT_TRAVERSE_POLICY;
#endif

 // Traverse policy namespace
namespace traverse_policy {

    inline by_row_policy<DEFAULT_WRAP_POLICY> by_row() {
    return by_row_policy<DEFAULT_WRAP_POLICY>();
    }

    inline by_row_policy<wrap> by_row_wrap() {
        return by_row_policy<wrap>();
    }

    inline by_row_policy<no_wrap> by_row_no_wrap() {
        return by_row_policy<no_wrap>();
    }

    inline by_column_policy<DEFAULT_WRAP_POLICY> by_column() {
        return by_column_policy<DEFAULT_WRAP_POLICY>();
    }

    inline by_column_policy<wrap> by_column_wrap() {
        return by_column_policy<wrap>();
    }

    inline by_column_policy<no_wrap> by_column_no_wrap() {
        return by_column_policy<no_wrap>();
    }

}

/**
* \brief  An assigner object used to fill a vector using operator <<= and operator, (comma)
*
* This object is meant to be created by appropriate object generators.
* Please see EXAMPLES_LINK for usage information.
*
* \todo Add examples link
*/
template <class E, class Fill_Policy = fill_policy::index_assign>
class vector_expression_assigner {
public:
    typedef typename E::expression_type::value_type value_type;
    typedef typename E::expression_type::size_type size_type;

    BOOST_UBLAS_INLINE
    vector_expression_assigner(E &e):ve(&e), i(0) {
    }

    BOOST_UBLAS_INLINE
    vector_expression_assigner(size_type k, E &e):ve(&e), i(k) {
        // Overloaded like that so it can be differentiated from (E, val).
        // Otherwise there would be an ambiquity when value_type == size_type.
    }

    BOOST_UBLAS_INLINE
    vector_expression_assigner(E &e, value_type val):ve(&e), i(0) {
        operator,(val);
    }

    template <class AE>
    BOOST_UBLAS_INLINE
    vector_expression_assigner(E &e, const vector_expression<AE> &nve):ve(&e), i(0) {
        operator,(nve);
    }

    template <typename T>
    BOOST_UBLAS_INLINE
    vector_expression_assigner(E &e, const index_manipulator<T> &ta):ve(&e), i(0) {
        operator,(ta);
    }

    BOOST_UBLAS_INLINE
    vector_expression_assigner &operator, (const value_type& val) {
        apply(val);
        return *this;
    }

    template <class AE>
    BOOST_UBLAS_INLINE
    vector_expression_assigner &operator, (const vector_expression<AE> &nve) {
        for (typename AE::size_type k = 0; k!= nve().size(); k++)
            operator,(nve()(k));
        return *this;
    }

    template <typename T>
    BOOST_UBLAS_INLINE
    vector_expression_assigner &operator, (const index_manipulator<T> &ta) {
        ta().manip(i);
        return *this;
    }

    template <class T>
    BOOST_UBLAS_INLINE
    vector_expression_assigner<E, T> operator, (fill_policy_wrapper<T>) const {
        return vector_expression_assigner<E, T>(i, *ve);
    }

private:
    BOOST_UBLAS_INLINE
    vector_expression_assigner &apply(const typename E::expression_type::value_type& val) {
        Fill_Policy::apply(*ve, i++, val);
        return *this;
    }

private:
    E *ve;
    size_type i;
};

/*
// The following static assigner is about 30% slower than the dynamic one, probably due to the recursive creation of assigner objects.
// It remains commented here for future reference.

template <class E, std::size_t I=0>
class static_vector_expression_assigner {
public:
    typedef typename E::expression_type::value_type value_type;
    typedef typename E::expression_type::size_type size_type;

    BOOST_UBLAS_INLINE
    static_vector_expression_assigner(E &e):ve(e) {
    }

    BOOST_UBLAS_INLINE
    static_vector_expression_assigner(E &e, value_type val):ve(e) {
        operator,(val);
    }

    BOOST_UBLAS_INLINE
    static_vector_expression_assigner<E, I+1> operator, (const value_type& val) {
        return apply(val);
    }

private:
    BOOST_UBLAS_INLINE
    static_vector_expression_assigner<E, I+1> apply(const typename E::expression_type::value_type& val) {
        ve()(I)=val;
        return static_vector_expression_assigner<E, I+1>(ve);
    }

private:
    E &ve;
};

template <class E>
BOOST_UBLAS_INLINE
static_vector_expression_assigner<vector_expression<E>, 1 > test_static(vector_expression<E> &v, const typename E::value_type &val) {
    v()(0)=val;
    return static_vector_expression_assigner<vector_expression<E>, 1 >(v);
}
*/


/**
* \brief  A vector_expression_assigner generator used with operator<<= for simple types
*
* Please see EXAMPLES_LINK for usage information.
*
* \todo Add examples link
*/
template <class E>
BOOST_UBLAS_INLINE
vector_expression_assigner<vector_expression<E> > operator<<=(vector_expression<E> &v, const typename E::value_type &val) {
    return vector_expression_assigner<vector_expression<E> >(v,val);
}

/**
* \brief  ! A vector_expression_assigner generator used with operator<<= for vector expressions
*
* Please see EXAMPLES_LINK for usage information.
*
* \todo Add examples link
*/
template <class E1, class E2>
BOOST_UBLAS_INLINE
vector_expression_assigner<vector_expression<E1> > operator<<=(vector_expression<E1> &v, const vector_expression<E2> &ve) {
    return vector_expression_assigner<vector_expression<E1> >(v,ve);
}

/**
* \brief  A vector_expression_assigner generator used with operator<<= for traverse manipulators
*
* Please see EXAMPLES_LINK for usage information.
*
* \todo Add examples link
*/
template <class E, typename T>
BOOST_UBLAS_INLINE
vector_expression_assigner<vector_expression<E> > operator<<=(vector_expression<E> &v, const index_manipulator<T> &nv) {
    return vector_expression_assigner<vector_expression<E> >(v,nv);
}

/**
* \brief  A vector_expression_assigner generator used with operator<<= for choice of fill policy
*
* Please see EXAMPLES_LINK for usage information.
*
* \todo Add examples link
*/
template <class E, typename T>
BOOST_UBLAS_INLINE
vector_expression_assigner<vector_expression<E>, T> operator<<=(vector_expression<E> &v, fill_policy_wrapper<T>) {
    return vector_expression_assigner<vector_expression<E>, T>(v);
}

/**
* \brief  An assigner object used to fill a vector using operator <<= and operator, (comma)
*
* This object is meant to be created by appropriate object generators.
* Please see EXAMPLES_LINK for usage information.
*
* \todo Add examples link
*/
template <class E, class Fill_Policy = fill_policy::index_assign, class Traverse_Policy = DEFAULT_TRAVERSE_POLICY >
class matrix_expression_assigner {
public:
    typedef typename E::expression_type::size_type size_type;

    BOOST_UBLAS_INLINE
    matrix_expression_assigner(E &e): me(&e), i(0), j(0) {
    }

    BOOST_UBLAS_INLINE
    matrix_expression_assigner(E &e, size_type k, size_type l): me(&e), i(k), j(l) {
    }

    BOOST_UBLAS_INLINE
    matrix_expression_assigner(E &e, typename E::expression_type::value_type val): me(&e), i(0), j(0) {
        operator,(val);
    }

    template <class AE>
    BOOST_UBLAS_INLINE
    matrix_expression_assigner(E &e, const vector_expression<AE> &nve):me(&e), i(0), j(0) {
        operator,(nve);
    }

    template <class AE>
    BOOST_UBLAS_INLINE
    matrix_expression_assigner(E &e, const matrix_expression<AE> &nme):me(&e), i(0), j(0) {
        operator,(nme);
    }

    template <typename T>
    BOOST_UBLAS_INLINE
    matrix_expression_assigner(E &e, const index_manipulator<T> &ta):me(&e), i(0), j(0) {
        operator,(ta);
    }

    BOOST_UBLAS_INLINE
    matrix_expression_assigner &operator, (const typename E::expression_type::value_type& val) {
        Traverse_Policy::apply_wrap(*me, i ,j);
        return apply(val);
    }

    template <class AE>
    BOOST_UBLAS_INLINE
    matrix_expression_assigner &operator, (const vector_expression<AE> &nve) {
        for (typename AE::size_type k = 0; k!= nve().size(); k++) {
            operator,(nve()(k));
        }
        return *this;
    }

    template <class AE>
    BOOST_UBLAS_INLINE
    matrix_expression_assigner &operator, (const matrix_expression<AE> &nme) {
        return apply(nme);
    }

    template <typename T>
    BOOST_UBLAS_INLINE
    matrix_expression_assigner &operator, (const index_manipulator<T> &ta) {
        ta().manip(i, j);
        return *this;
    } 

    template <class T>
    BOOST_UBLAS_INLINE
    matrix_expression_assigner<E, T, Traverse_Policy> operator, (fill_policy_wrapper<T>) const {
        return matrix_expression_assigner<E, T, Traverse_Policy>(*me, i, j);
    }


    template <class T>
    BOOST_UBLAS_INLINE
    matrix_expression_assigner<E, Fill_Policy, T> operator, (traverse_policy_wrapper<T>) {
        Traverse_Policy::apply_wrap(*me, i ,j);
        return matrix_expression_assigner<E, Fill_Policy, T>(*me, i, j);
    }

private:
    BOOST_UBLAS_INLINE
    matrix_expression_assigner &apply(const typename E::expression_type::value_type& val) {
        Fill_Policy::apply(*me, i, j, val);
        Traverse_Policy::advance(i,j);
        return *this;
    }

    template <class AE>
    BOOST_UBLAS_INLINE
    matrix_expression_assigner &apply(const matrix_expression<AE> &nme) {
        size_type bi = i;
        size_type bj = j;
        typename AE::size_type k=0, l=0;
        Fill_Policy::apply(*me, i, j, nme()(k, l));
        while (Traverse_Policy::next(nme, *me, i, j, bi, bj, k, l))
            Fill_Policy::apply(*me, i, j, nme()(k, l));
        return *this;
    }

private:
    E *me;
    size_type i, j;
};

/**
* \brief  A matrix_expression_assigner generator used with operator<<= for simple types
*
* Please see EXAMPLES_LINK for usage information.
*
* \todo Add examples link
*/
template <class E>
BOOST_UBLAS_INLINE
matrix_expression_assigner<matrix_expression<E> > operator<<=(matrix_expression<E> &me, const typename E::value_type &val) {
    return matrix_expression_assigner<matrix_expression<E> >(me,val);
}

/**
* \brief  A matrix_expression_assigner generator used with operator<<= for choice of fill policy
*
* Please see EXAMPLES_LINK for usage information.
*
* \todo Add examples link
*/
template <class E, typename T>
BOOST_UBLAS_INLINE
matrix_expression_assigner<matrix_expression<E>, T> operator<<=(matrix_expression<E> &me, fill_policy_wrapper<T>) {
    return matrix_expression_assigner<matrix_expression<E>, T>(me);
}

/**
* \brief  A matrix_expression_assigner generator used with operator<<= for traverse manipulators
*
* Please see EXAMPLES_LINK for usage information.
*
* \todo Add examples link
*/
template <class E, typename T>
BOOST_UBLAS_INLINE
matrix_expression_assigner<matrix_expression<E> > operator<<=(matrix_expression<E> &me, const index_manipulator<T> &ta) {
    return matrix_expression_assigner<matrix_expression<E> >(me,ta);
}

/**
* \brief  A matrix_expression_assigner generator used with operator<<= for traverse manipulators
*
* Please see EXAMPLES_LINK for usage information.
*
* \todo Add examples link
*/
template <class E, typename T>
BOOST_UBLAS_INLINE
matrix_expression_assigner<matrix_expression<E>, fill_policy::index_assign, T> operator<<=(matrix_expression<E> &me, traverse_policy_wrapper<T>) {
    return matrix_expression_assigner<matrix_expression<E>, fill_policy::index_assign, T>(me);
}

/**
* \brief  A matrix_expression_assigner generator used with operator<<= for vector expressions
*
* Please see EXAMPLES_LINK for usage information.
*
* \todo Add examples link
*/
template <class E1, class E2>
BOOST_UBLAS_INLINE
matrix_expression_assigner<matrix_expression<E1> > operator<<=(matrix_expression<E1> &me, const vector_expression<E2> &ve) {
    return matrix_expression_assigner<matrix_expression<E1> >(me,ve);
}

/**
* \brief  A matrix_expression_assigner generator used with operator<<= for matrix expressions
*
* Please see EXAMPLES_LINK for usage information.
*
* \todo Add examples link
*/
template <class E1, class E2>
BOOST_UBLAS_INLINE
matrix_expression_assigner<matrix_expression<E1> > operator<<=(matrix_expression<E1> &me1, const matrix_expression<E2> &me2) {
    return matrix_expression_assigner<matrix_expression<E1> >(me1,me2);
}

} } }

#endif // ASSIGNMENT_HPP

/* assignment.hpp
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
*/