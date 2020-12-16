/**
 * \file size.hpp
 *
 * \brief The family of \c size operations.
 *
 * Copyright (c) 2009-2010, Marco Guazzone
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * \author Marco Guazzone, marco.guazzone@gmail.com
 */

#ifndef BOOST_NUMERIC_UBLAS_OPERATION_SIZE_HPP
#define BOOST_NUMERIC_UBLAS_OPERATION_SIZE_HPP


#include <boost/mpl/has_xxx.hpp> 
#include <boost/mpl/if.hpp>
#include <boost/numeric/ublas/detail/config.hpp>
#include <boost/numeric/ublas/expression_types.hpp>
#include <boost/numeric/ublas/fwd.hpp>
#include <boost/numeric/ublas/tags.hpp>
#include <boost/numeric/ublas/traits.hpp>
#include <boost/utility/enable_if.hpp>
#include <cstddef>


namespace boost { namespace numeric { namespace ublas {

namespace detail { namespace /*<unnamed>*/ {

/// Define a \c has_size_type trait class.
BOOST_MPL_HAS_XXX_TRAIT_DEF(size_type)


/**
 * \brief Wrapper type-traits used in \c boost::lazy_enabled_if for getting the
 *  size type (see below).
 * \tparam VectorT A vector type.
 */
template <typename VectorT>
struct vector_size_type
{
    /// The size type.
    typedef typename vector_traits<VectorT>::size_type type;
};

/**
 * \brief Wrapper type-traits used in \c boost::lazy_enabled_if for getting the
 *  size type (see below).
 * \tparam MatrixT A matrix type.
 */
template <typename MatrixT>
struct matrix_size_type
{
    /// The size type.
    typedef typename matrix_traits<MatrixT>::size_type type;
};


/**
 * \brief Auxiliary class for computing the size of the given dimension for
 *  a container of the given category.
 * \tparam Dim The dimension number (starting from 1).
 * \tparam CategoryT The category type (e.g., vector_tag).
 */
template <std::size_t Dim, typename CategoryT>
struct size_by_dim_impl;


/**
 * \brief Auxiliary class for computing the size of the given dimension for
 *  a container of the given category and with the given orientation.
 * \tparam Dim The dimension number (starting from 1).
 * \tparam CategoryT The category type (e.g., vector_tag).
 * \tparam OrientationT The orientation category type (e.g., row_major_tag).
 */
template <typename TagT, typename CategoryT, typename OrientationT>
struct size_by_tag_impl;


/**
 * \brief Specialization of \c size_by_dim_impl for computing the size of a
 *  vector.
 */
template <>
struct size_by_dim_impl<1, vector_tag>
{
    /**
     * \brief Compute the size of the given vector.
     * \tparam ExprT A vector expression type.
     * \pre ExprT must be a model of VectorExpression.
     */
    template <typename ExprT>
    BOOST_UBLAS_INLINE
    static typename vector_traits<ExprT>::size_type apply(vector_expression<ExprT> const& ve)
    {
        return ve().size();
    }
};


/**
 * \brief Specialization of \c size_by_dim_impl for computing the number of
 *  rows of a matrix
 */
template <>
struct size_by_dim_impl<1, matrix_tag>
{
    /**
     * \brief Compute the number of rows of the given matrix.
     * \tparam ExprT A matrix expression type.
     * \pre ExprT must be a model of MatrixExpression.
     */
    template <typename ExprT>
    BOOST_UBLAS_INLINE
    static typename matrix_traits<ExprT>::size_type apply(matrix_expression<ExprT> const& me)
    {
        return me().size1();
    }
};


/**
 * \brief Specialization of \c size_by_dim_impl for computing the number of
 *  columns of a matrix
 */
template <>
struct size_by_dim_impl<2, matrix_tag>
{
    /**
     * \brief Compute the number of columns of the given matrix.
     * \tparam ExprT A matrix expression type.
     * \pre ExprT must be a model of MatrixExpression.
     */
    template <typename ExprT>
    BOOST_UBLAS_INLINE
    static typename matrix_traits<ExprT>::size_type apply(matrix_expression<ExprT> const& me)
    {
        return me().size2();
    }
};


/**
 * \brief Specialization of \c size_by_tag_impl for computing the size of the
 *  major dimension of a row-major oriented matrix.
 */
template <>
struct size_by_tag_impl<tag::major, matrix_tag, row_major_tag>
{
    /**
     * \brief Compute the number of rows of the given matrix.
     * \tparam ExprT A matrix expression type.
     * \pre ExprT must be a model of MatrixExpression.
     */
    template <typename ExprT>
    BOOST_UBLAS_INLINE
    static typename matrix_traits<ExprT>::size_type apply(matrix_expression<ExprT> const& me)
    {
        return me().size1();
    }
};


/**
 * \brief Specialization of \c size_by_tag_impl for computing the size of the
 *  minor dimension of a row-major oriented matrix.
 */
template <>
struct size_by_tag_impl<tag::minor, matrix_tag, row_major_tag>
{
    /**
     * \brief Compute the number of columns of the given matrix.
     * \tparam ExprT A matrix expression type.
     * \pre ExprT must be a model of MatrixExpression.
     */
    template <typename ExprT>
    BOOST_UBLAS_INLINE
    static typename matrix_traits<ExprT>::size_type apply(matrix_expression<ExprT> const& me)
    {
        return me().size2();
    }
};


/**
 * \brief Specialization of \c size_by_tag_impl for computing the size of the
 *  leading dimension of a row-major oriented matrix.
 */
template <>
struct size_by_tag_impl<tag::leading, matrix_tag, row_major_tag>
{
    /**
     * \brief Compute the number of columns of the given matrix.
     * \tparam ExprT A matrix expression type.
     * \pre ExprT must be a model of MatrixExpression.
     */
    template <typename ExprT>
    BOOST_UBLAS_INLINE
    static typename matrix_traits<ExprT>::size_type apply(matrix_expression<ExprT> const& me)
    {
        return me().size2();
    }
};


/// \brief Specialization of \c size_by_tag_impl for computing the size of the
///  major dimension of a column-major oriented matrix.
template <>
struct size_by_tag_impl<tag::major, matrix_tag, column_major_tag>
{
    /**
     * \brief Compute the number of columns of the given matrix.
     * \tparam ExprT A matrix expression type.
     * \pre ExprT must be a model of MatrixExpression.
     */
    template <typename ExprT>
    BOOST_UBLAS_INLINE
    static typename matrix_traits<ExprT>::size_type apply(matrix_expression<ExprT> const& me)
    {
        return me().size2();
    }
};


/// \brief Specialization of \c size_by_tag_impl for computing the size of the
///  minor dimension of a column-major oriented matrix.
template <>
struct size_by_tag_impl<tag::minor, matrix_tag, column_major_tag>
{
    /**
     * \brief Compute the number of rows of the given matrix.
     * \tparam ExprT A matrix expression type.
     * \pre ExprT must be a model of MatrixExpression.
     */
    template <typename ExprT>
    BOOST_UBLAS_INLINE
    static typename matrix_traits<ExprT>::size_type apply(matrix_expression<ExprT> const& me)
    {
        return me().size1();
    }
};


/// \brief Specialization of \c size_by_tag_impl for computing the size of the
///  leading dimension of a column-major oriented matrix.
template <>
struct size_by_tag_impl<tag::leading, matrix_tag, column_major_tag>
{
    /**
     * \brief Compute the number of rows of the given matrix.
     * \tparam ExprT A matrix expression type.
     * \pre ExprT must be a model of MatrixExpression.
     */
    template <typename ExprT>
    BOOST_UBLAS_INLINE
    static typename matrix_traits<ExprT>::size_type apply(matrix_expression<ExprT> const& me)
    {
        return me().size1();
    }
};


/// \brief Specialization of \c size_by_tag_impl for computing the size of the
///  given dimension of a unknown oriented expression.
template <typename TagT, typename CategoryT>
struct size_by_tag_impl<TagT, CategoryT, unknown_orientation_tag>: size_by_tag_impl<TagT, CategoryT, row_major_tag>
{
    // Empty
};

}} // Namespace detail::<unnamed>


/**
 * \brief Return the number of columns.
 * \tparam VectorExprT A type which models the vector expression concept.
 * \param ve A vector expression.
 * \return The length of the input vector expression.
 */
template <typename VectorExprT>
BOOST_UBLAS_INLINE
typename ::boost::lazy_enable_if_c<
    detail::has_size_type<VectorExprT>::value,
    detail::vector_size_type<VectorExprT>
>::type size(vector_expression<VectorExprT> const& ve)
{
    return ve().size();
}


/**
 * \brief Return the size of the given dimension for the given vector
 *  expression.
 * \tparam Dim The dimension number (starting from 1).
 * \tparam VectorExprT A vector expression type.
 * \param ve A vector expression.
 * \return The length of the input vector expression.
 */
template <std::size_t Dim, typename VectorExprT>
BOOST_UBLAS_INLINE
typename vector_traits<VectorExprT>::size_type size(vector_expression<VectorExprT> const& ve)
{
    return detail::size_by_dim_impl<Dim, vector_tag>::apply(ve);
}


/**
 * \brief Return the size of the given dimension for the given matrix
 *  expression.
 * \tparam Dim The dimension number (starting from 1).
 * \tparam MatrixExprT A matrix expression type.
 * \param e A matrix expression.
 * \return The size of the input matrix expression associated to the dimension
 *  \a Dim.
 */
template <std::size_t Dim, typename MatrixExprT>
BOOST_UBLAS_INLINE
typename matrix_traits<MatrixExprT>::size_type size(matrix_expression<MatrixExprT> const& me)
{
    return detail::size_by_dim_impl<Dim, matrix_tag>::apply(me);
}


/**
 * \brief Return the size of the given dimension tag for the given matrix
 *  expression.
 * \tparam TagT The dimension tag type (e.g., tag::major).
 * \tparam MatrixExprT A matrix expression type.
 * \param e A matrix expression.
 * \return The size of the input matrix expression associated to the dimension
 *  tag \a TagT.
 */
template <typename TagT, typename MatrixExprT>
BOOST_UBLAS_INLINE
typename ::boost::lazy_enable_if_c<
    detail::has_size_type<MatrixExprT>::value,
    detail::matrix_size_type<MatrixExprT>
>::type size(matrix_expression<MatrixExprT> const& me)
{
    return detail::size_by_tag_impl<TagT, matrix_tag, typename matrix_traits<MatrixExprT>::orientation_category>::apply(me);
}

}}} // Namespace boost::numeric::ublas


