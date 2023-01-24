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
EAcA0+t9mNSzJgNttdgd7CiGu8RQRhQQzGvk++oCGqBwkm8erhc9TlXGOsmhMMKxE5wno3AcF/K4WFZW5aZA4McplCEktWBS9WlM5WnPQL1wPKWVn3/oOJlnHqKuSZ6FsDAb+V8Nd+M0Fw01pNTeTxDvSXCyK5uw8LpZCOvd8SRRG8KvIRj2YdH5s4Xfwmy7KdvPxvMqPMqrgD9ODoJ8Rp78N2DqCUw3gVnOSxfCryEEdkcRNr3qOA8Hi7IFxUZ1M1O8HnWTth5RkhwnT8qesCMR+AjFSAq4wDiaz/zXQ1kqfSoJv4aJ0TR20XKAmz4byz+YrLnEVPEGYMpIbU784PyNOLUPG+EhIFuTOQr9NECdvCAOi4+FcFI2KpR0rwIzw82S8vNIDaBpiLU34s5hipv7NELtuh6e38Azb4D++jHYJNTZu8zArV/4xvPqbNq1OBFjbbcrT1O1UM3FlSVdzZmYrKk56/eRAQwzRmMh2I/y2rqc09/mQAudsZXFYEO8TsOopVp1vsIc7KMCjOrA35yiN+8UaHGIKYWLPjqBtcLcxUOFTeT+TVJS+P2hAbD+0Ajgi5tqfwWADBF+kGVv5bALC3VYxTGhtM6BsgahABBoB6DOQjU7rqHuigK9ok5eP6f20ckuxQCo7fK+lBgc/tgWxeGHYzUcXt7IcXg8Fofq048T43mS0xUh8jgi0nU2Dt/aG4PDIKfCJ6/X
*/