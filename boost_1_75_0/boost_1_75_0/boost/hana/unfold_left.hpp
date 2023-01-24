/*!
@file
Defines `boost::hana::unfold_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_UNFOLD_LEFT_HPP
#define BOOST_HANA_UNFOLD_LEFT_HPP

#include <boost/hana/fwd/unfold_left.hpp>

#include <boost/hana/append.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/empty.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/second.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename S>
    struct unfold_left_t {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::unfold_left<S> requires 'S' to be a Sequence");
    #endif

        template <typename State, typename F>
        constexpr auto operator()(State&& state, F&& f) const {
            return unfold_left_impl<S>::apply(
                static_cast<State&&>(state),
                static_cast<F&&>(f)
            );
        }
    };
    //! @endcond

    template <typename S, bool condition>
    struct unfold_left_impl<S, when<condition>> : default_ {
        struct unfold_left_helper {
            template <typename F, typename P>
            constexpr auto operator()(F&& f, P&& p) const {
                return hana::append(
                    unfold_left_impl::apply(
                        hana::first(static_cast<P&&>(p)),
                        static_cast<F&&>(f)
                    ),
                    hana::second(static_cast<P&&>(p))
                );
            }
        };

        template <typename Init, typename F>
        static constexpr auto apply(Init&& init, F&& f) {
            decltype(auto) elt = f(static_cast<Init&&>(init));
            return hana::maybe(empty<S>(),
                hana::partial(unfold_left_helper{}, static_cast<F&&>(f)),
                static_cast<decltype(elt)&&>(elt)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_UNFOLD_LEFT_HPP

/* unfold_left.hpp
OZ2kEj4F4YKp6WzRLt1Fpg/ke1WY34q6yL0VNQN50Zd156HBICRpyhNN4VA7XSVattEWf4Dc0x0i8gsG4LPB8O2WFsgoyFNwbj+ca1cyRmehRmvPADXLU3SAH0v4sZcX94BaTVGtkq5yTwSUvFeh+ZQu7UYJkcct7o6mRslDuVM3qGY7AMxD2IxpoZlRgvTdsOocDkKrZYVWWYpPM8KbBMoadnFncmDRdaNEePoYKog3Ki1PF6Ibhz+N6lKeXiSBr0eV9JALXDAWKzKjTPSRCBW2URGnPVFJiXXU3NOT0E1YoD6glLU8g8xjqJMOjWQAmslsdl84GB/dXO0L5qfuKyLK1sFB3CeXfnZE/WqK3w1wYi+dRrOMM09s2kRwC+eAW9jjE+rG2iAufJWUDPZlvwdE8DKmoL1TEP52xTHI7eyFn7rs8YaVJKuWO7PExTm0oeZQlsZQa/6ABS5IArj+vDHvfzlv/KP3f3zAgiNY/wGLMO+Gz2FWeDf8gAWuW+GQsBSOlJxLxrGDbMxGDv7Nxb8FDdcnC6lc3hV/9gD6uMKD2xVzhND+cFuf+v3hMy+yPxxcBCHepPqtNw70csurlFuk2N4jsDHLgO+OoNG3l3FE2fxHGDcf4xJPwvIr3NLhxBDWoyUBGucxn97Ute4zFW6NP1Ph3PAzFWXapCOwBW2KHx5q0wBgR9WANIlLDfu6IKnD95pMKOqEP/AE
*/