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
yKhnab+DtLd58VzQU8GsPumDgoQ9OIzX+HDe4p1Rkif0sGvj3umGgawI8UBcTwhJUkVxr1RQiUJPKZlxPA0xlYnPqHQ8ixNESA316Fe/DDj4GR9rU4DUR4dX7An9dSLTw5prulBHTA49wDuD3vtgGICpg/CvDWJgc58xCiG5bwaJMlQoT4OP6SXfAUaH7oikr/e/W0RwvK1VD20K4P+dnx8aPX9PqU0A3aeTQPLg715e3Ax/8R/2vEVWz5do5ZhxPvFmj1QqPhI81uSJilzseVNjptxCsUWCOglfMQdt3tbKWQmV8IJt5nMX72KtEgFzPLC90w0PsYKMJ3aemgFI905rYGPjSZXHAFIqw0+mgrMW+NVOfJJZqmEA/TOVEr8w3gdtyMtBPuvG5kwS1u2cypWC6UOInXixj7O2eOQcd92OTVYyUTxVrS0MqE51RQB1hk4v9OAnGOGE3tmft1KvrzoxZvxL6taBALNELv0G2w5TOMZLFSwqO5NmRda+FD/Sje354f3KKS38bxI69T9YSvXPeNBPb8qj2wrsX16tCJsYQSkOIiXQt0Uk4Q==
*/