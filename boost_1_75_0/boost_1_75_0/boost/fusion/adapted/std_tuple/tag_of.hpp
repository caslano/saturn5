/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_TAG_OF_09112011_1842)
#define BOOST_FUSION_TAG_OF_09112011_1842

#include <boost/fusion/support/config.hpp>
#include <tuple>
#include <boost/fusion/support/tag_of_fwd.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;
    struct fusion_sequence_tag;

    namespace traits
    {
        template <typename... Elements>
        struct tag_of<std::tuple<Elements...>>
        {
            typedef std_tuple_tag type;
        };
    }
}}

namespace boost { namespace mpl
{
    template <typename>
    struct sequence_tag;

    template <typename... Elements>
    struct sequence_tag<std::tuple<Elements...>>
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template <typename... Elements>
    struct sequence_tag<std::tuple<Elements...> const>
    {
        typedef fusion::fusion_sequence_tag type;
    };
}}

#endif

/* tag_of.hpp
CqLd3i0G+ILMt9WGXFVJXu8SI87CDx+TsFvYZYJeCV+3RXpPtnWVDXwR9gwm/OXyuj0E5/YXR5aNDod+43QW3sy/cJITC6f5ZRPeJ6Da90Xb7o1qpSLrItLreVQEkXXtGd4J7yNcFtxM89YCtu7OMCRzSMVUxsDgs/QAoHEPETv7+QTyd3qy0+W9e7+odugfcWyUtj2DRilK8LMTbdJ6tEm7VJvUbKCwSaLeeYAn4z3B2TMyd+I3DSDK8+ib5gniNwriyjfNk980z/qmgnlwhJoMN/mb2hOZzW7wtxi42YqC74OVHnJRpMaE15xL4eRM+s8IZgDwN/OE31F6B+4QpG/G9dQWwhkGsMGC9hlecAd6zeWtcnJLEUho5mvIdSb4z5xQoD1K7kRwzoP5Olbr9oYlgM8jTAIG+qnd2oyCqEKs2D8AjBk2S2qGd0RCvHizQCcYhu0DIDj5h9rbBesLgI6oaQHEmf4eh26UVjMtkM3E8IcAT1ywwIUODeImh5ZFUmhZQYh3P7TaAgQzFRNfpcocrnKgq+j+5RrXuVzU+XytWmcbCd14PpbjSmNc3gnLaRcM7gbX2mMv1LpZYjA/r1RbcztUu7o2W7y4Vla7VlSryWrBXURU3F5UvBYqvgBL8sgEwTQAyLwWyOKD3lh1RG+uuRIhV6Dmda6yzBngX9YenXMGzoBDJsyzhqg64BeWoqC3zkCYMYkZsxLd
*/