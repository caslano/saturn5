/*!
@file
Defines operators for Iterables.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_ITERABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_ITERABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/at.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Derived>
    struct iterable_operators {
        template <typename N>
        constexpr decltype(auto) operator[](N&& n) & {
            return hana::at(static_cast<Derived&>(*this),
                            static_cast<N&&>(n));
        }

        template <typename N>
        constexpr decltype(auto) operator[](N&& n) const& {
            return hana::at(static_cast<Derived const&>(*this),
                            static_cast<N&&>(n));
        }

        template <typename N>
        constexpr decltype(auto) operator[](N&& n) && {
            return hana::at(static_cast<Derived&&>(*this),
                            static_cast<N&&>(n));
        }
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_ITERABLE_HPP

/* iterable.hpp
bi/WtBLNUNmjO8x4BKAdWg9aPwJcWRPB6fsjm+O+OdbcFbfOHt2hh9Y7LCNzztwByro1wDxzQJPK71Hr7NFwWp89avAm9p8afab/Y+qZg6v7FfX5qppnD/3kQoxLc6gXjhLpmSpFF3NTXeyE92bbKeaIY450vDDGqJZChVE7CW/BOTsy6khg1KPKgWzKqK1SQVnMNUcv5dTOi5Syv+Ro3XJkaNxyJKW2xL1yjIASuN1zjYdFJzKnM82THXfCcS3Vxk5zW3+uj41S1A1HI92xfZsNUqfZju3bbJA6rezYLqJ+MzrejqhQdxz67ttsKDqt7Ngy6K/8rioKs8ZhP1JhU2IwbutjuJ+qwJM08H/TwOmOrQJHU5hvs9HktLJjq4Rka1Ls1cAzNPCXNXAd5sSGi9PKjq0S8tmgmqKiWoV14FyXuU+4V/XH8R7A3mZDwekKpxpzB0LZIHC64hYV+iOaHl0pKDu2kcqJoZr4ji1E+X58x3byMIk/mfpUWFMOInwskxfTfCf4Eup8Iz18p2f8mouddHzE7dZTVriEP450qtrkG6l3H9UfR7rKO4ozjpOq6OiSZtyGoqMboG469YmIzh5V62H8hA45kJ8Gs6KUn+JKD/JTXOmh/OSiLiY64nqOOw59N67aLI1Df+VfVEVh1jjsRypsSgym8JMCT9LA/00Dp/ykwJGf4trJnzUh2ZoUezXwDA38ZQ0c+Smu
*/