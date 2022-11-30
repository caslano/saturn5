/**
 * -*- c++ -*-
 *
 * \file iterator_type.hpp
 *
 * \brief Iterator to a given container type.
 *
 * Copyright (c) 2009, Marco Guazzone
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * \author Marco Guazzone, marco.guazzone@gmail.com
 */


#ifndef BOOST_NUMERIC_UBLAS_TRAITS_ITERATOR_TYPE_HPP
#define BOOST_NUMERIC_UBLAS_TRAITS_ITERATOR_TYPE_HPP


#include <boost/numeric/ublas/fwd.hpp>
#include <boost/numeric/ublas/traits.hpp>
#include <boost/numeric/ublas/tags.hpp>


namespace boost { namespace numeric { namespace ublas {

    namespace detail {

        /**
         * \brief Auxiliary class for retrieving the iterator to the given
         *  matrix expression according its orientation and to the given dimension tag.
         * \tparam MatrixT A model of MatrixExpression.
         * \tparam TagT A dimension tag type (e.g., tag::major).
         * \tparam OrientationT An orientation category type (e.g., row_major_tag).
         */
        template <typename MatrixT, typename TagT, typename OrientationT>
        struct iterator_type_impl;


        /// \brief Specialization of \c iterator_type_impl for row-major oriented
        ///  matrices and over the major dimension.
        template <typename MatrixT>
        struct iterator_type_impl<MatrixT,tag::major,row_major_tag>
        {
            typedef typename matrix_traits<MatrixT>::iterator1 type;
        };


        /// \brief Specialization of \c iterator_type_impl for column-major oriented
        ///  matrices and over the major dimension.
        template <typename MatrixT>
        struct iterator_type_impl<MatrixT,tag::major,column_major_tag>
        {
            typedef typename matrix_traits<MatrixT>::iterator2 type;
        };


        /// \brief Specialization of \c iterator_type_impl for row-major oriented
        ///  matrices and over the minor dimension.
        template <typename MatrixT>
        struct iterator_type_impl<MatrixT,tag::minor,row_major_tag>
        {
            typedef typename matrix_traits<MatrixT>::iterator2 type;
        };


        /// \brief Specialization of \c iterator_type_impl for column-major oriented
        ///  matrices and over the minor dimension.
        template <typename MatrixT>
        struct iterator_type_impl<MatrixT,tag::minor,column_major_tag>
        {
            typedef typename matrix_traits<MatrixT>::iterator1 type;
        };

    } // Namespace detail


    /**
     * \brief A iterator for the given container type over the given dimension.
     * \tparam ContainerT A container expression type.
     * \tparam TagT A dimension tag type (e.g., tag::major).
     */
    template <typename ContainerT, typename TagT=void>
    struct iterator_type;


    /**
     * \brief Specialization of \c iterator_type for vector expressions.
     * \tparam VectorT A model of VectorExpression type.
     */
    template <typename VectorT>
    struct iterator_type<VectorT, void>
    {
        typedef typename vector_traits<VectorT>::iterator type;
    };


    /**
     * \brief Specialization of \c iterator_type for matrix expressions and
     *  over the major dimension.
     * \tparam MatrixT A model of MatrixExpression type.
     */
    template <typename MatrixT>
    struct iterator_type<MatrixT,tag::major>
    {
        typedef typename detail::iterator_type_impl<MatrixT,tag::major,typename matrix_traits<MatrixT>::orientation_category>::type type;
    };


    /**
     * \brief Specialization of \c iterator_type for matrix expressions and
     *  over the minor dimension.
     * \tparam MatrixT A model of MatrixExpression type.
     */
    template <typename MatrixT>
    struct iterator_type<MatrixT,tag::minor>
    {
        typedef typename detail::iterator_type_impl<MatrixT,tag::minor,typename matrix_traits<MatrixT>::orientation_category>::type type;
    };

}}} // Namespace boost::numeric::ublas


#endif // BOOST_NUMERIC_UBLAS_TRAITS_ITERATOR_TYPE_HPP

/* iterator_type.hpp
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
*/