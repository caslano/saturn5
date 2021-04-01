/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_09242011_1744)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<std_tuple_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
jJwFGWP8TSWOBPaKRXKCzcnespQrLgQUUiruJzpUYQTBUbYb45SwaliJC52bjKZuoR6QkIacH/geK6SBuyHHMYlHIJv7lmmf5aEf7WWSqZAdz0J17W//oUU2jR35Pn7R6BvP7f8qRzzbHnwTyxrXW39jWqov5im/Pt6hlV2kP4Q8ezHWS1ZT4SnIbwfCpqIX8MVQKtv61ykTxqZ+o/g63NR+uFN4y2sqBl9zE15Zzf4U42KWmVsQRD051kqB9Br8PCCPeoWJOfVSDLWnGd5OkblKVlgysKCHKLp6azLujTYwPgv+cTyAAcz2aB8Xe63Kzmt9hHK+9u4NNUeyc9DWp3J7fNVcKJ+ol9VCgxSZkan1Ab7gB4l+pvxAZ/VknxK35eHfCGooAW/NC6b87WNxO4VdL4rxSRbDmKkCGw1Ptna5+6TaX1//UG5aZ93z2zLjg5z6UUSTtr+ltRUEiF7C9vjZ+8jKTVIpytNAjky/eUgLQJIQlqk75OKsVur+sDVF3FBXywFVXGg2cFXrFbnWPj8eRTbbwmy9jb7T96zyKoeW/f3XH+5oRLHlJg==
*/