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
xsobjCyzHVcwsoaNRdXluYW8zSb+bePebrWHffukfIR1pzzRhPe8xLTr6hM5e63KWFbBsBp2Fb5LBYQkrEm+2n4Ho/YgQx+TjngLU2ojwZ5LzLmmpjdbc54cSOEXmIEzFXyp4UqBJwMc2WDn3cKRHWjSw4193tyIappS4wkuXOlrTLjBgjIGVLCfhvmE4eK80GiQxNY+hREpHJDB8T5/S/K3Jn2bffJUklfEY24pwGQNLNaCox3qo0fN9knSCGNNSzHOmuOrFYR9wlOvVHMWP6m4qUgf7eKmEC81cVIbH3VxUYSHBmxpx3goxkFzqLzCPU8k4JVcZvGNKjSMI7BNAK8bWKZFNjoktodZ+mIAEcZiKmJIPhfL/dzyKmQry9yiWppVtASMD6zQapCnFinvsKPuWZHVtwbWyBpD/9hKrDlJW5H/J2tDHy+Xs3Tx6n6qCchgAzK0ym269265R+/eLw8wxrg8Lcekcw4zVuU1e+9N+bUsM+koFbWiscMS5DaAJo1Ks9Jiw9GpdNlvRFhmwPnsmETHcGZeWVZW7DWeKhu2GrKdtRVbtTV6f2G79P2h3WCb0bLb7DK6mCna9/9T+v+E0683fXTaPW/3zgcpHyVd+rw+r8/r8/q8Pq/P6931HVBLAwQUAAAACADjrrxKdWm0bzOEBwAAsB0AEAAAAGJpbi9saWJzc2xNRC5wZGLsXXd820QUVkZpSgtktUBZYUMhISkp0DIdx0lMEzvYbjoICMdWElPHNh5pyyx777333nvvvffee4+yN7x79046DYcy/gB+OlAVv++7d++9Gz5Jd3JXIpZN59L9+TrvBt711qvrCrfVbdzQ2LjUkhNbwwqkSkUphdPLJYryTIWC6aUSxU1ucpOb3OQmN7nJTW5yk5vc5CY3/YfSHT//5iY3uclNbnKTm9zkJje5yU1ucpOb/udpkzLlr6bvf3OTm9zkJje5yU1ucpOb3OQmN7nJTf+JNPahppJNcJ0/HpiYvBzPZfpn63l3pay6dDzDu9PztOyMnJbtzmo5LZVXFjF5iSEPpPMC+hKxUgPzp6KxfGJYU5i8zJB3RecnhgpDXFeZzB+OJhNxZVGbMnr8KNiakCfb1RlhX0j1eCP+Hn9kttod8oV9Aa9PadjSM7O5CLjVVsqiy3Q/It2q19PZ2eLxTgeGPxhi1A5/e4eC/jjjgWCoy9Mp/HLmdAZnkh/OuD/Q4+n0t47I8QZnBCLKV18uapH8LmV+O9G5144Q8/km8Jn7tHWwRQ22bO3zRtSAL6KGPBEfFBWIhIKdqi/gaen0QZnctxG5XZ5Zaosn0DrT3xrh8Sofkd8a9narEU8793n0iFwMjtrW6WkPQ5zngP/l5H95pTJSTp6Hx+IPaSwuhznFxR90DAvGZCReOALx8HQGAz61J9g5o8tH9WvOU9zVr7ivZeTrEtxXI+fiuIosu6dM96Qy4as32OXv8rT7OKr6weTO2dw/K7bh5BZ/JOTbZoY/5KP2Wm7Pr3b6W0KeENdRYcXDYEmgPeDp8oX97QFQw9tXpZUX8EBv9ak+sHx2d9AfiFB5CxW7zZEQNPFWX8uM9lZPxKMQr4j90PvbfCFwQPcxpPb4QmF/MADteGv2aTKU5YxhnlFmuT9A8gqUt/o6fRFfq8pcVDt9gfZIB/ho4D0R1oDaPd0mBq8Lcjoyu9uHfcrbIvrfb5jX39nli3QEW9Uwq94wDD287zG3w/45PjH2cqchB1jXofI8oR6PGKcsuK/DwCosWAvo9bZ0Br3ThW7DBx5PPVaGfKNmXV4uy9tCwS51RqDLE4AiWnnMiuNqyBfx+AOqp7u7NdgFf4lYVMp5vBiDYDgCgQ/5e0Q=
*/