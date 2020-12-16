/*!
@file
Defines `boost::hana::sum`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SUM_HPP
#define BOOST_HANA_SUM_HPP

#include <boost/hana/fwd/sum.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/monoid.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/integral_constant.hpp> // required by fwd decl
#include <boost/hana/plus.hpp>
#include <boost/hana/zero.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    template <typename Xs>
    constexpr decltype(auto) sum_t<M>::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Sum = BOOST_HANA_DISPATCH_IF(sum_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monoid<M>::value,
        "hana::sum<M> requires 'M' to be a Monoid");

        static_assert(hana::Foldable<S>::value,
        "hana::sum<M>(xs) requires 'xs' to be Foldable");
    #endif

        return Sum::template apply<M>(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename T, bool condition>
    struct sum_impl<T, when<condition>> : default_ {
        template <typename M, typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            return hana::fold_left(static_cast<Xs&&>(xs), hana::zero<M>(), hana::plus);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SUM_HPP

/* sum.hpp
mMpxIdt4P4HhC9FvFGINZ/v3PXh4lLYHnrngylDYna8Tv1UMu9/cAWMcxt79IK8dWI7YKu/5wQJGwPHcIBivBneznJvmNYrIwRwuRf1oSnxQXr/++gPCO1nAMIdLud5MgQQehnves0p83r5WqofXi1jL0SQwfo0ZWQte330fALio1Kfr/GdNcARU31dDv1QOtCOLWPDB+tgTy1jNoeZCmKZZxCOYDy2FJaB5ee9etKln9dA2uqsU2xjdU0bU49OtB0Z3+Bjssw9/Il4wYqdNxijcHkrbZ4yPW5A5mVRECspN4q+fVK41Te+s6ir+HzEbSIAU+nHRNp3fe2uHYXDRhjI73kLH/i2MgU306ANo3CAGYVmoCc0nAKSAhpNsLGv7qY/a56isW8tu8JXzAwt4HGhXyLRfLmiVsFL43gbaBy/QfqOU6+Wgu6YLtPdfsFf8JNHi/bmU2vVyfu7FfgF7Pj6JEcYt9I6cT3Bs87ly5dnl2aRuRed0vXj+B9H/3akSwJAZsYdQ+aJjTWtVawRH+UHu7UCmO1568IPibOCCucdQ7vFEbld1g9aNWJT74LPkPniZ3PdN5Brfea2NXZR7/7Pk3p/KfUBes6ncxrNO9l1dtXbpebUck3aI/68WJQ9eKJn7it7nOaVtVqpGmE76/26fDyMeN4kdk23/hbwq+IMNbrBL9I8zP+aTsMd/6eoJOzmm26vdUI9npi/D86/FuC2ouzw0od/Jdy4AvKF8gtPTXyg9J4cptFE/rfRHFL12fS8s04fU7eQWMVFtdDiBP+7aLdjMP1bI6Vnwveqc7oJS8N8Iwnw+Ty/lyKEdJDeaHrriAOIZqMTfxJx3P6C4Z2PuPGDD8h+V5ffP5Rn/8ee4d8fdFs8Kf6B7LTlM0HvmCy7utYR6fr//tGeUeOXSDa1pbVLugaNUdrcz39co38CE5rJrqob5NCIddQYEvqxP/eQZpX7e2LrTg5eoX5M6pzEuD3vm5J5s0Gro+v/y3g3mHlGMr5FsANe5eprPeSoTnfX4gsGnDYF8cO152+MneIBV5Qeul0LHpMhpZcefcAcaUIrKYEv0CS3kGua9bkXj2+XfAYJAlvmyCxkd63vZaK0jqOp/FALzB21PTyhtT7YVQrZaInZI/AbaRQenFXLHRmXwlvnKmbrp58r9NJX+RCwIQ59f/4SJnqJr3fK2SVEdqL1HXNflDbsB3kU8YXKeFVzXBt3KiqPDDfN3QnluqYRqetPW7LwpRuXzKJ0QTFWt9EOjl2NFrqZby/PSSWde3+eK+uqhbrnvG7Y6xXj5wqQ+47isqqH69/WtYn2ocxc6rmeD5Nw3VqQ4KAItuLtE12W4ZtlxzWqTPwHLz++Tn4dIA3ie16n75efLjyco9yDRJQ8OjFU5mZ992nSQ2MplD8N1crHsMYTvYakwlz0p85EyxFpJ7aDHIHqGel4qR8g1gjHyElKWA3py2YdwrYeTHdRL7TSfX8Rqwx5Rui8vocMe0JwrTyz9yGqtAgAoQ4t7RP1M7nj3HZ34ACE9+WqR8y2VI0GOdK3xuirPRe2Zx6JT4tN/iyeV96lONkq5zqRzUfj//kejL+ZRPh9tJf/lcESia8XDqKzaMaWUdXZYZnsS7TItiMh62eR8pJq2tUIImh/qOCsA0Ex0YiSnNjxHFn1smGy8VL79D6K2QlTI/cJ3TH1GflLIqlkdIGwtd1TYg5cIw6axuayLPbncz6yyRnLfnykLU2At+i3ceCKrbWzLu4aKesC/E4U4iVQOdEt1RupWFIIK9wqyLcE8LjAXH1bIMkx2ehgGS95hZlw6YPHC0Oa9v5BVsVYqH2Cu2GQmrYZQ/a2EywvfEFxTU7g=
*/