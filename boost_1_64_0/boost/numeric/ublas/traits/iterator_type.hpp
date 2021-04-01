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
m3qDgu13H7z6wFKIBAFwxf8EhF+AGL21vg3W6EXeNIQymAgu0TJDLj0sCSL/tL+tmHLiAVOr4ZzzBm2Hjl1x5vrWV2y/+fhvRrbtHfNOcl/SFDZwEzjGFmHB+C9w/woV2wAS7+FhqJtp1EHxJB2C25xqJjJk04/yzzBjd81Nt2sXdRpm0DpAG3zAzf8skFmPccWoMUjBtfH3fk3m6/88pfa3kEKbHbWLyIo5FbWnQeROTUGK2Ay/AHS9293p2xSoAtB/UZUwD7NALfW7totLooxu8etyIlhlfKrE7p+AtyTkeLXI8F1+BkBklaj3+yx8dlygEHUyWYToYDnSSgz3pjabf7Mf3aLVVFrKDhzkKY2eOG+GbMPnwhqwqmzMXWjeG9lpdosxgO1rTHxuwEyL2qzgpYeX7brYHbEikhwQ75BuhzkvUN3RvV9OFBTcKOIDykrOJkOMnmBZWQYdvQnkpriZ7gbqiub7OBi51ai9KxvCPSefarRW8UaV+t0ihlhnjHhmsr7KCoGtaZE/ijHY1JG0WCe/5IK+mw6PfHpKHK0bq2OtN+GzfY0myw==
*/