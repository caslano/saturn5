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

#ifndef BOOST_UBLAS_TENSOR_OPERATORS_ARITHMETIC_HPP
#define BOOST_UBLAS_TENSOR_OPERATORS_ARITHMETIC_HPP

#include "expression.hpp"
#include "expression_evaluation.hpp"
#include "multi_index_utility.hpp"
#include "functions.hpp"

#include <type_traits>
#include <functional>
#include <algorithm>

namespace boost{
namespace numeric{
namespace ublas {


template<class element_type, class storage_format, class storage_type>
class tensor;

template<class E>
class matrix_expression;


template<class E>
class vector_expression;

}
}
}

#define FIRST_ORDER_OPERATOR_RIGHT(OP, EXPR_TYPE_L, EXPR_TYPE_R) \
template<class T, class L, class R> \
auto operator OP ( boost::numeric::ublas:: EXPR_TYPE_L <T,L> const& lhs, boost::numeric::ublas:: EXPR_TYPE_R <R> const& rhs) { \
	return boost::numeric::ublas::detail::make_binary_tensor_expression<T> (lhs(), rhs(), \
	  [](auto const& l, auto const& r){ return l OP r; }); \
} \

FIRST_ORDER_OPERATOR_RIGHT (*, detail:: tensor_expression , vector_expression)
FIRST_ORDER_OPERATOR_RIGHT (+, detail:: tensor_expression , vector_expression)
FIRST_ORDER_OPERATOR_RIGHT (-, detail:: tensor_expression , vector_expression)
FIRST_ORDER_OPERATOR_RIGHT (/, detail:: tensor_expression , vector_expression)

FIRST_ORDER_OPERATOR_RIGHT (*, detail:: tensor_expression , matrix_expression)
FIRST_ORDER_OPERATOR_RIGHT (+, detail:: tensor_expression , matrix_expression)
FIRST_ORDER_OPERATOR_RIGHT (-, detail:: tensor_expression , matrix_expression)
FIRST_ORDER_OPERATOR_RIGHT (/, detail:: tensor_expression , matrix_expression)


#define FIRST_ORDER_OPERATOR_LEFT(OP, EXPR_TYPE_L, EXPR_TYPE_R) \
template<class T, class L, class R> \
auto operator OP ( boost::numeric::ublas:: EXPR_TYPE_L <L> const& lhs, boost::numeric::ublas:: EXPR_TYPE_R <T,R> const& rhs) { \
	return boost::numeric::ublas::detail::make_binary_tensor_expression<T> (lhs(), rhs(), \
	  [](auto const& l, auto const& r){ return l OP r; }); \
} \

FIRST_ORDER_OPERATOR_LEFT (*, vector_expression, detail:: tensor_expression)
FIRST_ORDER_OPERATOR_LEFT (+, vector_expression, detail:: tensor_expression)
FIRST_ORDER_OPERATOR_LEFT (-, vector_expression, detail:: tensor_expression)
FIRST_ORDER_OPERATOR_LEFT (/, vector_expression, detail:: tensor_expression)

FIRST_ORDER_OPERATOR_LEFT (*, matrix_expression, detail:: tensor_expression)
FIRST_ORDER_OPERATOR_LEFT (+, matrix_expression, detail:: tensor_expression)
FIRST_ORDER_OPERATOR_LEFT (-, matrix_expression, detail:: tensor_expression)
FIRST_ORDER_OPERATOR_LEFT (/, matrix_expression, detail:: tensor_expression)




template<class T, class L, class R>
auto operator+( boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs, boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::make_binary_tensor_expression<T> (lhs(), rhs(), [](auto const& l, auto const& r){ return l + r; });
}
template<class T, class L, class R>
auto operator-( boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs, boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::make_binary_tensor_expression<T> (lhs(), rhs(), [](auto const& l, auto const& r){ return l - r; });
//	return boost::numeric::ublas::detail::make_lambda<T>([&lhs,&rhs](std::size_t i){ return lhs(i) - rhs(i);});
}
template<class T, class L, class R>
auto operator*( boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs, boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::make_binary_tensor_expression<T> (lhs(), rhs(), [](auto const& l, auto const& r){ return l * r; });
}
template<class T, class L, class R>
auto operator/( boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs, boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::make_binary_tensor_expression<T> (lhs(), rhs(), [](auto const& l, auto const& r){ return l / r; });
}


// Overloaded Arithmetic Operators with Scalars
template<class T, class R>
auto operator+(typename T::const_reference lhs, boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::make_unary_tensor_expression<T> (rhs(), [lhs](auto const& r){ return lhs + r; });
	//return boost::numeric::ublas::detail::make_lambda<T>( [&lhs,&rhs](std::size_t i) {return lhs + rhs(i); } );
}
template<class T, class R>
auto operator-(typename T::const_reference lhs, boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::make_unary_tensor_expression<T> (rhs(), [lhs](auto const& r){ return lhs - r; });
}
template<class T, class R>
auto operator*(typename T::const_reference lhs, boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::make_unary_tensor_expression<T> (rhs(), [lhs](auto const& r){ return lhs * r; });
}
template<class T, class R>
auto operator/(typename T::const_reference lhs, boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::make_unary_tensor_expression<T> (rhs(), [lhs](auto const& r){ return lhs / r; });
}


