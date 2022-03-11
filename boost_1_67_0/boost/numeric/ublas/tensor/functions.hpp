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