/*=============================================================================
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_LIST_TIE_06182015_0825
#define FUSION_LIST_TIE_06182015_0825

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/list.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/generation/detail/pp_list_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct list_tie
        {
            typedef list<T&...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T&...>
    list_tie(T&... arg)
    {
        return list<T&...>(arg...);
    }
}}

#endif

#endif


/* list_tie.hpp
fa6l+R3rHqpiimjO+tH7x88t8zYv5sypqRSSjR6BxHIQEIuKJH/hozmdqt6k2PCQlmbUAY7vXuZ88HcSvwFfkT0F8i6vzADFxlDyaGHOX6jJb1tNC5BsMtfXD9PiFVr4btSp58jge5rEuUygGgHrQ5rQTkbi5eHYU7NGKNnjVyOvkJI38LnTW9RAjq5w1Ug5qlETPgAD/oNWMRPKwj9ZwQ1iFYBoYopjOhqe0tj1d/VIw+uE3VxXvdCQsK81vyMnME/MBOWsOHc0Y3npeJoIgolumieDQIldBN5Hj82VFhVIRr3lNmqaEXcWYJe6bm3YRyL08qIjsn7fJXmefoJiGm01jTcvncew2qtzH6o8rSooGDwMw/h+gpLffi4hU7QnHz6wF/wTUCkGonxSOXvCU8U9CVh/WWSFDwu+7vCzAz9/iJO0nc8R5abHAmsM2w2Bg7cH45zldJKUvwxlFqxg3sOcI1vZ+gkOaGjPZ4jFoaWiQ4Gx79VHmkLsU+JDWl7Bd+8EcGTM8sAczJ7nn6G8tBWEHXeGGIpVG5MdW31GjxbxPsjwmJL0NgfpcQ==
*/