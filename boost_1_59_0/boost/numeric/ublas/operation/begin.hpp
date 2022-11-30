/**
 * -*- c++ -*-
 *
 * \file begin.hpp
 *
 * \brief The \c begin operation.
 *
 * Copyright (c) 2009, Marco Guazzone
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * \author Marco Guazzone, marco.guazzone@gmail.com
 */

#ifndef BOOST_NUMERIC_UBLAS_OPERATION_BEGIN_HPP
#define BOOST_NUMERIC_UBLAS_OPERATION_BEGIN_HPP


#include <boost/numeric/ublas/expression_types.hpp>
#include <boost/numeric/ublas/fwd.hpp>
#include <boost/numeric/ublas/traits/const_iterator_type.hpp>
#include <boost/numeric/ublas/traits/iterator_type.hpp>


namespace boost { namespace numeric { namespace ublas {

    namespace detail {

		    /**
				 * \brief Auxiliary class for implementing the \c begin operation.
				 * \tparam CategoryT The expression category type (e.g., vector_tag).
				 * \tparam TagT The dimension type tag (e.g., tag::major).
				 * \tparam OrientationT The orientation category type (e.g., row_major_tag).
				 */
		    template <typename CategoryT, typename TagT=void, typename OrientationT=void>
		    struct begin_impl;


				/// \brief Specialization of \c begin_impl for iterating vector expressions.
				template <>
				struct begin_impl<vector_tag,void,void>
				{
					  /**
						 * \brief Return an iterator to the first element of the given vector
						 *  expression.
						 * \tparam ExprT A model of VectorExpression type.
						 * \param e A vector expression.
						 * \return An iterator over the given vector expression.
						 */
					  template <typename ExprT>
					  static typename ExprT::iterator apply(ExprT& e)
						{
							  return e.begin();
						}


						/**
						 * \brief Return a const iterator to the first element of the given vector
						 *  expression.
						 * \tparam ExprT A model of VectorExpression type.
						 * \param e A vector expression.
						 * \return A const iterator to the first element of the given vector
						 *  expression.
						 */
						template <typename ExprT>
						static typename ExprT::const_iterator apply(ExprT const& e)
						{
							  return e.begin();
						}
				};


				/// \brief Specialization of \c begin_impl for iterating matrix expressions with
				///  a row-major orientation over the major dimension.
				template <>
				struct begin_impl<matrix_tag,tag::major,row_major_tag>
				{
					  /**
						 * \brief Return an iterator to the first element of the given row-major
						 *  matrix expression over the major dimension.
						 * \tparam ExprT A model of MatrixExpression type.
						 * \param e A matrix expression.
						 * \return An iterator over the major dimension of the given matrix
						 *  expression.
						 */
					  template <typename ExprT>
					  static typename ExprT::iterator1 apply(ExprT& e)
						{
							  return e.begin1();
						}


						/**
						 * \brief Return a const iterator to the first element of the given
						 *  row-major matrix expression over the major dimension.
						 * \tparam ExprT A model of MatrixExpression type.
						 * \param e A matrix expression.
						 * \return A const iterator over the major dimension of the given matrix
						 *  expression.
						 */
						template <typename ExprT>
						static typename ExprT::const_iterator1 apply(ExprT const& e)
						{
							  return e.begin1();
						}
				};


				/// \brief Specialization of \c begin_impl for iterating matrix expressions with
				///  a column-major orientation over the major dimension.
				template <>
				struct begin_impl<matrix_tag,tag::major,column_major_tag>
				{
					  /**
						 * \brief Return an iterator to the first element of the given column-major
						 *  matrix expression over the major dimension.
						 * \tparam ExprT A model of MatrixExpression type.
						 * \param e A matrix expression.
						 * \return An iterator over the major dimension of the given matrix
						 *  expression.
						 */
					  template <typename ExprT>
					  static typename ExprT::iterator2 apply(ExprT& e)
						{
							  return e.begin2();
						}


						/**
						 * \brief Return a const iterator to the first element of the given
						 *  column-major matrix expression over the major dimension.
						 * \tparam ExprT A model of MatrixExpression type.
						 * \param e A matrix expression.
						 * \return A const iterator over the major dimension of the given matrix
						 *  expression.
						 */
						template <typename ExprT>
						static typename ExprT::const_iterator2 apply(ExprT const& e)
						{
							  return e.begin2();
						}
				};


				/// \brief Specialization of \c begin_impl for iterating matrix expressions with
				///  a row-major orientation over the minor dimension.
				template <>
				struct begin_impl<matrix_tag,tag::minor,row_major_tag>
				{
					  /**
						 * \brief Return an iterator to the first element of the given row-major
						 *  matrix expression over the minor dimension.
						 * \tparam ExprT A model of MatrixExpression type.
						 * \param e A matrix expression.
						 * \return An iterator over the minor dimension of the given matrix
						 *  expression.
						 */
					  template <typename ExprT>
					  static typename ExprT::iterator2 apply(ExprT& e)
						{
							  return e.begin2();
						}


