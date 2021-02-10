/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ERASE_KEY_10022005_1907)
#define FUSION_ERASE_KEY_10022005_1907

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/erase_key.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct erase_key_impl;

    template <>
    struct erase_key_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Key>
        struct apply
        {
            typedef typename
                fusion::result_of::erase_key<Sequence, Key>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* erase_key.hpp
tAXaU1p173w++FrrkKv+edMou+PF6CQYvh/3Px6WVT/nIY6UDjmsleUYZ3B0pfAmFKGZFTOcwYlGBZHQ8HMi9QrHsQKv5eZhBMbAQmCwI8qRktgWPIBVv6hApNPuGCkUkh8fUXuMq5IrZNdC7m3vOHh3MeyPB2fDoHf+/uLDyXB8VKuHTsTr13fIoLCtFVBn22Y59kHV2lLbMIFmcs5XiXWAWfV8I2Ng34GGJHdAlbM+KOzq0VrsbCbbzbaEw1DyA5SPn57t9hqrq8+cBQ7mlMdTk+zyNk492RZvuxnA1b6trf/RnO/NXBtf1krVzbq5aG1WpOk+XXxExugW48cGZsq0uMP4nba7sQepa6NORnXbKNSEGG/b/fhINDcGsxbq0YbtwHgg5u7i02zta7NM+Q4w5ohGfA8c8cy0Yc4CvOliSc4Jml1XKWq2BlT4uBBRz1tZ4O1Epa2iqGA5cz1R4Y78f+anmMrftmIb6q5z5gVW0qqRxLYxyrTazEr3Boe8G1KFRbOqJyXgWE+KlCbgBzm2Fmy+cJRXkPUB0UktawWqOYhxuoEYSwuP2vQaYlvOitzmxCKR6cYty0rhSuHt3U4+t8dRX2zunlJ2BuGDYvChIdjpdFxabqBK9q/C81FDD4/BK5cyTZbbcPMp
*/