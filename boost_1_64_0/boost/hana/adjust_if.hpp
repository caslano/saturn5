/*!
@file
Defines `boost::hana::adjust_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ADJUST_IF_HPP
#define BOOST_HANA_ADJUST_IF_HPP

#include <boost/hana/fwd/adjust_if.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/functor.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred, typename F>
    constexpr auto adjust_if_t::operator()(Xs&& xs, Pred const& pred, F const& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using AdjustIf = BOOST_HANA_DISPATCH_IF(adjust_if_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::adjust_if(xs, pred, f) requires 'xs' to be a Functor");
    #endif

        return AdjustIf::apply(static_cast<Xs&&>(xs), pred, f);
    }
    //! @endcond

    namespace detail {
        template <typename Pred, typename F>
        struct apply_if {
            Pred const& pred;
            F const& f;

            template <typename X>
            constexpr decltype(auto) helper(bool cond, X&& x) const
            { return cond ? f(static_cast<X&&>(x)) : static_cast<X&&>(x); }

            template <typename X>
            constexpr decltype(auto) helper(hana::true_, X&& x) const
            { return f(static_cast<X&&>(x)); }

            template <typename X>
            constexpr decltype(auto) helper(hana::false_, X&& x) const
            { return static_cast<X&&>(x); }


            template <typename X>
            constexpr decltype(auto) operator()(X&& x) const {
                auto cond = hana::if_(pred(x), hana::true_c, hana::false_c);
                return this->helper(cond, static_cast<X&&>(x));
            }
        };
    }

    template <typename Fun, bool condition>
    struct adjust_if_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename Pred, typename F>
        static constexpr auto apply(Xs&& xs, Pred const& pred, F const& f) {
            return hana::transform(static_cast<Xs&&>(xs),
                                   detail::apply_if<Pred, F>{pred, f});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ADJUST_IF_HPP

/* adjust_if.hpp
P+Zd9oUNqejuPEHXrLdH1v4laS3lhA/sUlM6VRQ1p6yMG5jI2TVL6qtkx32WYJDRckir0Q9MPvHo8SrBnvOgl8T5WN6UHoiXOxRd9HJLM8NvJinD+97/3qKl0kr26ueIgq8/x+xCyfTrU/EWjtHihJ+FwK4owj8uwWO/azUUKt6zbbHqyVx5ij4Z3xv04nbxNEHAt0kEFmDhsIP4VIiOVHRO5JJbKqz/GBcWX1FVYzaloj4j5Ccp9rtrKsGxGCBGZArjI3pvYz/KKfTis1y8YSJqcB+WDZAx/sicmfe1j1QSx2R+LZqQ2wdqgwMppCzhv9enCXeY5FRws8Dt2wxFnhT8h2aauprwrKBziuNEskMdqRhXMDk0lK12XaLEgQIm0tghX5w6QHPPF2O2QpwoepVBASYnwPuifwiu7PhX2TPnm2EvetXwq1cK1llCdskv/nSduVEKn+mJ74ZPs5qe91d3H417mOPg79KCmi9GSkxgO0g3aTgxGHe36Rq4Ug8ldsbmLq7JgvC4gPbfe20xn7OuX59amy4pIXQgFBw7HgVnx9rhKY82w2hZvQ==
*/