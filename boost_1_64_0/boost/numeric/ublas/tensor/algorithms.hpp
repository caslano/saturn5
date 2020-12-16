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
Rjv7O1pOVRgZBLqU5zAjn8LT2SzuE38mFUo7pbHWNOseKwJr9iv7Wua/h5EEpqficHZ+SNgHTR0l9hbjxAQxSUzBKXeCOFm8Alo0TkqTaqQXcZo+Kg3HKWG9vF/+SomAx/Zn9ZhJ6t11XoE9XsnP4xfwi/klfDGsW7h0tSRIv5Qm44ZwIe5DRqo56kx4Sz20u6GDn9d2a/1M1ZxgLYNn0N6ebt8Pvb4DuiWMnSkj+T7CKOFeMd9zpXQjfOtbcSqul76UOsNe1MrlOF184a3W1+mf61+Y8fA2EukeaXTH/W1+nvCe2NvzBCzsa569nnOesXKu/IB8k8J7M/Ry+Ccb4I9QfRJGCP67VkyR1ku7ZMVreod5E7zJ3jTvJG+GdyrOMiU4yczFOWYhTjHLcYZZgxPMszjBbcPtzm7c7RzEzc6HuNc5hludk7jTCYXn2BX3OX1xm3OVOkgVVVW11Th1JPbVeHWymqXmqYVqmTpbrVTnq4vVpbixXY17ibW4rd2Mu9qd8BwPwG98H17jZ/AZj8NjPAffOALeYi/4ipfDUxwCP1GHlzhCS9JStQnaL+GTT8Nt7kxtjnaXtkC7F3dlK3FT9iTuyTZAK74MnbgXGvEd6MNPoA2/hC48DV3dXo/E6Tpav0zvrw/UeV3RTX0YPM9kPU2fpGfoU2EnS/QKfS605kLozOXQmGugL5/VN8Iu1ONkv18/qB+GfWjCfmjRT+pnoXk6Gl3hd/aF13kVfE4RHqcNf3MkvM3x8DWz4GkWws+cbVTiLL/YWApPfzXs3lrcdm3GXddOeP0HjEPG+0Yj7iSajePGKeOcEW5GQCf3Mi81LzcH4KQjmboZa44wk+DFTDB/aWab08xic6Y5B7fYC3DnucxcCb/mSXg1G+DTvGzuMveaDeY7uG/+xDxqfmmeME+bxGpvRVrdrWjrMqu/NdDiLcUyrWFWAu480qxJ0PpTofNLYIPnWvOshdYSnCdX4f6txnoW54ptVr2129pvHbQOWx/Cqz0Gn/YkPNpQ+LNd4c32hQ91FT1Nwo+1YS9GYueNh63IgqUoxIl9Ns7r83FaX4qz+mqc1NfCE9lsb7d32nvsA9jx79uNuJlqto/bp+xzdrgT4UQ5vZxLncudAc4Q3G7oTizuwJKcVOj2X+KMNM0pdmY6c3CaXuDcC59tJTy2J+GvbYC39rKzy9nrNDjvwNv9BL7ul7BRp9l5NJxUsL9E0B4Wqjt83Mvg4Q6Ef6vAux0G3zYZnu0k+LVT+QK+hK/g52KHL+SXwPKu4tfwNfyz/EacyOr53TjbHeQP8x/C/z3Gt/AnoflChY5CV4ET+gqT4K+0E2Nwg/YK81AjPTGeq3HfMxV3Yrd75nsSpBukydIU6R5oyIelx3APs07aIG3Ffn9dOgC9cwS3X824+SJyJ7krfIjL5AG4r0iAH5Ep/17+QP4Yt5ZfyN/gBjpE6ahcovRSfq70VwYpkmIq1ytJSqoyGTZoljJXeU/5SPmj8rnytfKdck5p54309vD29f7CO8DLe1X8mjHKm+Id783Abn/YuwPn3nnq87AtTdB0oVoHnNYy4WHshmfxGU7k2Tj58sYaoycsj2mOwj1RprkEHvUhs5GtrzC2tuLhxd1ijbZjMTf1+KXjFB33qHCykd598b35q3kVo3wfXw3dv55/lf8dP1rIFJYKK3E7+gF0+BnhOtw2dvYM9EieeM963JENljzSvRin1Ribt6VQuZs8RL5fXg4fcKe8FzfxH+J28BjuBk/iPBuK8eiqcEpfJUa5CiMiKiruduOUkUqKMh6jkqXk4b6+TJmtVCrzlcXwlFcoq3GbuBY+1WbcAe3Erz0HcJv4vkJiw6k=
*/