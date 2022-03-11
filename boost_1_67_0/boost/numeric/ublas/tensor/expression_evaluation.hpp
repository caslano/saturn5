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