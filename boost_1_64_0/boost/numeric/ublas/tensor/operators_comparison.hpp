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
QkBjKcKZur/0mpPa2tleHbm8XS01P3dDeDXC8xAuQdjLUu1/gaXapw9CqVP0RfiK5I3wRwj7IzyAcADCX8j3A+e/SvBaSfYN59+K5kP1KwGeTJuF0C/nWUvJwXxZD9nWCOcjvBHhLQhrEUqetyC8E2GDpfrvZoSPc7zso3kIvynnaYRPcbxcV20aKcQuwGFAziiUB7AIsA1wABAZjToBJgDKAUsAG0YjHbAXcGS07EzMD4AiQDlgNWALYA/gIOAkoN0YyABgJqAesGoM+AB2AF4eAz6AyFjMU4AiQBlgOWDdWOCMBQ7gIOAkoOBSvGcBxYBFgI2A7YC9lwLnUuAAuo0DDmAqYAlgC+BlwBFA+DKUF9AbMBwwC9AI2ADYBTgEOAEIjkdegBGASsBqwHbAPsAhQPBy1AvQDzAOMAuwHLAJsAOwH3AYEJ6AeRVQBCgD1ANWA7YCdk8ADiB4BXAAIwDFgHrAOsA2wB7AQcBJQIeJKDegCFA+EXwAOwH7J4IP4DggeCV4AYYAigH1gFWAjVeCH2Af4BDAVww8QBGgHLAEsAWwqxjpgJOA8FVoS0AhYAqgHrABsAtwEHAUEJwEPoARgMpJaoLfANgK2Ak4ADg2SSkfOZPBD1AImAqomQx8wNrJwAfsngy+k4EPiExBXQETADMBSwCbAHsARwC+q5EvoAhQCVgN2AbYBdgLOHy1UnTaXQM8QDGgBrAcsOEa4AEOAk4CgteirwFFgKmAmmuBA9hxLXAAx64VSAAvQD/ABEA5oBGwZSrwAC9PBS7gKCA8DXiACYBKwFrALsB+wBFAcDp4AYYAxgFmAmoAqwE7pwNvOvAAwRloA8AUQD1gHWArYBfgAOAI4ASgYCbaFDABUA5YPhO4gC2AHYCDM4EHCF4HGQIMB0wB1AOWAzYBdgEOAo4DfNeDJ2AEoAywCrAdcBgQLkFegJklKC9gN+BQiVIaOwCGAGYCGgFbAfsBwVLEA8pLxdnf2d/Z39nf2V+Kv3+p/X//knpwOiP2/ysiyid5nyf53qX7nm/yPU33Pdxke+Jnbu/VfW+35Xvo7nvxLT9LcD/DSL637n42kGyvvOV74u5nGC3fu3ffW09+duJ+RpLsLOfMnWGs8ja5RuJ1lPu6qNxcD5lrIb0OauEa6Eytf87k2qel6x73NU/ytc7qJGucesC2FNYzLV3DbAA0nuE1zJlavxhrF163mGsW53plwhlapzjXKP/etQmvS87+zv7O/s7+zv7O/s7+zv7+539kQ/yvW//Tbbi0ASDEae8B3BGR34drTWU9zGfG56qAzpHrpF/Ij8hesXjk6MvHTCEXlv5kY3hjDtnQz9d2nG0Q7iHczu6+IJRmEW0D2SfSLajuvh+MmyeuoG8OlaFsq1BWb37AE/Z6hEdMzNJpG5B2J9JCIhAIhzLA5wq6U3Id4C7Eh32C8CUk95spGG/6+sm65XLdtF2jLHMulZl9/bjdFrGPfQ+h/Gm6Az4j/Vod7TZ7cX20LmnbHSf8ru7+rUbbtYo03XYmboOQuJXRKsPu+q+U3gG2XJar78Mxo+2PoA0Pebjtz4m1fT6ntUPd71ZtHPKj+YPpgtr/MGhyvM23v68F7Y96c/vHfBwaBOK4fmaflDPjTvqcGLAYPAv2GX1Cl1uX9Nd+pjfpPjH8hLoRfkgE3W1uwS91mda4qcrgTSnI4DCu7wa/s763gb7YUV8WQmedbf+zKUST7VZf8EtdDgnXKYeuMld8BtqmJfJRGIj35UgD3CKNIOPaqza6oLSiCpNmYlu5tk3jadTBLFs/FEb1j/plynoAd60qW00p3dQ7t7r2plJ5tYDrfEK2boSf4e5H6NY3hgxsoPQ=
*/