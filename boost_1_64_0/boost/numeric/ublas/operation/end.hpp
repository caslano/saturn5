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
y40gp9y9k3P+DPwlWOrr87fBMl/Pb2Pj4E74sz4rEPAOC/J9PX4uKIb+aDsz3f2tZrdvLaQLPH4QEhSevO6XiLykptPrgI98azbYLx1LathstpW+GHRvhmmAb1OSk85GZWMgxud8+W5WKoPu0Hy6qLQc+jOL/JrVG+R/kJGszmDJd9B6wb8lnUbY9yscvrm3XB9HjE3FqaYkB0Po3rTlo/ZhyYR8xGLcSqcXUsuRm+y71iSfsLjcoINPLnL8nkmHZxZM8T2rz4b37VbpMEL+gJBf06UPpT5HOnK+05qmHGft1hDm+mBraCghhwIh36ZndXwYXOowf6m4Z3PvfEbHDcnGcfMX7cbmlCXhFjDePUN+FHp9TtnYWaU4Y6ZRL7W8XWsgrWgEHD8mJhORLjjfbWGJpSklRVNySnEtOCKHzWMKfDhquVa2G1cIHz+7ICc7vmJKTjE1oyipLAf5bqL1/2R0d1rLcNfp95VOZrVLyymZkV+IyfGLiB1+AxbIrJScErpKM/GbwXD4krSEHj8uITGb9A6SpuVRcwwh+fj8vg8tDXS3b0hcfmlmFkIscVJ+VklmySyMeEEpmRBGt2B+ZgE21Ngk3NMlIAUpw3jE5WSV5+bmlPjHYQ8rnx5syosTcfl4IymmktHMoUxgI3AjIaPiU5Pjkzwimx4ygtCfzLE8SQL9xu5URpLSMpzwMXrXUxm9xCZx9BuTXUnScUhw/woHu+PEekT6olnuJSKRSXoOG+Z0d9BLJKx/FFJIxg9PHZecljg6XpB4t3aesLOKIpF7aZ2F1IL0Ibewm98rCL13KCwiZCBhd4w0kkjseyEL3Egys2hKlTAdX4ZpI1rr9/QcMhSpc/LoeQKCdFSJ0qm2mZqfy/RAJhbXrdSpm8nane8f6EBUTuHM/JKiwhl0eIlyXoqiQnqTmV5Gpw0rhMBBys0vRT3+mIBH15+OCBydsjaZ+qEtJWX+K9HL/KH0W8rzsf+ZkPSG1P02jZT51yXJLM4fPKN08K35hYORZzAdw8EFwmBhsDuubePdG9q/laK8LL8AblhQkrYp8GNZ22oufi5+Ln4ufi5+Ln7+uz/Opf/4vwNx8fO//glhiyEaR702cvyBT3oBeadw+Mf4VvxWO1L2H/uXPv53P2VhEvtHUcaSdPw/nqTiWyIZQ5IRTsT/R+A7/bwU/tU5jC/7056QADu+csKB0DZlH4IgBOXhtzCSTwpJLkrLJwUkhyQiNJUUIU0dS8MTCdAYZ+H/uLEhgyEfjjQzSDHJRPpZaE0mQjms7DSSh28xZAxicxA7Fn+SEE4hJcgzDbIpqHcQJHngMqTSyXX4cyv7MwRp3Hyl+FNAw8iXi3jCRqM3CQm0NQ4oRWnoA/KU4f9FyIdP27qRKg8tLIEsG6ECpMxCCBK0HR/U0iGo3PFACfK0licgBYD+T2VhkXQiIWysyljaQpRVEDQKrAZfD0aTOJZnGOmCPGNYa3MBlidQZ+FP5UWt2fjmnhQSCEdC3JGEtJyO5D809mlIX4QypqPsMtb+Dm3LadPrH/e5itjIk4RUuazlw9lMzXL7w+aSXEAWgzI0/FHJYNTKI6RA9lPtHIq2lCGuiLVkCJWwvscElVjKQph51t6ZdE6RkrBRDkEvMKs/Xs349Gc7IY3NeyEb3czgNQP9VBdOLn4ufi5+LvyB8p8H+oznhSbhqNAstAgnhFPCWYGIu8UoT5PnqKfZ0+I54TnlOeshUrjUXu4iH5Gf9i5TV6ir1Cq1Wq1Ra9U6daO6Rd2u1qu71D3qfrVBPaQeVo+ojWq2lqcVaMVamVahbdT36XcZ3cy7zL7WUvtnztvO9477ECG1iqP4e/jvpCT5GqU=
*/