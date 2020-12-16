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
SR8PlRECd2jc8xTH2ul8JlH8Spfow57SemG4yy9zk0Gvcld5ZQPFh8AkSiojf/ilgs0/a2zWu3DC5c3yy5//l4+2Hxp5j/59gqJy1SSKF+q3ay+TsNGyQWxo0xbK0sGAm9eNdlHErs1xqM62fEP5yumZiKTuVh+xylCNeHq34NWL2R1V3n/g9//H6deTd1Rm8oCsGFPTtRFv9hZ6YTyRu61lfJidXY+W57WzOxnSQfZVwh6552+1k8iaFqpJ1GHVrK82lqa9P39dtWyrieWDe75csqky86TYl02UFuWGwAsyYZqDCw1iU3YTcZLDvCm7F2tH3pRN5CkwZXB/JQ7n4UchJxn+ZOB36iUh2Djs5Kw7eU2+M72UANk8J4Li9i4zly4jurQiAu/wDk2MziTwpN/aQjlCrckLNwmMHHN2k8BjMAziI91j/vcsbCZER7pxJuaicqSrMvKLZzVGPmM5h0mgl6UJNznYpOAOpun3Y5WzgXXuwnVsJLbOfw+QNAG/phK3b6jQq01NWnKSIMBvs/CprCrKx5mhx735x9Pzj8yzTc88nka2VwsNyfQT7Z+JeNc/2Lse+KqrKv7+bTzGg/fAxxzybwQoOqiZpNAox9pLNGZvk6WVmSbZ61lG7D00Y8B4LPcYr0CZaamRYWFhYalNA9uMBItsGCqVFRLV7/nIVs1cNlnfc8699/3e24bT/vfhffb77f7uPffcc8/9f+65505k6S4lJZpgB/DWWChl/7oamsvXPFPurrE4I6zxFStWqmax0SwRZi1A26qZ48fOEmWv4tgZIJ83casNCzfZWHjnVsnBhcDyypp9bxk1uGZfoUtX4z6n1uz7k75U5eT642r2CXVXGOYu1aSNUKR9CwDcsM5V6cXPttV8k78Pm/w12/L3yJcEyTVFRj2wRlTFPElnVj1waRGxvkvE7CWi41dxARQFRTkNrYMaRUlZfRfOTJHFZt7iDyLUHQ7U0Z6N9S6tIRp01x9J1ge5Fxiv1QKLmKOsxZBZxOl7y+iUmJVc6OXPgFt9BjiXiDKN64fWhuP4AYfWB2FMuiKM5bQmAwSnxSpqvfFx2JRnefMzVA06y7n2dDFdXVwGQQBUhA40+KD3SPPUtYX9NH3qcsQL0vf3yUwqXqYq6nSbrkQAWYJew/UBR9zHpXvGJVy6pN44daToGM53ZRvNPQMbzRvulCL5OeqXvlWVpCvxt/NUEQmP1FV9Lvc/Fo4rBHQxf8cUc4+tmH/+RcF5g9eoVpqjoPvsGpbTEOrJ7Vq3s3Cvm9z1+zKzBHJ8fCogXRryiA3SEkicnEM3TemTjnBNRxnVEinZitCRhpGibyjVJRnaTN1s2slH9zY7VpwnZa5qUc2+1pGt8e3rg66W4BjC5uWd3H3JIlFt5C9WMuXaCDz86c1sZeCKmo4Gf7ZWpHugxGyUGse5lP4VZdDjX+tyZef8bO5is5PY0PyEv/l3Tj0EieTlaXwbLafEQ0qdsRO+XDO5/eWcugO2dUWMrSM+R+kv5vqerBTh3GxGY0OAvVmF8RCrML5oqsuHddE6tkjRbrepMJblqzAWEKJwtHhwTbg664r3GJVCklXbVI/8zc/aVKiV+uLjWg/2pcXZnbFf1RocZA/VrMdK+rvyR67xhWbkGlkw2MhV9gUzcqULFJe5gR32oBmE7qPthfhbRAfMrYnZW6+GrNuiUM26LWy99w6tiVRzW611nnwRzjbgzBSZKgE3q3JJ9XgSixFpaSjNdo383Heb3G21MaTSzQzZJGBNb3bg2//ptfbJimf5Cq3eaCvVxF+d8cuyyrGxunzF2Fhl1iZxCwkkm54FLkf89Ky+W5bo6FJeGOKi94tY/J0=
*/