#ifndef BOOST_QVM_DETAIL_COFACTOR_IMPL_HPP_INCLUDED
#define BOOST_QVM_DETAIL_COFACTOR_IMPL_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/detail/determinant_impl.hpp>
#include <boost/qvm/mat_traits.hpp>
#include <boost/qvm/static_assert.hpp>

namespace boost { namespace qvm {

namespace
qvm_detail
    {
    template <class A>
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_OPERATIONS
    typename deduce_mat<A>::type
    cofactor_impl( A const & a )
        {
        BOOST_QVM_STATIC_ASSERT(mat_traits<A>::rows==mat_traits<A>::cols);
        int const N=mat_traits<A>::rows;
        typedef typename mat_traits<A>::scalar_type T;
        T c[N-1][N-1];
        typedef typename deduce_mat<A>::type R;
        R b;
        for( int j=0; j!=N; ++j )
            {
            for( int i=0; i!=N; ++i )
                {
                int i1=0;
                for( int ii=0; ii!=N; ++ii )
                    {
                    if( ii==i )
                        continue;
                    int j1=0;
                    for( int jj=0; jj!=N; ++jj )
                        {
                        if( jj==j )
                            continue;
                        c[i1][j1] = mat_traits<A>::read_element_idx(ii,jj,a);
                        ++j1;
                        }
                    ++i1;
                    }
                T det = determinant_impl(c);
                if( (i+j)&1 )
                    det=-det;
                mat_traits<R>::write_element_idx(i,j,b) = det;
                }
            }
        return b;
        }
    }

} }

#endif

/* cofactor_impl.hpp
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
*/