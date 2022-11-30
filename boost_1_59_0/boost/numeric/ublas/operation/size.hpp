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
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
*/