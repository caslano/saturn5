/*!
@file
Defines `boost::hana::prepend`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PREPEND_HPP
#define BOOST_HANA_PREPEND_HPP

#include <boost/hana/fwd/prepend.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/lift.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename X>
    constexpr auto prepend_t::operator()(Xs&& xs, X&& x) const {
        using M = typename hana::tag_of<Xs>::type;
        using Prepend = BOOST_HANA_DISPATCH_IF(prepend_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::prepend(xs, x) requires 'xs' to be a MonadPlus");
    #endif

        return Prepend::apply(static_cast<Xs&&>(xs), static_cast<X&&>(x));
    }
    //! @endcond

    template <typename M, bool condition>
    struct prepend_impl<M, when<condition>> : default_ {
        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            return hana::concat(hana::lift<M>(static_cast<X&&>(x)),
                                static_cast<Xs&&>(xs));
        }
    };

    template <typename S>
    struct prepend_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename X, std::size_t ...i>
        static constexpr auto prepend_helper(Xs&& xs, X&& x, std::index_sequence<i...>) {
            return hana::make<S>(
                static_cast<X&&>(x), hana::at_c<i>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return prepend_helper(static_cast<Xs&&>(xs), static_cast<X&&>(x),
                                  std::make_index_sequence<N>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PREPEND_HPP

/* prepend.hpp
rK/QXNByeKCW48poswDMaczSDwaLbCJ8aJRPDN+PZmyJUV3Ahufcd9ct7iKhXbe2Gz8zKs39seJM1lsUJwm5p4j3xVFAlsSvi2wmOT+96WLI64iE6dEWdIBpdifniBqwLBFozZvBAsg/onius8Ly8CLv2zVveJYB1CpgclCRK7o6RZ8/aIZIQLkT6DrcvInefAyNQtfT6zWuIDUvaI7q85F333+IVmknk988EUDVf7qzHwio8BKwKOf8YFb05vEQvv+JIinxe+ZcqOC3QmzN/NIAKwFOfrwwlyV1EKyK93oVpdokckaY3h5fbi4Uo/kL0PHt6YbDxnKMFCksOcxJoStYQkQoS5Ht+tR6fbHcJ8ZL3p9j35CbgByRWSO1up94McSzHd+Lgnaj7CZ1iYOu011T539K9ghGMpgyJZfz3ZLxDaYQWvt5teuwhHI5A2b1eM2AUcqPTjUUPup14Rc+g11rqo8CWE4n6J0/7WWzhXfeEvNS3ux/O+jWubKbuNpdeB+MwobQ8foqSG/gfNcmS6V85nm0Kz1X3mkLfPwXADcsyNNzg69rFzIPqjL69LnmCf37bdfNBUz8+JMlH5aAvyd1D2+9gNn6SdX8wu4xwG+G28z5zE9/JPw4PrU5gn2in6dEMSemNRPY9xkC8MSjpfOYVRt/W/tzB5Bv9riZPvOYad/dO7Z6JPiDuXPbqOTMfFFZntgHxsP/cO6l
*/