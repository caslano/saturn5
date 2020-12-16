/*!
@file
Defines `boost::hana::eval`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EVAL_HPP
#define BOOST_HANA_EVAL_HPP

#include <boost/hana/fwd/eval.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/wrong.hpp>
#include <boost/hana/functional/id.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Expr>
    constexpr decltype(auto) eval_t::operator()(Expr&& expr) const {
        return eval_impl<typename hana::tag_of<Expr>::type>::apply(
            static_cast<Expr&&>(expr)
        );
    }
    //! @endcond

    template <typename T, bool condition>
    struct eval_impl<T, when<condition>> : default_ {
        template <typename Expr>
        static constexpr auto eval_helper(Expr&& expr, int)
            -> decltype(static_cast<Expr&&>(expr)())
        { return static_cast<Expr&&>(expr)(); }

        template <typename Expr>
        static constexpr auto eval_helper(Expr&& expr, long)
            -> decltype(static_cast<Expr&&>(expr)(hana::id))
        { return static_cast<Expr&&>(expr)(hana::id); }

        template <typename Expr>
        static constexpr auto eval_helper(Expr&&, ...) {
            static_assert(detail::wrong<Expr>{},
            "hana::eval(expr) requires the expression to be a hana::lazy, "
            "a nullary Callable or a unary Callable that may be "
            "called with hana::id");
        }

        template <typename Expr>
        static constexpr decltype(auto) apply(Expr&& expr)
        { return eval_helper(static_cast<Expr&&>(expr), int{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EVAL_HPP

/* eval.hpp
lzlKtTLZPrrrZS6n0Olt5zX31qyOjlikTrdun/xQCC/MSUZuavqKhNyVGSs8Oh3zpFuGhYs35kZEWeNTEpPN6WnGIntx+dKw2FijwOcpVQf1eeMSjWnxSYnJlkST0eSoKi+21SyNdhY5qpZGV7lKSmyVNSzvaStTX/5xS2pivNlijTM6SgvLKktk7qI05m17VvHkNSUYU5LTLbGJscuM5tJyl3NptLuIDenSRUujC+yFNlcxvlgTUnElLN5cVmpfGj3e9izWV6tve6ElNTUpJTbJgrZlu9GJ6hg36cdoMZrSY02pCSmJWruOYvs/tTq+SBxsqTrWkVxdPU8kWNMT0tMtScYyl9Mz2BTmHbprrGhqWZLVbEpYZkx3Of+3wRq1cTbpx/nxZQkpyWlxVqu7XdmmOs72Rv0404wmc0LKsvTYJHeb/2WgWj3qONuM+nHGxaanJ1kTU40b7TX/Os6iAV3e+DhjQlKyKQnzYrRWOjbZnGgOxf7zaO/SpX59u4+bktJMsVZLurHcVlXFxfCcV0HViq5dszEtMT3FnB6f/E/tuss+W1ZZsDTS/X9LF5UXVdqq7EZhVNvstOjbXBafYLEuS0gwVtkrHbZithmn6pG+zbhlxuSU+GRLnMnibrMU42Gh6FJXyTp75dLoTbZil13WUbWQdeTp60gzWlNiExPjk5OMVa51G+z5ztwiW1WRLCLWqe2W39VuihF7LNZiSo/T2h0vi/8ZL6xv1tNuo76OVGwB6GJaQorRUVXlslfqmxVVarstd7VrNi5Ljk1OS7Umqu3Ksv+uWVE1V2tXfxalm1OSUkzL0o369lxqe8f/aX7NSWkp8SZrvHFlTWlZaU3JuBq5dehfJ0trr3e9XndT0tKSEpKS0o0sITM/qerbXe3FGVNMCenW9Lh/nVdT2r+Mq3OTXm8SYs1pOGKTOJ0y94bHmbf7rvMn1hhnXrbMak6Jv3seZTP6fXhN37/o5GXJ8abkeIvRXmJzUDWFK5F5x/5prSym1GWJqfFJahuyULStoKDSXlXlPmLs7v+msB7jAtbTslTX10VWa5wl1oI9OO7nFticdua3Pcn8ATX6dhOMlsRYy7JkKPRKO1otLXPG2bFodvfZYy8uuHt8vfq2nsApE5u+zGQ22ksLZEv6tQq/qx2TMSU23q2OWjOxhU575V2tCK2dFsdd59mylLRlqaY4Y7mrsrysiu1otuKudqzQweQEc0KsSZ3HMhf+k2+vdDoKHfnj5wyrqbp7bHn6eqLTkhNTElPSzEb3wJhTLFXbLLqrzVRjYnJqQoIJixhX5sTGUmcQ8cjSaI5TX4/WZtB2/TjjUxLiE0ymJGNJWYGr2MXccaq+/EbcvdfS01Mt8aYUdZzOIrS4YmUsz1F9HVp7te/r90DSsvhYq8lswryuQxmZdanqZ9TfNcYkY1y62WqOT0qjbWKDKFrsyHe3yfJhC1k+5lmhP78sllizxWROMRY6StfbK8edUllCiPxElmnRtxkfb0xKSEkxJ6cn6sb4T2vpqU0/r113r+Wy5PR4C2yErdhh09YyTtXpmrvP6ri4hBRTqsnMcf5Te7oqdH7G4JNC115cmjktPs6aZCwt0yy1qFTbG7mrPZi/tOQ0ayI2SFoZlFW2GbE0eoOratzY25yuf20v4DFdHY+b4Wgvi01zt+fu6z+to+9zd69jYmqCOS02Nh7t3TU2Ns7iHnsbqi//eHxacmwihlaWX1XuKGBeh+pbhOvzwszGJ6TjCFymnc+Nq+W/FQmNsOaNx9uBf3pe4KMI+Uzv+KNS5i2ECFxV9nlVZkWub3t5ZJfefP45VRbwAurRyU6L765XZeW1QlQZdHW2nfujKhs=
*/