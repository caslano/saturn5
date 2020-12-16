/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_KEY_05052005_0229)
#define FUSION_VALUE_AT_KEY_05052005_0229

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>
#include <boost/fusion/algorithm/query/find.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/category_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct value_at_key_impl
        {
            template <typename Seq, typename Key>
            struct apply
              : result_of::value_of_data<
                    typename result_of::find<Seq, Key>::type
                >
            {};
        };

        template <>
        struct value_at_key_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : Sequence::template value_at_key<Sequence, Key> {};
        };

        template <>
        struct value_at_key_impl<boost_array_tag>;

        template <>
        struct value_at_key_impl<mpl_sequence_tag>;

        template <>
        struct value_at_key_impl<std_pair_tag>;
    }

    namespace detail
    {
        template <typename Sequence, typename N, typename Tag>
        struct value_at_key_impl
            : mpl::if_<
                  mpl::or_<
                      typename extension::has_key_impl<Tag>::template apply<Sequence, N>
                    , traits::is_unbounded<Sequence>
                  >
                , typename extension::value_at_key_impl<Tag>::template apply<Sequence, N>
                , mpl::empty_base
              >::type
        {};
    }

    namespace result_of
    {
        template <typename Sequence, typename N>
        struct value_at_key
            : detail::value_at_key_impl<Sequence, N, typename detail::tag_of<Sequence>::type>
        {};
    }
}}

#endif


/* value_at_key.hpp
zQHvRH1ajgOezHmVE2Zx5TDxLvV02Qc2TMSANg3rLb48d2MvSR0mmq/mk9bZkg/nHpPvcJgHeerFrF50rbqdb5WRprFflj5n4rOSMmjdLrb4qjQrwiovmOju5J1o3T5Lvknq5q7v85LBpmy519blfdHEFqzw3CJPAs5q14aNuXnDEdvBdd/kmRROrnmSekzcgyvxffRfJO/gsTDhKTRwwh62tgX+Plt9mdeoOWrr82YxBWvgd808CTD+he/NkGH3CD83EvMCHP1oxguNOT5sYJZA640QjblCMetbcC5bWxOxyQxb0xELo8cyxpE2MGL3J+3X0H5qTNOlayEKwf3+jgYjA3FszQsbbIhZb8b6+fJOiZG2fI1Lkj5LPPJ6ig5HUoPvgePy+UIPRK89QTGirSLSt9YHtefM9TVmUHv+jmC62/PsDS2MVda5XRrTbq9boe2axOD5T+otbiyf1/Zz0I9hmChmlE8wsDbqWuhYrzcxMZCLROaGwPfooLfLGZowMXDd29F3NgkGO4+OZYd0bUMvvx/KyG+KmM54eJ836aLNMRqeXmvZzTSm3T8uGjT1qpAhrb/0xB5i9t28A7O0SjCv0xjVEiqVAGJucYsGI+tQQ+tVfkNjnteBqWdgw3Z7/JY2RiwJAEEb9zMWRg06PQrXjHLHbmXjxVRu1u3JHRixpJiY37Uw/Y53fMatLYz1jrt3WxjrHS9YmH//jvw2Ft56xysWBt8Rx+f6bSUGtqpmP/us8VzyIy2/naTJxd7sF/z2ktYfPA4uI4aMA5T/yDtoervsK0jD/qv3d3cCmr5/xPufi/XzuWXhAYNbLnEpPP9Y3JPt2yMwMEkpunGn9dKadkp8MNg5oxycM/Hu6y5dOFwfEDd5104cloux7/YKnFT5iuneuNOauRvQxJ3WMXXZgheNOvaehaH39vvubtHxpg5lWBhqD8zuYdHxXh/jZ32U2LrESRJVRRUyciqQmxj0b/0o9fGuUl6VccnM84AVP+uj1L6QJ4EbJG7OBn06KQB9Wwl/wkLfcQOheB3wSSW79m01+TmrfL+A13QZPcXQ/d2n6Ht6ueukXlTV2+L2e2L8E+Ah/pxl6fCk8tmx1pajYdxU+8Ifm3z355nHw5gDkxG5awVtQ0gZASs838+cCOD29qMdi2fiY9SG0vVF2sC4BN72tsSKxbOP8IaMV1EapWUBvPZ2peX/Hn+M1jnIIlekfyO8A+r86Fa5Xl5WblDlwGtvb2S56ONv8nKWcz+pCpczuuug3/28yVOxMvKbrkpmXFlJjL1m8uSMQxlJ5IdMz8S0jEu0jMCHMVTBJySzpywjVbrXj1F7xKLyvcT3XdZcHEKa0cfK3KsQaGK+t9xxDhlF3/6P0fNRwp3Mc0KRpHyht6287Oc2TvXoeWz845TPiwO3dAuX8PVXYDRSG9A9hM9lcVGUXp7ltVe8fNupE1snT+o4LouqzMMtXs/nPPB5ZBxoO+NwcKvMPIsc7jNVnn5JLBPjSrR4y4C7qRuFyEtelNb3jFWuk6Q891n/Cf29c31xy4P1JWfdFl/uJklQVV7NtwCMA/gufpzqJ3MHelIZ1GyPW1p7PGEaMmxZSHkJi8MQZrgs1L7nMMnBYQc6kuhh0LOoncWPCX/OPJdXIvug5oerMRhldfmrazJURSND3ImxO8Mc+4LmDtD0CBdnWBEz+soLkYbe4MSHUejrtD94A4TOYOZZmfgo9UnjPAySOIiu9c5mE4JUMlEm3Lt96eDQEKymSrnC5Zoq0qKJmteY7wzCrD8BMd/txoi1vcbcGDA/AczMcXC/dqk/3A1HmqdqMamHnbE/+/awxrTPdc8b0TSZy8Di56MaA0Q=
*/