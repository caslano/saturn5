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