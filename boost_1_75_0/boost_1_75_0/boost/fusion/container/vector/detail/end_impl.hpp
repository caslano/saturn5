/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05042005_1142)
#define FUSION_END_IMPL_05042005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_iterator.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<vector_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::size size;
                typedef vector_iterator<Sequence, size::value> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
NAPmpirbGCpjcllCNKTohxDdCjCrlsA/elcC7x4LeYfma0qxVQbkKAoTboh0GluetJr01BhW1fHCk0LmSA5Pf0EyRwEs4dUFIfbs2WDPFve4xq+nqR21Hlcgl/88sRl/Bunx02bd3p2oheJY/B/CZMtvF2mCCOywHE0uVYH6lvLtVcqRT33CivuTDPVsCWqFuIIy6lHgSSL/EfGuSsHgcC0+i9I+VIgP6Hq0U//wgOB21Ii94i1e61q91rVGjgimCkrgWpi2Bev1JMNfUJGnu2GT2MsO4EWlGrgNXpjW3+k5BSzrg0iDXFDH5YJ6TlDqcId2ZuNewfYyqOp+XgiIy1498XV7OKmXJyTbE+i7vUcZigMn7AlE6k7YW9GGh/gYQ2NMWj6kQTujeE6ZMp6uiFwcHwRzCBgzqBw/B5u+ks7B3o4kNaBciTB0v4p3fx/vfhV2v2AldV9vgfq+gvf9zki971XYd0YwseP7qOPZmJXmtkxDrx/YEaVlwslrvssbH6cux2IzRBATYeY7RdDKrtRXdqVAC0xj/D0vsAYlGOw/5UylgkRaoWAVumw60v+K5Zd9f9sOqXvldbw8yfRgFuB3YFuw7genwTnMJCYXPWzFXu9VHVnsz0y5zn9Re8D3aY+DZNOAkg3c/pIiv8omD9lkuN8zg4maWWz8ZpJq0lntyi13UHa/ZNWx/TErSofJqISRGAtTrucRb8vH
*/