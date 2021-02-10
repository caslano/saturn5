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
8rE/eTe6nJCPxnhsDCdXZHRKjOEVAnvfH57A1vswWUzo3TKmCUweE3+xDHzqiTkf73OwtXXAVmFFWewKzpnBhJY7d8KQBvvJkrr+zHeJS+MUvziwDzc05l8Fg8Cq3cijgrsQXhQG92QK9Ahvoi9AiOk97wEcmgjQXReXAxj84IdukMHDbeQfO6FptuzOt/HBzKMzcmmZttV7ZwyH5gDbQtn4Eag1+mjZlnXR3/qBEBrHgPp2zwmfpTDdYomrkSNJki2XEXD5LVA3ylKCo7rbWz/QEPgOJgOofkiJ+elipExo94cTczw0BrY1GV/2JpaCbr4SBdl3hmWfG8NLGPDBHPdPr2wDkFMG3aRBggMUMIDBrNSUxmwxeisjzyILUn96n9KaZ8vYD9MSqHmUpO6cul/0ZtjCBHbPvvXD/3jBFnCwy0Q9cJKU5P0YQwilMaWvcL/K+NBFFN/rwKHNo9PsmhNGEPat0XtvDk9gY8IwSYL946njgrL1ih7nxie7Z5z2B0D+/n+b5Pnh317++PNPBDB7Ts79t2x2Cc086w/tnjmekO19/LAGgg39037PmJisdbvY1+GJ6P5byB4hLtXuW0D6DKwhsrsN++uHNg2vAYANeM/8ayTYz+RfW4ScfByNYTVTy/+DHsHvdwjM
*/