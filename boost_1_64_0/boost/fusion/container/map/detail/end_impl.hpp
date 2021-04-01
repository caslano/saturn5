/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_END_IMPL_02042013_0857)
#define BOOST_FUSION_MAP_END_IMPL_02042013_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map_iterator.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template<typename T>
        struct end_impl;

        template<>
        struct end_impl<map_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef map_iterator<Sequence, Sequence::size::value> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
K/KVi/qWtF+SJDQAW1q85pF0qhtZ8oK7iFM+hRx/RaGekHqzdpqqunuQbpwxMJCayJcXAwh92wQYWj59DxkRMIlO8iZ0ONKZuRunQrzBCGN5LxWdKudklsgP5HX1s7fg5+WxlGPu9VRD7Lm5eapqo6jL4TvUAVa/8UwV4GYvEu9R/IolHfr++n8b0NjB9OiZKOAhv8lG/vmBQqIohoVsLqaeL2Tt2097hreVZcaHJOXXHwE6NgckR131fniMovN1T++8T8gVwAVSVvydT7Gb7RG3P2qyHVG2G+egsyHmRCO/nFBEj0p+nrmbQTn/epcQRPGmd8G1GEbYnxM36vp4QoLGgwwS9FoAepZOL1CHBALaw7vCR1AtR9xSiGFShhqWFXh2WRLD3+sbSeAd7cP3tntEYjMcKuw2QgBZQxWsXG+po1TMw61BP3YaH35VqvZcfrLlDgX8r2K8fEfBU5PfQrMpVeF8hrtj/E5aJxxZjZUMoslhwN67Ph9OQndUHPmUqwyrP04FocZn4ImRJlLZsiTY2UV5jcfAlymxfYN00r3lVhEtiRkD/IIwOg==
*/