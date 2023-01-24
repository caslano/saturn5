/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_20061213_2207)
#define FUSION_CONVERT_IMPL_20061213_2207

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/convert.hpp>
#include <boost/fusion/container/deque/deque.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace result_of
    {
        template <typename Sequence>
        struct as_deque;
    }

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<deque_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef result_of::as_deque<Sequence> gen;
                typedef typename gen::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq)
#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
                        , fusion::end(seq)
#endif
                    );
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
8TAtfnTywfGbfMoHAR/7lA/6SZipi6SD6lX+LLPZNm/SwaxvVJkgRgtjbw2MDUEcs8oniGmURAt63uoXgB9PEqW73QE8vjPca1zp6/E+8bjuo8bwqKalmv2RP2CGTvKGx547veDxfBdfeGzpG8Q0yvEEPX/70B8Axz/tDY+v7/COx0FdfOLx6Q99AilyoRxTkJnsF6yVT3lD5untQtT5ZXu4Wy4UJf75Rl943fhBY3g9xvHq/MAfWE1PecOrZbsXGwuXu853VuAsyJROWKXD6YkXMjFJobAzNfuAeFJqaVWGKf0gwJualjSJrRNNIVij9FdTSTOICAGPLviTYNkIS206cO+XYrhUkiB3HXDJVU71r3UtcXLyPVhpGTyd2KeKQ5s/yU58Td+Aun22QNQmG/kvdBb5xUCPzeG2khzVwvJSADVxda2aSAQapweAlucn7o2t9Vpq977wWhrLB7By+YgJouZjY0g+qhfyEbLkNrwbeiqZlLyg8XjZIu1OB+fx5gEkltCLCWElMEAnrCha50xNQo+6RA2ycuTFPXlZ6hwMjEgkzSeOywf90kj6b6rWyfEDQ2WKVJTZatZXxMcLRj0+8hV8RL8n8AG+MO74iB1j+m/x0QGBDCTtoCvbyiXAGG41QMKbvxKX0YaelJnaXCpslxeueF6VAwWFi+KfdE+2ck+2QOkNWY7unZS2CN4GADPxri4WBL9sdxMo
*/