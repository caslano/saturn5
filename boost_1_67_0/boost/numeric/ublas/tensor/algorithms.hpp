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