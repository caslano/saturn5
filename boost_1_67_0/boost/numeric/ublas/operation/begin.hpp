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