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
XuC+iUt+2WFEYspY35NTgVbnzJgyo5icDB0+ZnRK69ugWejKdPIdk7pPv2X7ZL8LroGJ3Fa/HSQPrnV9mxYF5/ncjXObTqKD+83WS99gCdqVg3XeM1jGZqlHkIQtWDSYkBAmjcvPxdocV4xxxryfbdcqG5FfmFnAUnZvm5/8EJRubH5uIUtLNrftCduvERGpQ5Pj0rNmYRMQYvrLYvu1ny8U3OdzQWUnQqfQJpxp2y6yKWJswlAhnSYgm93vaSV4fw9PnmBNb6MSUZTc+JdZSFbc0Cu+UHD6V6nMo/rSv05DsiC6oT2+UHD6RzuMjpNZNPQM+94a6fWvHLbt3BlYGljzECJhDvmWrZzWmTweCLs5HvBpHyw/cih4XPFcnn/pcP7RC4z1z4IkQeaAfBW0jvxj+kpwqYF27Goj9a+q2A6QY7PJZBz7hgfoBEKePW+3FxW7bS/xj0BpWQl9c7OetSplVPzE1jeYsvLL0K4dwTF4EywuASfggMxt0f5A2G8uKgMSt760QLi1H+N+JKPPYo06X8pyJwRkreN4W6ssOwdv/eT4rNuctnI2yOx1YTK7bRxZ1irBrOGZLl8pD7SVk9vD44enX586ZlwKM1AYIxTNnkaqpTFISeU81eoYz/JI9rxj8tDR8T69/2AXJmGBPe53VDSvQ2JymkekX0lM10mBwOLO4wLff8HkikS/9+86aVwgQCYQ+lpR+pjhafFpeEoyNTH5eiYvDZrdQjq95B03JYz3DF97fhckwWs85N2gMF7jIbMC6yYuMdVnCyvOk+XAlmwIXl2leflTUfszbVYc9Od5qejozcA6LC+cQq7wtzQtITV+aFw60zFsdVx+oRjW9Gv8MZllRTPyp7DHZMf4Zbns/S53MRVmYw9d2aackvLC9KLCKRiBpb79y15uIvMCbUxKcFtwZ7CE1Xx3sCQfOqKkjCwMkjEHIz8H62raeVbeVSmEeLoEPfrJ6vhFkMS31oMk/t3UKVgW2D+fRbaRsvwd26ZlC/rnbaWlQY89ZhFyWXA8e2qZ9q1321zBz9yRs23qx9j7XSpy9AJxvO8t0q8vECf44qKDamyrIT+/QD7/27o92uYLerAPN8AXiPW99kvy3Ljx8amJIyampwxNHTqaKTpCii4cw54E9j1QR6ZeIM2Mopk5rQ/6nmEpAmOdU+IbI/87aqVBmoJu1VWXYPelUxkhL7G86Gfg7WpX45xicv/quJOF3AH0yxb7ZHCLSHFrDUwwJyicl0l99NM/aiMh7TulYPW6bx3mF7kNej7QntZ3lv2z87DrVeO5zPSCzFL/QljbxkslpDpYwnTT88GS0iJUnhrk2bna/uMOY4aNTC/MzxZLsY/+wiwxawfzUU75w77xOe2GZxfkZxEvs4U5hVNcB5moCLOkPnczaxbLQrSAPJv5MH75lFZLkFlaKLgnGcwd5r5NDFuO7GXW0+HxydcnJsf7Hh4lr4TF+TTIH1k/SgtFdIWQL2E5fJYE6cqY8AUq81lWeGTBhoas9cexsoTgVc3eMYWOzHQfevy2Y/DswWizbVJKeoQNH5M8Ih2h0hz3dc1b6LwxZXz+unyQyVmxrgRz3NwVSVjlfhn6i7WyKjCD6C8GtmRWcVkRWRKQwnGtyEe6N2jv2cJjSpsM9XssPl9lvN9vgV9IyI3+EDxB2Dp/CD4gIRP9IXh9+FtfLJSdUwpdNoUMDIRysnM8TERGMlnJFIkk+b+l583InEIrx9mFyfKzczLd1CN8aUQWjAuEJN6NP8xmPhM1CKLKRB+cL5kyg3x8niQXkj+1SjS35G8CEnSRSU6eL0Gus8ESVs57bWtnPXGH8ERw6jZx7/9UPjbA3/5UThY=
*/