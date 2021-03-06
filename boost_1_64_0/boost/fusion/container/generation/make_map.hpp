/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAKE_MAP_07222005_1247)
#define FUSION_MAKE_MAP_07222005_1247

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/generation/detail/pp_make_map.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/support/pair.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...Key>
        struct make_map
        {
            template <typename ...T>
            struct apply
            {
                typedef map<
                    fusion::pair<
                        Key
                      , typename detail::as_fusion_element<T>::type
                    >...>
                type;
            };
        };
    }

    template <typename ...Key, typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<
        fusion::pair<
            Key
          , typename detail::as_fusion_element<T>::type
        >...>
    make_map(T const&... arg)
    {
        typedef map<
            fusion::pair<
                Key
              , typename detail::as_fusion_element<T>::type
            >...>
        result_type;

        return result_type(arg...);
    }
 }}

#endif
#endif

/* make_map.hpp
yw3Z4HaHrxywzNqMhhxN+57ssJ6fgoureoZcR1ugDuAeOKXOW2UyT41BSdpXtBon1jVC9m96AfUphwUOMWbfGeRxOdBttGijEaM6qLt/D0Hb26e9DA0L4XY34HJZSWcelauZdMp7UtpqobJfa+u4RxwxlJ/bSlwcavMTBfw6V+D8mU1KL3Ey/8EIoG8rj8SkwuPS4zCNxOL89WmtJw7N121c+fGk9y9LC+jqStADoXbTk5UJxIauYOoAV/uIOleb4LQIF01xKl0LiGjS0mlH3JLHRXtM5lrmMzVdPLzWfQX19EiR49CJdLziu4dtqD4yprdoPwFCzA2A9gJWjaAg/LZo+3ScrEvyCrBUrT+zSL50mQwvYrhDJzNItYohMUtyLlVO7xZ2JN8yhpT7qlR7MAZRJGRFvpAwwjv5FZ3oS8rqKCVh/5oIQgWQIUl6lBaVw7yvw5i4IplGAHFQkQQfpbpZ1oE+MD2DsHmWDMmu76rNwuZgN1UU2c95+y75UNCWI1M6V+hSZOPSAuNFGFyjjkETlLg5IRRjzcCrjTsGRjInaKgiKhexPCYORA==
*/