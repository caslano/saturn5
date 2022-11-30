/**
 * -*- c++ -*-
 *
 * \file const_iterator_type.hpp
 *
 * \brief Const iterator to a given container type.
 *
 * Copyright (c) 2009, Marco Guazzone
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * \author Marco Guazzone, marco.guazzone@gmail.com
 */


#ifndef BOOST_NUMERIC_UBLAS_TRAITS_CONST_ITERATOR_TYPE_HPP
#define BOOST_NUMERIC_UBLAS_TRAITS_CONST_ITERATOR_TYPE_HPP


#include <boost/numeric/ublas/fwd.hpp>
#include <boost/numeric/ublas/tags.hpp>
#include <boost/numeric/ublas/traits.hpp>


namespace boost { namespace numeric { namespace ublas {

    namespace detail {

        /**
         * \brief Auxiliary class for retrieving the const iterator to the given
         *  matrix expression according its orientation and to the given dimension tag.
         * \tparam MatrixT A model of MatrixExpression.
         * \tparam TagT A dimension tag type (e.g., tag::major).
         * \tparam OrientationT An orientation category type (e.g., row_major_tag).
         */
        template <typename MatrixT, typename TagT, typename OrientationT>
        struct const_iterator_type_impl;


        /// \brief Specialization of \c const_iterator_type_impl for row-major oriented
        ///  matrices and over the major dimension.
        template <typename MatrixT>
        struct const_iterator_type_impl<MatrixT,tag::major,row_major_tag>
        {
            typedef typename matrix_view_traits<MatrixT>::const_iterator1 type;
        };


        /// \brief Specialization of \c const_iterator_type_impl for column-major
        ///  oriented matrices and over the major dimension.
        template <typename MatrixT>
        struct const_iterator_type_impl<MatrixT,tag::major,column_major_tag>
        {
            typedef typename matrix_view_traits<MatrixT>::const_iterator2 type;
        };


        /// \brief Specialization of \c const_iterator_type_impl for row-major oriented
        ///  matrices and over the minor dimension.
        template <typename MatrixT>
        struct const_iterator_type_impl<MatrixT,tag::minor,row_major_tag>
        {
            typedef typename matrix_view_traits<MatrixT>::const_iterator2 type;
        };


        /// \brief Specialization of \c const_iterator_type_impl for column-major
        ///  oriented matrices and over the minor dimension.
        template <typename MatrixT>
        struct const_iterator_type_impl<MatrixT,tag::minor,column_major_tag>
        {
            typedef typename matrix_view_traits<MatrixT>::const_iterator1 type;
        };

    } // Namespace detail


    /**
     * \brief A const iterator for the given container type over the given
     *  dimension.
     * \tparam ContainerT A container expression type.
     * \tparam TagT A dimension tag type (e.g., tag::major).
     */
    template <typename ContainerT, typename TagT=void>
    struct const_iterator_type;


    /**
     * \brief Specialization of \c const_iterator_type for vector expressions.
     * \tparam VectorT A model of VectorExpression type.
     */
    template <typename VectorT>
    struct const_iterator_type<VectorT, void>
    {
        typedef typename vector_view_traits<VectorT>::const_iterator type;
    };


    /**
     * \brief Specialization of \c const_iterator_type for matrix expressions and
     *  over the major dimension.
     * \tparam MatrixT A model of MatrixExpression type.
     */
    template <typename MatrixT>
    struct const_iterator_type<MatrixT,tag::major>
    {
        typedef typename detail::const_iterator_type_impl<MatrixT,tag::minor,typename matrix_view_traits<MatrixT>::orientation_category>::type type;
    };


    /**
     * \brief Specialization of \c const_iterator_type for matrix expressions and
     *  over the minor dimension.
     * \tparam MatrixT A model of MatrixExpression type.
     */
    template <typename MatrixT>
    struct const_iterator_type<MatrixT,tag::minor>
    {
        typedef typename detail::const_iterator_type_impl<MatrixT,tag::minor,typename matrix_view_traits<MatrixT>::orientation_category>::type type;
    };

}}} // Namespace boost::numeric::ublas


#endif // BOOST_NUMERIC_UBLAS_TRAITS_CONST_ITERATOR_TYPE_HPP

/* const_iterator_type.hpp
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
*/