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


#ifndef BOOST_UBLAS_TENSOR_FUNCTIONS_HPP
#define BOOST_UBLAS_TENSOR_FUNCTIONS_HPP


#include <stdexcept>
#include <vector>
#include <algorithm>
#include <numeric>


#include "multiplication.hpp"
#include "algorithms.hpp"
#include "expression.hpp"
#include "expression_evaluation.hpp"
#include "storage_traits.hpp"

namespace boost {
namespace numeric {
namespace ublas {

template<class Value, class Format, class Allocator>
class tensor;

template<class Value, class Format, class Allocator>
class matrix;

template<class Value, class Allocator>
class vector;




/** @brief Computes the m-mode tensor-times-vector product
 *
 * Implements C[i1,...,im-1,im+1,...,ip] = A[i1,i2,...,ip] * b[im]
 *
 * @note calls ublas::ttv
 *
 * @param[in] m contraction dimension with 1 <= m <= p
 * @param[in] a tensor object A with order p
 * @param[in] b vector object B
 *
 * @returns tensor object C with order p-1, the same storage format and allocator type as A
*/
template<class V, class F, class A1, class A2>
auto prod(tensor<V,F,A1> const& a, vector<V,A2> const& b, const std::size_t m)
{

	using tensor_type  = tensor<V,F,A1>;
	using extents_type = typename tensor_type::extents_type;
	using ebase_type   = typename extents_type::base_type;
	using value_type   = typename tensor_type::value_type;
	using size_type = typename extents_type::value_type;

	auto const p = std::size_t(a.rank());
	
	if( m == 0)
		throw std::length_error("error in boost::numeric::ublas::prod(ttv): contraction mode must be greater than zero.");

	if( p < m )
		throw std::length_error("error in boost::numeric::ublas::prod(ttv): rank of tensor must be greater than or equal to the modus.");

	if( p == 0)
		throw std::length_error("error in boost::numeric::ublas::prod(ttv): rank of tensor must be greater than zero.");

	if( a.empty() )
		throw std::length_error("error in boost::numeric::ublas::prod(ttv): first argument tensor should not be empty.");

	if( b.size() == 0)
		throw std::length_error("error in boost::numeric::ublas::prod(ttv): second argument vector should not be empty.");


	auto nc = ebase_type(std::max(p-1, size_type(2)) , size_type(1));
	auto nb = ebase_type{b.size(),1};


	for(auto i = 0u, j = 0u; i < p; ++i)
		if(i != m-1)
			nc[j++] = a.extents().at(i);

	auto c = tensor_type(extents_type(nc),value_type{});

	auto bb = &(b(0));

	ttv(m, p,
	    c.data(), c.extents().data(), c.strides().data(),
	    a.data(), a.extents().data(), a.strides().data(),
	    bb, nb.data(), nb.data());


	return c;
}



/** @brief Computes the m-mode tensor-times-matrix product
 *
 * Implements C[i1,...,im-1,j,im+1,...,ip] = A[i1,i2,...,ip] * B[j,im]
 *
 * @note calls ublas::ttm
 *
 * @param[in] a tensor object A with order p
 * @param[in] b vector object B
 * @param[in] m contraction dimension with 1 <= m <= p
 *
 * @returns tensor object C with order p, the same storage format and allocator type as A
*/
template<class V, class F, class A1, class A2>
auto prod(tensor<V,F,A1> const& a, matrix<V,F,A2> const& b, const std::size_t m)
{

	using tensor_type  = tensor<V,F,A1>;
	using extents_type = typename tensor_type::extents_type;
	using strides_type = typename tensor_type::strides_type;
	using value_type   = typename tensor_type::value_type;


	auto const p = a.rank();

	if( m == 0)
		throw std::length_error("error in boost::numeric::ublas::prod(ttm): contraction mode must be greater than zero.");

	if( p < m || m > a.extents().size())
		throw std::length_error("error in boost::numeric::ublas::prod(ttm): rank of the tensor must be greater equal the modus.");

	if( p == 0)
		throw std::length_error("error in boost::numeric::ublas::prod(ttm): rank of the tensor must be greater than zero.");

	if( a.empty() )
		throw std::length_error("error in boost::numeric::ublas::prod(ttm): first argument tensor should not be empty.");

	if( b.size1()*b.size2() == 0)
		throw std::length_error("error in boost::numeric::ublas::prod(ttm): second argument matrix should not be empty.");


	auto nc = a.extents().base();
	auto nb = extents_type {b.size1(),b.size2()};
	auto wb = strides_type (nb);

	nc[m-1] = nb[0];

	auto c = tensor_type(extents_type(nc),value_type{});

	auto bb = &(b(0,0));

	ttm(m, p,
	    c.data(), c.extents().data(), c.strides().data(),
	    a.data(), a.extents().data(), a.strides().data(),
	    bb, nb.data(), wb.data());


	return c;
}




/** @brief Computes the q-mode tensor-times-tensor product
 *
 * Implements C[i1,...,ir,j1,...,js] = sum( A[i1,...,ir+q] * B[j1,...,js+q]  )
 *
 * @note calls ublas::ttt
 *
 * na[phia[x]] = nb[phib[x]] for 1 <= x <= q
 *
 * @param[in]	 phia one-based permutation tuple of length q for the first input tensor a
 * @param[in]	 phib one-based permutation tuple of length q for the second input tensor b
 * @param[in]  a  left-hand side tensor with order r+q
 * @param[in]  b  right-hand side tensor with order s+q
 * @result     tensor with order r+s
*/
template<class V, class F, class A1, class A2>
auto prod(tensor<V,F,A1> const& a, tensor<V,F,A2> const& b,
          std::vector<std::size_t> const& phia, std::vector<std::size_t> const& phib)
{

	using tensor_type  = tensor<V,F,A1>;
	using extents_type = typename tensor_type::extents_type;
	using value_type   = typename tensor_type::value_type;
	using size_type = typename extents_type::value_type;

	auto const pa = a.rank();
	auto const pb = b.rank();

	auto const q  = size_type(phia.size());

	if(pa == 0ul)
		throw std::runtime_error("error in ublas::prod: order of left-hand side tensor must be greater than 0.");
	if(pb == 0ul)
		throw std::runtime_error("error in ublas::prod: order of right-hand side tensor must be greater than 0.");
	if(pa < q)
		throw std::runtime_error("error in ublas::prod: number of contraction dimensions cannot be greater than the order of the left-hand side tensor.");
	if(pb < q)
		throw std::runtime_error("error in ublas::prod: number of contraction dimensions cannot be greater than the order of the right-hand side tensor.");

	if(q != phib.size())
		throw std::runtime_error("error in ublas::prod: permutation tuples must have the same length.");

	if(pa < phia.size())
		throw std::runtime_error("error in ublas::prod: permutation tuple for the left-hand side tensor cannot be greater than the corresponding order.");
	if(pb < phib.size())
		throw std::runtime_error("error in ublas::prod: permutation tuple for the right-hand side tensor cannot be greater than the corresponding order.");


	auto const& na = a.extents();
	auto const& nb = b.extents();

	for(auto i = 0ul; i < q; ++i)
		if( na.at(phia.at(i)-1) != nb.at(phib.at(i)-1))
			throw std::runtime_error("error in ublas::prod: permutations of the extents are not correct.");

	auto const r = pa - q;
	auto const s = pb - q;


	std::vector<std::size_t> phia1(pa), phib1(pb);
	std::iota(phia1.begin(), phia1.end(), 1ul);
	std::iota(phib1.begin(), phib1.end(), 1ul);

	std::vector<std::size_t> nc( std::max ( r+s , size_type(2) ), size_type(1) );

	for(auto i = 0ul; i < phia.size(); ++i)
		* std::remove(phia1.begin(), phia1.end(), phia.at(i)) = phia.at(i);

	//phia1.erase( std::remove(phia1.begin(), phia1.end(), phia.at(i)),  phia1.end() )  ;

	assert(phia1.size() == pa);

	for(auto i = 0ul; i < r; ++i)
		nc[ i ] = na[ phia1[ i  ] - 1  ];

	for(auto i = 0ul; i < phib.size(); ++i)
		* std::remove(phib1.begin(), phib1.end(), phib.at(i))  = phib.at(i) ;
	//phib1.erase( std::remove(phib1.begin(), phib1.end(), phia.at(i)), phib1.end() )  ;

	assert(phib1.size() == pb);

	for(auto i = 0ul; i < s; ++i)
		nc[ r + i ] = nb[ phib1[ i  ] - 1  ];

	//	std::copy( phib.begin(), phib.end(), phib1.end()  );

	assert(  phia1.size() == pa  );
	assert(  phib1.size() == pb  );

	auto c = tensor_type(extents_type(nc), value_type{});

	ttt(pa, pb, q,
	    phia1.data(), phib1.data(),
	    c.data(), c.extents().data(), c.strides().data(),
	    a.data(), a.extents().data(), a.strides().data(),
	    b.data(), b.extents().data(), b.strides().data());

	return c;
}

//template<class V, class F, class A1, class A2, std::size_t N, std::size_t M>
//auto operator*( tensor_index<V,F,A1,N> const& lhs, tensor_index<V,F,A2,M> const& rhs)




/** @brief Computes the q-mode tensor-times-tensor product
 *
 * Implements C[i1,...,ir,j1,...,js] = sum( A[i1,...,ir+q] * B[j1,...,js+q]  )
 *
 * @note calls ublas::ttt
 *
 * na[phi[x]] = nb[phi[x]] for 1 <= x <= q
 *
 * @param[in]	 phi one-based permutation tuple of length q for bot input tensors
 * @param[in]  a  left-hand side tensor with order r+q
 * @param[in]  b  right-hand side tensor with order s+q
 * @result     tensor with order r+s
*/
template<class V, class F, class A1, class A2>
auto prod(tensor<V,F,A1> const& a, tensor<V,F,A2> const& b,
          std::vector<std::size_t> const& phi)
{
	return prod(a, b, phi, phi);
}


/** @brief Computes the inner product of two tensors
 *
 * Implements c = sum(A[i1,i2,...,ip] * B[i1,i2,...,jp])
 *
 * @note calls inner function
 *
 * @param[in] a tensor object A
 * @param[in] b tensor object B
 *
 * @returns a value type.
*/
template<class V, class F, class A1, class A2>
auto inner_prod(tensor<V,F,A1> const& a, tensor<V,F,A2> const& b)
{
	using value_type   = typename tensor<V,F,A1>::value_type;

	if( a.rank() != b.rank() )
		throw std::length_error("error in boost::numeric::ublas::inner_prod: Rank of both tensors must be the same.");

	if( a.empty() || b.empty())
		throw std::length_error("error in boost::numeric::ublas::inner_prod: Tensors should not be empty.");

	if( a.extents() != b.extents())
		throw std::length_error("error in boost::numeric::ublas::inner_prod: Tensor extents should be the same.");

	return inner(a.rank(), a.extents().data(),
	             a.data(), a.strides().data(),
	             b.data(), b.strides().data(), value_type{0});
}

/** @brief Computes the outer product of two tensors
 *
 * Implements C[i1,...,ip,j1,...,jq] = A[i1,i2,...,ip] * B[j1,j2,...,jq]
 *
 * @note calls outer function
 *
 * @param[in] a tensor object A
 * @param[in] b tensor object B
 *
 * @returns tensor object C with the same storage format F and allocator type A1
*/
template<class V, class F, class A1, class A2>
auto outer_prod(tensor<V,F,A1> const& a, tensor<V,F,A2> const& b)
{
	using tensor_type  = tensor<V,F,A1>;
	using extents_type = typename tensor_type::extents_type;

	if( a.empty() || b.empty() )
		throw std::runtime_error("error in boost::numeric::ublas::outer_prod: tensors should not be empty.");

	auto nc = typename extents_type::base_type(a.rank() + b.rank());
	for(auto i = 0u; i < a.rank(); ++i)
		nc.at(i) = a.extents().at(i);

	for(auto i = 0u; i < b.rank(); ++i)
		nc.at(a.rank()+i) = b.extents().at(i);

	auto c = tensor_type(extents_type(nc));

	outer(c.data(), c.rank(), c.extents().data(), c.strides().data(),
	      a.data(), a.rank(), a.extents().data(), a.strides().data(),
	      b.data(), b.rank(), b.extents().data(), b.strides().data());

	return c;
}



/** @brief Transposes a tensor according to a permutation tuple
 *
 * Implements C[tau[i1],tau[i2]...,tau[ip]] = A[i1,i2,...,ip]
 *
 * @note calls trans function
 *
 * @param[in] a    tensor object of rank p
 * @param[in] tau  one-based permutation tuple of length p
 * @returns        a transposed tensor object with the same storage format F and allocator type A
*/
template<class V, class F, class A>
auto trans(tensor<V,F,A> const& a, std::vector<std::size_t> const& tau)
{
	using tensor_type  = tensor<V,F,A>;
	using extents_type = typename tensor_type::extents_type;
	//	using strides_type = typename tensor_type::strides_type;

	if( a.empty() )
		return tensor<V,F,A>{};

	auto const   p = a.rank();
	auto const& na = a.extents();

	auto nc = typename extents_type::base_type (p);
	for(auto i = 0u; i < p; ++i)
		nc.at(tau.at(i)-1) = na.at(i);

	//	auto wc = strides_type(extents_type(nc));

	auto c = tensor_type(extents_type(nc));


	trans( a.rank(), a.extents().data(), tau.data(),
	       c.data(), c.strides().data(),
	       a.data(), a.strides().data());

	//	auto wc_pi = typename strides_type::base_type (p);
	//	for(auto i = 0u; i < p; ++i)
	//		wc_pi.at(tau.at(i)-1) = c.strides().at(i);


	//copy(a.rank(),
	//		 a.extents().data(),
	//		 c.data(), wc_pi.data(),
	//		 a.data(), a.strides().data() );

	return c;
}

/** @brief Computes the frobenius norm of a tensor expression
 *
 * @note evaluates the tensor expression and calls the accumulate function
 *
 *
 * Implements the two-norm with
 * k = sqrt( sum_(i1,...,ip) A(i1,...,ip)^2 )
 *
 * @param[in] a    tensor object of rank p
 * @returns        the frobenius norm of the tensor
*/
//template<class V, class F, class A>
//auto norm(tensor<V,F,A> const& a)
template<class T, class D>
auto norm(detail::tensor_expression<T,D> const& expr)
{

	using tensor_type = typename detail::tensor_expression<T,D>::tensor_type;
	using value_type = typename tensor_type::value_type;

	auto a = tensor_type( expr );

	if( a.empty() )
		throw std::runtime_error("error in boost::numeric::ublas::norm: tensors should not be empty.");

	return std::sqrt( accumulate( a.order(), a.extents().data(), a.data(), a.strides().data(), value_type{},
	                              [](auto const& l, auto const& r){ return l + r*r; }  ) ) ;
}



/** @brief Extract the real component of tensor elements within a tensor expression
 *
 * @param[in] lhs tensor expression
 * @returns   unary tensor expression
*/
template<class T, class D>
auto real(detail::tensor_expression<T,D> const& expr) {
	return detail::make_unary_tensor_expression<T> (expr(), [] (auto const& l) { return std::real( l ); } );
}

/** @brief Extract the real component of tensor elements within a tensor expression
 *
 * @param[in] lhs tensor expression
 * @returns   unary tensor expression
*/
template<class V, class F, class A, class D>
auto real(detail::tensor_expression<tensor<std::complex<V>,F,A>,D> const& expr)
{
	using tensor_complex_type = tensor<std::complex<V>,F,A>;
	using tensor_type = tensor<V,F,typename storage_traits<A>::template rebind<V>>;

	if( detail::retrieve_extents( expr  ).empty() )
		throw std::runtime_error("error in boost::numeric::ublas::real: tensors should not be empty.");

	auto a = tensor_complex_type( expr );
	auto c = tensor_type( a.extents() );

	std::transform( a.begin(), a.end(),  c.begin(), [](auto const& l){ return std::real(l) ; }  );

	return c;
}


/** @brief Extract the imaginary component of tensor elements within a tensor expression
 *
 * @param[in] lhs tensor expression
 * @returns   unary tensor expression
*/
template<class T, class D>
auto imag(detail::tensor_expression<T,D> const& lhs) {
	return detail::make_unary_tensor_expression<T> (lhs(), [] (auto const& l) { return std::imag( l ); } );
}


/** @brief Extract the imag component of tensor elements within a tensor expression
 *
 * @param[in] lhs tensor expression
 * @returns   unary tensor expression
*/
template<class V, class A, class F, class D>
auto imag(detail::tensor_expression<tensor<std::complex<V>,F,A>,D> const& expr)
{
	using tensor_complex_type = tensor<std::complex<V>,F,A>;
	using tensor_type = tensor<V,F,typename storage_traits<A>::template rebind<V>>;

	if( detail::retrieve_extents( expr  ).empty() )
		throw std::runtime_error("error in boost::numeric::ublas::real: tensors should not be empty.");

	auto a = tensor_complex_type( expr );
	auto c = tensor_type( a.extents() );

	std::transform( a.begin(), a.end(),  c.begin(), [](auto const& l){ return std::imag(l) ; }  );

	return c;
}

/** @brief Computes the complex conjugate component of tensor elements within a tensor expression
 *
 * @param[in] expr tensor expression
 * @returns   complex tensor
*/
template<class T, class D>
auto conj(detail::tensor_expression<T,D> const& expr)
{
	using tensor_type = T;
	using value_type = typename tensor_type::value_type;
	using layout_type = typename tensor_type::layout_type;
	using array_type = typename tensor_type::array_type;

	using new_value_type = std::complex<value_type>;
	using new_array_type = typename storage_traits<array_type>::template rebind<new_value_type>;

	using tensor_complex_type = tensor<new_value_type,layout_type, new_array_type>;

	if( detail::retrieve_extents( expr  ).empty() )
		throw std::runtime_error("error in boost::numeric::ublas::conj: tensors should not be empty.");

	auto a = tensor_type( expr );
	auto c = tensor_complex_type( a.extents() );

	std::transform( a.begin(), a.end(),  c.begin(), [](auto const& l){ return std::conj(l) ; }  );

	return c;
}


/** @brief Computes the complex conjugate component of tensor elements within a tensor expression
 *
 * @param[in] lhs tensor expression
 * @returns   unary tensor expression
*/
template<class V, class A, class F, class D>
auto conj(detail::tensor_expression<tensor<std::complex<V>,F,A>,D> const& expr)
{
	return detail::make_unary_tensor_expression<tensor<std::complex<V>,F,A>> (expr(), [] (auto const& l) { return std::conj( l ); } );
}



}
}
}


#endif

/* functions.hpp
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
*/