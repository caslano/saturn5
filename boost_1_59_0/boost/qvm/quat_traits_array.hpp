#ifndef BOOST_QVM_QUAT_TRAITS_ARRAY_HPP_INCLUDED
#define BOOST_QVM_QUAT_TRAITS_ARRAY_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/inline.hpp>
#include <boost/qvm/deduce_quat.hpp>
#include <boost/qvm/detail/remove_const.hpp>
#include <boost/qvm/assert.hpp>

namespace boost { namespace qvm {

template <class T,int D>
struct
quat_traits<T[D]>
    {
    typedef void scalar_type;
    };
template <class T,int D>
struct
quat_traits<T[D][4]>
    {
    typedef void scalar_type;
    };
template <class T,int D>
struct
quat_traits<T[4][D]>
    {
    typedef void scalar_type;
    };
template <class T>
struct
quat_traits<T[4][4]>
    {
    typedef void scalar_type;
    };
template <class T,int M,int N>
struct
quat_traits<T[M][N]>
    {
    typedef void scalar_type;
    };

template <class T>
struct
quat_traits<T[4]>
    {
    typedef T this_quaternion[4];
    typedef typename qvm_detail::remove_const<T>::type scalar_type;

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_quaternion const & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<4);
        return x[I];
        }

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_quaternion & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<4);
        return x[I];
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int i, this_quaternion const & x )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<4);
        return x[i];
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element_idx( int i, this_quaternion & x )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<4);
        return x[i];
        }
    };

template <class T>
struct
deduce_quat<T[4]>
    {
    typedef quat<T> type;
    };

template <class T>
struct
deduce_quat<T const[4]>
    {
    typedef quat<T> type;
    };

template <class T1,class T2>
struct
deduce_quat2<T1[4],T2[4]>
    {
    typedef quat<typename deduce_scalar<T1,T2>::type> type;
    };

template <class T>
T (&ptr_qref( T * ptr ))[4]
    {
    return *reinterpret_cast<T (*)[4]>(ptr);
    }

} }

#endif

/* quat_traits_array.hpp
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
*/