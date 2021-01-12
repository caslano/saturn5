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
xfV9nK5Rc64twGbTqhDdzwJ7dxpDQSy0IWgQHO/69S1tY8CMDlUEdI/bizLhDlXF/L7ZFGVMQ8SvBjQT6E/6p81Vzy5LPcvvn3wW4iKjD2LH4paq9zHZe8xaeQ2fVniFlE8465aQ9fA4WonLhAuOVtfycJhoPEVgrpGaKE7n7pLkMPtP5PdzyatB81LCfe7EsDudGzwYMqB5QdvD2dU83mOI+TzwAjt7uGY9D4uk2pKTecJ4
*/