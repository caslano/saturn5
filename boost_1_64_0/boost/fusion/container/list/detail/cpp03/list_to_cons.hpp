/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LIST_TO_CONS_07172005_1041)
#define FUSION_LIST_TO_CONS_07172005_1041

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/container/list/detail/cpp03/limits.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#define FUSION_VOID(z, n, _) void_

namespace boost { namespace fusion
{
    struct nil_;
    struct void_;
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/list/detail/cpp03/preprocessed/list_to_cons.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/list_to_cons" FUSION_MAX_LIST_SIZE_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion { namespace detail
{
    template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_LIST_SIZE, typename T)>
    struct list_to_cons
    {
        typedef T0 head_type;
        typedef list_to_cons<
            BOOST_PP_ENUM_SHIFTED_PARAMS(FUSION_MAX_LIST_SIZE, T), void_>
        tail_list_to_cons;
        typedef typename tail_list_to_cons::type tail_type;

        typedef cons<head_type, tail_type> type;

        #include <boost/fusion/container/list/detail/cpp03/list_to_cons_call.hpp>
    };

    template <>
    struct list_to_cons<BOOST_PP_ENUM(FUSION_MAX_LIST_SIZE, FUSION_VOID, _)>
    {
        typedef nil_ type;
    };
}}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#undef FUSION_VOID
#endif

/* list_to_cons.hpp
kXf7+rG4B6DBe6U7j99G/J5x4vw20b5nHK2fR+x3+u/6eXrmSsdXXr1ofcUZt62b3vXg9k8vO21a7H6eJq/xHoAZ9IMMA5PBQ9Xr+l7jPQB7c32+DzgI7KteL/ca7wHYnevXKWA/cB/1OrTXeA/AVK4n7wtm0h8xP8L3D70PmHsA7mzvHyZ6D8DmA5J22LuH0a51/1vfOVyK62gt8kvITea6t5nMZCYzmSmOtB3i/8uqSkoSFv/fWCDN/VGkvPW/f97fprdFiSFPNYqlV+b9kJNNim7Ov4TlWpF3R96Tc/6mWmXOH9G3BKS5bnvBnNgaYs6/jbr3QE6i/rmQb6hV5vwx6VXXbxHn/F1Zty6c8zfWqub8cdZPP+dP+Q/s+2/u5fXfmPNPlOf8P/W9+ZKUp3v93adT+a0vTv1sauxzfkuIOT+K9EpMB5PBwSDleD9B2QZz8N05B98T3E8dy0e5PfRy/G51Erg35buo5Bop11W0VkA9KWAXcJ8o9v3fas75//dzfnO+H99837oae/4jZyFPXm3O981kJjOZyUyJS9th/l9akD8kYfP/XHn+LxXZMv//y9byfn6Kwfy/vrZl/g/hsPNYzTfxDPz9ubWt7+/f2sbgnd8FifP3X2Dg77fW7hh//46a+4vn8tGvCZhz/51r7l8rz/3LD2j348JpNwy4fI+jO8//8rLTYp/719fG5u/PrY3N3+9bEJu/31obnb/fixNKVkf+vpg5949t7r9LYbI5/9+J5v8ZhcmttgawENfbUuQG5HXmGoCZzGQmM5kpQWk7xP+XFgxLzB6Agfh/i38NgMW2rAP8ZmuJA+hnsA7QuEC1DjAs8r36AvPxgZwrO8Eh4DhQ3ktunnYvuSVh9pLzqvaSqxfMmVcI9pJrEOwlt1a7l5yyP9wKeb6NKmJ7OPUec3seJB+HIpzLb4BZBXvMZYbZY+5RtoODayLTuSaSNU+1JhLnN/WUNRGh/dp+yeAef+O5TjKW6yT2uf51kni+56bVq9vDjHpnc+3ExbWThrmqtZM420G/dmLXrp0Y2cj1FON5sni9wGg9Jfp5tXg+H/26gHg9yGidIvr1jmjfb4g2dkS8jmC0PhX9+pF4Hcp4XUa8rmS8/iVebzJaBzFep6vsKR1varfgouGnfZaeM+/VM08uLRphvL6jxChwfaO94LtSF3M9ZRGYDC5Wf1dqnl/OKfiu1FCcNwQcDo4ADwePBUeAJ4JHgjng0eBscCToAUeB88Bx4E3gceDt4ATwEfAE8C3QDn4ATgK3gCeBf4BTwJ6wYSrYB8wBR4Ang6PAmeBk8FTwFDAXrAWd4HlgAXg9OAtcAxaCj4PF4DvgbPADsAT8CywF26Lu5WAf0A0eAHrAYWAVOBo8AxwHBvZPykbOYvs52O67giPY7gO4HjVQKg88mO04CMwCDwGng+lKebwXg+MF5fXkOlUq2Bvcl/2zH3go2AscC9pU5TWwvNmC8vpy/aofOADcn/17AHgceCDoAtPAhRHGtLy3unViWtK4tjUCnHFU9Psk7UxrW7Gua60rTI57basAeXKUa1tY18L61v93bau11rW24lrq8iC+nYU8Atn+oLm2ZSYzbe+0Xfz/w6Spf3zv/gf8//X5nPujWAvn/T9H4P/Pmque94ePY4/E/2+Zu+P8/+6a1vf/N9T8v/z/O7ufP1Hv+//f/P8Nsv//osKPTpubWbNq5mFzPh9ZdON1sfv/s+bG5v+3zI3N/++uic3/31ATnf8/0vf9ix5snXnS/8X/vyPnSKb//98zR/LiOlqCvBK50ZwfmclMZjKTmRKYtsv8PyNx8/8szv8zVPP/HyOY/+fWqOb/GYmZ/9tqdtw=
*/