#ifndef BOOST_QVM_MAT_TRAITS_DEFAULTS_HPP_INCLUDED
#define BOOST_QVM_MAT_TRAITS_DEFAULTS_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/inline.hpp>
#include <boost/qvm/assert.hpp>

namespace boost { namespace qvm {

template <class>
struct mat_traits;

namespace
qvm_detail
    {
    template <int I,int N>
    struct
    matrix_w
        {
        template <class A>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
        typename mat_traits<A>::scalar_type &
        write_element_idx( int r, int c, A & a )
            {
            return (I/mat_traits<A>::cols)==r && (I%mat_traits<A>::cols)==c?
                mat_traits<A>::template write_element<I/mat_traits<A>::cols,I%mat_traits<A>::cols>(a) :
                matrix_w<I+1,N>::write_element_idx(r,c,a);
            }
        };

    template <int N>
    struct
    matrix_w<N,N>
        {
        template <class A>
        static
        BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
        typename mat_traits<A>::scalar_type &
        write_element_idx( int, int, A & a )
            {
            BOOST_QVM_ASSERT(0);
            return mat_traits<A>::template write_element<0,0>(a);
            }
        };
    }

template <class MatType,class ScalarType,int Rows,int Cols>
struct
mat_traits_defaults
    {
    typedef MatType mat_type;
    typedef ScalarType scalar_type;
    static int const rows=Rows;
    static int const cols=Cols;

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( mat_type const & x )
        {
        return mat_traits<mat_type>::template write_element<Row,Col>(const_cast<mat_type &>(x));
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int r, int c, mat_type const & x )
        {
        return mat_traits<mat_type>::write_element_idx(r,c,const_cast<mat_type &>(x));
        }

    protected:

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
    scalar_type &
    write_element_idx( int r, int c, mat_type & m )
        {
        return qvm_detail::matrix_w<0,mat_traits<mat_type>::rows*mat_traits<mat_type>::cols>::write_element_idx(r,c,m);
        }
    };

} }

#endif

/* mat_traits_defaults.hpp
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
*/