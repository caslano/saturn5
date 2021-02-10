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
nRlbAtDV1dXV1dXV9djf+XZ/trwdb+0fn/7vwx/4l1r00+S/wnHu/tr3f/f4P2j1K/y7rpN9Tzf53a9765v87tWoiS96+Ql/9v11Hf2KuOFf+9jyVx9/hCfQDFu2ksVDGt3c5l6tVfcOf/zxB2/XOzo4Omx4Z0EchTNvmIfxdZjeNLyfJvTkP26Dz5/3svBNwwtzL5jtCVCj2yjzsmSa3wdp6MHPs2gcxlk48YLMm4TZOI2u4Zco9vLb0JtGs9Br9fofO923De/+NhrfIpCHZOllt8lyNvFug7vQS8NxGN0xjEWQ5l4yheYAfBJlOQBc5lES70HfoZeH6TxDGNh9MMsSL7gLollwDR0FuXeb54vs1f7+eJnOAPv9STLO9sdy+Hu3+VyN5CMgMQ8evGSRe3niLbOw4eGXDW+eTKIp/gsEgYeL5fUsym4bGhvoKp7sJ6mXhbMZwoJ2UZgx2qE3FORp4GfeAjCOcvwnS+IMu7q/TebWh0BHhDJdpjF0BHSAjyYJkLnhLeNJmNLHNHLZhaApEbhyajS+Ey+JARlvuzn0OsNt7zrIoqzh/dwZvetdjbyfm4NBszv66PXOvWb3IwJ73+mewdRH0FnqhZ8XaZhB56kXzRezKJyIPr/dn/2trX0axTBZpmPBOVPo
*/