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
svciHQ6L8OPtExvbNeTY9jr784sU2g+LBBo6yqO0jAlw98814dijMqXVjLqsVCVtjC6aRXoKhWwnUFd0dt/FuAa8+1SRVSlUTdRaZf9HaZfY3f3EtfNN+H/3Wsvd/c4uJ2wpPj0cxW+XFj9ChDbtqKULq34C9gLYLrC/gLGzflss8Tfj5Vp20XLtSLCZYA+CPQn2B7CduuqNOgn2uS5mgKUlj0e1q/7BoyZynENLl8Tapz3qGcG/e9Qzgou09Kw=
*/