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