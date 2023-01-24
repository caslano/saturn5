/*!
@file
Forward declares `boost::hana::take_front` and `boost::hana::take_front_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TAKE_FRONT_HPP
#define BOOST_HANA_FWD_TAKE_FRONT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the first `n` elements of a sequence, or the whole sequence
    //! if the sequence has less than `n` elements.
    //! @ingroup group-Sequence
    //!
    //! Given a `Sequence` `xs` and an `IntegralConstant` `n`, `take_front(xs, n)`
    //! is a new sequence containing the first `n` elements of `xs`, in the
    //! same order. If `length(xs) <= n`, the whole sequence is returned and
    //! no error is triggered.
    //!
    //!
    //! @param xs
    //! The sequence to take the elements from.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of elements
    //! to keep in the resulting sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_front.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto take_front = [](auto&& xs, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct take_front_impl : take_front_impl<S, when<true>> { };

    struct take_front_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;
    };

    constexpr take_front_t take_front{};
#endif

    //! Equivalent to `take_front`; provided for convenience.
    //! @ingroup group-Sequence
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_front_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto take_front_c = [](auto&& xs) {
        return hana::take_front(forwarded(xs), hana::size_c<n>);
    };
#else
    template <std::size_t n>
    struct take_front_c_t;

    template <std::size_t n>
    constexpr take_front_c_t<n> take_front_c{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TAKE_FRONT_HPP

/* take_front.hpp
P/Uh8qpubS2npLfipWHwi5iJywxleAtXSXUVBfwKbk1ILMaLL5aNmuIGGnJzGO1Vg3B/aNQyw6DMwiuJQNLgwJ9QuOJZ+E1gdXM1+mPCathGq/8NMetjRmsnVn/j1iNya41KcnMipXJ4CHj2RZ3BgC2uWM74a3pG46HVyLy4QGiY8rtmzqngLhLGR6aa5elOihWW0UO18peQDgegE47LX3D7xaOuD6OlsrVrZw/xHpR0NcM1BEHgNH9MOP2mxKELp+RH7udT6zecjsbpPj79DafjZT/+TfaPzqf7cPobn47B6e9nSzgaYXqdarhahfmcHtA6EboXG6TolIzl4go90vqLRfml9JXn7co6r4w+J9U2cBWxcFJdE1fp8J6/rxZ3VPWt4X0Hyndfmw01m7HHDGNXQw5vaBgZdrVDZ9kfaUjeAUPqkFEMrIDr2ZTSIqBPLRQ+/bvIjh4NyLTNhrQGtcBiNL0CG8z4+7sX2a6N/Hz7ftWkUclxlYWiSZDm3LDSMQ45SlIJb89efnx//v71hUL//O3Fx1PlzdnL03fnp8rF6ce355VW6FSrujeIYJTqC/i/Bf/3RlPxWywJsN+IeSfE/Dqod256uvqvprP39Hf27vzixZs3px+VDx/f/+fpy4tz5fS/L8A8Z+/fKa/ff1T+enb+6cUb5fzi06uz98PGNBAjYg2dspM9DfUx6ZNdDkBwLy5AoPYiPVDH
*/