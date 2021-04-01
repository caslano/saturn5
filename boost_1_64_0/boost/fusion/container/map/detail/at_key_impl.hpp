/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_AT_KEY_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_AT_KEY_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_key_impl;

        template <>
        struct at_key_impl<map_tag>
        {
            template <typename Sequence, typename Key>
            struct apply
            {
                typedef
                    decltype(boost::declval<Sequence>().get(mpl::identity<Key>()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& m)
                {
                    return m.get(mpl::identity<Key>());
                }
            };

            template <typename Sequence, typename Key>
            struct apply<Sequence const, Key>
            {
                typedef
                    decltype(boost::declval<Sequence const>().get(mpl::identity<Key>()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& m)
                {
                    return m.get(mpl::identity<Key>());
                }
            };
        };
    }
}}

#endif

/* at_key_impl.hpp
9UG8ulcdQ+lQ9srFurvVYcsEdwcqtxhJ2f4jz5Tyv7PP6n6hPBK8xcDXKaE2Iq2+Co7+souiTH6EuZMt0NZnP8sQ+RgTH+l1I55e580i0Kl3RnI/HjFtKinQ0AIiBiuL/+/wBaFmDDhR70nZH79vp7EYI1/Ct0kvaDCUStPcguoVSuUjZp7QLFeX6kRrbA1H/2w1PTk/vMZLGuI2aRj0qIOqjJmSxlT/BPOQAoHrW75XamSo9NBXY7UAladetiDQ4Z0WY2tqky7mXPdr4xZYEdB84ySIt4HTu3QeJaANuDqmEaGy9OZZXDWbzlcpK76k4e6t37eOUH0646L28EbpBkXIgPozRr+jqNTsEE5t2Okoh6kvC3QMrfpXbiMvKIgt6iRS7qYXKyVe6Hv2etp3Ps5CEIcXH1orSFX1AZSRlCHsASzojihFU9JUCT6S+UZ9hQl2/vcLYPTKyL3YFYzr0WffhCTEdSTG+CT4g5CrqupYbv1VQ4HczVyRGlOmozs1/CoOfTSpO74ReoMt8iecyPlIz9qHrU+w5UdiBlyTu0DEnXwJE6wdaR7myQ==
*/