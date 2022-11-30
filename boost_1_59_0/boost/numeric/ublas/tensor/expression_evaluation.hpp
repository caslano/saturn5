//
//  Copyright (c) 2018-2019, Cem Bassoy, cem.bassoy@gmail.com
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  Fraunhofer IOSB, Ettlingen, Germany
//

#ifndef _BOOST_UBLAS_TENSOR_EXPRESSIONS_EVALUATION_HPP_
#define _BOOST_UBLAS_TENSOR_EXPRESSIONS_EVALUATION_HPP_

#include <type_traits>
#include <stdexcept>


namespace boost::numeric::ublas {

template<class element_type, class storage_format, class storage_type>
class tensor;

template<class size_type>
class basic_extents;

}

namespace boost::numeric::ublas::detail {

template<class T, class D>
struct tensor_expression;

template<class T, class EL, class ER, class OP>
struct binary_tensor_expression;

template<class T, class E, class OP>
struct unary_tensor_expression;

}

namespace boost::numeric::ublas::detail {

template<class T, class E>
struct has_tensor_types
{ static constexpr bool value = false; };

template<class T>
struct has_tensor_types<T,T>
{ static constexpr bool value = true; };

template<class T, class D>
struct has_tensor_types<T, tensor_expression<T,D>>
{ static constexpr bool value = std::is_same<T,D>::value || has_tensor_types<T,D>::value; };


template<class T, class EL, class ER, class OP>
struct has_tensor_types<T, binary_tensor_expression<T,EL,ER,OP>>
{ static constexpr bool value = std::is_same<T,EL>::value || std::is_same<T,ER>::value || has_tensor_types<T,EL>::value || has_tensor_types<T,ER>::value;  };

template<class T, class E, class OP>
struct has_tensor_types<T, unary_tensor_expression<T,E,OP>>
{ static constexpr bool value = std::is_same<T,E>::value || has_tensor_types<T,E>::value; };

} // namespace boost::numeric::ublas::detail


namespace boost::numeric::ublas::detail {





/** @brief Retrieves extents of the tensor
 *
*/
template<class T, class F, class A>
auto retrieve_extents(tensor<T,F,A> const& t)
{
	return t.extents();
}

/** @brief Retrieves extents of the tensor expression
 *
 * @note tensor expression must be a binary tree with at least one tensor type
 *
 * @returns extents of the child expression if it is a tensor or extents of one child of its child.
*/
template<class T, class D>
auto retrieve_extents(tensor_expression<T,D> const& expr)
{
	static_assert(detail::has_tensor_types<T,tensor_expression<T,D>>::value,
	              "Error in boost::numeric::ublas::detail::retrieve_extents: Expression to evaluate should contain tensors.");

	auto const& cast_expr = static_cast<D const&>(expr);

	if constexpr ( std::is_same<T,D>::value )
	    return cast_expr.extents();
	else
	return retrieve_extents(cast_expr);
}

/** @brief Retrieves extents of the binary tensor expression
 *
 * @note tensor expression must be a binary tree with at least one tensor type
 *
 * @returns extents of the (left and if necessary then right) child expression if it is a tensor or extents of a child of its (left and if necessary then right) child.
*/
template<class T, class EL, class ER, class OP>
auto retrieve_extents(binary_tensor_expression<T,EL,ER,OP> const& expr)
{
	static_assert(detail::has_tensor_types<T,binary_tensor_expression<T,EL,ER,OP>>::value,
	              "Error in boost::numeric::ublas::detail::retrieve_extents: Expression to evaluate should contain tensors.");

	if constexpr ( std::is_same<T,EL>::value )
	    return expr.el.extents();

	if constexpr ( std::is_same<T,ER>::value )
	    return expr.er.extents();

	else if constexpr ( detail::has_tensor_types<T,EL>::value )
	    return retrieve_extents(expr.el);

	else if constexpr ( detail::has_tensor_types<T,ER>::value  )
	    return retrieve_extents(expr.er);
}

/** @brief Retrieves extents of the binary tensor expression
 *
 * @note tensor expression must be a binary tree with at least one tensor type
 *
 * @returns extents of the child expression if it is a tensor or extents of a child of its child.
*/
template<class T, class E, class OP>
auto retrieve_extents(unary_tensor_expression<T,E,OP> const& expr)
{

	static_assert(detail::has_tensor_types<T,unary_tensor_expression<T,E,OP>>::value,
	              "Error in boost::numeric::ublas::detail::retrieve_extents: Expression to evaluate should contain tensors.");

	if constexpr ( std::is_same<T,E>::value )
	    return expr.e.extents();

	else if constexpr ( detail::has_tensor_types<T,E>::value  )
	    return retrieve_extents(expr.e);
}

} // namespace boost::numeric::ublas::detail


