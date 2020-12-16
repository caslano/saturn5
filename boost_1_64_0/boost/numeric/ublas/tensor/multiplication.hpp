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


#ifndef BOOST_UBLAS_TENSOR_MULTIPLICATION
#define BOOST_UBLAS_TENSOR_MULTIPLICATION

#include <cassert>

namespace boost {
namespace numeric {
namespace ublas {
namespace detail {
namespace recursive {


/** @brief Computes the tensor-times-tensor product for q contraction modes
 *
 * Implements C[i1,...,ir,j1,...,js] = sum( A[i1,...,ir+q] * B[j1,...,js+q]  )
 *
 * nc[x]         = na[phia[x]  ] for 1 <= x <= r
 * nc[r+x]       = nb[phib[x]  ] for 1 <= x <= s
 * na[phia[r+x]] = nb[phib[s+x]] for 1 <= x <= q
 *
 * @note is used in function ttt
 *
 * @param k  zero-based recursion level starting with 0
 * @param r  number of non-contraction indices of A
 * @param s  number of non-contraction indices of B
 * @param q  number of contraction indices with q > 0
 * @param phia pointer to the permutation tuple of length q+r for A
 * @param phib pointer to the permutation tuple of length q+s for B
 * @param c  pointer to the output tensor C with rank(A)=r+s
 * @param nc pointer to the extents of tensor C
 * @param wc pointer to the strides of tensor C
 * @param a  pointer to the first input tensor with rank(A)=r+q
 * @param na pointer to the extents of the first input tensor A
 * @param wa pointer to the strides of the first input tensor A
 * @param b  pointer to the second input tensor B with rank(B)=s+q
 * @param nb pointer to the extents of the second input tensor B
 * @param wb pointer to the strides of the second input tensor B
*/

template <class PointerOut, class PointerIn1, class PointerIn2, class SizeType>
void ttt(SizeType const k,
         SizeType const r, SizeType const s, SizeType const q,
         SizeType const*const phia, SizeType const*const phib,
         PointerOut c, SizeType const*const nc, SizeType const*const wc,
         PointerIn1 a, SizeType const*const na, SizeType const*const wa,
         PointerIn2 b, SizeType const*const nb, SizeType const*const wb)
{
	if(k < r)
	{
		assert(nc[k] == na[phia[k]-1]);
		for(size_t ic = 0u; ic < nc[k]; a += wa[phia[k]-1], c += wc[k], ++ic)
			ttt(k+1, r, s, q,  phia,phib,  c, nc, wc,   a, na, wa,   b, nb, wb);
	}
	else if(k < r+s)
	{
		assert(nc[k] == nb[phib[k-r]-1]);
		for(size_t ic = 0u; ic < nc[k]; b += wb[phib[k-r]-1], c += wc[k], ++ic)
			ttt(k+1, r, s, q,  phia, phib,    c, nc, wc,   a, na, wa,   b, nb, wb);
	}
	else if(k < r+s+q-1)
	{
		assert(na[phia[k-s]-1] == nb[phib[k-r]-1]);
		for(size_t ia = 0u; ia < na[phia[k-s]-1]; a += wa[phia[k-s]-1], b += wb[phib[k-r]-1], ++ia)
			ttt(k+1, r, s, q,  phia, phib,  c, nc, wc,   a, na, wa,   b, nb, wb);
	}
	else
	{
		assert(na[phia[k-s]-1] == nb[phib[k-r]-1]);
		for(size_t ia = 0u; ia < na[phia[k-s]-1]; a += wa[phia[k-s]-1], b += wb[phib[k-r]-1], ++ia)
			*c += *a * *b;
	}
}




/** @brief Computes the tensor-times-tensor product for q contraction modes
 *
 * Implements C[i1,...,ir,j1,...,js] = sum( A[i1,...,ir+q] * B[j1,...,js+q]  )
 *
 * @note no permutation tuple is used
 *
 * nc[x]   = na[x  ] for 1 <= x <= r
 * nc[r+x] = nb[x  ] for 1 <= x <= s
 * na[r+x] = nb[s+x] for 1 <= x <= q
 *
 * @note is used in function ttt
 *
 * @param k  zero-based recursion level starting with 0
 * @param r  number of non-contraction indices of A
 * @param s  number of non-contraction indices of B
 * @param q  number of contraction indices with q > 0
 * @param c  pointer to the output tensor C with rank(A)=r+s
 * @param nc pointer to the extents of tensor C
 * @param wc pointer to the strides of tensor C
 * @param a  pointer to the first input tensor with rank(A)=r+q
 * @param na pointer to the extents of the first input tensor A
 * @param wa pointer to the strides of the first input tensor A
 * @param b  pointer to the second input tensor B with rank(B)=s+q
 * @param nb pointer to the extents of the second input tensor B
 * @param wb pointer to the strides of the second input tensor B
*/

template <class PointerOut, class PointerIn1, class PointerIn2, class SizeType>
void ttt(SizeType const k,
         SizeType const r, SizeType const s, SizeType const q,
         PointerOut c, SizeType const*const nc, SizeType const*const wc,
         PointerIn1 a, SizeType const*const na, SizeType const*const wa,
         PointerIn2 b, SizeType const*const nb, SizeType const*const wb)
{
	if(k < r)
	{
		assert(nc[k] == na[k]);
		for(size_t ic = 0u; ic < nc[k]; a += wa[k], c += wc[k], ++ic)
			ttt(k+1, r, s, q,  c, nc, wc,   a, na, wa,   b, nb, wb);
	}
	else if(k < r+s)
	{
		assert(nc[k] == nb[k-r]);
		for(size_t ic = 0u; ic < nc[k]; b += wb[k-r], c += wc[k], ++ic)
			ttt(k+1, r, s, q,  c, nc, wc,   a, na, wa,   b, nb, wb);
	}
	else if(k < r+s+q-1)
	{
		assert(na[k-s] == nb[k-r]);
		for(size_t ia = 0u; ia < na[k-s]; a += wa[k-s], b += wb[k-r], ++ia)
			ttt(k+1, r, s, q,  c, nc, wc,   a, na, wa,   b, nb, wb);
	}
	else
	{
		assert(na[k-s] == nb[k-r]);
		for(size_t ia = 0u; ia < na[k-s]; a += wa[k-s], b += wb[k-r], ++ia)
			*c += *a * *b;
	}
}


/** @brief Computes the tensor-times-matrix product for the contraction mode m > 0
 *
 * Implements C[i1,i2,...,im-1,j,im+1,...,ip] = sum(A[i1,i2,...,im,...,ip] * B[j,im])
 *
 * @note is used in function ttm
 *
 * @param m  zero-based contraction mode with 0<m<p
 * @param r  zero-based recursion level starting with p-1
 * @param c  pointer to the output tensor
 * @param nc pointer to the extents of tensor c
 * @param wc pointer to the strides of tensor c
 * @param a  pointer to the first input tensor
 * @param na pointer to the extents of input tensor a
 * @param wa pointer to the strides of input tensor a
 * @param b  pointer to the second input tensor
 * @param nb pointer to the extents of input tensor b
 * @param wb pointer to the strides of input tensor b
*/

template <class PointerOut, class PointerIn1, class PointerIn2, class SizeType>
void ttm(SizeType const m,  SizeType const r,
         PointerOut c, SizeType const*const nc, SizeType const*const wc,
         PointerIn1 a, SizeType const*const na, SizeType const*const wa,
         PointerIn2 b, SizeType const*const nb, SizeType const*const wb)
{

	if(r == m) {
		ttm(m, r-1, c, nc, wc,    a, na, wa,    b, nb, wb);
	}
	else if(r == 0){
		for(auto i0 = 0ul; i0 < nc[0]; c += wc[0], a += wa[0], ++i0) {
			auto cm = c;
			auto b0 = b;
			for(auto i0 = 0ul; i0 < nc[m]; cm += wc[m], b0 += wb[0], ++i0){
				auto am = a;
				auto b1 = b0;
				for(auto i1 = 0ul; i1 < nb[1]; am += wa[m], b1 += wb[1], ++i1)
					*cm += *am * *b1;
			}
		}
	}

	else{
		for(auto i = 0ul; i < na[r]; c += wc[r], a += wa[r], ++i)
			ttm(m, r-1, c, nc, wc,    a, na, wa,    b, nb, wb);
	}
}

/** @brief Computes the tensor-times-matrix product for the contraction mode m = 0
 *
 * Implements C[j,i2,...,ip] = sum(A[i1,i2,...,ip] * B[j,i1])
 *
 * @note is used in function ttm
 *
 * @param m  zero-based contraction mode with 0<m<p
 * @param r  zero-based recursion level starting with p-1
 * @param c  pointer to the output tensor
 * @param nc pointer to the extents of tensor c
 * @param wc pointer to the strides of tensor c
 * @param a  pointer to the first input tensor
 * @param na pointer to the extents of input tensor a
 * @param wa pointer to the strides of input tensor a
 * @param b  pointer to the second input tensor
 * @param nb pointer to the extents of input tensor b
 * @param wb pointer to the strides of input tensor b
*/
template <class PointerOut, class PointerIn1, class PointerIn2, class SizeType>
void ttm0( SizeType const r,
           PointerOut c, SizeType const*const nc, SizeType const*const wc,
           PointerIn1 a, SizeType const*const na, SizeType const*const wa,
           PointerIn2 b, SizeType const*const nb, SizeType const*const wb)
{

	if(r > 1){
		for(auto i = 0ul; i < na[r]; c += wc[r], a += wa[r], ++i)
			ttm0(r-1, c, nc, wc,    a, na, wa,    b, nb, wb);
	}
	else{
		for(auto i1 = 0ul; i1 < nc[1]; c += wc[1], a += wa[1], ++i1) {
			auto cm = c;
			auto b0 = b;
			// r == m == 0
			for(auto i0 = 0ul; i0 < nc[0]; cm += wc[0], b0 += wb[0], ++i0){

				auto am = a;
				auto b1 = b0;
				for(auto i1 = 0u; i1 < nb[1]; am += wa[0], b1 += wb[1], ++i1){

					*cm += *am * *b1;
				}
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


/** @brief Computes the tensor-times-vector product for the contraction mode m > 0
 *
 * Implements C[i1,i2,...,im-1,im+1,...,ip] = sum(A[i1,i2,...,im,...,ip] * b[im])
 *
 * @note is used in function ttv
 *
 * @param m  zero-based contraction mode with 0<m<p
 * @param r  zero-based recursion level starting with p-1 for tensor A
 * @param q  zero-based recursion level starting with p-1 for tensor C
 * @param c  pointer to the output tensor
 * @param nc pointer to the extents of tensor c
 * @param wc pointer to the strides of tensor c
 * @param a  pointer to the first input tensor
 * @param na pointer to the extents of input tensor a
 * @param wa pointer to the strides of input tensor a
 * @param b  pointer to the second input tensor
*/

template <class PointerOut, class PointerIn1, class PointerIn2, class SizeType>
void ttv( SizeType const m, SizeType const r, SizeType const q,
          PointerOut c, SizeType const*const nc, SizeType const*const wc,
          PointerIn1 a, SizeType const*const na, SizeType const*const wa,
          PointerIn2 b)
{

	if(r == m) {
		ttv(m, r-1, q, c, nc, wc,    a, na, wa,    b);
	}
	else if(r == 0){
		for(auto i0 = 0u; i0 < na[0]; c += wc[0], a += wa[0], ++i0) {
			auto c1 = c; auto a1 = a; auto b1 = b;
			for(auto im = 0u; im < na[m]; a1 += wa[m], ++b1, ++im)
				*c1 += *a1 * *b1;
		}
	}
	else{
		for(auto i = 0u; i < na[r]; c += wc[q], a += wa[r], ++i)
			ttv(m, r-1, q-1, c, nc, wc,    a, na, wa,    b);
	}
}


/** @brief Computes the tensor-times-vector product for the contraction mode m = 0
 *
 * Implements C[i2,...,ip] = sum(A[i1,...,ip] * b[i1])
 *
 * @note is used in function ttv
 *
 * @param m  zero-based contraction mode with m=0
 * @param r  zero-based recursion level starting with p-1
 * @param c  pointer to the output tensor
 * @param nc pointer to the extents of tensor c
 * @param wc pointer to the strides of tensor c
 * @param a  pointer to the first input tensor
 * @param na pointer to the extents of input tensor a
 * @param wa pointer to the strides of input tensor a
 * @param b  pointer to the second input tensor
*/
template <class PointerOut, class PointerIn1, class PointerIn2, class SizeType>
void ttv0(SizeType const r,
          PointerOut c, SizeType const*const nc, SizeType const*const wc,
          PointerIn1 a, SizeType const*const na, SizeType const*const wa,
          PointerIn2 b)
{

	if(r > 1){
		for(auto i = 0u; i < na[r]; c += wc[r-1], a += wa[r], ++i)
			ttv0(r-1, c, nc, wc,    a, na, wa,    b);
	}
	else{
		for(auto i1 = 0u; i1 < na[1]; c += wc[0], a += wa[1], ++i1)
		{
			auto c1 = c; auto a1 = a; auto b1 = b;
			for(auto i0 = 0u; i0 < na[0]; a1 += wa[0], ++b1, ++i0)
				*c1 += *a1 * *b1;
		}
	}
}


/** @brief Computes the matrix-times-vector product
 *
 * Implements C[i1] = sum(A[i1,i2] * b[i2]) or C[i2] = sum(A[i1,i2] * b[i1])
 *
 * @note is used in function ttv
 *
 * @param[in]  m  zero-based contraction mode with m=0 or m=1
 * @param[out] c  pointer to the output tensor C
 * @param[in]  nc pointer to the extents of tensor C
 * @param[in]  wc pointer to the strides of tensor C
 * @param[in]  a  pointer to the first input tensor A
 * @param[in]  na pointer to the extents of input tensor A
 * @param[in]  wa pointer to the strides of input tensor A
 * @param[in]  b  pointer to the second input tensor B
*/
template <class PointerOut, class PointerIn1, class PointerIn2, class SizeType>
void mtv(SizeType const m,
         PointerOut c, SizeType const*const   , SizeType const*const wc,
         PointerIn1 a, SizeType const*const na, SizeType const*const wa,
         PointerIn2 b)
{
	// decides whether matrix multiplied with vector or vector multiplied with matrix
	const auto o = (m == 0) ? 1 : 0;

	for(auto io = 0u; io < na[o]; c += wc[o], a += wa[o], ++io) {
		auto c1 = c; auto a1 = a; auto b1 = b;
		for(auto im = 0u; im < na[m]; a1 += wa[m], ++b1, ++im)
			*c1 += *a1 * *b1;
	}
}


/** @brief Computes the matrix-times-matrix product
 *
 * Implements C[i1,i3] = sum(A[i1,i2] * B[i2,i3])
 *
 * @note is used in function ttm
 *
 * @param[out] c  pointer to the output tensor C
 * @param[in]  nc pointer to the extents of tensor C
 * @param[in]  wc pointer to the strides of tensor C
 * @param[in]  a  pointer to the first input tensor A
 * @param[in]  na pointer to the extents of input tensor A
 * @param[in]  wa pointer to the strides of input tensor A
 * @param[in]  b  pointer to the second input tensor B
 * @param[in]  nb pointer to the extents of input tensor B
 * @param[in]  wb pointer to the strides of input tensor B
*/
template <class PointerOut, class PointerIn1, class PointerIn2, class SizeType>
void mtm(PointerOut c, SizeType const*const nc, SizeType const*const wc,
         PointerIn1 a, SizeType const*const na, SizeType const*const wa,
         PointerIn2 b, SizeType const*const nb, SizeType const*const wb)
{

	// C(i,j) = A(i,k) * B(k,j)

	assert(nc[0] == na[0]);
	assert(nc[1] == nb[1]);
	assert(na[1] == nb[0]);

	auto cj = c; auto bj = b;
	for(auto j = 0u; j < nc[1]; cj += wc[1], bj += wb[1], ++j) {

		auto bk = bj; auto ak = a;
		for(auto k = 0u; k < na[1]; ak += wa[1], bk += wb[0], ++k) {

			auto ci = cj; auto ai = ak;
			for(auto i = 0u; i < na[0]; ai += wa[0], ci += wc[0], ++i){
				*ci += *ai * *bk;
			}

		}

	}
}



/** @brief Computes the inner product of two tensors
 *
 * Implements c = sum(A[i1,i2,...,ip] * B[i1,i2,...,ip])
 *
 * @note is used in function inner
 *
 * @param r   zero-based recursion level starting with p-1
 * @param n   pointer to the extents of input or output tensor
 * @param a   pointer to the first input tensor
 * @param wa  pointer to the strides of input tensor a
 * @param b   pointer to the second input tensor
 * @param wb  pointer to the strides of tensor b
 * @param v   previously computed value (start with v = 0).
 * @return    inner product of two tensors.
*/
template <class PointerIn1, class PointerIn2, class value_t, class SizeType>
value_t inner(SizeType const r, SizeType const*const n,
              PointerIn1  a, SizeType const*const wa,
              PointerIn2  b, SizeType const*const wb,
              value_t v)
{
	if(r == 0)
		for(auto i0 = 0u; i0 < n[0]; a += wa[0], b += wb[0], ++i0)
			v += *a * *b;
	else
		for(auto ir = 0u; ir < n[r]; a += wa[r], b += wb[r], ++ir)
			v = inner(r-1, n,   a, wa,    b, wb, v);
	return v;
}


template <class PointerOut, class PointerIn1, class PointerIn2, class SizeType>
void outer_2x2(SizeType const pa,
               PointerOut c, SizeType const*const   , SizeType const*const wc,
               PointerIn1 a, SizeType const*const na, SizeType const*const wa,
               PointerIn2 b, SizeType const*const nb, SizeType const*const wb)
{
	//	assert(rc == 3);
	//	assert(ra == 1);
	//	assert(rb == 1);

	for(auto ib1 = 0u; ib1 < nb[1]; b += wb[1], c += wc[pa+1], ++ib1) {
		auto c2 = c;
		auto b0 = b;
		for(auto ib0 = 0u; ib0 < nb[0]; b0 += wb[0], c2 += wc[pa], ++ib0) {
			const auto b = *b0;
			auto c1 = c2;
			auto a1 = a;
			for(auto ia1 = 0u; ia1 < na[1]; a1 += wa[1], c1 += wc[1], ++ia1) {
				auto a0 = a1;
				auto c0 = c1;
				for(SizeType ia0 = 0u; ia0 < na[0]; a0 += wa[0], c0 += wc[0], ++ia0)
					*c0 = *a0 * b;
			}
		}
	}
}

/** @brief Computes the outer product of two tensors
 *
 * Implements C[i1,...,ip,j1,...,jq] = A[i1,i2,...,ip] * B[j1,j2,...,jq]
 *
 * @note called by outer
 *
 *
 * @param[in]  pa number of dimensions (rank) of the first input tensor A with pa > 0
 *
 * @param[in]  rc recursion level for C that starts with pc-1
 * @param[out] c  pointer to the output tensor
 * @param[in]  nc pointer to the extents of output tensor c
 * @param[in]  wc pointer to the strides of output tensor c
 *
 * @param[in]  ra recursion level for A that starts with pa-1
 * @param[in]  a  pointer to the first input tensor
 * @param[in]  na pointer to the extents of the first input tensor a
 * @param[in]  wa pointer to the strides of the first input tensor a
 *
 * @param[in]  rb recursion level for B that starts with pb-1
 * @param[in]  b  pointer to the second input tensor
 * @param[in]  nb pointer to the extents of the second input tensor b
 * @param[in]  wb pointer to the strides of the second input tensor b
*/
template<class PointerOut, class PointerIn1, class PointerIn2, class SizeType>
void outer(SizeType const pa,
           SizeType const rc, PointerOut c, SizeType const*const nc, SizeType const*const wc,
           SizeType const ra, PointerIn1 a, SizeType const*const na, SizeType const*const wa,
           SizeType const rb, PointerIn2 b, SizeType const*const nb, SizeType const*const wb)
{
	if(rb > 1)
		for(auto ib = 0u; ib < nb[rb]; b += wb[rb], c += wc[rc], ++ib)
			outer(pa, rc-1, c, nc, wc,    ra, a, na, wa,    rb-1, b, nb, wb);
	else if(ra > 1)
		for(auto ia = 0u; ia < na[ra]; a += wa[ra], c += wc[ra], ++ia)
			outer(pa, rc-1, c, nc, wc,   ra-1, a, na, wa,   rb, b, nb, wb);
	else
		outer_2x2(pa, c, nc, wc,   a, na, wa,    b, nb, wb); //assert(ra==1 && rb==1 && rc==3);
}




/** @brief Computes the outer product with permutation tuples
 *
 * Implements C[i1,...,ir,j1,...,js] = sum( A[i1,...,ir] * B[j1,...,js]  )
 *
 * nc[x]         = na[phia[x]] for 1 <= x <= r
 * nc[r+x]       = nb[phib[x]] for 1 <= x <= s
 *
 * @note maybe called by ttt function
 *
 * @param k  zero-based recursion level starting with 0
 * @param r  number of non-contraction indices of A
 * @param s  number of non-contraction indices of B
 * @param phia pointer to the permutation tuple of length r for A
 * @param phib pointer to the permutation tuple of length s for B
 * @param c  pointer to the output tensor C with rank(A)=r+s
 * @param nc pointer to the extents of tensor C
 * @param wc pointer to the strides of tensor C
 * @param a  pointer to the first input tensor with rank(A)=r
 * @param na pointer to the extents of the first input tensor A
 * @param wa pointer to the strides of the first input tensor A
 * @param b  pointer to the second input tensor B with rank(B)=s
 * @param nb pointer to the extents of the second input tensor B
 * @param wb pointer to the strides of the second input tensor B
*/

template <class PointerOut, class PointerIn1, class PointerIn2, class SizeType>
void outer(SizeType const k,
           SizeType const r, SizeType const s,
           SizeType const*const phia, SizeType const*const phib,
           PointerOut c, SizeType const*const nc, SizeType const*const wc,
           PointerIn1 a, SizeType const*const na, SizeType const*const wa,
           PointerIn2 b, SizeType const*const nb, SizeType const*const wb)
{
	if(k < r)
	{
		assert(nc[k] == na[phia[k]-1]);
		for(size_t ic = 0u; ic < nc[k]; a += wa[phia[k]-1], c += wc[k], ++ic)
			outer(k+1, r, s,   phia,phib,  c, nc, wc,   a, na, wa,   b, nb, wb);
	}
	else if(k < r+s-1)
	{
		assert(nc[k] == nb[phib[k-r]-1]);
		for(size_t ic = 0u; ic < nc[k]; b += wb[phib[k-r]-1], c += wc[k], ++ic)
			outer(k+1, r, s, phia, phib,    c, nc, wc,   a, na, wa,   b, nb, wb);
	}
	else
	{
		assert(nc[k] == nb[phib[k-r]-1]);
		for(size_t ic = 0u; ic < nc[k]; b += wb[phib[k-r]-1], c += wc[k], ++ic)
			*c = *a * *b;
	}
}


} // namespace recursive
} // namespace detail
} // namespace ublas
} // namespace numeric
} // namespace boost




//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


#include <stdexcept>

namespace boost {
namespace numeric {
namespace ublas {

/** @brief Computes the tensor-times-vector product
 *
 * Implements
 *   C[i1,i2,...,im-1,im+1,...,ip] = sum(A[i1,i2,...,im,...,ip] * b[im]) for m>1 and
 *   C[i2,...,ip]                  = sum(A[i1,...,ip]           * b[i1]) for m=1
 *
 * @note calls detail::ttv, detail::ttv0 or detail::mtv
 *
 * @param[in]  m  contraction mode with 0 < m <= p
 * @param[in]  p  number of dimensions (rank) of the first input tensor with p > 0
 * @param[out] c  pointer to the output tensor with rank p-1
 * @param[in]  nc pointer to the extents of tensor c
 * @param[in]  wc pointer to the strides of tensor c
 * @param[in]  a  pointer to the first input tensor
 * @param[in]  na pointer to the extents of input tensor a
 * @param[in]  wa pointer to the strides of input tensor a
 * @param[in]  b  pointer to the second input tensor
 * @param[in]  nb pointer to the extents of input tensor b
 * @param[in]  wb pointer to the strides of input tensor b
*/
template <class PointerOut, class PointerIn1, class PointerIn2, class SizeType>
void ttv(SizeType const m, SizeType const p,
         PointerOut c,       SizeType const*const nc, SizeType const*const wc,
         const PointerIn1 a, SizeType const*const na, SizeType const*const wa,
         const PointerIn2 b, SizeType const*const nb, SizeType const*const wb)
{
	static_assert( std::is_pointer<PointerOut>::value & std::is_pointer<PointerIn1>::value & std::is_pointer<PointerIn2>::value,
	               "Static error in boost::numeric::ublas::ttv: Argument types for pointers are not pointer types.");

	if( m == 0)
		throw std::length_error("Error in boost::numeric::ublas::ttv: Contraction mode must be greater than zero.");

	if( p < m )
		throw std::length_error("Error in boost::numeric::ublas::ttv: Rank must be greater equal the modus.");

	if( p == 0)
		throw std::length_error("Error in boost::numeric::ublas::ttv: Rank must be greater than zero.");

	if(c == nullptr || a == nullptr || b == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::ttv: Pointers shall not be null pointers.");

	for(auto i = 0u; i < m-1; ++i)
		if(na[i] != nc[i])
			throw std::length_error("Error in boost::numeric::ublas::ttv: Extents (except of dimension mode) of A and C must be equal.");

	for(auto i = m; i < p; ++i)
		if(na[i] != nc[i-1])
			throw std::length_error("Error in boost::numeric::ublas::ttv: Extents (except of dimension mode) of A and C must be equal.");

	const auto max = std::max(nb[0], nb[1]);
	if(  na[m-1] != max)
		throw std::length_error("Error in boost::numeric::ublas::ttv: Extent of dimension mode of A and b must be equal.");


	if((m != 1) && (p > 2))
		detail::recursive::ttv(m-1, p-1, p-2, c, nc, wc,    a, na, wa,   b);
	else if ((m == 1) && (p > 2))
		detail::recursive::ttv0(p-1, c, nc, wc,  a, na, wa,   b);
	else if( p == 2 )
		detail::recursive::mtv(m-1, c, nc, wc,  a, na, wa,   b);
	else /*if( p == 1 )*/{
		auto v = std::remove_pointer_t<std::remove_cv_t<PointerOut>>{};
		*c = detail::recursive::inner(SizeType(0), na, a, wa, b, wb, v);
	}

}



/** @brief Computes the tensor-times-matrix product
 *
 * Implements
 *   C[i1,i2,...,im-1,j,im+1,...,ip] = sum(A[i1,i2,...,im,...,ip] * B[j,im]) for m>1 and
 *   C[j,i2,...,ip]                  = sum(A[i1,i2,...,ip]        * B[j,i1]) for m=1
 *
 * @note calls detail::ttm or detail::ttm0
 *
 * @param[in]  m  contraction mode with 0 < m <= p
 * @param[in]  p  number of dimensions (rank) of the first input tensor with p > 0
 * @param[out] c  pointer to the output tensor with rank p-1
 * @param[in]  nc pointer to the extents of tensor c
 * @param[in]  wc pointer to the strides of tensor c
 * @param[in]  a  pointer to the first input tensor
 * @param[in]  na pointer to the extents of input tensor a
 * @param[in]  wa pointer to the strides of input tensor a
 * @param[in]  b  pointer to the second input tensor
 * @param[in]  nb pointer to the extents of input tensor b
 * @param[in]  wb pointer to the strides of input tensor b
*/

template <class PointerIn1, class PointerIn2, class PointerOut, class SizeType>
void ttm(SizeType const m, SizeType const p,
         PointerOut c,       SizeType const*const nc, SizeType const*const wc,
         const PointerIn1 a, SizeType const*const na, SizeType const*const wa,
         const PointerIn2 b, SizeType const*const nb, SizeType const*const wb)
{

	static_assert( std::is_pointer<PointerOut>::value & std::is_pointer<PointerIn1>::value & std::is_pointer<PointerIn2>::value,
	               "Static error in boost::numeric::ublas::ttm: Argument types for pointers are not pointer types.");

	if( m == 0 )
		throw std::length_error("Error in boost::numeric::ublas::ttm: Contraction mode must be greater than zero.");

	if( p < m )
		throw std::length_error("Error in boost::numeric::ublas::ttm: Rank must be greater equal than the specified mode.");

	if( p == 0)
		throw std::length_error("Error in boost::numeric::ublas::ttm:Rank must be greater than zero.");

	if(c == nullptr || a == nullptr || b == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::ttm: Pointers shall not be null pointers.");

	for(auto i = 0u; i < m-1; ++i)
		if(na[i] != nc[i])
			throw std::length_error("Error in boost::numeric::ublas::ttm: Extents (except of dimension mode) of A and C must be equal.");

	for(auto i = m; i < p; ++i)
		if(na[i] != nc[i])
			throw std::length_error("Error in boost::numeric::ublas::ttm: Extents (except of dimension mode) of A and C must be equal.");

	if(na[m-1] != nb[1])
		throw std::length_error("Error in boost::numeric::ublas::ttm: 2nd Extent of B and M-th Extent of A must be the equal.");

	if(nc[m-1] != nb[0])
		throw std::length_error("Error in boost::numeric::ublas::ttm: 1nd Extent of B and M-th Extent of C must be the equal.");

	if ( m != 1 )
		detail::recursive::ttm (m-1, p-1, c, nc, wc,    a, na, wa,   b, nb, wb);
	else /*if (m == 1 && p >  2)*/
		detail::recursive::ttm0(     p-1, c, nc, wc,    a, na, wa,   b, nb, wb);

}


/** @brief Computes the tensor-times-tensor product
 *
 * Implements C[i1,...,ir,j1,...,js] = sum( A[i1,...,ir+q] * B[j1,...,js+q]  )
 *
 * @note calls detail::recursive::ttt or ttm or ttv or inner or outer
 *
 * nc[x]         = na[phia[x]  ] for 1 <= x <= r
 * nc[r+x]       = nb[phib[x]  ] for 1 <= x <= s
 * na[phia[r+x]] = nb[phib[s+x]] for 1 <= x <= q
 *
 * @param[in]  pa number of dimensions (rank) of the first input tensor a with pa > 0
 * @param[in]  pb number of dimensions (rank) of the second input tensor b with pb > 0
 * @param[in]	 q  number of contraction dimensions with pa >= q and pb >= q and q >= 0
 * @param[in]	 phia pointer to a permutation tuple for the first input tensor a
 * @param[in]	 phib pointer to a permutation tuple for the second input tensor b
 * @param[out] c  pointer to the output tensor with rank p-1
 * @param[in]  nc pointer to the extents of tensor c
 * @param[in]  wc pointer to the strides of tensor c
 * @param[in]  a  pointer to the first input tensor
 * @param[in]  na pointer to the extents of input tensor a
 * @param[in]  wa pointer to the strides of input tensor a
 * @param[in]  b  pointer to the second input tensor
 * @param[in]  nb pointer to the extents of input tensor b
 * @param[in]  wb pointer to the strides of input tensor b
*/

template <class PointerIn1, class PointerIn2, class PointerOut, class SizeType>
void ttt(SizeType const pa, SizeType const pb, SizeType const q,
         SizeType const*const phia, SizeType const*const phib,
         PointerOut c, SizeType const*const nc, SizeType const*const wc,
         PointerIn1 a, SizeType const*const na, SizeType const*const wa,
         PointerIn2 b, SizeType const*const nb, SizeType const*const wb)
{
	static_assert( std::is_pointer<PointerOut>::value & std::is_pointer<PointerIn1>::value & std::is_pointer<PointerIn2>::value,
	               "Static error in boost::numeric::ublas::ttm: Argument types for pointers are not pointer types.");

	if( pa == 0 || pb == 0)
		throw std::length_error("Error in boost::numeric::ublas::ttt: tensor order must be greater zero.");

	if( q > pa && q > pb)
		throw std::length_error("Error in boost::numeric::ublas::ttt: number of contraction must be smaller than or equal to the tensor order.");


	SizeType const r = pa - q;
	SizeType const s = pb - q;

	if(c == nullptr || a == nullptr || b == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::ttm: Pointers shall not be null pointers.");

	for(auto i = 0ul; i < r; ++i)
		if( na[phia[i]-1] != nc[i] )
			throw std::length_error("Error in boost::numeric::ublas::ttt: dimensions of lhs and res tensor not correct.");

	for(auto i = 0ul; i < s; ++i)
		if( nb[phib[i]-1] != nc[r+i] )
			throw std::length_error("Error in boost::numeric::ublas::ttt: dimensions of rhs and res not correct.");

	for(auto i = 0ul; i < q; ++i)
		if( nb[phib[s+i]-1] != na[phia[r+i]-1] )
			throw std::length_error("Error in boost::numeric::ublas::ttt: dimensions of lhs and rhs not correct.");


	if(q == 0ul)
		detail::recursive::outer(SizeType{0},r,s,  phia,phib, c,nc,wc, a,na,wa, b,nb,wb);
	else
		detail::recursive::ttt(SizeType{0},r,s,q,  phia,phib, c,nc,wc, a,na,wa, b,nb,wb);
}



/** @brief Computes the tensor-times-tensor product
 *
 * Implements C[i1,...,ir,j1,...,js] = sum( A[i1,...,ir+q] * B[j1,...,js+q]  )
 *
 * @note calls detail::recursive::ttt or ttm or ttv or inner or outer
 *
 * nc[x]   = na[x  ] for 1 <= x <= r
 * nc[r+x] = nb[x  ] for 1 <= x <= s
 * na[r+x] = nb[s+x] for 1 <= x <= q
 *
 * @param[in]  pa number of dimensions (rank) of the first input tensor a with pa > 0
 * @param[in]  pb number of dimensions (rank) of the second input tensor b with pb > 0
 * @param[in]	 q  number of contraction dimensions with pa >= q and pb >= q and q >= 0
 * @param[out] c  pointer to the output tensor with rank p-1
 * @param[in]  nc pointer to the extents of tensor c
 * @param[in]  wc pointer to the strides of tensor c
 * @param[in]  a  pointer to the first input tensor
 * @param[in]  na pointer to the extents of input tensor a
 * @param[in]  wa pointer to the strides of input tensor a
 * @param[in]  b  pointer to the second input tensor
 * @param[in]  nb pointer to the extents of input tensor b
 * @param[in]  wb pointer to the strides of input tensor b
*/

template <class PointerIn1, class PointerIn2, class PointerOut, class SizeType>
void ttt(SizeType const pa, SizeType const pb, SizeType const q,
         PointerOut c, SizeType const*const nc, SizeType const*const wc,
         PointerIn1 a, SizeType const*const na, SizeType const*const wa,
         PointerIn2 b, SizeType const*const nb, SizeType const*const wb)
{
	static_assert( std::is_pointer<PointerOut>::value & std::is_pointer<PointerIn1>::value & std::is_pointer<PointerIn2>::value,
	               "Static error in boost::numeric::ublas::ttm: Argument types for pointers are not pointer types.");

	if( pa == 0 || pb == 0)
		throw std::length_error("Error in boost::numeric::ublas::ttt: tensor order must be greater zero.");

	if( q > pa && q > pb)
		throw std::length_error("Error in boost::numeric::ublas::ttt: number of contraction must be smaller than or equal to the tensor order.");


	SizeType const r  = pa - q;
	SizeType const s  = pb - q;
	SizeType const pc = r+s;

	if(c == nullptr || a == nullptr || b == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::ttm: Pointers shall not be null pointers.");

	for(auto i = 0ul; i < r; ++i)
		if( na[i] != nc[i] )
			throw std::length_error("Error in boost::numeric::ublas::ttt: dimensions of lhs and res tensor not correct.");

	for(auto i = 0ul; i < s; ++i)
		if( nb[i] != nc[r+i] )
			throw std::length_error("Error in boost::numeric::ublas::ttt: dimensions of rhs and res not correct.");

	for(auto i = 0ul; i < q; ++i)
		if( nb[s+i] != na[r+i] )
			throw std::length_error("Error in boost::numeric::ublas::ttt: dimensions of lhs and rhs not correct.");

	using value_type = std::decay_t<decltype(*c)>;



	if(q == 0ul)
		detail::recursive::outer(pa, pc-1, c,nc,wc, pa-1, a,na,wa, pb-1, b,nb,wb);
	else if(r == 0ul && s == 0ul)
		*c = detail::recursive::inner(q-1, na, a,wa,  b,wb, value_type(0) );
	else
		detail::recursive::ttt(SizeType{0},r,s,q, c,nc,wc, a,na,wa, b,nb,wb);
}


/** @brief Computes the inner product of two tensors
 *
 * Implements c = sum(A[i1,i2,...,ip] * B[i1,i2,...,ip])
 *
 * @note calls detail::inner
 *
 * @param[in] p  number of dimensions (rank) of the first input tensor with p > 0
 * @param[in] n  pointer to the extents of input or output tensor
 * @param[in] a  pointer to the first input tensor
 * @param[in] wa pointer to the strides of input tensor a
 * @param[in] b  pointer to the second input tensor
 * @param[in] wb pointer to the strides of input tensor b
 * @param[in] v  inital value
 *
 * @return   inner product of two tensors.
*/
template <class PointerIn1, class PointerIn2, class value_t, class SizeType>
auto inner(const SizeType    p, SizeType const*const n,
           const PointerIn1  a, SizeType const*const wa,
           const PointerIn2  b, SizeType const*const wb,
           value_t v)
{
	static_assert( std::is_pointer<PointerIn1>::value && std::is_pointer<PointerIn2>::value,
	               "Static error in boost::numeric::ublas::inner: Argument types for pointers must be pointer types.");
	if(p<2)
		throw std::length_error("Error in boost::numeric::ublas::inner: Rank must be greater than zero.");
	if(a == nullptr || b == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::inner: Pointers shall not be null pointers.");

	return detail::recursive::inner(p-1, n, a, wa, b, wb, v);

}


/** @brief Computes the outer product of two tensors
 *
 * Implements C[i1,...,ip,j1,...,jq] = A[i1,i2,...,ip] * B[j1,j2,...,jq]
 *
 * @note calls detail::outer
 *
 * @param[out] c  pointer to the output tensor
 * @param[in]  pc number of dimensions (rank) of the output tensor c with pc > 0
 * @param[in]  nc pointer to the extents of output tensor c
 * @param[in]  wc pointer to the strides of output tensor c
 * @param[in]  a  pointer to the first input tensor
 * @param[in]  pa number of dimensions (rank) of the first input tensor a with pa > 0
 * @param[in]  na pointer to the extents of the first input tensor a
 * @param[in]  wa pointer to the strides of the first input tensor a
 * @param[in]  b  pointer to the second input tensor
 * @param[in]  pb number of dimensions (rank) of the second input tensor b with pb > 0
 * @param[in]  nb pointer to the extents of the second input tensor b
 * @param[in]  wb pointer to the strides of the second input tensor b
*/
template <class PointerOut, class PointerIn1, class PointerIn2, class SizeType>
void outer(PointerOut c,       SizeType const pc, SizeType const*const nc, SizeType const*const wc,
           const PointerIn1 a, SizeType const pa, SizeType const*const na, SizeType const*const wa,
           const PointerIn2 b, SizeType const pb, SizeType const*const nb, SizeType const*const wb)
{
	static_assert( std::is_pointer<PointerIn1>::value & std::is_pointer<PointerIn2>::value & std::is_pointer<PointerOut>::value,
	               "Static error in boost::numeric::ublas::outer: argument types for pointers must be pointer types.");
	if(pa < 2u || pb < 2u)
		throw std::length_error("Error in boost::numeric::ublas::outer: number of extents of lhs and rhs tensor must be equal or greater than two.");
	if((pa + pb) != pc)
		throw std::length_error("Error in boost::numeric::ublas::outer: number of extents of lhs plus rhs tensor must be equal to the number of extents of C.");
	if(a == nullptr || b == nullptr || c == nullptr)
		throw std::length_error("Error in boost::numeric::ublas::outer: pointers shall not be null pointers.");

	detail::recursive::outer(pa, pc-1, c, nc, wc,   pa-1, a, na, wa,   pb-1, b, nb, wb);

}




}
}
}

#endif

/* multiplication.hpp
N/TlZDtmrMOktfKnyJxCBrpZP/p4qiRHw7v5UuHp2gK0/bTiuOoJB5qEj6cX5enjIdp6hpUXCnsMKtd1ZjGOUSzyzirGM4rFMs+28MxLrnmZ54zAwRKpTZ47Ei82GE2ksFzUed4IXGRR2edbeDgOJeLQBVmfH0ykaM35BRYejVVsZEc9FxbHsTjRzi6Cs7xLSV6ffrEFw7XhtPBR1OEljpxB2JDHOib36VJHjjE4iT52mSMvo0FpWNbljjj8qsBcTe+HV9g5xvYc6TvxShvP+I4VsbnKgQMqMP/VDhi9c5ltlMD2cY2dQ1+BsbQxwPAx61oHLrkGk6R+jQ03WP0Uq+uc+UOi7q4vhqcLerxvsHDYemsqE/2/0YLT+mnEbrJg4JfeNm92xNT+DNl2iyPOwgZTQrLtVguHjWVNEHxRz7c540aborJut/OMeqay7rBxzLG804YbsRTxuMvCoXEVsbsJs+wfQuweAzP2DtHe1XsFFo3FtAzfl3qfLovHm7CfcT33k9yyxwjb4QMSxiautA660LcjTNmgxtPwhQxfPdgOH5S4OFAUIQu/H5L4fG9BOl5I8v0gD+tYEnTgdkbascnj+khRHFbxA4npeNTEwa1ZJh2P2XFZB9r4OHEs+50Qe0LHIHuObywSvj1JGN8HxUd00WaeIsy+R4rX3dOEc41c3zMmmZitcuxZwqjuxOiAup4jjPZSYTt4nmRi/7Gw6wWSF9t7/CLhlv1XWM5LBpYV+2ZfJplt3xXpe0XGSZ0o61Uds++nek3G2GQpyloQz/e6jqVhSErFYZP4XLGf+w0dK2REOW9KMn2xPc113iLM2LPF283bunx+Jp3FwYe1mSGoxGwimkTOOwYH9i7zXwYtZBgdIkb2vEsceU/geyTj30/GxgXIhja9L+MYAG7TBzY5buFNs+m+8PVDmWMED8fEj0yYccEFfw6k84moKP9jmcdnxKj7E7NcY9vioc8j9qkNg+93svszwpz3jnHO5zJH/CxDXO9TWMYXEqdJ343D8y+SMaMaaDbCbfxS4rAzG09Fv/hKxmAYUKO5BfAjrv3xHMe/lnDTnJDK/8aEQ6scgMItOr41OKb9IcK/7+x4Ttj3vcDs++IQ/8GG6yoQ/9EBz0LfSQ9x/T+Z8EI2ayjAtvOzHTdtaxZx+MWBx/pQFPsH5/xqcBzuy/DvpN8Mzkj3blCfUmLjiu9fvZ+XGBz6kREe81Jdbr+HUuaAqbOmNE6F38yE35nlX8fx+djPy2VuP393wihJRtupNfGugiV0zHa/BfOO1nH7HsEKCcOuhg2S9xXBGWPnGI2WbFjSytGN5DaMlXFjWyjmHSdhpmsQKn8pG26/Rlla59jugfD3QMh4Fl6XQP2k0pDT/bnoIPyLeapMWL8+n6/W5U73Urg9NTrH+T5KrYTrIzZevbNxlE2GuJ7xEo+uq6ivcfsnWHE+WKKdyzpiYs85z7+cxLHu315exvjbU0zjwEQ7Ln7iG3WvIOHWd4+sKGEik+hfK+kY3U8JcPnKVvkAt3MVq7yQo6tTjtfZcR4Jwlc140YV0HxpNcIte1rRptUNTPxKNsZ+DUNu3+ZH5a6pcyz3Tghfi3Db/lXC17bjeBszSfP0dSw41S3ava6MzYP+QPJJJnm/fg20HsnZdRubucSg6w04zPnWl3nw8p040ESZ9QKDmxV9Wj9sjeTyBkNOlyRcvoEuz6nsZ8eF342GnPGN8ZDyNRk4NXteJ5NJzvfwGl98rKrFHGtD4rDrTyFrJhkb1+ZSGVNIJnwU3I1IjmMJxWRjQ6bPjkRcN3HA1GhfX1YbZn/qY85UB55eNpUzTeewhiiuTXjMNjVjtmufzQinsUg=
*/