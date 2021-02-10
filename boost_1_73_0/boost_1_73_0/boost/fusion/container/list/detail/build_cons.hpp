/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BUILD_CONS_09232005_1222)
#define FUSION_BUILD_CONS_09232005_1222

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <
        typename First
      , typename Last
      , bool is_empty = result_of::equal_to<First, Last>::value>
    struct build_cons;

    template <typename First, typename Last>
    struct build_cons<First, Last, true>
    {
        typedef nil_ type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static nil_
        call(First const&, Last const&)
        {
            return nil_();
        }
    };

    template <typename First, typename Last>
    struct build_cons<First, Last, false>
    {
        typedef
            build_cons<typename result_of::next<First>::type, Last>
        next_build_cons;

        typedef cons<
            typename result_of::value_of<First>::type
          , typename next_build_cons::type> 
        type;

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const& f, Last const& l)
        {
            typename result_of::value_of<First>::type v = *f;
            return type(v, next_build_cons::call(fusion::next(f), l));
        }
    };

}}}

#endif

/* build_cons.hpp
Skx+/u7lxm75QJwRtnQ9be56utbXvMQDqecclFQOIFdQCCsLyrTlXAOksAp++/jtv+oiHl2/215TJeptewMYzLBpUzNST69IKrY1wSQtNHnbvxwPzhS5xxg7ocdyLtuqt5jzlVJVNcrWHk4VbmMPJgwmJ5JpS6okNwkIWuukbS93PMvcC5NPI+UjxHSvSEoKrHr0ecvezD1JDrXL7uQ9GCZocijptVrpXj0qWg+qnDXrCtq44WBH1msXR0khgxI5RRSYS3LdCRNvRkjUi7MKDB9xesncnMf4vbgzfL9SMqPuG0hsYZqTeGlIID296uNpZkAkuNuQKOLguXMZ9v9uOadPWI+5f1urYWg8mZP/5yfjpiSonmGr9sUW/7LCuYNQX4VMv4dI20ljqSdmaEfTRyj3mXdrQQjXmkgI3d+GQGp3X2wpIcaIWNmudCHvVqkXWALhCOJLQPILoR8DKxljdxkl6EHvzd3wEl/+aVAYkd+UJOyZ1JGEY+CUcT8UxlmkhfVQKaSRltm9poC7E1XFxXY4MuS+E6tWV88xTQw806WsqIoJIxQHld7jUTCER2BISHv1ExaexGhFMWYICHcW3peZIP+1WOFC4qkdmgj5654nYMxlyu8jKitjGMaR1gP7Rrrcvs9Y3hRCNWg2
*/