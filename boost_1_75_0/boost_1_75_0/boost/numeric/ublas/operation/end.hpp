/**
 * -*- c++ -*-
 *
 * \file end.hpp
 *
 * \brief The \c end operation.
 *
 * Copyright (c) 2009, Marco Guazzone
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * \author Marco Guazzone, marco.guazzone@gmail.com
 */


#ifndef BOOST_NUMERIC_UBLAS_OPERATION_END_HPP
#define BOOST_NUMERIC_UBLAS_OPERATION_END_HPP


#include <boost/numeric/ublas/expression_types.hpp>
#include <boost/numeric/ublas/fwd.hpp>
#include <boost/numeric/ublas/traits/const_iterator_type.hpp>
#include <boost/numeric/ublas/traits/iterator_type.hpp>


namespace boost { namespace numeric { namespace ublas {

    namespace detail {

        /**
         * \brief Auxiliary class for implementing the \c end operation.
         * \tparam CategoryT The expression category type (e.g., vector_tag).
         * \tparam TagT The dimension type tag (e.g., tag::major).
         * \tparam OrientationT The orientation category type (e.g., row_major_tag).
         */
        template <typename CategoryT, typename TagT=void, typename OrientationT=void>
        struct end_impl;


        /// \brief Specialization of \c end_impl for iterating vector expressions.
        template <>
        struct end_impl<vector_tag,void,void>
        {
            /**
             * \brief Return an iterator to the last element of the given vector
             *  expression.
             * \tparam ExprT A model of VectorExpression type.
             * \param e A vector expression.
             * \return An iterator over the given vector expression.
             */
            template <typename ExprT>
            static typename ExprT::iterator apply(ExprT& e)
            {
                return e.end();
            }


            /**
             * \brief Return a const iterator to the last element of the given vector
             *  expression.
             * \tparam ExprT A model of VectorExpression type.
             * \param e A vector expression.
             * \return A const iterator to the first element of the given vector
             *  expression.
             */
            template <typename ExprT>
            static typename ExprT::const_iterator apply(ExprT const& e)
            {
                return e.end();
            }
        };


        /// \brief Specialization of \c end_impl for iterating matrix expressions with a
        ///  row-major orientation over the major dimension.
        template <>
        struct end_impl<matrix_tag,tag::major,row_major_tag>
        {
            /**
             * \brief Return an iterator to the last element of the given row-major
             *  matrix expression over the major dimension.
             * \tparam ExprT A model of MatrixExpression type.
             * \param e A matrix expression.
             * \return An iterator over the major dimension of the given matrix
             *  expression.
             */
            template <typename ExprT>
            static typename ExprT::iterator1 apply(ExprT& e)
            {
                return e.end1();
            }


            /**
             * \brief Return a const iterator to the last element of the given row-major
             *  matrix expression over the major dimension.
             * \tparam ExprT A model of MatrixExpression type.
             * \param e A matrix expression.
             * \return A const iterator over the major dimension of the given matrix
             *  expression.
             */
            template <typename ExprT>
            static typename ExprT::const_iterator1 apply(ExprT const& e)
            {
                return e.end1();
            }
        };


        /// \brief Specialization of \c end_impl for iterating matrix expressions with a
        ///  column-major orientation over the major dimension.
        template <>
        struct end_impl<matrix_tag,tag::major,column_major_tag>
        {
            /**
             * \brief Return an iterator to the last element of the given column-major
             *  matrix expression over the major dimension.
             * \tparam ExprT A model of MatrixExpression type.
             * \param e A matrix expression.
             * \return An iterator over the major dimension of the given matrix
             *  expression.
             */
            template <typename ExprT>
            static typename ExprT::iterator2 apply(ExprT& e)
            {
                return e.end2();
            }


            /**
             * \brief Return a const iterator to the last element of the given
             *  column-major matrix expression over the major dimension.
             * \tparam ExprT A model of MatrixExpression type.
             * \param e A matrix expression.
             * \return A const iterator over the major dimension of the given matrix
             *  expression.
             */
            template <typename ExprT>
            static typename ExprT::const_iterator2 apply(ExprT const& e)
            {
                return e.end2();
            }
        };


        /// \brief Specialization of \c end_impl for iterating matrix expressions with a
        ///  row-major orientation over the minor dimension.
        template <>
        struct end_impl<matrix_tag,tag::minor,row_major_tag>
        {
            /**
             * \brief Return an iterator to the last element of the given row-major
             *  matrix expression over the minor dimension.
             * \tparam ExprT A model of MatrixExpression type.
             * \param e A matrix expression.
             * \return An iterator over the minor dimension of the given matrix
             *  expression.
             */
            template <typename ExprT>
            static typename ExprT::iterator2 apply(ExprT& e)
            {
                return e.end2();
            }


            /**
             * \brief Return a const iterator to the last element of the given
             *  row-minor matrix expression over the major dimension.
             * \tparam ExprT A model of MatrixExpression type.
             * \param e A matrix expression.
             * \return A const iterator over the minor dimension of the given matrix
             *  expression.
             */
            template <typename ExprT>
            static typename ExprT::const_iterator2 apply(ExprT const& e)
            {
                return e.end2();
            }
        };


        /// \brief Specialization of \c end_impl for iterating matrix expressions with a
        ///  column-major orientation over the minor dimension.
        template <>
        struct end_impl<matrix_tag,tag::minor,column_major_tag>
        {
            /**
             * \brief Return an iterator to the last element of the given column-major
             *  matrix expression over the minor dimension.
             * \tparam ExprT A model of MatrixExpression type.
             * \param e A matrix expression.
             * \return An iterator over the minor dimension of the given matrix
             *  expression.
             */
            template <typename ExprT>
            static typename ExprT::iterator1 apply(ExprT& e)
            {
                return e.end1();
            }


