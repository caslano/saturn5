/*!
@file
Defines `boost::hana::detail::type_foldl1`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_TYPE_FOLDL1_HPP
#define BOOST_HANA_DETAIL_TYPE_FOLDL1_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <unsigned n>
    struct type_foldl1_t;

    template <>
    struct type_foldl1_t<0> {
        template <
            template <typename ...> class f,
            typename state
        >
        using result = state;
    };

    template <>
    struct type_foldl1_t<1> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1
        >
        using result = typename f<state, x1>::type;
    };

    template <>
    struct type_foldl1_t<2> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2
        >
        using result = typename f<typename f<state, x1>::type, x2>::type;
    };

    template <>
    struct type_foldl1_t<3> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2, typename x3
        >
        using result = typename f<
            typename f<
                typename f<state, x1>::type,
                x2
            >::type,
            x3
        >::type;
    };

    template <>
    struct type_foldl1_t<4> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2, typename x3, typename x4
        >
        using result = typename f<
            typename f<
                typename f<
                    typename f<state, x1>::type,
                    x2
                >::type,
                x3
            >::type,
            x4
        >::type;
    };

    template <>
    struct type_foldl1_t<5> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2, typename x3, typename x4, typename x5
        >
        using result = typename f<
            typename f<
                typename f<
                    typename f<
                        typename f<state, x1>::type,
                        x2
                    >::type,
                    x3
                >::type,
                x4
            >::type,
            x5
        >::type;
    };

    template <>
    struct type_foldl1_t<6> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2, typename x3, typename x4, typename x5, typename x6,
            typename ...xs
        >
        using result =
            typename type_foldl1_t<(sizeof...(xs) > 6 ? 6 : sizeof...(xs))>::
            template result<
                f,
                typename f<
                    typename f<
                        typename f<
                            typename f<
                                typename f<
                                    typename f<state, x1>::type,
                                    x2
                                >::type,
                                x3
                            >::type,
                            x4
                        >::type,
                        x5
                    >::type,
                    x6
                >::type,
                xs...
            >;
    };

    template <template <typename ...> class f, typename x1, typename ...xn>
    struct type_foldl1 {
        using type = typename type_foldl1_t<(sizeof...(xn) > 6 ? 6 : sizeof...(xn))>
                     ::template result<f, x1, xn...>;
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_TYPE_FOLDL1_HPP

/* type_foldl1.hpp
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
*/