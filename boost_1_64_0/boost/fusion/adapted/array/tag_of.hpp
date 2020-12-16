/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_TAG_OF_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_TAG_OF_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>
#include <cstddef>

namespace boost
{
    namespace fusion
    {
        struct po_array_tag;
        struct po_array_iterator_tag;
        struct random_access_traversal_tag;
        struct fusion_sequence_tag;

        namespace traits
        {
#ifdef BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS
            template<typename T, std::size_t N>
            struct tag_of<T[N], void>
            {
                typedef po_array_tag type;
            };

            template<typename T, std::size_t N>
            struct tag_of<T const[N], void>
            {
                typedef po_array_tag type;
            };
#else
            template<typename T, std::size_t N>
            struct tag_of<T[N], void>
            {
                typedef po_array_tag type;
            };

            template<typename T, std::size_t N>
            struct tag_of<T const[N], void>
            {
                typedef po_array_tag type;
            };
#endif
        }
    }

    namespace mpl
    {
        template<typename>
        struct sequence_tag;

        template<typename T, std::size_t N>
        struct sequence_tag<T[N]>
        {
            typedef fusion::po_array_tag type;
        };

        template<typename T, std::size_t N>
        struct sequence_tag<T const[N] >
        {
            typedef fusion::po_array_tag type;
        };
    }
}

#endif

/* tag_of.hpp
y8XA1gNbSCMXD78NbEVdXt26Bd7LPSD/SOq0XYYPHK43xnbB+y+czN5aPJG9pbymTp6k013YR6sAEz4N7CJNvdMue3uFltVr228mH7/fC33ANhchBqRo4XeuUgXeJepBDRVtDFJgVBuhbcck28jswxP62yviVlt4tugjWpQSwZw0ISqLiVYU0ZzjRua3KW6FLWX22mW3vV1NSp/iy6a3dIwvQPDrD06VEu0oTVbknhXxhPmW8kCKe/W3yMHsmQjsa+KDHFKHm02buEzben95z9SxoWYTnyd6kjgsrsU9J//BsdC0a227zbZIpIFCwX+a7rLV1gXNfu8aY0rm/pqTMKC2DBmvvzBNRomfZacdZas7GwvMjvFA2F3mBU+QXW4uQ2TXUJr94FWoyG4CltG/lSl8hCjcmbTzHlLO7XfawtOksYvXkplkX+kvNPep2oLcp2aVfJBvzJgRL8Fc237ik1/G9ikv09znnXxJOrmH0sMdbWC/+J0XE/gNF1P877KYal9cMSn9NIpnsy+YmMjvk8TCLrlsuf1JCY38Am4Yzw+pbtmTbw/00m1TqS3YXJjRTNEnAArVXvJPtNf3U+r5xnuzcjUINuGFs1001UVzaqbG0soKjgvBp/dMSbcjaropEZOtJSd7JgZrBu9md5q9Y90kqwtDf+NRnehLZQHyXkL7pXPYbvZ2P3DwwrWMhN2lsuySqsxm3k/kN7R8mFvsN3MaW1bv/UIqyaSbZduKabole5/ALOIpWfnhveEkwl0d27++etLuezlAhw4V2bWRHBMCcM6bIp4HgrhtbMMklcxNOwwL+f/xY5p1IrtI4kPkmDWhCYFjPMiYINObgdxENwi2I9uQayjFRUFeRmkW/5cun1nPBUUiJ0GLaGHEIUIQYwj74Z7wAS58k9/xLCES5wRThvLODAURmnAaoaVyE0oUoZm2Q82kTGGHshFaYrBtWIRmUlRfQxahObLaG0ojNFMtQksly5tGaL66mwlBhGaSK6JFaEL5eEwMQTxmgsVjplk8FsjS7Pw0EDVr4nyMZhaL0UTLBGSiZgMy0ZOATLRMQOZk8dJ+Bx4nMZpoFqMBJoySGE20IEYTts3FiPlGtDD2ShXncBKjUbSjJwVOVBHadkyyjRRzD39bEb0YTSiK0SglQliYJEYzMSyKxWAheeuEbocxmghBjCacidFETWM0EXMxmsh+SJYI6H5JjGaaxWimWYwWiiZlYjSRe8RoZrIYLZYGCsViNKE4RhPJj9GMLUYzTUaJy2IxmnAYo4kQxGgmWIwmUhijhYrtxmI0U7wYzUSL0UyzGM0ki9FE82I0IYvRlAwQoxkzRpOffoxmbDGaaRajmaSd3GI0Rxvwl8VoTrAYzRSL0Uy1GM2kTIxmth23RD9JQzYRg5AtFnbJZcvtXgps5E3EJlolBPHa7Bxva6e2Hqv1WqVXdrlhb6ukNlstiQB76ba51BZsLsxopjhqFNWLGg0tahSpd9RoVq4GwabgcP6NJt9ols9UdFrH4ZHKosGMYttJo0aKydaSE1ATbc0kahTNosZIsrow9Dce1olFjQKIFe0X5rIgahSOo8ZUcrtLo0aqOvta1Oij5XOznRc1+mxZg6hRJIsIU7atmMYt+VGjIKJG+eGFiRGi6qOoUSSLGgUsaowU2bWRHKUCMOf9qDEQ6HYcNaaSuWknBlHUaJp1IosafYgcsyY0wRyzqNEEnp25qNEg2A63MTps5ZUH4EzDrmKNfKScfXnjTVj6OpbW55tp5JVq+2ng00xjrGYcYzWzUdRYFGsdnQSGogVnaomw6zxHrl0PyiRclEmWVqamQOSlSKGXImS8PFpU88o034lE2DVRZh8=
*/