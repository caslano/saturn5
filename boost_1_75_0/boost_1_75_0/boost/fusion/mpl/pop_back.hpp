/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_BACK_10022005_1801)
#define FUSION_POP_BACK_10022005_1801

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/pop_back.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct pop_back_impl;

    template <>
    struct pop_back_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef typename
                fusion::result_of::pop_back<Sequence>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* pop_back.hpp
+IDBKKLDZjEOzZUUr0g1F+6OH/MiO7bJGOiMXmJLffVN2lLp3fzcuw0ouFMjoeFLa3lTNYi2ZbWABuJTtj0+VXosvyyBQy3K/gMmZ2KK/SlfX+zFLuUsCX2wlb3eTJzqLfSTJa4FPEr5nyZUOx4HPkXQ/hFXL6BXGiWO37qLpv/r5Uiue2q96Ayf6usG0zFqI+EByjgbqePNAqGzmjwtkUDQR7dSjdIAka/6AH/Lg7EeQ4wEnfIWE6sAnlCJl5zADjaew0vFyB3+QHRCtUq5rp7bYtJJWb5FkPKeWmpH1S6Br+8ngJu1q2iWlZpjmcxuJx7y4zR7YPTlNFMiKpHs9VamHHpZC25ZvRv4JZIMeaYgosEyddlLEHLpTiLkonv/CyHP7/r/QEilupl/+f5/IKltcyJJb9iZQNKRK7siqZEjg+W65IJ/pYvMTSPpmysN8W/4K3Ct5Cz+moV+KZdSTGrtbzVKSIIzfqOR4SAu94aot/mfer1H/mnUu/efRr21/DVLvfgbrvCOxAo717fRqO/RWH0rYvUtFvVh2qnBoo3pl7WxUw4wzmeVPIae9YCI5oF+erLE4d6fSebEgyoZBdoJeg+EXpglmdGJQI97+qBSyJ+p2ZQtZs5mFpkKFczJUq/BTkVsoR/0EvfFSqRRiSQqEfcuN0VwqCPIqKC0P/QcjCnsDL8iO7k/U537K4YtNbyZ8hL3WFwgRmKz
*/