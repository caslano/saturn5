#ifndef BOOST_QVM_VEC_TRAITS_ARRAY_HPP_INCLUDED
#define BOOST_QVM_VEC_TRAITS_ARRAY_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/inline.hpp>
#include <boost/qvm/deduce_vec.hpp>
#include <boost/qvm/detail/remove_const.hpp>
#include <boost/qvm/assert.hpp>

namespace boost { namespace qvm {

template <class T,int M,int N>
struct
vec_traits<T[M][N]>
    {
    static int const dim=0;
    typedef void scalar_type;
    };

template <class T,int Dim>
struct
vec_traits<T[Dim]>
    {
    typedef T this_vector[Dim];
    typedef typename qvm_detail::remove_const<T>::type scalar_type;
    static int const dim=Dim;

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_vector const & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<Dim);
        return x[I];
        }

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_vector & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<Dim);
        return x[I];
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int i, this_vector const & x )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<Dim);
        return x[i];
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element_idx( int i, this_vector & x )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<Dim);
        return x[i];
        }
    };

template <class T,int Dim,int D>
struct
deduce_vec<T[Dim],D>
    {
    typedef vec<T,D> type;
    };

template <class T,int Dim,int D>
struct
deduce_vec<T const[Dim],D>
    {
    typedef vec<T,D> type;
    };

template <class T1,class T2,int Dim,int D>
struct
deduce_vec2<T1[Dim],T2[Dim],D>
    {
    typedef vec<typename deduce_scalar<T1,T2>::type,D> type;
    };

template <int Dim,class T>
T (&ptr_vref( T * ptr ))[Dim]
    {
    return *reinterpret_cast<T (*)[Dim]>(ptr);
    }

} }

#endif

/* vec_traits_array.hpp
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
*/