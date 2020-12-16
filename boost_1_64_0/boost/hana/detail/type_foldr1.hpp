/*!
@file
Defines `boost::hana::detail::type_foldr1`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_TYPE_FOLDR1_HPP
#define BOOST_HANA_DETAIL_TYPE_FOLDR1_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <unsigned n>
    struct type_foldr1_t;

    template <>
    struct type_foldr1_t<0> {
        template <
            template <typename ...> class f,
            typename state
        >
        using result = state;
    };

    template <>
    struct type_foldr1_t<1> {
        template <
            template <typename ...> class f,
            typename x1,
            typename state
        >
        using result = typename f<x1, state>::type;
    };

    template <>
    struct type_foldr1_t<2> {
        template <
            template <typename ...> class f,
            typename x1, typename x2,
            typename state
        >
        using result = typename f<x1, typename f<x2, state>::type>::type;
    };

    template <>
    struct type_foldr1_t<3> {
        template <
            template <typename ...> class f,
            typename x1, typename x2, typename x3,
            typename state
        >
        using result = typename f<
            x1,
            typename f<
                x2,
                typename f<
                    x3,
                    state
                >::type
            >::type
        >::type;
    };

    template <>
    struct type_foldr1_t<4> {
        template <
            template <typename ...> class f,
            typename x1, typename x2, typename x3, typename x4,
            typename state
        >
        using result = typename f<
            x1,
            typename f<
                x2,
                typename f<
                    x3,
                    typename f<
                        x4,
                        state
                    >::type
                >::type
            >::type
        >::type;
    };

    template <>
    struct type_foldr1_t<5> {
        template <
            template <typename ...> class f,
            typename x1, typename x2, typename x3, typename x4, typename x5,
            typename state
        >
        using result = typename f<
            x1,
            typename f<
                x2,
                typename f<
                    x3,
                    typename f<
                        x4,
                        typename f<
                            x5,
                            state
                        >::type
                    >::type
                >::type
            >::type
        >::type;
    };

    template <>
    struct type_foldr1_t<6> {
        template <
            template <typename ...> class f,
            typename x1, typename x2, typename x3, typename x4, typename x5, typename x6,
            typename ...xs
        >
        using result =
        typename f<
            x1,
            typename f<
                x2,
                typename f<
                    x3,
                    typename f<
                        x4,
                        typename f<
                            x5,
                            typename type_foldr1_t<(sizeof...(xs) > 6 ? 6 : sizeof...(xs))>::
                            template result<f, x6, xs...>
                        >::type
                    >::type
                >::type
            >::type
        >::type;
    };

    template <template <typename ...> class f, typename x1, typename ...xn>
    struct type_foldr1 {
        using type = typename type_foldr1_t<(sizeof...(xn) > 6 ? 6 : sizeof...(xn))>
                     ::template result<f, x1, xn...>;
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_TYPE_FOLDR1_HPP

/* type_foldr1.hpp
p7Y5llV0imVRR/n9y5zy9F6hAGHJu+cijDjgJXWbp9IUISx5TXE5xyDjXD3upY52gYtnfZ+r+Psi0kNZeGdAhNWaZmDfUD5QlgAm45FvWu/q422czn95uRsrNu7HwMmUOnsQ7XuqMFpZLurH8rmxUy3ubqMsvn2v4fytQNi/raJ49uo4bjZwbXvLeb0Gcak7ZcQF/ZS+FWm9znVtuf3kXeN15eH703rsPQx4s2f/u/Uq8t6T1rOE9SpaDjnPwaROhdIv0qZexQg2rD004dSrtGZ2K7jVrTTiYk6mwwqPLHyhk4e3drfUgbyBLaKNeoORI+m7ULFQyrbB4oC8uiQg114SkGGXBmTYSwP6n2VKx7Hc9kNtJ+ms8OGst+leqeT5Zf7+A/6z3uWUDzsZ0CrKgDaUT08GtI06d9ouN3fL95Q9zPznePEwtHVsBz0PUJvnxnJHpa1tZ3d7LFS32WoockZ5pfxpBHpk6b/0jMjeb8W6mrp3eN8yH/ZzA7CY9x/k2i/nxqbytA3NVc73JNMdV57YlDxYatevLYBJn4f/KE3bNN0n/d0F7MJOKlf2hYE9AmDxHD+ZvOH9pck5q2tp2tbrSoRPBd5p+FL+VwR/AE5eX4yPZbp1UcqOCHn6NpF0UE7qt5XtYS3oXD0jG41/l/4W8w2jjzxG6qTiOVDM8Vg/zTkgx+HnMO6kDy99J69RrAkPXyH8lKHGO8pFu9OPpusvGV+k/H1OiLVJrr1Fau1rRfqPzOh+a32UtLvlkQVC3xVsb6UHnxfQhxUF+F0xdXaEkqc7WrgN0yHuVql1Y2FAV7RIwLJNLe1Odn4M67lb3GvVutqSRO8cJXy8sam9Uy4kkp/vaKmtl7zcBAUfV/ejljscAVsh9OuON5dxXLZPc1xunepujZTfSQgSnjn1+xVGVqgshsJxoGX3WhyPco9Vaj/ay9AfGnlZd3nCyzrcb1DoFPvU3YRbHq/8OzC/nvL03vFJam+q/UQ+hfl/QPk3ypYnPtz03ulpgqZJt0D5Bdvj5jvj5XzuF/wX+Dyj29/SN9tesR7sKrflQZ2Br9eOudF+xDm+v0vgyfPVWW5/qe62dIj2PaDOAUMIy7YeRrgGcQvYluD37GP73U7YeL63HDBzD5LmE3gWWEl5FfCkLz2sR+Irtx/SpM50E6reh55hcc8rhcPzrrp7fB7ghTPikf+uNUryL/JNqmgdz5T7wWK115uv+DLv/3di69lR2xLJPa/Y69ZECU88KbY5LCHPefo0eY5cC6/CHf7wezb9+x3nwK8p3jvqT96vsz+Ts22h3OMgZTnvV6u3CZ4NeJ4790PZfbmhPu/y2IXFOznlMo9kbD8XcDlmnufnOOLUGv588pQLBE97lppbL1Dn8hciLGW1+k7Yi4mPvFJy6YtVeU385fhQlrSPOaa/FP+1/zjA0r7jChFXqOs8L7qCsoNnCZ7xSlWvK5kG9bP7RNFOl6o6v1qFny/S6v06YLovPD++muW6QJTrGvzW8vo3qDP2G32b2zjd5m9mP15EWq4sa1GuawEDTYzB9L75rUxj6qrlRW8HTOgAgGPTvINpXhBI8y6V5gVM827Rrm9QvP29pHedXNOI937xyXuTH2C41NEQfPOmUsfvlW844Oz5r+Wb7T07xbm0yMN2ZWp3kn96GAxU2lq3ezmC4qsLPN+VPLSlraG7GRe05V6zvRu7SPJThrUNJu0v5D5T742XeJhJbPeBS8mTPzptnszxxbVe6DYwRwPvGvj+RrweI8T5lNpLXaf2PZ9R8cg/recpJ88R8ZeLPYMb55LnXCdo3h6g+UWEpc4AOGFaGDnXq/LpM/gNRrb4X3FWTcbaPLFeF6k=
*/