            /**
             * \brief Return a const iterator to the last element of the given
             *  column-minor matrix expression over the major dimension.
             * \tparam ExprT A model of MatrixExpression type.
             * \param e A matrix expression.
             * \return A const iterator over the minor dimension of the given matrix
             *  expression.
             */
            template <typename ExprT>
            static typename ExprT::const_iterator1 apply(ExprT const& e)
            {
                return e.end1();
            }
        };

    } // Namespace detail


    /**
     * \brief An iterator to the last element of the given vector expression.
     * \tparam ExprT A model of VectorExpression type.
     * \param e A vector expression.
     * \return An iterator to the last element of the given vector expression.
     */
    template <typename ExprT>
    BOOST_UBLAS_INLINE
    typename ExprT::iterator end(vector_expression<ExprT>& e)
    {
        return detail::end_impl<typename ExprT::type_category>::apply(e());
    }


    /**
     * \brief A const iterator to the last element of the given vector expression.
     * \tparam ExprT A model of VectorExpression type.
     * \param e A vector expression.
     * \return A const iterator to the last element of the given vector expression.
     */
    template <typename ExprT>
    BOOST_UBLAS_INLINE
    typename ExprT::const_iterator end(vector_expression<ExprT> const& e)
    {
        return detail::end_impl<typename ExprT::type_category>::apply(e());
    }


    /**
     * \brief An iterator to the last element of the given matrix expression
     *  according to its orientation.
     * \tparam DimTagT A dimension tag type (e.g., tag::major).
     * \tparam ExprT A model of MatrixExpression type.
     * \param e A matrix expression.
     * \return An iterator to the last element of the given matrix expression
     *  according to its orientation.
     */
    template <typename TagT, typename ExprT>
    BOOST_UBLAS_INLINE
    typename iterator_type<ExprT,TagT>::type end(matrix_expression<ExprT>& e)
    {
        return detail::end_impl<typename ExprT::type_category, TagT, typename ExprT::orientation_category>::apply(e());
    }


    /**
     * \brief A const iterator to the last element of the given matrix expression
     *  according to its orientation.
     * \tparam TagT A dimension tag type (e.g., tag::major).
     * \tparam ExprT A model of MatrixExpression type.
     * \param e A matrix expression.
     * \return A const iterator to the last element of the given matrix expression
     *  according to its orientation.
     */
    template <typename TagT, typename ExprT>
    BOOST_UBLAS_INLINE
    typename const_iterator_type<ExprT,TagT>::type end(matrix_expression<ExprT> const& e)
    {
        return detail::end_impl<typename ExprT::type_category, TagT, typename ExprT::orientation_category>::apply(e());
    }


    /**
     * \brief An iterator to the last element over the dual dimension of the given
     *  iterator.
     * \tparam IteratorT A model of Iterator type.
     * \param it An iterator.
     * \return An iterator to the last element over the dual dimension of the given
     *  iterator.
     */
    template <typename IteratorT>
    BOOST_UBLAS_INLINE
    typename IteratorT::dual_iterator_type end(IteratorT& it)
    {
        return it.end();
    }


    /**
     * \brief A const iterator to the last element over the dual dimension of the
     *  given iterator.
     * \tparam IteratorT A model of Iterator type.
     * \param it An iterator.
     * \return A const iterator to the last element over the dual dimension of the
     *  given iterator.
     */
    template <typename IteratorT>
    BOOST_UBLAS_INLINE
    typename IteratorT::dual_iterator_type end(IteratorT const& it)
    {
        return it.end();
    }

}}} // Namespace boost::numeric::ublas


#endif // BOOST_NUMERIC_UBLAS_OPERATION_END_HPP

/* end.hpp
I6pG+ZJwc+u/ADNPk+uwnRMjIuXH4BfjQjlczC+1Gzj/fh2ianUtTEdOD8xScaq+7iyZafTU9sWY7T3xES2caj5rxSx2ZpY4WPS27QG6ZxDae0S4o+rI9q8p1m/CzPtmzb4cfl1hbN2y5E4XsgNfazhT0SVvEQ6WOWJ+l3xmS/mXlTANlhwVq7laziwdmMIu+9zTqVDP/bMO65XFUjmiD/7OGZmxQgqWj7De9ntVkF4aINUsIel9fM77o8DNrCSkM4FqWKLKrGxXvJzkZma5PTll5smVIDZh/a/+Ujkz7Vnq+neuZZDg05sjgg/+vIDGJ3E4GcOvWX1mHeOS/iH4WebuYjETrnmY/6Eu23qV7mjIA7xFxgMMc3LP76pXWccaX/3a5l1ntlNlcg+z48ixQrW6vTpeGXHv+I9Z08rIha98sFPdjlr2R2rPBHcgrulMng69G/MCHO+Mn66pXar/T2ekqqWRqf6R0N/iBKYp65GLIuhmS8Kd90Evv0OXBAjNRYQ7oLFm2Q3zqnOanKC3MtQ3d5IxDjG+UfVMV++99Dvp0rVy6g7lRrM3z6eAM+E6KGsSPmwIW9n7ktZ8N8LZ+UG3NpeDT7M2lzhrPZetYOtnZppJEC8la13kC+G0kdcR4dpXc9ss5O+PZk/Fpwb/cChQm9MX2ZPTxrH7nKlxSjQaM1pb0ZPKYZraUvkXapARuBbfsRBEE4Kd8nL8
*/