template<class T, class L>
auto operator+(boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs, typename T::const_reference rhs) {
	return boost::numeric::ublas::detail::make_unary_tensor_expression<T> (lhs(), [rhs] (auto const& l) { return l + rhs; } );
}
template<class T, class L>
auto operator-(boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs, typename T::const_reference rhs) {
	return boost::numeric::ublas::detail::make_unary_tensor_expression<T> (lhs(), [rhs] (auto const& l) { return l - rhs; } );
}
template<class T, class L>
auto operator*(boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs, typename T::const_reference rhs) {
	return boost::numeric::ublas::detail::make_unary_tensor_expression<T> (lhs(), [rhs] (auto const& l) { return l * rhs; } );
}
template<class T, class L>
auto operator/(boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs, typename T::const_reference rhs) {
	return boost::numeric::ublas::detail::make_unary_tensor_expression<T> (lhs(), [rhs] (auto const& l) { return l / rhs; } );
}



template<class T, class D>
auto& operator += (T& lhs, const boost::numeric::ublas::detail::tensor_expression<T,D> &expr) {
	boost::numeric::ublas::detail::eval(lhs, expr(), [](auto& l, auto const& r) { l+=r; } );
	return lhs;
}

template<class T, class D>
auto& operator -= (T& lhs, const boost::numeric::ublas::detail::tensor_expression<T,D> &expr) {
	boost::numeric::ublas::detail::eval(lhs, expr(), [](auto& l, auto const& r) { l-=r; } );
	return lhs;
}

template<class T, class D>
auto& operator *= (T& lhs, const boost::numeric::ublas::detail::tensor_expression<T,D> &expr) {
	boost::numeric::ublas::detail::eval(lhs, expr(), [](auto& l, auto const& r) { l*=r; } );
	return lhs;
}

template<class T, class D>
auto& operator /= (T& lhs, const boost::numeric::ublas::detail::tensor_expression<T,D> &expr) {
	boost::numeric::ublas::detail::eval(lhs, expr(), [](auto& l, auto const& r) { l/=r; } );
	return lhs;
}




template<class E, class F, class A>
auto& operator += (boost::numeric::ublas::tensor<E,F,A>& lhs, typename boost::numeric::ublas::tensor<E,F,A>::const_reference r) {
	boost::numeric::ublas::detail::eval(lhs, [r](auto& l) { l+=r; } );
	return lhs;
}

template<class E, class F, class A>
auto& operator -= (boost::numeric::ublas::tensor<E,F,A>& lhs, typename boost::numeric::ublas::tensor<E,F,A>::const_reference r) {
	boost::numeric::ublas::detail::eval(lhs, [r](auto& l) { l-=r; } );
	return lhs;
}

template<class E, class F, class A>
auto& operator *= (boost::numeric::ublas::tensor<E,F,A>& lhs, typename boost::numeric::ublas::tensor<E,F,A>::const_reference r) {
	boost::numeric::ublas::detail::eval(lhs, [r](auto& l) { l*=r; } );
	return lhs;
}

template<class E, class F, class A>
auto& operator /= (boost::numeric::ublas::tensor<E,F,A>& lhs, typename boost::numeric::ublas::tensor<E,F,A>::const_reference r) {
	boost::numeric::ublas::detail::eval(lhs, [r](auto& l) { l/=r; } );
	return lhs;
}






template<class T, class D>
auto const& operator +(const boost::numeric::ublas::detail::tensor_expression<T,D>& lhs) {
	return lhs;
}

template<class T, class D>
auto operator -(boost::numeric::ublas::detail::tensor_expression<T,D> const& lhs) {
	return boost::numeric::ublas::detail::make_unary_tensor_expression<T> (lhs(), [] (auto const& l) { return -l; } );
}





/** @brief Performs a tensor contraction, not an elementwise multiplication
	*
*/

template<class tensor_type_left, class tuple_type_left, class tensor_type_right, class tuple_type_right>
auto operator*(
		std::pair< tensor_type_left  const&, tuple_type_left  > lhs,
		std::pair< tensor_type_right const&, tuple_type_right > rhs)
{

	using namespace boost::numeric::ublas;

	auto const& tensor_left  = lhs.first;
	auto const& tensor_right = rhs.first;

	auto multi_index_left = lhs.second;
	auto multi_index_right = rhs.second;

	static constexpr auto num_equal_ind = number_equal_indexes<tuple_type_left, tuple_type_right>::value;

	if constexpr ( num_equal_ind == 0  ){
		return tensor_left * tensor_right;
	}
	else if constexpr ( num_equal_ind==std::tuple_size<tuple_type_left>::value && std::is_same<tuple_type_left, tuple_type_right>::value ){

		return boost::numeric::ublas::inner_prod( tensor_left, tensor_right );
	}
	else {
		auto array_index_pairs = index_position_pairs(multi_index_left,multi_index_right);
		auto index_pairs = array_to_vector(  array_index_pairs  );
		return boost::numeric::ublas::prod( tensor_left, tensor_right, index_pairs.first, index_pairs.second );
	}

}

#endif

/* operators_arithmetic.hpp
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
*/