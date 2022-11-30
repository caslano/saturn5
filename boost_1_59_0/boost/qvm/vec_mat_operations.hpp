#ifndef BOOST_QVM_VEC_MAT_OPERATIONS_HPP_INCLUDED
#define BOOST_QVM_VEC_MAT_OPERATIONS_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/vec_mat_operations2.hpp>
#include <boost/qvm/vec_mat_operations3.hpp>
#include <boost/qvm/vec_mat_operations4.hpp>

namespace boost { namespace qvm {

namespace
qvm_detail
    {
    template <int M,int N>
    struct
    mul_mv_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_mat<A>::value && is_vec<B>::value &&
    mat_traits<A>::cols==vec_traits<B>::dim &&
    !qvm_detail::mul_mv_defined<mat_traits<A>::rows,mat_traits<A>::cols>::value,
    deduce_vec2<A,B,mat_traits<A>::rows> >::type
operator*( A const & a, B const & b )
    {
    typedef typename deduce_vec2<A,B,mat_traits<A>::rows>::type R;
    R r;
    for( int i=0; i<mat_traits<A>::rows; ++i )
        {
        typedef typename vec_traits<R>::scalar_type Tr;
        Tr x(scalar_traits<Tr>::value(0));
        for( int j=0; j<mat_traits<A>::cols; ++j )
            x += mat_traits<A>::read_element_idx(i,j,a)*vec_traits<B>::read_element_idx(j,b);
        vec_traits<R>::write_element_idx(i,r) = x;
        }
    return r;
    }

namespace
qvm_detail
    {
    template <int M,int N>
    struct
    mul_vm_defined
        {
        static bool const value=false;
        };
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    is_vec<A>::value && is_mat<B>::value &&
    vec_traits<A>::dim==mat_traits<B>::rows &&
    !qvm_detail::mul_vm_defined<mat_traits<B>::rows,mat_traits<B>::cols>::value,
    deduce_vec2<A,B,mat_traits<B>::cols> >::type
operator*( A const & a, B const & b )
    {
    typedef typename deduce_vec2<A,B,mat_traits<B>::cols>::type R;
    R r;
    for( int i=0; i<mat_traits<B>::cols; ++i )
        {
        typedef typename vec_traits<R>::scalar_type Tr;
        Tr x(scalar_traits<Tr>::value(0));
        for( int j=0; j<mat_traits<B>::rows; ++j )
            x += vec_traits<A>::read_element_idx(j,a)*mat_traits<B>::read_element_idx(j,i,b);
        vec_traits<R>::write_element_idx(i,r) = x;
        }
    return r;
    }

////////////////////////////////////////////////

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    mat_traits<A>::rows==4 && mat_traits<A>::cols==4 &&
    vec_traits<B>::dim==3,
    deduce_vec2<A,B,3> >::type
transform_point( A const & a, B const & b )
    {
    typedef typename mat_traits<A>::scalar_type Ta;
    typedef typename vec_traits<B>::scalar_type Tb;
    Ta const a00 = mat_traits<A>::template read_element<0,0>(a);
    Ta const a01 = mat_traits<A>::template read_element<0,1>(a);
    Ta const a02 = mat_traits<A>::template read_element<0,2>(a);
    Ta const a03 = mat_traits<A>::template read_element<0,3>(a);
    Ta const a10 = mat_traits<A>::template read_element<1,0>(a);
    Ta const a11 = mat_traits<A>::template read_element<1,1>(a);
    Ta const a12 = mat_traits<A>::template read_element<1,2>(a);
    Ta const a13 = mat_traits<A>::template read_element<1,3>(a);
    Ta const a20 = mat_traits<A>::template read_element<2,0>(a);
    Ta const a21 = mat_traits<A>::template read_element<2,1>(a);
    Ta const a22 = mat_traits<A>::template read_element<2,2>(a);
    Ta const a23 = mat_traits<A>::template read_element<2,3>(a);
    Tb const b0 = vec_traits<B>::template read_element<0>(b);
    Tb const b1 = vec_traits<B>::template read_element<1>(b);
    Tb const b2 = vec_traits<B>::template read_element<2>(b);
    typedef typename deduce_vec2<A,B,3>::type R;
    BOOST_QVM_STATIC_ASSERT(vec_traits<R>::dim==3);
    R r;
    vec_traits<R>::template write_element<0>(r)=a00*b0+a01*b1+a02*b2+a03;
    vec_traits<R>::template write_element<1>(r)=a10*b0+a11*b1+a12*b2+a13;
    vec_traits<R>::template write_element<2>(r)=a20*b0+a21*b1+a22*b2+a23;
    return r;
    }

template <class A,class B>
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
typename lazy_enable_if_c<
    mat_traits<A>::rows==4 && mat_traits<A>::cols==4 &&
    vec_traits<B>::dim==3,
    deduce_vec2<A,B,3> >::type
transform_vector( A const & a, B const & b )
    {
    typedef typename mat_traits<A>::scalar_type Ta;
    typedef typename vec_traits<B>::scalar_type Tb;
    Ta const a00 = mat_traits<A>::template read_element<0,0>(a);
    Ta const a01 = mat_traits<A>::template read_element<0,1>(a);
    Ta const a02 = mat_traits<A>::template read_element<0,2>(a);
    Ta const a10 = mat_traits<A>::template read_element<1,0>(a);
    Ta const a11 = mat_traits<A>::template read_element<1,1>(a);
    Ta const a12 = mat_traits<A>::template read_element<1,2>(a);
    Ta const a20 = mat_traits<A>::template read_element<2,0>(a);
    Ta const a21 = mat_traits<A>::template read_element<2,1>(a);
    Ta const a22 = mat_traits<A>::template read_element<2,2>(a);
    Tb const b0 = vec_traits<B>::template read_element<0>(b);
    Tb const b1 = vec_traits<B>::template read_element<1>(b);
    Tb const b2 = vec_traits<B>::template read_element<2>(b);
    typedef typename deduce_vec2<A,B,3>::type R;
    BOOST_QVM_STATIC_ASSERT(vec_traits<R>::dim==3);
    R r;
    vec_traits<R>::template write_element<0>(r)=a00*b0+a01*b1+a02*b2;
    vec_traits<R>::template write_element<1>(r)=a10*b0+a11*b1+a12*b2;
    vec_traits<R>::template write_element<2>(r)=a20*b0+a21*b1+a22*b2;
    return r;
    }

////////////////////////////////////////////////

namespace
sfinae
    {
    using ::boost::qvm::operator*;
    using ::boost::qvm::transform_point;
    using ::boost::qvm::transform_vector;
    }

} }

#endif

/* vec_mat_operations.hpp
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
*/