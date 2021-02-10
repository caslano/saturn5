/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FIND_FWD_HPP_INCLUDED)
#define BOOST_FUSION_FIND_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct find;
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find<Sequence, T>
        >::type const
    find(Sequence& seq);

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find<Sequence const, T>::type const
    find(Sequence const& seq);
}}

#endif

/* find_fwd.hpp
rybl7KbIZtMAWBlL6kFDmxNJHbFZuuJFRC9QSwMECgAAAAgALWdKUiE29nwXAQAA5wEAAB0ACQBjdXJsLW1hc3Rlci9pbmNsdWRlL1JFQURNRS5tZFVUBQABtkgkYGWQO04EMRBEc5+iJYJN0HABRE5GQELo8bSZ1vozarcX5vaUd1m+DizZble9qhuSElJf2LmnPicJ1zNFSdwoVqUkc+iabonfjbX4RL2xtsm555X3gzL5lGhLPvCC72Qr0/hArc+LKAerutPKGBxyMxtkoG9j2JedjlIWqtFxOYnWkrnYRC+1U+7N/gJpzRet3qS8ThMwCOvmOnY/rO/GNq0PzmGAmu0JkDDZqhS7ANa8QVAP7ctg87aS1fPzD+6aFhiNW/cv1USPRtkfAYY4uQIryZHTPnRa15OcAN6t4yHXRaIEb1LLZ3m0XTo/6/7OGXxBU9RWr2g1Kg9RVPfGXEAXIypAFLRuKDU3N+J933sNqxgg4QyzD1BLAwQKAAAAAAAtZ0pSAAAAAAAAAAAAAAAAGQAJAGN1cmwtbWFzdGVyL2luY2x1ZGUvY3VybC9VVAUAAbZIJGBQSwMECgAAAAgALWdKUnRapiYcAAAAIQAAACMACQBjdXJsLW1hc3Rlci9pbmNsdWRlL2N1cmwv
*/