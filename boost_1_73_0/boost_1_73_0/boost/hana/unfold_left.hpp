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
JuXvOqlRtSdZHbYdGmrkIEcxXEykY7/VpoqYES950/M537aAnM8SMpcUVn6w3rbM+H6rxqjckcBtsRx5P/+iph2DMMNTx5jrv5IqvrJ14JCWTErnh7VbVYSBWFTD+ktuDr5hEXlYV3UVLKeffDkxC7QWFzQo/PSsjZf9HyYtFHMBEzhHGuCUCOe55s/nZ9HZORwu2sdv+GYDPGq2KONTtAYtZ2pRN9zDnrubtl8eR16jL6LvX5iFHRZdOu5KXEuG8ZpwdsIwIVEFefGlqgPMk0XNQKmvvzZ7v7dBwc6lrvzYT2lAqLfn6rztDGYx1QrrqXGRXlA0IshlksLU8kNPHDmVCYvwMZVr48B8F3KGq31NQ2ouS0E/jbi8h66bO2Oue7hn8G5cY8AHKprbpOH3RlS2IugOCGNhUB6Lv/SITqcEJ7Rlo52IsAykERauqXfRWr2g07TJYZdN63oHhBXO1fWUqezF4M7ZBw13u+Hy9xVzH5jCnO1D+cQ5XFbmx2pGQc56HZ+5hJKNL03k4GzIOQiM6cK8l93JvfTk3dr17UUNuvTxWK/uIs8sC3WBM8FbC2AFyAiQR6Q/cgMwv2X41GzNj/br4nc3yoSM1x80FYqMyARtdGPEf2Eose17phYAXEqym7q43Y3p0vAe
*/