#ifndef BOOST_QVM_DETAIL_DETERMINANT_IMPL_HPP_INCLUDED
#define BOOST_QVM_DETAIL_DETERMINANT_IMPL_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/inline.hpp>
#include <boost/qvm/mat_traits_array.hpp>
#include <boost/qvm/static_assert.hpp>

namespace boost { namespace qvm {

namespace
qvm_detail
    {
    template <int N>
    struct
    det_size
        {
        };

    template <class M>
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
    typename mat_traits<M>::scalar_type
    determinant_impl_( M const & a, det_size<2> )
        {
        return
            mat_traits<M>::template read_element<0,0>(a) * mat_traits<M>::template read_element<1,1>(a) -
            mat_traits<M>::template read_element<1,0>(a) * mat_traits<M>::template read_element<0,1>(a);
        }

    template <class M,int N>
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_RECURSION
    typename mat_traits<M>::scalar_type
    determinant_impl_( M const & a, det_size<N> )
        {
        typedef typename mat_traits<M>::scalar_type T;
        T m[N-1][N-1];
        T det=T(0);
        for( int j1=0; j1!=N; ++j1 )
            {
            for( int i=1; i!=N; ++i )
                {
                int j2 = 0;
                for( int j=0; j!=N; ++j )
                    {
                    if( j==j1 )
                        continue;
                    m[i-1][j2] = mat_traits<M>::read_element_idx(i,j,a);
                    ++j2;
                    }
                }
            T d=determinant_impl_(m,det_size<N-1>());
            if( j1&1 )
                d=-d;
            det += mat_traits<M>::read_element_idx(0,j1,a) * d;
            }
        return det;
        }

    template <class M>
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL
    typename mat_traits<M>::scalar_type
    determinant_impl( M const & a )
        {
        BOOST_QVM_STATIC_ASSERT(mat_traits<M>::rows==mat_traits<M>::cols);
        return determinant_impl_(a,det_size<mat_traits<M>::rows>());
        }
    }

} }

#endif

/* determinant_impl.hpp
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
*/