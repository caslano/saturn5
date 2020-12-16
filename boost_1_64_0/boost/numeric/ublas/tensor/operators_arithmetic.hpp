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
97v5ctiU3ony6w/f6ej1D7mh/81lf7nkm3VWbYbvA5Rv9t06a0e+3XX/S9rnLPfJ6IP3gNkUxnmnVdatu2bZY678ccH1Bzx+4JchmGeWMXnw+gsCr/92qf/zi447YcmL14SXrDxbwuQXz9551idLHHbu7hfUvPHIeUfCiwBuRf0Xnn5u697lZb+2xDa+KPXWxjDDXRv5Nzx59XM/rdC+y71bZR+/r/nuw6Ado/78xAO/2XObk+bsO2nmaZXNY96B521jmbzs9qp43071Z5508VUzf13tEViTORXlnxxSd3L9Pamf9/zynBv3OmeVS2FNKerJPDG03zdfrP3g00d5V1z/7U2gvbH9tLPEczF69tZB/bOTOtruMFBMZP0TzvVw3gvOjey7Fc5bsu9IOM+E8z5wjsF5PzgfQjjTf4Z47oT3orh+fJaj6PfnFjKsFs5j+L3ZhePYOA/npfizwIWrwHlZOE/i1ywLp8B5eThvxa9xF07n17wLe9iYB+conFeCM+5xh/POcF4FzvswW+B8GJw3gHNdCSuH23mHeIZEz6o60BbWtng6AXjsfCKcWXyuIntPgXMNnE+D80rc34Vrw/ksODfB+Rw4bwrnc+Hsg/N5cA7C+Xw4z4bzBQqP24VwHoLzRXCeB+eL4bwnnC+B88FwvhTOx/LnZwtP5zYuvBDOV8L5MrLnS4wbPTsi+zvo995+Z+9awKMqrvDcfWWT3cAmJAEij4CAiEABw7OoPAIiIkZA5aUhkIVEQhLzQFCqAQFREdFSoZZaFFRqaUstKipa2lKrFlu01FKlLVpqaYstVlpppbX/nDlzd3bv3WQD9PG17MdhcmfOOfM6M/fMzDlzu3E9vmupeuxBmIPwe1aMbi3TtXGh28d0ryPMRvhjg257E/l9g+me5Py+adDta4LuaaZ7humeNeiONUG3jem+ynRfM+gibyWv3ytM9yrXb69B168JuheY7kWm223IffFbyeX+Qpb7QpajgSz3xSz3g1juB7PcD2G5H8pyP4zl/tMs98NZ7i9iub+Y5f4SlvsRLPdXstwXs7wMsXjPk/dVx3Hd4FNIv8lczmsQdkA4FWFPhNMRFiK8jsszC6GcM+ZwecoQIk5EEd6AcC7CeoTzEN6KsBzhKoQVCO9HCJxGOf/MR/gYwkqETyJcgPBFhEvkMwpyG8LnETbi3wsIlyE8inA5wjSU/25ZToSr5ThEeA/CAQjXILwI4b0IxyFci3AywvsQXo/wfoQVCD8rxx/CaxHegvBzCJcgvEOWF+GdCO+leG4/vQ9Kc5BqP59sP+7ndSwfn0PYCuF6nk83WDH6fk3Q38P0a5h+LdPfZ9DPaoL+EabfzPSPMv1jBv3aJui/wPQbmf4hpv8S0/eU8sP0k1nOu8p5mOXnDzxv/pHl+hjPlx8g7I4QPOh98iHCYQj/jHA4wr8gHI/wBMJJCP+KcCrCv7E8fYywQa5HEN6G8B88X34i+wehhfKtR+hB+EU5ZhF+XdYN4XMI/Qj3IExD+BLCIML9cm2C8KDUKRG+izCMUOqLmQjBW7RCmC7f1wiBI7IQtkeYh/BShO0RXoEwH+FEhG0RTpLP3F6LhN6vgYxye4dJ3tXvbR5vBxG2Rvhzbq9fIJR6+O+Eav9fIpR9dIjH4Ts8H/wK4WyEhxGWI/w1vT+IjvPnPQuqszP/p3neeY7753mERQi/w/3xPZ5XXkZ4j5wvET6M8AcIv4rwRwhRBvFjzu8lhB8Zz1tl/XltGeX8s1n3kL/BlpKTEQilbI5CeD3CIoSyjGMRLkM4nvv1CoQoiyhG+FOEVyH8q5LFRpnJFCmvCK+x1Lx3LcLzEU5F2AfhNIRXIpyOcAY=
*/