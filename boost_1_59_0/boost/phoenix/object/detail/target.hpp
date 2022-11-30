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
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
*/