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
SpWw4rnswAAe8DyW0ze5Esl4T7VYuLY4QOfuHB78uyQw92sDzInh0kzKDlgHI9jRwK2REsSJhqnUGG6RN1rbDtfFRCGarwS4M9bz6jECun4RPAiWvSTPXLa4OmPm9/E1gkvCI4RxClKi42i+udg9Pu/ikgeJA03s723DJm8/QH8sOX7J8zA29/c0rkijU5nn1qHs4JuydDcJOFPX9KLmtaeOQNjavot39gH9v31Xm3Mm2uHntGNDPZBo3/Lr3ljdi5N440PsW/81EaTzlgYa/Ab5PcQ+tDNDYXY5O2VKPtFRxTL75Rp30NbrlhU5JnIbsQ5oUIHhl5VEmcYYCg6zhuADVqxlcxYOImDaWp8WQ22tE0o2P7OJ/UDQCiZvfb7s5K2nZq8C1CYfZLhdyxb+5rBw23M4qhxRNN7dspiV0H4y6dljaemGZApa1j01BLjvSrZA0ZTb3RbMPHxE3U3e8tVgWgY+FWoU7oOlD12iU5yd9QROJICyMEa8P/FOae/1wLFne/traIrLfQGLGJMk2d+AaZM323xq/LNzELTHRz4Fe3Psk1tCHGC/6Q==
*/