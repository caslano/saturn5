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