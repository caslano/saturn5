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
cFvxHWbBVgVnfBYCynxkIWDFZyGgzEwWAlZ8FgJu5igLLVfULGTdLVgWwlmQ98L0vZJ1QczGBG4ns9VbxOqi6GZNdQF0jd8LAbS6e6FBKILM3k2jIDYMRDeSrrbUjaQ7okbSzfhqhNyiFy+O1FRFvDW1VcuCS5eGlvmXVi2uhP8q+L/iM+niBeWLK+F/b9fiCnytEN9KqwxryO0gfUotj6STHbFZ/e1nnlxeuWCu1zu3fH55ifErB+DcuRCWz54=
*/