						/**
						 * \brief Return a const iterator to the first element of the given
						 *  row-major matrix expression over the minor dimension.
						 * \tparam ExprT A model of MatrixExpression type.
						 * \param e A matrix expression.
						 * \return A const iterator over the minor dimension of the given matrix
						 *  expression.
						 */
						template <typename ExprT>
						static typename ExprT::const_iterator2 apply(ExprT const& e)
						{
							  return e.begin2();
						}
				};



				/// \brief Specialization of \c begin_impl for iterating matrix expressions with
				///  a column-major orientation over the minor dimension.
				template <>
				struct begin_impl<matrix_tag,tag::minor,column_major_tag>
				{
					  /**
						 * \brief Return an iterator to the first element of the given column-major
						 *  matrix expression over the minor dimension.
						 * \tparam ExprT A model of MatrixExpression type.
						 * \param e A matrix expression.
						 * \return An iterator over the minor dimension of the given matrix
						 *  expression.
						 */
					  template <typename ExprT>
					  static typename ExprT::iterator1 apply(ExprT& e)
						{
							  return e.begin1();
						}


						/**
						 * \brief Return a const iterator to the first element of the given
						 *  column-major matrix expression over the minor dimension.
						 * \tparam ExprT A model of MatrixExpression type.
						 * \param e A matrix expression.
						 * \return A const iterator over the minor dimension of the given matrix
						 *  expression.
						 */
						template <typename ExprT>
						static typename ExprT::const_iterator1 apply(ExprT const& e)
						{
							  return e.begin1();
						}
				};

		} // Namespace detail


		/**
		 * \brief An iterator to the first element of the given vector expression.
		 * \tparam ExprT A model of VectorExpression type.
		 * \param e A vector expression.
		 * \return An iterator to the first element of the given vector expression.
		 */
		template <typename ExprT>
		BOOST_UBLAS_INLINE
		typename ExprT::iterator begin(vector_expression<ExprT>& e)
		{
			  return detail::begin_impl<typename ExprT::type_category>::apply(e());
		}


		/**
		 * \brief A const iterator to the first element of the given vector expression.
		 * \tparam ExprT A model of VectorExpression type.
		 * \param e A vector expression.
		 * \return A const iterator to the first element of the given vector expression.
		 */
		template <typename ExprT>
		BOOST_UBLAS_INLINE
		typename ExprT::const_iterator begin(vector_expression<ExprT> const& e)
		{
			  return detail::begin_impl<typename ExprT::type_category>::apply(e());
		}


		/**
		 * \brief An iterator to the first element of the given matrix expression
		 *  according to its orientation.
		 * \tparam DimTagT A dimension tag type (e.g., tag::major).
		 * \tparam ExprT A model of MatrixExpression type.
		 * \param e A matrix expression.
		 * \return An iterator to the first element of the given matrix expression
		 *  according to its orientation.
		 */
		template <typename TagT, typename ExprT>
		BOOST_UBLAS_INLINE
		typename iterator_type<ExprT,TagT>::type begin(matrix_expression<ExprT>& e)
		{
			  return detail::begin_impl<typename ExprT::type_category, TagT, typename ExprT::orientation_category>::apply(e());
		}


		/**
		 * \brief A const iterator to the first element of the given matrix expression
		 *  according to its orientation.
		 * \tparam TagT A dimension tag type (e.g., tag::major).
		 * \tparam ExprT A model of MatrixExpression type.
		 * \param e A matrix expression.
		 * \return A const iterator to the first element of the given matrix expression
		 *  according to its orientation.
		 */
		template <typename TagT, typename ExprT>
		BOOST_UBLAS_INLINE
		typename const_iterator_type<ExprT,TagT>::type begin(matrix_expression<ExprT> const& e)
		{
			  return detail::begin_impl<typename ExprT::type_category, TagT, typename ExprT::orientation_category>::apply(e());
		}


		/**
		 * \brief An iterator to the first element over the dual dimension of the given
		 *  iterator.
		 * \tparam IteratorT A model of Iterator type.
		 * \param it An iterator.
		 * \return An iterator to the first element over the dual dimension of the given
		 *  iterator.
		 */
		template <typename IteratorT>
		BOOST_UBLAS_INLINE
		typename IteratorT::dual_iterator_type begin(IteratorT& it)
		{
			  return it.begin();
		}


		/**
		 * \brief A const iterator to the first element over the dual dimension of the
		 *  given iterator.
		 * \tparam IteratorT A model of Iterator type.
		 * \param it An iterator.
		 * \return A const iterator to the first element over the dual dimension of the
		 *  given iterator.
		 */
		template <typename IteratorT>
		BOOST_UBLAS_INLINE
		typename IteratorT::dual_iterator_type begin(IteratorT const& it)
		{
			  return it.begin();
		}

}}} // Namespace boost::numeric::ublas


#endif // BOOST_NUMERIC_UBLAS_OPERATION_BEGIN_HPP

/* begin.hpp
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
*/