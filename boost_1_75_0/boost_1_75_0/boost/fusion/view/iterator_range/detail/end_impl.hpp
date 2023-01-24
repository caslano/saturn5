/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05062005_1226)
#define FUSION_END_IMPL_05062005_1226

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<iterator_range_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::end_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return s.last;
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
CTBqpKqHz/QcRB94rZsVJaL5JJm/f08iS2AreJwvGXuaVp8n4nli7U+v31cqDqA7gDf+DsQvOlFdh7ESAzX17eoDL671qIaHfX7HSiNrfXrrTtvynq5Mz63LF8v0e1jPQB85fngiZ62IbxZyED+HRxaBNPTpBndHnyi0UpiDyREkKHpeWNtPemtv5pBEfi0ejU1PdynEadyVU98NfHTCKy7n7OLtcdMWPH5oydjn2mfn1ox4bt3aF9/9bt76238dfuDDl3v1Xrdo+5kr35s7qvG1D265ZsjQxEf6fnFVq7X3tfrtgT5HB/40teerBSFrH/tmYOa8ljccb//Q6NiJM+/OOF2vaFHvp2c+/dWkU87NzwT1Hnb69PTNy5p8evDoucRZS9+/L+ie/53K7HnsnZCgLc4XlyXc1eu1vEahzZdNq/1ir4R52z/s2rL1sq9u/zBv8bJ2wyIfDlt4Rfv6ibfNykwd8NGOppGzD/742a7jjQduvL3rl6f+saXnNvfVSTe99e7xFvUHPJWRdKD3K88M/K3Bsdfqtly+rv3xS2slvDpn2k/XXXVZ+MawqVkvDh4W/vh/Ws75/Zlp278uefOez34+Fr1md/czDU+diE+ZNPbwqyV9Ypb8Mjn37SVXz2tQr+TrrhPnR80/u/a3RoN6DRvwaEz/oFdjIxaM+Xnf4nk7Xt5cJ++RiZfUjdnas8YXw/s+N6Tep5fd
*/