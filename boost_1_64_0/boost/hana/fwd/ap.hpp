/*!
@file
Forward declares `boost::hana::ap`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_AP_HPP
#define BOOST_HANA_FWD_AP_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Lifted application.
    //! @ingroup group-Applicative
    //!
    //! Specifically, `ap` applies a structure containing functions to a
    //! structure containing values, and returns a new structure containing
    //! values. The exact way in which the functions are applied to the values
    //! depends on the `Applicative`.
    //!
    //! `ap` can be called with two arguments or more; the functions in the `f`
    //! structure are curried and then applied to the values in each `x...`
    //! structure using the binary form of `ap`. Note that this requires the
    //! number of `x...` must match the arity of the functions in the `f`
    //! structure. In other words, `ap(f, x1, ..., xN)` is equivalent to
    //! @code
    //!     ((curry(f) ap x1) ap x2) ... ap xN
    //! @endcode
    //! where `x ap y` is just `ap(x, y)` written in infix notation to
    //! emphasize the left associativity.
    //!
    //!
    //! Signature
    //! ---------
    //! Given an Applicative `A`, the signature is
    //! @f$ \mathtt{ap} : A(T_1 \times \cdots \times T_n \to U)
    //!                   \times A(T_1) \times \cdots \times A(T_n)
    //!                   \to A(U) @f$.
    //!
    //! @param f
    //! A structure containing function(s).
    //!
    //! @param x...
    //! Structure(s) containing value(s) and on which `f` is applied. The
    //! number of structures must match the arity of the functions in the
    //! `f` structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/ap.cpp
    //!
    //! @todo
    //! Consider giving access to all the arguments to the tag-dispatched
    //! implementation for performance purposes.
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto ap = [](auto&& f, auto&& ...x) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename A, typename = void>
    struct ap_impl : ap_impl<A, when<true>> { };

    struct ap_t {
        template <typename F, typename X>
        constexpr decltype(auto) operator()(F&& f, X&& x) const;

        template <typename F, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, Xs&& ...xs) const;
    };

    constexpr ap_t ap{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_AP_HPP

/* ap.hpp
ISdcZ+igrUSSb1uIU7XmaPhgqNF2OGL0D4e6XUhBV8c4hHNRqLz7XFe09HDEjLLFelkDy8aKspYuU3Q6eOe48gY2mtO3CDHnqVAzqWpyt72x2qwW53QG/sYJZv9kMxDZi3jHS/OPbKjwrdKBfo0i4mYIiWdnwjDkvRF5jMP12V3qZ04R0T4ul7eGe7ZJDToIPe/Ad01o49Hbf4FINZiIVPQ76GA1OijMP7KxwHetXuGr8Q6u69PBzlHxDjbrHZwW62Ae4KHgKpe3Y7jRVlZ+iTpOnKozEWgyzBcAYFSvOTCM3aIaY9yMmJWtRn/6YyMoKJdvNeFxJB8v3mrD4yl8LNwq4TGTj7N/ZMB0+uXHJuCN7U02ytcfQXgwNzuWKzF36GOU9nw14JVxLn56IK7Fo3+q90soEwjB6dha6JhoUEfmiEloK9IZpoi/DaENUjTHgwqjjerosbo/ldHuw6lxEAC1ogNzCBibQ2gylyLnLb89MBlrJKvcXaFOHBe3lze8w0bfTWpJzXQQ2QtcZRtmtDFEhGFaebLRxvZc7MLrXIAW3DkaCuPhh5OhnPlnFTpG+gdXqN8YwWyJ+lkC9g8o26RzCc4FcPThRX8Sln7LcTGzNp75FfZEweDy3mvjxLlRPJnV1OVmMYGs3ozqB1YDU+LEfQF1QkUW/uG9klbJwsmfTGlDL5233K1m6615ChBR3XMgaR5bQEwLIr7LiSecd3FGG3QOC2gIWAxTGFug9hdjtVdteWKI0VaeYbTdjr+7sP624u8y/H3VarSdjb9v4++Cocb/av/CvzvR9tlYCBvokM1GsdVppkgf+2gLhbmVO8Ypm036bnmhMZhmiqmWA9bPYn1xv3LzfCP/WjbPj7c3B9Okftq7udkzstmrEZlz1ZmI4TCmgZ/7D82mrUYziLJI4jwb7Nq0TqJK79ZGXXX3OJt+zBsU7LIHDnxMhDfxDx7dtI4BreF53wl2jlk3OTzvMf61h+ftDnYOXpcVPGr3jyzz3kXRMKrgS4RPP+rTMSw+Mon4AA1acTW2Uy4KalvGgVt2n3flevorIe3tdF1wd6W/ou445WMAGsmwYp5BLo5uqDtuYlY2smAgYyZu/xvhqMtoDx408T16ad1xiXXOFXWy4nVa9tsy2mMvJnxuKvFiDrZKbC2J1uPEwc3jVjddGN+UchUU5HSaOyA5eQ0PcdR/FFTZOBSYN7ghE8QYxcEWv7B8/zkH3HLBaiARNJ6J3HDHYfLXj+wx8RZMvN8cfK3rcMTkn8XyvHCxmNqccLGY2tPDxWJqx7HmKe7eUxtA4w8PR2x+wVl4OXg4Ivkz6rrIo3w/fiQidp1hDD1EVlrdaxoOJg376EQXYw1N1Md/spHGTVnC/gU9XwhTSXz2iGodtxFq7tTYeQbj5iICiyWHix+AHMp2Z10glKKP6JLkozPjlsPFmZLf6fVQ6b8fw8fSc2DT9i5LZKyT1BEOwsvCoULsEGn8jYYW/+neyu56NvWN0/WNstgm6hVzm2VFo3+k9wq9Iv2jEb3ayZxQYSllc25fWaq1IG6CGOctieXTwXoL9ooXpsVNkG0FmQMvzKZZpJN8XrJ+OAO0nOPcCdFYWEH6uJxvMVgmTArDDEBqk8KcGZwGR8ZOrDOwFw06n53OiniCXdQc3wlvTIQjHUGwTmmweTchlQc7TfJtL5nYftNwBIMRb28jFa7dJoYq3GwsDe4wYadfFlrKE4t8x53I53oPatP8g4OaXW7QMChns3Mf43FY4wE0X7VF3n5e6fx4Q9ar34J8tJLrbxMPCIv4vZEPiIt4Eg8g3uy641+8554x8q2MKeXISC5oMLKal0l9hooR28AfPSI7Ef4=
*/