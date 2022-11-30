#ifndef BOOST_QVM_DEDUCE_MAT_HPP_INCLUDED
#define BOOST_QVM_DEDUCE_MAT_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/deduce_scalar.hpp>
#include <boost/qvm/mat_traits.hpp>
#include <boost/qvm/static_assert.hpp>

namespace boost { namespace qvm {

template <class T,int Rows,int Cols>
struct mat;

namespace
qvm_detail
    {
    template <class M,int R,int C,class S,
        int MR=mat_traits<M>::rows,
        int MC=mat_traits<M>::cols,
        class MS=typename mat_traits<M>::scalar_type>
    struct
    deduce_m_default
        {
        BOOST_QVM_STATIC_ASSERT(is_mat<M>::value);
        typedef mat<typename mat_traits<M>::scalar_type,R,C> type;
        };

    template <class M,int R,int C,class S>
    struct
    deduce_m_default<M,R,C,S,R,C,S>
        {
        BOOST_QVM_STATIC_ASSERT(is_mat<M>::value);
        typedef M type;
        };
    }

template <class M,int R=mat_traits<M>::rows,int C=mat_traits<M>::cols,class S=typename mat_traits<M>::scalar_type>
struct
deduce_mat
    {
    BOOST_QVM_STATIC_ASSERT(is_mat<M>::value);
    typedef typename qvm_detail::deduce_m_default<M,R,C,S>::type type;
    };

namespace
qvm_detail
    {
    template <class A,class B,int R,int C,class S,
        bool IsScalarA=is_scalar<A>::value,
        bool IsScalarB=is_scalar<B>::value>
    struct
    deduce_m2_default
        {
        typedef mat<S,R,C> type;
        };

    template <class M,int R,int C,class S>
    struct
    deduce_m2_default<M,M,R,C,S,false,false>
        {
        BOOST_QVM_STATIC_ASSERT(is_mat<M>::value);
        typedef M type;
        };

    template <class A,class B,int R,int C,class S>
    struct
    deduce_m2_default<A,B,R,C,S,false,true>
        {
        BOOST_QVM_STATIC_ASSERT(is_mat<A>::value);
        typedef typename deduce_mat<A,R,C,S>::type type;
        };

    template <class A,class B,int R,int C,class S>
    struct
    deduce_m2_default<A,B,R,C,S,true,false>
        {
        BOOST_QVM_STATIC_ASSERT(is_mat<B>::value);
        typedef typename deduce_mat<B,R,C,S>::type type;
        };
    }

template <class A,class B,int R,int C,class S=typename deduce_scalar<typename scalar<A>::type,typename scalar<B>::type>::type>
struct
deduce_mat2
    {
    BOOST_QVM_STATIC_ASSERT(is_mat<A>::value || is_mat<B>::value);
    typedef typename qvm_detail::deduce_m2_default<A,B,R,C,S>::type type;
    };

} }

#endif

/* deduce_mat.hpp
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
*/