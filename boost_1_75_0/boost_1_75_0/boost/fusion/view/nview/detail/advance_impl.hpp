/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_ADVANCE_IMPL_SEP_24_2009_0212PM)
#define BOOST_FUSION_NVIEW_ADVANCE_IMPL_SEP_24_2009_0212PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<nview_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef typename Iterator::first_type iterator_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef nview_iterator<sequence_type,
                    typename result_of::advance<iterator_type, Dist>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.seq);
                }
            };
        };
    }

}}

#endif

/* advance_impl.hpp
G0rCRb8p0cvIoOpvkDysNIlVWNSt9fBX9uKZbdqwfRSK+NkS4TrahpwILO5fP/YW9VeySLRXFy3G4m53FTrCG+k9Q/2D339kueavErjGap9n9NmNJ1X/jIAyvicDHlKpwtApQk8FXuA6XTwmKzxQlUJY7MHYcFr0Gy57Onbjd92edJwrNFMwMVKS9IMiKWVy0YIh/VTgQzJZIRHEOsDT98zn68hWsKBm/yoC9X3OyuLVt3d38b3Rhc+ODVe9cNbizr1WDa0hLpi/kgagD7AbWSgAW9Q4c5GO2CivQYTv+WJig7yX1pF1xzHb0cJPS1z5Q56G36KH70cKB6pKbJ5l9iexjv3g/A4D2mRrukn7xaN1G0lUEaLID0bBFNWZfa4dwE7Whm5RLX4pus7678SvKpawfz3Y/ikHz0wRY4fdf+EvK2glFVTNO6OlSHi/MII71Tcl9d5IkT/1xbtHrCWExUB832/rW8XvE6PWqGsHf1RIH9VjoRKBLauC8sUz5TQHQ+1v0ragJmfk1dOR5+LdqpGHvpkuqp++UUwucEEpvfq5qjmTZjaFX7F1aF5GfkKG+k7lpKBxYgufp6JrXZbSco5Zq0A9IQYkn2DZ77V5cwafVG5zLoWL4SFQVxwlOx2WLjShd+ea9kT1+YA10P5YpWfKBKzIpGpy9kMeUtXYeVmeF52ojj9mbcmVpy3VRRs49rsTtA6bwjEVxr+k
*/