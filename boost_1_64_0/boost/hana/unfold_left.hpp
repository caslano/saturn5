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
NZVUM5EeRXFAffasffUmg1fcpHA0R/otiBde/IIfSFxaKwE6dnXgL5FJm6aK4UZHbFWDbvI04nxUYPxVlfjGCk4Efy2G9Y3pevdNezVgIV0cOHNwdoW7goeq37AYHgxC2cC8rYFzUNduNqlWUL5+4qCqIB4FcBs2u/ZEBdaIbLpx+9HnbeljWfxcycEfI1rBu2xlhwmE1EbZfQ6leVcj+7Ii07h//b/PwPjQ8iNXAQbvgt+sjhVyJ9qugK4hma2cOSO/z1lphlXg0HwRQgd513mLpxj7oiYcCfa9cebcBVJQrdWxbBfzW8nDTn6YiqdJ4ACr9td8/RZO8jHHkKcI/gX7S2bT4SdMJwb+EB8HngVRdKKsF+2q3d0kBMD7C/ms85VqZVb0XbyyVysZxkqyREiHs6/sW3KP6DEaFtuw9T1q4rxNic0U3GBAFMt98TEfTfxLoJRex8fXl0RUERYZqWFtZo3e05ePlqyvyIuv0qgYdkwu+HVjWn0IZEn7tUI7Ho8XPyPCCOk8PjaeP/zPYROEBYOSXV3ae6N9ip7pstpC2XhoHYEv+ivlUA==
*/