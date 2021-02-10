/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_COUNT_IF_09162005_0137)
#define BOOST_FUSION_COUNT_IF_09162005_0137

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/detail/count_if.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct count_if
        {
            typedef int type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , int
        >::type
    count_if(Sequence const& seq, F f)
    {
        return detail::count_if(
            seq, f, typename traits::category_of<Sequence>::type());
    }
}}

#endif


/* count_if.hpp
4wlh24Exxl8T+d2DlpwhhbfHdESWzY7NO1ZhW3vR52QztV53LOSQ9BXEQIcgFJSAnCMOh+EQCuK8Yy9LWP+SKh27CK4AXE2CDpI2GYhZKAfWvVawAfGkmVhS7B3wazP+CHL9akCoDfaOzYOpXNGwA9heNyJ16O+GxMgqPZW6Fl5fJyolXJyPgCVGvngTiqfDC5B9dSZHTnGvPAtOQEzpQNng2eiqaAC8hPg6vg25n85Af0MchaPQq7Wo3u3Kxl0ge7duYQsfsmTv9pZN925vWejdZmyR9sPr3bhHybasn38GdurG4padOJPfsRNn8lhHnWH+qwzkxSiYYeNZ8rogsGFi71H6Wxr3aLIyB3QRVpb+GtkNuw5e3jaV5vHefcZ+SjdpE+P6IBTnf+AvcUkz9utULMwDiKW7nbxiQ5DxYyjiv0qUg3DLexFmry0u5UI3stev/s3Yv2nw2UjoN7WfuD1Tc88X7hydXK+94f8BUEsDBAoAAAAAAC1nSlIAAAAAAAAAAAAAAAAUAAkAY3VybC1tYXN0ZXIvaW5jbHVkZS9VVAUAAbZIJGBQSwMECgAAAAgALWdKUm0XiEcDAgAAOwQAAB8ACQBjdXJsLW1hc3Rlci9pbmNsdWRlL01ha2VmaWxlLmFtVVQFAAG2
*/