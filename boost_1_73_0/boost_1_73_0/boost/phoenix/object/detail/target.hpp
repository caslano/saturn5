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
lHyfIiqrkmarZ42BxiwFgTdIzELfD29VTLVwg3vmBIqtyDXDs1Ym7tJ7wIxg4t4nwjNHapTeN6qwlk5bYrdElT7toAK7a15siWu9vCvgPNiQ63EGwSRc4MS0dZhKuVC+HyljppJ9BkmktyHjdCg0/20JtXWYN1hk2ap3e16VDVtVDuZhdme3ZHd26+zOX2tw8DwF74Xbu/rg7eut1b9aXdUkzSyCZXmLl4QlzFgdiNRiuLUNH/phftWU6B5fgE/EF0FR+xchOE7Hw+anqoRygscicwq/YQzRxR/4k/6GwGV3f7+q5BvHUE5B3tAtlbUslkemnHaHYUFoB2N09qnPxdph388ShnpRR9o3Zy7xgmhZctNXMaxOAa60K93yuD0crWRRurWaR4N7BEpILpMZ1HCQLS7zVNkDjYJtVxEnwh2BlPIwmHbHQ6nfQqWoDiWFAkUceexeZFXRI5DEHiCrEf9WuGJpi8oev7oOgXxCW6y+2QTlTYjMPoOFjirbmY0Buy0GBovIeVagB0rsZW6bo6UW6EFdbVqWNiZ4+lbmnE+f0LGnJ9nugMneewlVoajFcor6yfUTo8iFETZ1DiMjWd4udV/lC8kIcd//gtDr0DR4uPmpMkBlE6Rym9V26CFLv8Ya1dkjhd8TmmNz
*/