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
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
*/