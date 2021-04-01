/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_DETAIL_CAST_TARGET_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_CAST_TARGET_HPP

namespace boost { namespace phoenix
{
    namespace detail
    {
        template <typename T>
        struct target
        {
            typedef T type;
        };

        namespace result_of
        {
            template <typename T>
            struct target
            {
                typedef
                    typename proto::detail::uncvref<
                        typename proto::result_of::value<T>::type
                    >::type
                    target_type;
                typedef typename target_type::type type;
            };

            template <typename T>
            struct target<T const&>
                : target<T>
            {};

            template <typename T>
            struct target<T&>
                : target<T>
            {};
        }
    }
}}

#endif

/* target.hpp
iGDeuL6k7/R57TpWd++szrLdGKqtqVTcEklfqQkeXP3EneG9bjYNptgYWj7yeJgP+QSpSv2ri07ZZSewGsO1K4T1di4zFb/gCHtH9UB5snuo1WX13d2GK4Nfi4/Z6wbjLNg3MPjzchlWbbJAEzfzGbl7b+Bg7hsPjfhdw4X0GGWBUAK07SO5A+aJ7cdA2WA5x3AUkxP7Gh9pKAWwM7H+GhlvMruQ72lixxyQSp/S4eNbd/mWJYJxEhy73B/IgCWNCJhTXb53gB3l0I2VWKN0CO9Q1XKYzBmLXWPKkIA1ze5I8e0ecSn02nP5w/aaXy93C72PTY59TPtDnEJKIefaEXGVxnKrluAmDD/uI5QjVbYlG333wGIvao33pZ2aiehXsMyvpwu3Qh+aqcKpNssRmkPE/v2ww7Wz/0a45dHu7ikipTWqTGJDPuKkvp6EDY6qChHTDVVGQK37n+urK607geF2vyUthHLzlxIv5itrCcf6LP23/qe7ulvNVf+hFzXeYvGmsqKRANGnMuFRQcLBbWDG7wfU8S1ia2sZCnZ+0oGch8iGjiG4XPc+Yg==
*/