#ifndef BOOST_QVM_DEDUCE_VEC_HPP_INCLUDED
#define BOOST_QVM_DEDUCE_VEC_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/deduce_scalar.hpp>
#include <boost/qvm/vec_traits.hpp>
#include <boost/qvm/static_assert.hpp>

namespace boost { namespace qvm {

template <class T,int D>
struct vec;

namespace
qvm_detail
    {
    template <class V,int D,class S,
        int VD=vec_traits<V>::dim,
        class VS=typename vec_traits<V>::scalar_type>
    struct
    deduce_v_default
        {
        BOOST_QVM_STATIC_ASSERT(is_vec<V>::value);
        typedef vec<typename vec_traits<V>::scalar_type,D> type;
        };

    template <class V,int D,class S>
    struct
    deduce_v_default<V,D,S,D,S>
        {
        BOOST_QVM_STATIC_ASSERT(is_vec<V>::value);
        typedef V type;
        };
    }

template <class V,int D=vec_traits<V>::dim,class S=typename vec_traits<V>::scalar_type>
struct
deduce_vec
    {
    BOOST_QVM_STATIC_ASSERT(is_vec<V>::value);
    typedef typename qvm_detail::deduce_v_default<V,D,S>::type type;
    };

namespace
qvm_detail
    {
    template <class A,class B,int D,class S,
        bool IsScalarA=is_scalar<A>::value,
        bool IsScalarB=is_scalar<B>::value>
    struct
    deduce_v2_default
        {
        typedef vec<S,D> type;
        };

    template <class V,int D,class S>
    struct
    deduce_v2_default<V,V,D,S,false,false>
        {
        BOOST_QVM_STATIC_ASSERT(is_vec<V>::value);
        typedef V type;
        };

    template <class A,class B,int D,class S>
    struct
    deduce_v2_default<A,B,D,S,false,true>
        {
        BOOST_QVM_STATIC_ASSERT(is_vec<A>::value);
        typedef typename deduce_vec<A,D,S>::type type;
        };

    template <class A,class B,int D,class S>
    struct
    deduce_v2_default<A,B,D,S,true,false>
        {
        BOOST_QVM_STATIC_ASSERT(is_vec<B>::value);
        typedef typename deduce_vec<B,D,S>::type type;
        };
    }

template <class A,class B,int D,class S=typename deduce_scalar<typename scalar<A>::type,typename scalar<B>::type>::type>
struct
deduce_vec2
    {
    BOOST_QVM_STATIC_ASSERT(is_vec<A>::value || is_vec<B>::value);
    typedef typename qvm_detail::deduce_v2_default<A,B,D,S>::type type;
    };

} }

#endif

/* deduce_vec.hpp
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
*/