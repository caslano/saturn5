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
AdOZJyh3kzI9Rsmipw73vk2jNHooLiAp3J9sKi+QcHVpkpI27TruXYOY1JkX9z1BWG5s/bxCi6B1n9okzlWOCByNczOx99HFLJ8fTU6WKgBvNIWRpdC0Sal3MiUiISs3i73TDnif84bEoo09k4B6P4FWIM3dTmmadz2McDnILMp3QMsGJm4COZZxrReiUu+mw+inCtG4EKKy5Ip9vPkvAuM8PBeLOoe5r2nadJ1Nr6b2dds1+I16lEYV2Oe8m04SjnJu1zXcQEGTSPRegag/F4BxvW3Yv6x+fhK/Op7zp++3TiieQa80o42+xTzQX1UaDNlwgwpONCmAoHmCQjRv3PyJUrV7nnfjAISEtcW3HGHZBddkCW3TS926rdkzZ75F9I8zDf43z49nzteDJJrAhQiEhav3GE6658503Gea4EaXuKF6FmFip/ryZgzh4wE111d4uml2aSuEKSkAC94YtezOiN35UA3hJm5dV/lqh8YY24nvz3pZ03U0IJ8JDqQlMbrQINP2et0ORYaMCgLOWD5QazHo6FxQFxVx9/DB4yqSSrPwUAttqIo+CA==
*/