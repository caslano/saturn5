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
yXp6Tb4kazQPZMBAe43i+wZP2NRT/vWUdIgMuK0Se7Z5/Qk/GJf2+Nhkr5y69g7+zXjnWe+8O+697TphdJs9ffl+3HX0ZPx2+Ef2iucKnVJxirLnpZFb/RDdDGe0ho8tnksXJ9Dl+LRhRUPeFPwxU6cJOjEG3LPloodpdcOPse6QI3TD9dJIVpX0QuYMvHqburh5+xD2Mv3Y4BTKiP71BkTXFaFzr/y0DyMaUSDlTl013uQFhTey3FHv7QWAApAX5533lOmh6Rw8yMiI22U40168+kkjlzA7SWO0RRo1dLomA0UfsyHkUrM+49jbJC+gNe73Ggh4NdYzdJvFWTNJhpTeMrpqKMTsvVhNeHKplj11Jihz+tAHNgjX/nHWKuCdd4txsPQ7yRmIHvit/hjGaxMEpr8GJpuVMLqCPekBGvZe9KP0pT8nuiIQzgu6Fm5OUgEQlIPSVeA68xS33xfqJnnlUFBymRubCCUpTeQeD2paiEny00uByiaYytu4coojZDrsYRYGQN8b//4SAdWzns1uNc4B0PiBZE36UzK0reppRqSJVj/JEy1Oe/YWM0E85qWDGxF9GfVe9V29LTUaVgcydKonGX2r9BSAmnOQurrsG7/VZJRs7cVZYWdHVMSymTE2mF3jqwP04Du1
*/