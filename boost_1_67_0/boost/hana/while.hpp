/*!
@file
Defines `boost::hana::while_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_WHILE_HPP
#define BOOST_HANA_WHILE_HPP

#include <boost/hana/fwd/while.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/logical.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Pred, typename State, typename F>
    constexpr decltype(auto) while_t::operator()(Pred&& pred, State&& state, F&& f) const {
        using Cond = decltype(pred(state));
        using Bool = typename hana::tag_of<Cond>::type;
        using While = BOOST_HANA_DISPATCH_IF(while_impl<Bool>,
            hana::Logical<Bool>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Logical<Bool>::value,
        "hana::while_(pred, state, f) requires 'pred(state)' to be a Logical");
    #endif

        return While::apply(static_cast<Pred&&>(pred),
                            static_cast<State&&>(state),
                            static_cast<F&&>(f));
    }
    //! @endcond

    template <typename L, bool condition>
    struct while_impl<L, hana::when<condition>> : hana::default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename L>
    struct while_impl<L, hana::when<std::is_arithmetic<L>::value>> {
        template <typename Pred, typename State, typename F>
        static auto apply(Pred&& pred, State&& state, F&& f)
            -> decltype(
                true ? f(static_cast<State&&>(state))
                     : static_cast<State&&>(state)
            )
        {
            if (pred(state)) {
                decltype(auto) r = f(static_cast<State&&>(state));
                return hana::while_(static_cast<Pred&&>(pred),
                                    static_cast<decltype(r)&&>(r),
                                    static_cast<F&&>(f));
            }
            else {
                return static_cast<State&&>(state);
            }
        }
    };

    template <typename C>
    struct while_impl<C, hana::when<
        hana::Constant<C>::value &&
        hana::Logical<typename C::value_type>::value
    >> {
        template <typename Pred, typename State, typename F>
        static constexpr State
        while_helper(hana::false_, Pred&&, State&& state, F&&) {
            return static_cast<State&&>(state);
        }

        template <typename Pred, typename State, typename F>
        static constexpr decltype(auto)
        while_helper(hana::true_, Pred&& pred, State&& state, F&& f) {
            decltype(auto) r = f(static_cast<State&&>(state));
            return hana::while_(static_cast<Pred&&>(pred),
                                static_cast<decltype(r)&&>(r),
                                static_cast<F&&>(f));
        }

        template <typename Pred, typename State, typename F>
        static constexpr decltype(auto)
        apply(Pred&& pred, State&& state, F&& f) {
            // Since `pred(state)` returns a `Constant`, we do not actually
            // need to call it; we only need its decltype. However, we still
            // call it to run potential side effects. I'm not sure whether
            // that is desirable, since we pretty much take for granted that
            // functions are pure, but we'll do it like this for now. Also, I
            // think there is something rather deep hidden behind this, and
            // understanding what must be done here should give us a better
            // understanding of something non-trivial.
            auto cond_ = pred(state);
            constexpr auto cond = hana::value(cond_);
            constexpr bool truth_value = hana::if_(cond, true, false);
            return while_helper(hana::bool_c<truth_value>,
                                static_cast<Pred&&>(pred),
                                static_cast<State&&>(state),
                                static_cast<F&&>(f));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_WHILE_HPP

/* while.hpp
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
*/