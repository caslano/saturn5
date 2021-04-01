/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEQUE_TIE_01272013_1401)
#define FUSION_DEQUE_TIE_01272013_1401

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
# include <boost/fusion/container/generation/detail/pp_deque_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>

namespace boost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template <typename ...T>
        struct deque_tie
        {
            typedef deque<T&...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T&...>
    deque_tie(T&... arg)
    {
        return deque<T&...>(arg...);
    }
 }}

#endif
#endif


/* deque_tie.hpp
NxbW2iGHx3LXKIrhHX7I4Izxn5vlybW1ne8J3F0B0uRBBRx79ffXoMuFOMLjCHe3YNt/DEiGQCFWzR7rigKEPNKkENSGFRaMhrj7hBCZD0xBKcXs2OKjhbmE8sSa82z+JDv7C3TbK95/xWBnQnURl/Kk1huezf0jgJXJEYLL2GktyatKqKQRRyqH9n3BIcGMzCovsQCmoyf31ZfWcoNFQi+bNVFwZvoAljGxeqMIqrmyYoE4kOb0NpLuv9BBjpwcezMZYDYhghytTJVYPSNU+Ins0HSBHJJQ3H/r8NcFMDnUgJKG7MfGHLr1RxVEgrl4FhFUdWRQhbTiW6z5ItZ9NUbEDd2hLeAkJYa6wn7SXVgli82dFrfhCEpXrVv3tuQ1XWW3l7pMlFHqSkclpHHzg6p4MxNrHnFl0XcdHhVMnqATmuKHvJ/PAlU1dvoYX7GMUdsdCQYfBtofBJqJ+p9MjZV4oqP4Dlv5hNSuSwPIY+/7Roqai35vrS8nLuRsXptQyzUNhFI40FYCSWZsIeCSdfjSe2scJzoEqfSm0i7v84ofeSXE6Op+aUOydQ==
*/