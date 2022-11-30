#ifndef BOOST_QVM_DEDUCE_QUAT_HPP_INCLUDED
#define BOOST_QVM_DEDUCE_QUAT_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/deduce_scalar.hpp>
#include <boost/qvm/quat_traits.hpp>
#include <boost/qvm/static_assert.hpp>

namespace boost { namespace qvm {

template <class T>
struct quat;

namespace
qvm_detail
    {
    template <class Q,class S,
        class QS=typename quat_traits<Q>::scalar_type>
    struct
    deduce_q_default
        {
        BOOST_QVM_STATIC_ASSERT(is_quat<Q>::value);
        typedef quat<typename quat_traits<Q>::scalar_type> type;
        };

    template <class Q,class S>
    struct
    deduce_q_default<Q,S,S>
        {
        BOOST_QVM_STATIC_ASSERT(is_quat<Q>::value);
        typedef Q type;
        };
    }

template <class Q,class S=typename quat_traits<Q>::scalar_type>
struct
deduce_quat
    {
    BOOST_QVM_STATIC_ASSERT(is_quat<Q>::value);
    typedef typename qvm_detail::deduce_q_default<Q,S>::type type;
    };

namespace
qvm_detail
    {
    template <class A,class B,class S,
        bool IsScalarA=is_scalar<A>::value,
        bool IsScalarB=is_scalar<B>::value>
    struct
    deduce_q2_default
        {
        typedef quat<S> type;
        };

    template <class Q,class S>
    struct
    deduce_q2_default<Q,Q,S,false,false>
        {
        BOOST_QVM_STATIC_ASSERT(is_quat<Q>::value);
        typedef Q type;
        };

    template <class A,class B,class S>
    struct
    deduce_q2_default<A,B,S,false,true>
        {
        BOOST_QVM_STATIC_ASSERT(is_quat<A>::value);
        typedef typename deduce_quat<A,S>::type type;
        };

    template <class A,class B,class S>
    struct
    deduce_q2_default<A,B,S,true,false>
        {
        BOOST_QVM_STATIC_ASSERT(is_quat<B>::value);
        typedef typename deduce_quat<B,S>::type type;
        };
    }

template <class A,class B,class S=typename deduce_scalar<typename scalar<A>::type,typename scalar<B>::type>::type>
struct
deduce_quat2
    {
    BOOST_QVM_STATIC_ASSERT(is_quat<A>::value || is_quat<B>::value);
    typedef typename qvm_detail::deduce_q2_default<A,B,S>::type type;
    };

} }

#endif

/* deduce_quat.hpp
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
*/