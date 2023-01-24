/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_IMPL_09232005_1058)
#define FUSION_SIZE_IMPL_09232005_1058

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct filter_view_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<filter_view_tag>
        {
            template <typename Sequence>
            struct apply
                : result_of::distance<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>
            {};
        };
    }
}}

#endif



/* size_impl.hpp
hXWL+VJf5kZAOORWll+TLLHzhVv394flClbQUcIzJf1uzkesNUVgdMOYw6yZ4aukyKjSqd5PER5U0X70AFRudeYh4C0rbMZWAZrJvrEc/vfAd8Y2OalSD470rHqzbvBa1FBk5Wjc+Z/hM9b3G3F3Peyo0I+MvbHdtLPdz6buIWSB4fXZAtbNWmG30uP2Z3+m7M+S8H4ed9jde64So194UiY6MrrA8h/+IHDNUhb8v2K0Z+k5N1vMyQBxcMf821CriqBbJZKYh5EPVmGkri/4iOY9ejf5ph6ANWS/QSiQEuhcSuv0xqazxG48ChZQpjpEylcMqE5bKKoO4gAVoRicXJWdgV1jeTCrHCJGbE2hMwt2YJe2xA04NQS8U1AZjmILuTjnMxX1mkzMRt6MDBtylkN77J19i9UBphz8I2jCp5UQA7A6gLcL/kTavv0mmaCdNSZRpZ5XPGR7vyrONS/mrVNROfjO7StRQdw1ZjBq7Bl3WrlGKkX69+qWv6fR6UnMla5qZOUpde9Hrh0GxQawB8TY6KZNXSqIYFUmx8j8tdeX4WqITdxHFa+kFr5eJi45E7Nbmh1Z34d+/6nnV/CTUZsElzzDtw1afvBg368Az/3BtymoIQfCQ6PWC+T98r1d7jyDlOxp+kH5cOoawjq0NFq0FdOiSkDuDXMPpj+f3ReVHP0c2lEfkEWEyzQUK+BS3dATWaThj3voGkY/
*/