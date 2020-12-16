/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BUILD_DEQUE_02032013_1921)
#define BOOST_FUSION_BUILD_DEQUE_02032013_1921

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/container/deque/front_extended_deque.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename First, typename Last
      , bool is_empty = result_of::equal_to<First, Last>::value>
    struct build_deque;

    template <typename First, typename Last>
    struct build_deque<First, Last, true>
    {
        typedef deque<> type;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const&, Last const&)
        {
            return type();
        }
    };

    template <typename T, typename Rest>
    struct push_front_deque;

    template <typename T, typename ...Rest>
    struct push_front_deque<T, deque<Rest...>>
    {
        typedef deque<T, Rest...> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(T const& first, deque<Rest...> const& rest)
        {
            return type(front_extended_deque<deque<Rest...>, T>(rest, first));
        }
    };

    template <typename First, typename Last>
    struct build_deque<First, Last, false>
    {
        typedef
            build_deque<typename result_of::next<First>::type, Last>
        next_build_deque;

        typedef push_front_deque<
            typename result_of::value_of<First>::type
          , typename next_build_deque::type>
        push_front;

        typedef typename push_front::type type;

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const& f, Last const& l)
        {
            typename result_of::value_of<First>::type v = *f;
            return push_front::call(
                v, next_build_deque::call(fusion::next(f), l));
        }
    };
}}}

#endif

/* build_deque.hpp
VBMiWZ7CMq8i1iWU8O9QNLsPXTGa5fwtgfxVjdbuS5fyvhpP8t5vDOvwfj/hGOFHQoyVvBOS+JtNxjxvxXVW7V72rjHkCyutdfe0X2RZDSHQpt3fjsUsglesdq87BEttxGOru+8dz7Ia3Muys3gIlXvgaSzvg2V4ysb2mMT7g1h7Xzy4mOMQS94ItffIs1h2DEtxM+HHQcSNgWOJG6MxOJywjP3j3xZCDP9OIYSFsw3v1/DvbYTa++tVy+rusXstJy9KXISdvD+NVRgp8/OlYAzrJBFO8X4NlrGsgrBtOeviCYLPeO3e/JHl2v3505jD8enDcp8S7X59GJrds09i+UGMH89ytqm9f5/C+zKC8T7+Vt6HKpawPesew9OEGJZVjiceQuAK7T5/ItrwBMuyVpCPOMoDw3CN8ne0EcoJe4lrPx4jGNsFzvLebwLbEA6u0NoJ4vh3HsFLaRvASkI1oT3vT7JOKL5IfDWEGP59egJpT3RuT4hcSflhOH9LXEmeCLsI8byvwix0bG84wfJ1LN9FOEQ4SQhkuc8k+3aIYN63vlJrj/DK8PYK49/RLEvCJCzBckIp/95G2Me/D+AxNLZfVLMsuFRrx4hU5H0ylhLax7MtGts39vE+Fo9jeDxpX1XX3hHKv5NZFo8lWE4oY3kJ7yvj2R9lGe8reR9CnuMJFsJWwgFCDcE7k/YRQgLBRthGOJjpaf/wvDwvz8vz8rw8L8/L8/K8PC/P69xev0L7f5HVIn0ALkD7vzLXXxY3pGpuUOb6I3arLd1WbE21ZZdobVf8/Xv+7rdJ/r4wPTevuEgZ/7+wUOYCXG/Sf2CZtPssJSg32Mrb1fUfmJko+Wdwn9XCpIJujJNX+g/8s519/4FEkzazZHxE+hRI3NKHwP756NKexD+0ca1LaEkLkPGwqyLUZVab7KSxfa1E2px/Vi7h8RO8SGnr9jfbP2vuooJ0G8Wl9Y8wb2Ebr0Tcil4IFrX9s4m6r1+0d+gr4WeXV62vhJ9d3wBtPLef3h6nNuwFsWwXy17qoi4jP9lFqYXFduOgJY6c9Fwt3kiTZ8knO8w/EK6/XyzHorb91jIsI7dQ74vxRLu6dI1tdj8YllsNz5H/OMB+/HYs/izrcjCsxjH422W5l0N7eZi33NeUOphC8Fbayy81O0ZqeZ5TG72MZTceF9O6Zl6vHJ53bsizv+S5GXm2BKh5zrZa1QkalALj86v2KnE7z3o5GeYq8NaOlZ7fi9V10m22Ivsxi8HSnvySjOE6iC2UstTyRQt3qs3qXJ5ujYu/tqPDuHiT8kWnz2iZU1nKeEfzz7gsUzsG6PXy0Uu17dNTC9Lzs2mTkHpfTND7DqXmkaLUQxd1OVna6B37GyWa9Dcyluvm5s7jYZeQAUtQbfv42JlTB6fOSpoYfU7jYXMjzcfDhrRwHoOaz7oVzume0xjU3MiGx6COqC2DFs5lcDF1q0bPy4SZM1PHT5iRlDo5rpH73zJK8uGQZrCP8/63YV2/TiZpNnLfW0a5v+/lJvMA+LJ9op6PSROmTpgxNiF16tjLJyg77/6+dwwwP/bBLZ333Y80y0zTlJ1vRJl3DGh4//X639J5/1vTcFal5yVxyviZw1JnTp5EllInT504TSkEt/PSarD5ePfQVs5l4Mu6p12nqxZEY+YfaDW44XIYUlsPTMb9H+b7OzzY2E/m3PvIGNP60SStN0krzS6txtW1I13t0xqqj/c37/9THvzr9P+pzYePyZj7Y+Sj2i4fja/rR7o2fIxrP+t+bbQYYkhQbV9G/yiWd1bzwPdnZk525pLaLmNWd+YvUr4/A7vo359qWaTp3zl84RQWpaZLGeXo3/eSAn8=
*/