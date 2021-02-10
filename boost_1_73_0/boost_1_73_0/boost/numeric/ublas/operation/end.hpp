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
y2uI4FPn4DtDs9U3BSVRGWj2ZjCYNWHBjDARvB3MX4+v5vC2N532RvN3ML6A3ugdCXszGJ1j6AWCaeCfSs0NgmsQq7IQPA2Y3+/pNB4ImRRVyqFpucFQNRs7Wyu+SvmiWrptY5kVCTpdGgtJzrSLAC1KZewfH1780wBoKsmbEX3YtQofueZhjwLD0HuSFVAouUQjE83KU8hUpR3J6Go4bHzpNghOV9gR3mphufMxiRcSoVUlMSpdRxaUov1SqyX5K05YUSxY8rF1rUQKRwl6TtoSE0lVlK9pYZVlxc5aqjVh3/ME0uor1opY2w3SbE8Rfh0HUngBj590v3mOrJtTp2o7aNqFzhFcja5m/XPACNWnQe87T1HeV2d4iGtLxUqeSHnJZSrkktLSihV+he4Aa1EUkDCsRt8Bal9icciE2gBK8R5aYl8iB1PbwFTPMq5RZ5DVChuZqxOx4mYfKxE6qVboAZlwzP8196KULG4wDZZUWghcCImMwleal2dcv9miZDqUMLlQqMp4QUJeq4/ce0NkrdZeAH54AS30ejus8Tb47LlaO3HYElFA25hrjuZiMOzD0UopDFSm0KJWIRZUJzHTy6cRJvSi2e46UsRFurbLUnqyUqNAt4l0k9qfdW7WPlxjqcPVEB5ir6hc
*/