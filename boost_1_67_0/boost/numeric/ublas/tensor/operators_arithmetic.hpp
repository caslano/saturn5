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