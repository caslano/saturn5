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
g9ugkTjWKu5fpSynYxhCmhQfp7ZHo1i4mzdvrY+H7kHwrr3cq5wrqcmjh7ivIOfTo9JJ3ic2TdXVYeW0eoAgd00MJ1l5lCxTDx+g4Uul6MMRgjsFhDv33vVqXlT8fNfa7CUPZiqaHfpYsGcQeRTkY8U73dsjBFjgpPgVo5b4PUeMd3IYuyum0qy8x58FyTyWW4MJ4h2+4cO4gJWr22Kjbgb/lOUEkb2RD9heut+xXqD98sf+Kfo6srCQVUvuz2+lu5q3J/VSdlwfgJiHmeMtSHhHV4tLUukvGa+cq9k3UKrF9Jqk8su9qtSEAbD/1cAN25kYPOZe2xhFG6Qp9tQCZLgM7WwB+vd1OGAJl31/DphKJ0CF9uLd4Dxm8d1BsqhRDkdTSVOWF6ggb80htimFXE8Yb+6OC9zBXIKXk0Ie3C1jAJ0b6kng8IYYPaY1wU+7NiS2sui9Cw+p9+HZQ3l58ACu84ZswpFPN2DIkRCryYtMvD8avt0/Qu3RRgQsiGHRwRpBGsGLidlXY8HcQdzB4m7ktVitND50534WvG74F02ajVrXLfRn+L3iG8obbPmk+y/byTWlkbjJ7s5Mp6tELtjNL1eD6C0kpitXzjWPdnFOUD0l68FoRdxuHDbHUQg2+TARqldKyPYw7NgbVQ5+ohuaulx7t/f0MX9d9btrkCI5xb8cz7W3mY4YDAf671X/gvn0wF/dXA+tbl3Y
*/