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
GOLbTxZ+ky8A1eAuGgQ4TOXqmPEvrPrx7LPr/+VVlT09pc/shxG01R5NooeoKsDc8vA6iMTI3yFiYgT66o78IJSvxO+DiMfa9xmSRKjJB57rc9k94dOA38P6d4DgDjPXUJtUUdBODz78cv5rr3taxUedt4BpqkgeuAVy4dtBCOs3rjaoVy0HNwN3eHz04fDgqFdN9RWAMw4BFeYF/ohEHSRVmXJDgKyed38+q2qaDhGBp8weW6Flw/KImB+gjvKCO+5Uk36n3QMY8cPZSXevlxJwHoLCANRQG8U8mlo2x0WCSwv5knTeOznZO/74sXd0noyNndttWO+TCYqfw2MgOxuNRvm59/74tHfSPe0dVamDgH/NhwEqLB8UDvdRxwGEMYe1qPXuvj/vncrOSm9rCBQu7inG3Ts8PuuVjctsD+RnWW8gt1veG0i2kh6nvfNPp0dHxzpXQx6DCmN3oDiCWcwIQMpKBKx2kIIEQNMOwwDnDqdF6/rzKfTpHZ5lUoNdnxn3onTWImuiTx1xkHpWlU61xwy72XDo2i7OojYaYXjW+3iwdwzSWmWsyIyIT1yQzsBPMeweHfX233862lMHs0DT+j6spuHMt3H3AsUW4TaTisv745Pe0cfjfZ2yIc2yz7kTAd8nlh0GwBqx
*/