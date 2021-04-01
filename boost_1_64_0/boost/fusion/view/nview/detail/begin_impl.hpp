/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_BEGIN_IMPL_SEP_23_2009_1036PM)
#define BOOST_FUSION_NVIEW_BEGIN_IMPL_SEP_23_2009_1036PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template<typename Tag>
        struct begin_impl;

        template<>
        struct begin_impl<nview_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef typename Sequence::index_type index_type;

                typedef nview_iterator<Sequence,
                    typename result_of::begin<index_type>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& s)
                {
                    return type(s);
                }
            };
        };
    }

}}

#endif


/* begin_impl.hpp
i3S2m9iQuurm1VQ3CSVt01HBYR70tgm9/GAuNGp+1t4Vs2cB50UxbO7wjkU2kdWliFQkQHBuZRk9KIq5tjfrplwfS3o5tAd72NqeKqg7aBhCBLf8hHnVY+Y5Z1vyFRh50e9g6aBhyLQbzutddIm1LVtJo8rPQe2BpwNDNyssDkOIGZ5szUda+r4vQMK0Bo0EulS4mmD7OGFEeXejvoo2zHbUqj6wLe9UPbWvlL6r9Vq7s3eZdN/sPIrpMgkElHtruhZWYNTZUt1ZuvzhZov6hBTXMKU65qTndpm0OrX+R/VAAc5PbvFINnZ20iMr6ohDNRgbo1GSemNjcq3pRnBRDBIyovGyhV9199YN2ZMuZxPEet/i+7ewl6lxYCYteGEX0MuPFNJCOq56gEahB3y6mFFgqPoPp0HhcmXUa3+8btQ5o3zvP/pMLpqaFAA4zN/DU06hdgYcg0jh2vlxrZrThbqIeHijQadiX9mcR47ufaiRR3FNvAw/c1daxptuIYZEuoA+AKyhd98/+xuIwNgqw2x58f7PcJfLjsixMnbwLBoX70m40pwEBbY31Q==
*/