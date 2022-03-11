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