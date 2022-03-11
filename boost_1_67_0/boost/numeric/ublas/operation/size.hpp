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