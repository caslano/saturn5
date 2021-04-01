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
kS0EJznCsnNNpO2T3si7iTZLOo16njt+iNzR+ag2yaQBxu85Z9p/gTiryrBB0eMHkLoXad+Y4QxPNBDLoWrtC7W64KxweMr6HkypX6BGSz1Ml/SCOmgITCyyh21GknRSmmwGuXSXYqzb6XSPScTXrZoKhyz7rl2fovJtXNw58n5EsU+ukX8fDBJj5T+lB1TiKRPofCce9SY8UOCzmgpR0fMJCXvEUIz9shwvlbuSmiUyunV/RmxN5b6P9d/V9TLvBas9OsI6dPXkGwBPm6qIa0Db0BoCcn33JEohTRr8FdBDWV+F/Xviwmnee6cv4HCCyS40nTM/isEvE0BBpEL0a32aljSgnbTXFQGXFFCGBn9fxTEohC/8EcX3V9mredb6FxQ4UWl39kchhCMa/E2JiPUTGLCGh5miREHsnHM9K+2FANlBHq/irDLIiZtEbTYqCwWdo++1b2RL44IEXQSEYL+SumcgQi3tfWrpSqhGlDzkfdwQiqCkL7yWE0rxKsJ0Yj5Wg1vHDOoi88fRI6qGOCfxqhZFx0nAh50jyoxeJFDcUcAx0hJqWrSAcw==
*/