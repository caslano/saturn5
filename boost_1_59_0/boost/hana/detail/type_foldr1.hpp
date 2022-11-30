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


namespace boost { namespace hana { namespace detail {
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
} }} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_TYPE_FOLDR1_HPP

/* type_foldr1.hpp
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
*/