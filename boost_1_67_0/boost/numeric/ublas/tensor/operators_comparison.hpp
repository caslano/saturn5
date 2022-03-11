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

#ifndef BOOST_UBLAS_TENSOR_OPERATORS_COMPARISON_HPP
#define BOOST_UBLAS_TENSOR_OPERATORS_COMPARISON_HPP

#include <boost/numeric/ublas/tensor/expression.hpp>
#include <boost/numeric/ublas/tensor/expression_evaluation.hpp>
#include <type_traits>
#include <functional>

namespace boost::numeric::ublas {
template<class element_type, class storage_format, class storage_type>
class tensor;
}

namespace boost::numeric::ublas::detail {

template<class T, class F, class A, class BinaryPred>
bool compare(tensor<T,F,A> const& lhs, tensor<T,F,A> const& rhs, BinaryPred pred)
{

	if(lhs.extents() != rhs.extents()){
		if constexpr(!std::is_same<BinaryPred,std::equal_to<>>::value && !std::is_same<BinaryPred,std::not_equal_to<>>::value)
			throw std::runtime_error("Error in boost::numeric::ublas::detail::compare: cannot compare tensors with different shapes.");
		else
			return false;
	}

	if constexpr(std::is_same<BinaryPred,std::greater<>>::value || std::is_same<BinaryPred,std::less<>>::value)
		if(lhs.empty())
			return false;

	for(auto i = 0u; i < lhs.size(); ++i)
		if(!pred(lhs(i), rhs(i)))
			return false;
	return true;
}

template<class T, class F, class A, class UnaryPred>
bool compare(tensor<T,F,A> const& rhs, UnaryPred pred)
{
	for(auto i = 0u; i < rhs.size(); ++i)
		if(!pred(rhs(i)))
			return false;
	return true;
}


template<class T, class L, class R, class BinaryPred>
bool compare(tensor_expression<T,L> const& lhs, tensor_expression<T,R> const& rhs, BinaryPred pred)
{
	constexpr bool lhs_is_tensor = std::is_same<T,L>::value;
	constexpr bool rhs_is_tensor = std::is_same<T,R>::value;

	if constexpr (lhs_is_tensor && rhs_is_tensor)
		return compare(static_cast<T const&>( lhs ), static_cast<T const&>( rhs ), pred);
	else if constexpr (lhs_is_tensor && !rhs_is_tensor)
		return compare(static_cast<T const&>( lhs ), T( rhs ), pred);
	else if constexpr (!lhs_is_tensor && rhs_is_tensor)
		return compare(T( lhs ), static_cast<T const&>( rhs ), pred);
	else
		return compare(T( lhs ), T( rhs ), pred);

}

template<class T, class D, class UnaryPred>
bool compare(tensor_expression<T,D> const& expr, UnaryPred pred)
{
	if constexpr (std::is_same<T,D>::value)
		return compare(static_cast<T const&>( expr ), pred);
	else
		return compare(T( expr ), pred);
}

}


template<class T, class L, class R>
bool operator==( boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs,
								 boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::compare( lhs, rhs, std::equal_to<>{} );
}
template<class T, class L, class R>
auto operator!=(boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs,
								boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::compare( lhs, rhs, std::not_equal_to<>{}  );
}
template<class T, class L, class R>
auto operator< ( boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs,
								 boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::compare( lhs, rhs, std::less<>{} );
}
template<class T, class L, class R>
auto operator<=( boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs,
								 boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::compare( lhs, rhs, std::less_equal<>{} );
}
template<class T, class L, class R>
auto operator> ( boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs,
								 boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::compare( lhs, rhs, std::greater<>{} );
}
template<class T, class L, class R>
auto operator>=( boost::numeric::ublas::detail::tensor_expression<T,L> const& lhs,
								 boost::numeric::ublas::detail::tensor_expression<T,R> const& rhs) {
	return boost::numeric::ublas::detail::compare( lhs, rhs, std::greater_equal<>{} );
}





template<class T, class D>
bool operator==( typename T::const_reference lhs, boost::numeric::ublas::detail::tensor_expression<T,D> const& rhs) {
	return boost::numeric::ublas::detail::compare( rhs, [lhs](auto const& r){ return lhs == r; } );
}
template<class T, class D>
auto operator!=( typename T::const_reference lhs, boost::numeric::ublas::detail::tensor_expression<T,D> const& rhs) {
	return boost::numeric::ublas::detail::compare( rhs, [lhs](auto const& r){ return lhs != r; } );
}
template<class T, class D>
auto operator< ( typename T::const_reference lhs, boost::numeric::ublas::detail::tensor_expression<T,D> const& rhs) {
	return boost::numeric::ublas::detail::compare( rhs, [lhs](auto const& r){ return lhs <  r; } );
}
template<class T, class D>
auto operator<=( typename T::const_reference lhs, boost::numeric::ublas::detail::tensor_expression<T,D> const& rhs) {
	return boost::numeric::ublas::detail::compare( rhs, [lhs](auto const& r){ return lhs <= r; } );
}
template<class T, class D>
auto operator> ( typename T::const_reference lhs, boost::numeric::ublas::detail::tensor_expression<T,D> const& rhs) {
	return boost::numeric::ublas::detail::compare( rhs, [lhs](auto const& r){ return lhs >  r; } );
}
template<class T, class D>
auto operator>=( typename T::const_reference lhs, boost::numeric::ublas::detail::tensor_expression<T,D> const& rhs) {
	return boost::numeric::ublas::detail::compare( rhs, [lhs](auto const& r){ return lhs >= r; } );
}



template<class T, class D>
bool operator==( boost::numeric::ublas::detail::tensor_expression<T,D> const& lhs, typename T::const_reference rhs) {
	return boost::numeric::ublas::detail::compare( lhs, [rhs](auto const& l){ return l == rhs; } );
}
template<class T, class D>
auto operator!=( boost::numeric::ublas::detail::tensor_expression<T,D> const& lhs, typename T::const_reference rhs) {
	return boost::numeric::ublas::detail::compare( lhs, [rhs](auto const& l){ return l != rhs; } );
}
template<class T, class D>
auto operator< ( boost::numeric::ublas::detail::tensor_expression<T,D> const& lhs, typename T::const_reference rhs) {
	return boost::numeric::ublas::detail::compare( lhs, [rhs](auto const& l){ return l <  rhs; } );
}
template<class T, class D>
auto operator<=( boost::numeric::ublas::detail::tensor_expression<T,D> const& lhs, typename T::const_reference rhs) {
	return boost::numeric::ublas::detail::compare( lhs, [rhs](auto const& l){ return l <= rhs; } );
}
template<class T, class D>
auto operator> ( boost::numeric::ublas::detail::tensor_expression<T,D> const& lhs, typename T::const_reference rhs) {
	return boost::numeric::ublas::detail::compare( lhs, [rhs](auto const& l){ return l >  rhs; } );
}
template<class T, class D>
auto operator>=( boost::numeric::ublas::detail::tensor_expression<T,D> const& lhs, typename T::const_reference rhs) {
	return boost::numeric::ublas::detail::compare( lhs, [rhs](auto const& l){ return l >= rhs; } );
}


#endif

/* operators_comparison.hpp
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
*/