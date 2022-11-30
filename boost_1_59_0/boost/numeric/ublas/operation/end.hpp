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
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
*/