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


#ifndef _BOOST_UBLAS_TENSOR_ALGORITHMS_HPP
#define _BOOST_UBLAS_TENSOR_ALGORITHMS_HPP


#include <stdexcept>
#include <complex>
#include <functional>

namespace boost {
namespace numeric {
namespace ublas {



/** @brief Copies a tensor to another tensor with different layouts
 *
 * Implements C[i1,i2,...,ip] = A[i1,i2,...,ip]
 *
 * @param[in]  p rank of input and output tensor
 * @param[in]  n pointer to the extents of input or output tensor of length p
 * @param[in] pi pointer to a one-based permutation tuple of length p
 * @param[out] c pointer to the output tensor
 * @param[in] wc pointer to the strides of output tensor c
 * @param[in]  a pointer to the input tensor
 * @param[in] wa pointer to the strides of input tensor a
*/
template <class	PointerOut, class PointerIn, class SizeType>
void copy(const SizeType p, SizeType const*const n,
          PointerOut c, SizeType const*const wc,
          PointerIn a,  SizeType const*const wa)
{
	static_assert( std::is_pointer<PointerOut>::value & std::is_pointer<PointerIn>::value,
	               "Static error in boost::numeric::ublas::copy: Argument types for pointers are not pointer types.");
	if( p == 0 )
		return;

	if(c == nullptr || a == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::copy: Pointers shall not be null pointers.");

	if(wc == nullptr || wa == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::copy: Pointers shall not be null pointers.");

	if(n == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::copy: Pointers shall not be null pointers.");


	std::function<void(SizeType r, PointerOut c, PointerIn  a)> lambda;

	lambda = [&lambda, n, wc, wa](SizeType r, PointerOut c, PointerIn a)
	{
		if(r > 0)
			for(auto d = 0u; d < n[r]; c += wc[r], a += wa[r], ++d)
				lambda(r-1, c, a );
		else
			for(auto d = 0u; d < n[0]; c += wc[0], a += wa[0], ++d)
				*c = *a;
	};

	lambda( p-1, c, a );
}



/** @brief Copies a tensor to another tensor with different layouts applying a unary operation
 *
 * Implements C[i1,i2,...,ip] = op ( A[i1,i2,...,ip] )
 *
 * @param[in]  p rank of input and output tensor
 * @param[in]  n pointer to the extents of input or output tensor of length p
 * @param[in] pi pointer to a one-based permutation tuple of length p
 * @param[out] c pointer to the output tensor
 * @param[in] wc pointer to the strides of output tensor c
 * @param[in]  a pointer to the input tensor
 * @param[in] wa pointer to the strides of input tensor a
 * @param[in] op unary operation
*/
template <class	PointerOut, class PointerIn, class SizeType, class UnaryOp>
void transform(const SizeType p,
               SizeType const*const n,
               PointerOut c, SizeType const*const wc,
               PointerIn a,  SizeType const*const wa,
               UnaryOp op)
{
	static_assert( std::is_pointer<PointerOut>::value & std::is_pointer<PointerIn>::value,
	               "Static error in boost::numeric::ublas::transform: Argument types for pointers are not pointer types.");
	if( p == 0 )
		return;

	if(c == nullptr || a == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::transform: Pointers shall not be null pointers.");

	if(wc == nullptr || wa == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::transform: Pointers shall not be null pointers.");

	if(n == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::transform: Pointers shall not be null pointers.");


	std::function<void(SizeType r, PointerOut c, PointerIn a)> lambda;

	lambda = [&lambda, n, wc, wa, op](SizeType r, PointerOut c, PointerIn a)
	{
		if(r > 0)
			for(auto d = 0u; d < n[r]; c += wc[r], a += wa[r], ++d)
				lambda(r-1, c, a);
		else
			for(auto d = 0u; d < n[0]; c += wc[0], a += wa[0], ++d)
				*c = op(*a);
	};

	lambda( p-1, c, a );

}


/** @brief Performs a reduce operation with all elements of the tensor and an initial value
 *
 * Implements k = sum_{i1,..,ip} A[i1,i2,...,ip]
 *
 * @param[in] r  zero-based recursion level starting with r=p-1
 * @param[in] n  pointer to the extents of input or output tensor
 * @param[in] a  pointer to the first input tensor
 * @param[in] w  pointer to the strides of input tensor a
 * @param[in] k  accumulated value
*/
template <class PointerIn, class ValueType, class SizeType>
ValueType accumulate(SizeType const p, SizeType const*const n,
                     PointerIn a, SizeType const*const w,
                     ValueType k)
{
	static_assert(std::is_pointer<PointerIn>::value,
	              "Static error in boost::numeric::ublas::transform: Argument types for pointers are not pointer types.");

	if( p == 0 )
		return k;

	if(a == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::transform: Pointers shall not be null pointers.");

	if(w == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::transform: Pointers shall not be null pointers.");

	if(n == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::transform: Pointers shall not be null pointers.");


	std::function<ValueType(SizeType r, PointerIn a, ValueType k)> lambda;

	lambda = [&lambda, n, w](SizeType r, PointerIn a, ValueType k)
	{
		if(r > 0u)
			for(auto d = 0u; d < n[r]; a += w[r], ++d)
				k = lambda(r-1, a, k);
		else
			for(auto d = 0u; d < n[0]; a += w[0], ++d)
				k += *a;
		return k;
	};

	return lambda( p-1, a,  k );
}

/** @brief Performs a reduce operation with all elements of the tensor and an initial value
 *
 * Implements k = op ( k , A[i1,i2,...,ip] ), for all ir
 *
 * @param[in] r  zero-based recursion level starting with r=p-1
 * @param[in] n  pointer to the extents of input or output tensor
 * @param[in] a  pointer to the first input tensor
 * @param[in] w  pointer to the strides of input tensor a
 * @param[in] k  accumulated value
 * @param[in] op binary operation
*/

template <class PointerIn, class ValueType, class SizeType, class BinaryOp>
ValueType accumulate(SizeType const p, SizeType const*const n,
                     PointerIn a, SizeType const*const w,
                     ValueType k, BinaryOp op)
{
	static_assert(std::is_pointer<PointerIn>::value,
	              "Static error in boost::numeric::ublas::transform: Argument types for pointers are not pointer types.");


	if( p == 0 )
		return k;

	if(a == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::transform: Pointers shall not be null pointers.");

	if(w == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::transform: Pointers shall not be null pointers.");

	if(n == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::transform: Pointers shall not be null pointers.");


	std::function<ValueType(SizeType r, PointerIn a, ValueType k)> lambda;

	lambda = [&lambda, n, w, op](SizeType r, PointerIn a, ValueType k)
	{
		if(r > 0u)
			for(auto d = 0u; d < n[r]; a += w[r], ++d)
				k = lambda(r-1, a, k);
		else
			for(auto d = 0u; d < n[0]; a += w[0], ++d)
				k = op ( k, *a );
		return k;
	};

	return lambda( p-1, a,  k );
}

/** @brief Transposes a tensor
 *
 * Implements C[tau[i1],tau[i2],...,tau[ip]] = A[i1,i2,...,ip]
 *
 * @note is used in function trans
 *
 * @param[in]  p rank of input and output tensor
 * @param[in] na pointer to the extents of the input tensor a of length p
 * @param[in] pi pointer to a one-based permutation tuple of length p
 * @param[out] c pointer to the output tensor
 * @param[in] wc pointer to the strides of output tensor c
 * @param[in]  a pointer to the input tensor
 * @param[in] wa pointer to the strides of input tensor a
*/

template <class PointerOut, class PointerIn, class SizeType>
void trans( SizeType const p,  SizeType const*const na, SizeType const*const pi,
            PointerOut c,      SizeType const*const wc,
            PointerIn a,       SizeType const*const wa)
{

	static_assert( std::is_pointer<PointerOut>::value & std::is_pointer<PointerIn>::value,
	               "Static error in boost::numeric::ublas::trans: Argument types for pointers are not pointer types.");

	if( p < 2)
		return;

	if(c == nullptr || a == nullptr)
		throw std::runtime_error("Error in boost::numeric::ublas::trans: Pointers shall not be null pointers.");

	if(na == nullptr)
		throw std::runtime_error("Error in boost::numeric::ublas::trans: Pointers shall not be null.");

	if(wc == nullptr || wa == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::trans: Pointers shall not be null pointers.");

	if(na == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::trans: Pointers shall not be null pointers.");

	if(pi == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::trans: Pointers shall not be null pointers.");


	std::function<void(SizeType r, PointerOut c, PointerIn a)> lambda;

	lambda = [&lambda, na, wc, wa, pi](SizeType r, PointerOut c, PointerIn a)
	{
		if(r > 0)
			for(auto d = 0u; d < na[r]; c += wc[pi[r]-1], a += wa[r], ++d)
				lambda(r-1, c, a);
		else
			for(auto d = 0u; d < na[0]; c += wc[pi[0]-1], a += wa[0], ++d)
				*c = *a;
	};

	lambda( p-1, c, a );
}


/** @brief Transposes a tensor
 *
 * Implements C[tau[i1],tau[i2],...,tau[ip]] = A[i1,i2,...,ip]
 *
 * @note is used in function trans
 *
 * @param[in]  p rank of input and output tensor
 * @param[in] na pointer to the extents of the input tensor a of length p
 * @param[in] pi pointer to a one-based permutation tuple of length p
 * @param[out] c pointer to the output tensor
 * @param[in] wc pointer to the strides of output tensor c
 * @param[in]  a pointer to the input tensor
 * @param[in] wa pointer to the strides of input tensor a
*/

template <class ValueType, class SizeType>
void trans( SizeType const p,
            SizeType const*const na,
            SizeType const*const pi,
            std::complex<ValueType>* c,  SizeType const*const wc,
            std::complex<ValueType>* a,  SizeType const*const wa)
{
	if( p < 2)
		return;

	if(c == nullptr || a == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::trans: Pointers shall not be null pointers.");

	if(wc == nullptr || wa == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::trans: Pointers shall not be null pointers.");

	if(na == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::trans: Pointers shall not be null pointers.");

	if(pi == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::trans: Pointers shall not be null pointers.");


	std::function<void(SizeType r, std::complex<ValueType>* c, std::complex<ValueType>* a)> lambda;

	lambda = [&lambda, na, wc, wa, pi](SizeType r, std::complex<ValueType>* c, std::complex<ValueType>* a)
	{
		if(r > 0)
			for(auto d = 0u; d < na[r]; c += wc[pi[r]-1], a += wa[r], ++d)
				lambda(r-1, c, a);
		else
			for(auto d = 0u; d < na[0]; c += wc[pi[0]-1], a += wa[0], ++d)
				*c = std::conj(*a);
	};

	lambda( p-1, c, a );

}




}
}
}

#endif

/* algorithms.hpp
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
*/