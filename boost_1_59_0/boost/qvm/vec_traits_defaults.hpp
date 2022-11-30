#ifndef BOOST_QVM_VEC_TRAITS_DEFAULTS_HPP_INCLUDED
#define BOOST_QVM_VEC_TRAITS_DEFAULTS_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/inline.hpp>
#include <boost/qvm/assert.hpp>

namespace boost { namespace qvm {

template <class>
struct vec_traits;

namespace
qvm_detail
    {
    template <int I,int N>
    struct
    vector_w
        {
        template <class A>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        typename vec_traits<A>::scalar_type &
        write_element_idx( int i, A & a )
            {
            return I==i?
                vec_traits<A>::template write_element<I>(a) :
                vector_w<I+1,N>::write_element_idx(i,a);
            }
        };

    template <int N>
    struct
    vector_w<N,N>
        {
        template <class A>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        typename vec_traits<A>::scalar_type &
        write_element_idx( int, A & a )
            {
            BOOST_QVM_ASSERT(0);
            return vec_traits<A>::template write_element<0>(a);
            }
        };
    }

template <class VecType,class ScalarType,int Dim>
struct
vec_traits_defaults
    {
    typedef VecType vec_type;
    typedef ScalarType scalar_type;
    static int const dim=Dim;

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( vec_type const & x )
        {
        return vec_traits<vec_type>::template write_element<I>(const_cast<vec_type &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int i, vec_type const & x )
        {
        return vec_traits<vec_type>::write_element_idx(i,const_cast<vec_type &>(x));
        }

    protected:

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
    scalar_type &
    write_element_idx( int i, vec_type & m )
        {
        return qvm_detail::vector_w<0,vec_traits<vec_type>::dim>::write_element_idx(i,m);
        }
    };

} }

#endif

/* vec_traits_defaults.hpp
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
*/