///////////////

namespace boost::numeric::ublas::detail {

template<class T, class F, class A, class S>
auto all_extents_equal(tensor<T,F,A> const& t, basic_extents<S> const& extents)
{
	return extents == t.extents();
}

template<class T, class D, class S>
auto all_extents_equal(tensor_expression<T,D> const& expr, basic_extents<S> const& extents)
{
	static_assert(detail::has_tensor_types<T,tensor_expression<T,D>>::value,
	              "Error in boost::numeric::ublas::detail::all_extents_equal: Expression to evaluate should contain tensors.");
	auto const& cast_expr = static_cast<D const&>(expr);


	if constexpr ( std::is_same<T,D>::value )
	    if( extents != cast_expr.extents() )
	    return false;

	if constexpr ( detail::has_tensor_types<T,D>::value )
	    if ( !all_extents_equal(cast_expr, extents))
	    return false;

	return true;

}

template<class T, class EL, class ER, class OP, class S>
auto all_extents_equal(binary_tensor_expression<T,EL,ER,OP> const& expr, basic_extents<S> const& extents)
{
	static_assert(detail::has_tensor_types<T,binary_tensor_expression<T,EL,ER,OP>>::value,
	              "Error in boost::numeric::ublas::detail::all_extents_equal: Expression to evaluate should contain tensors.");

	if constexpr ( std::is_same<T,EL>::value )
	    if(extents !=  expr.el.extents())
	    return false;

	if constexpr ( std::is_same<T,ER>::value )
	    if(extents != expr.er.extents())
	    return false;

	if constexpr ( detail::has_tensor_types<T,EL>::value )
	    if(!all_extents_equal(expr.el, extents))
	    return false;

	if constexpr ( detail::has_tensor_types<T,ER>::value )
	    if(!all_extents_equal(expr.er, extents))
	    return false;

	return true;
}


template<class T, class E, class OP, class S>
auto all_extents_equal(unary_tensor_expression<T,E,OP> const& expr, basic_extents<S> const& extents)
{

	static_assert(detail::has_tensor_types<T,unary_tensor_expression<T,E,OP>>::value,
	              "Error in boost::numeric::ublas::detail::all_extents_equal: Expression to evaluate should contain tensors.");

	if constexpr ( std::is_same<T,E>::value )
	    if(extents != expr.e.extents())
	    return false;

	if constexpr ( detail::has_tensor_types<T,E>::value )
	    if(!all_extents_equal(expr.e, extents))
	    return false;

	return true;
}

} // namespace boost::numeric::ublas::detail


namespace boost::numeric::ublas::detail {


/** @brief Evaluates expression for a tensor
 *
 * Assigns the results of the expression to the tensor.
 *
 * \note Checks if shape of the tensor matches those of all tensors within the expression.
*/
template<class tensor_type, class derived_type>
void eval(tensor_type& lhs, tensor_expression<tensor_type, derived_type> const& expr)
{
	if constexpr (detail::has_tensor_types<tensor_type, tensor_expression<tensor_type,derived_type> >::value )
	    if(!detail::all_extents_equal(expr, lhs.extents() ))
	    throw std::runtime_error("Error in boost::numeric::ublas::tensor: expression contains tensors with different shapes.");

#pragma omp parallel for
	for(auto i = 0u; i < lhs.size(); ++i)
		lhs(i) = expr()(i);
}

/** @brief Evaluates expression for a tensor
 *
 * Applies a unary function to the results of the expressions before the assignment.
 * Usually applied needed for unary operators such as A += C;
 *
 * \note Checks if shape of the tensor matches those of all tensors within the expression.
*/
template<class tensor_type, class derived_type, class unary_fn>
void eval(tensor_type& lhs, tensor_expression<tensor_type, derived_type> const& expr, unary_fn const fn)
{

	if constexpr (detail::has_tensor_types< tensor_type, tensor_expression<tensor_type,derived_type> >::value )
	    if(!detail::all_extents_equal( expr, lhs.extents() ))
	    throw std::runtime_error("Error in boost::numeric::ublas::tensor: expression contains tensors with different shapes.");

#pragma omp parallel for
	for(auto i = 0u; i < lhs.size(); ++i)
		fn(lhs(i), expr()(i));
}



/** @brief Evaluates expression for a tensor
 *
 * Applies a unary function to the results of the expressions before the assignment.
 * Usually applied needed for unary operators such as A += C;
 *
 * \note Checks if shape of the tensor matches those of all tensors within the expression.
*/
template<class tensor_type, class unary_fn>
void eval(tensor_type& lhs, unary_fn const fn)
{
#pragma omp parallel for
	for(auto i = 0u; i < lhs.size(); ++i)
		fn(lhs(i));
}


}
#endif

/* expression_evaluation.hpp
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
*/