#endif // BOOST_NUMERIC_UBLAS_OPERATION_SIZE_HPP

/* size.hpp
uR9r8VHncezH55xN8J12wCb8zjnkHHaOOI3Ym0fh7bU4J5xTzlnmB4SSGnYOC+c78pF8FM/x0fylfAzfH57GIJ7nJV7lTT6Wj+MT+CQ+hU/jJ/CT+Qw+m2/CGreEBCFVyBMWCU9BN34G7XWlOBS6Nhse2mp4Yh9j3ZV5fuNZ69kHi/GNp7fESzJ8gDxY9XPy1Yqj5Cp3KK9rb2rvake0T6Epv9FOac3G5eYNZqV5p9Vgzbd/Z9c4JCOUzEEzS+CNvgDfYwc8vAacm94XvxG/9/SXBkiDUPKL8I0f14/oS42zBjHDzY5mpBllcmaquQwzvMqsMqvNGrMWFn+jucW8zDp/HkR47yucVU6VU+3UwHLXORudLeys5OqyCP5+oVaoEzYKW4Tt5536DgtHhEZ2fr1bXChO9mR4sj15ngJPMfpeAY1T6ZnnGSyPkBfJNfIb8jF5p/dD72mcBDK1Sq2TrmFFTzdWGVuND4zB0GtnzXHWbVhX99lv2pOcOx1SGcrszyL+KD9MyBdWCy/DpnUQF4lvYHwPe/pKEnz8THmOfLuyVNmtNCu3eL/3hmjDteXaQL1AbzGvsIZa6Xad/ZH9KbPnoSSB6cZbxQOezz2dpWslU3pF+rM0XC6QH5FPKJd4v/UOVYuwz19TQ7Uh2rdGmllqLsUJMNe6D6v9JeucdZlNqkKZrb2Gv4mfyT/Hy0KGcKN4u6fas8fztedn0hhph9RJnibPlV+SP1KugDV839ukZmhH9b/oFfD7m3ASn4S5OGYOsH5pVeD8V2eROrevc2AbBaEUHvN3wmU4jW3xhEo5Uk95uLwR56+fex2cwjPge72h3aY/rK/GCft30AljsMsLjVLjJivDysK+oLY2lL0hvwlngrfF9p4hnjjPNMzHPZ6J0KYG+voX5QfvIjUTXuI2aJgP9S5GlpFrjDL7w8Ma7ZCGUPa+72uY5U+FTvIZ5Wv1FliFo7AKydYlzjXYYTtpPY1uu8v5OfyTsJZdZE5OkdNwnp8sZ8jZch5Gtli+XLlGafL+2dtP7a8WqJO1X2kN+iBopFdx5lgBX/8N+xv7aZx2UFBLKPO5wvhEPpm/n1/O3wO7/wj83iz1qgucBw9j9zRqTWhXs9aincAeStXn6Qv0xfoSfZm+AlarSq9GH2v1On2jPsSQz9sfd8KepVkTrMkYt2zY0gKr2Dpu/aRWgh+61g5x3gtokTD0PViH7OL38XliATyWMrECJ4e2J7Yb5IXyPrm7ouKMOArrbLW602wxd8LrHk99uKgwZgO78I+IL4vviSukfbB5PDzVJmUdcmxSI7RkrQxn4z9p9XqoYRjPGQeNNWZna4CtOROgA7fh3BbGzvN3I/+9ngOejzz7pRx5q/yA8okS7V2K1dNJHaimwLq9pMboKma+G84G6YZlHjR/MEdgLM5YJfYmu9x5FjY5jExGWbfxzXwn+EN3Ywe+iH3fUbxG/Fwc4lnp2YPyQ6TRkqFMVf7g5dV4tUJ9Arc059RN2jG9p5FqFBmr0covjcnmqzhtxOI+pItzM7PVYWx9XsbnwGsbI9wivINy68XLPaM8N0v34z5lh3wzvGsLfkma+lvcyLyqdjJ5s948bnrsF3EPFcZ00xL+IX6CMBk7MBvauEAohj9ZAc+tEl7lAmGxsAS+5QphlVAlVAs1P6nFPhBPeX4uxyndcN91GqfIAtxavAUv7G6czf9oRJjXmePMx8xR1m9Qcwo0JT0XhbH7nNv5s3xPoZfn555Y7LB7pQdwRv7Au1C9RxtsTjb3wRrOd3YzXYqHS0Dt+XX8Gfi0p6XvVVIZxn736+XpaB+yFYcsCWP+8WtigWcIToovSG9K9UqFV9Z66TU=
*/