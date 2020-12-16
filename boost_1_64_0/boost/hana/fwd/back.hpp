/*!
@file
Forward declares `boost::hana::back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_BACK_HPP
#define BOOST_HANA_FWD_BACK_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the last element of a non-empty and finite iterable.
    //! @ingroup group-Iterable
    //!
    //! Given a non-empty and finite iterable `xs` with a linearization of
    //! `[x1, ..., xN]`, `back(xs)` is equal to `xN`. Equivalently, `back(xs)`
    //! must be equivalent to `at_c<N-1>(xs)`, and that regardless of the
    //! value category of `xs` (`back` must respect the reference semantics
    //! of `at`).
    //!
    //!
    //! Example
    //! -------
    //! @include example/back.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto back = [](auto&& xs) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct back_impl : back_impl<It, when<true>> { };

    struct back_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const;
    };

    constexpr back_t back{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_BACK_HPP

/* back.hpp
d3yLqdfCSbL5VRr+IvYA/k0GQqHHr7fJ2x8WR0vYSkaxUwRJif818RAqPkYBwJCq4Urbw3yGOQFWmsIdSifGQG/kSB+82mQzjx7y/6t3hXEWzDLO3NGI8vpmBHW1msBno/Q7Qljt8a2BjygfDqzfI9ZxVt0vPhNTTksxAVPBUy9NAN5RW+MYafD/slerwL1JUMsqPOXqD95nEzLundXm1k/4aYVPlHi8BkZpesRg/MTsUle93KU5dwJdXuDE50CUlsgJtBenXZ9RyLtR7XeNsxGE7aNAMH5R/arEdUs4E7x/p9nnLi+NLoxxp/WnanDMLE89mR9pNOMWMh6t+qOF6g5uPOHRqgcCwR+x0xgqsZ1AAOV99144jjdZsry7zzcidGAQ3w1Cpx3fzyeXaJ+n/p+ZrO9m0gYCU0gc1llhqwOf9DpX7SIATOoEl3YOy9QNYwVMYgk5c+ZovmXhFvVcIz465UNANI0uq4TrWDhj+T1M1vwQO9eJ2V3vm9MxNsl9yfsrtH/qRmfg4taoQPm7P4QpF3WowcRVwqmHC2wmpcQaSDt9KCGBn7XrpTJuXvEftzr1DQ4sO2oXnU3i7QVX8t0JfHmWRn6e/jbpX2dT0k7gU2QJfvqeGEMy/o+N4HkLjOkb5L3My6PWKBfDMcVqmhJsHTQrzT9e/wQCiuxfHscvarO4djZ2RUoJgcZDXrRVWhtt5w0PjK3f4x/R6DKeV2YMDAs2m4Itpvo9gdedzdFBUKTbjQA8okn7k6YRG52TCMF/khCOa70h1JwkBNrQekBo2gwIjcPOs6D9TrQvNZ5XwvatJoCo39mjvdxg1rjLJeFwojPxyVKMl3t8YmoTPbIDnCYO2P7a1cOfXgVeTH7/2pie73/p6ln/M1hEvfhHsZHXFYtiyjH27pTl4HEGjuIiBCUNV1vj0a4BLvkFzxcCAf+v5ReQD2ozesNK+R4zMTtGcXXZos4fRbMgCvjfCQ4vBHgTLIPepxKyLFP9xahELIj/DHdMHozoYr+MCM7yPhurzO/8dAp0quhiBEQHvG9p/CZtsaQshJHcArcRvxO90IY5ZkQRDY2II6Lqr7S2FVv4gBgpzvaJex77T6QXpa5iIC37vjflCVkpJ8vDXFSaRTscfWeoitAnLl4q3Dy/ZlJjWBozWXyFmsZe0mBfIM832dsJAnh/Cpj0V1H4X26O3ePkCYqnVYjDt4czLy8C9ZYUlz1wuGXsIc24J/9BWQAP5Nk1Y87nrcYNIzzuuGCqUJfCqxO1JedEaU+hBZB9CPVviw7909GtB/1oGs8KDGaY9YFHGfF6dHTsrRURy9jXEtUZP0H/79Ae8RMAchlVsctIxtUk31VgmXNEdJU26puQhLSHxChaeEr87FdQXdUd/vCwTQ9zADLsfihqo4m691QShOjtieWsHM+KvIDQHPvPKZ20B4qcnzGH9YSfZ9sfxR61mheDq0g5t+3ThFLo8qMdDCDW1OeG9Lv/sjzSq756qu5g66djSgIOmRQnMx6YC4pzuPrbbDgyuj/VZ1XXYEi0lDYPMIa+388zvNfV9/t5jJUU9+medIdvMDYa51EHpsOEFwRznol7QHjItPBsO5qNHtYHUUU1CFH3yJeobEA6UWvg9syPKdEVwzMiDRm6ntHwZ2LA6XlFCPiPv1SZlMhMFsiWYGdWAN80n4iuorjMO1pueJTmBnWSjhQVdPr8yYU2N79Dh2BNfuB+sT12nz+Ln+ILTNFmwsntVr/9OnEiE3q7Yyld0Gk4wBWUa0o6ditx8X/t64mVC/GGj/jjQ37BJ8Q/N6qddU7F2nRv7udwLh3kzcOfMrXyiKhegX64gtV6o8b3SvSTHsw3BBA=
*/