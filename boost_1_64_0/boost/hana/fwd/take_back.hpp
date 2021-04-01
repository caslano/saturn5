/*!
@file
Forward declares `boost::hana::take_back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TAKE_BACK_HPP
#define BOOST_HANA_FWD_TAKE_BACK_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the last `n` elements of a sequence, or the whole sequence
    //! if the sequence has less than `n` elements.
    //! @ingroup group-Sequence
    //!
    //! Given a `Sequence` `xs` and an `IntegralConstant` `n`, `take_back(xs, n)`
    //! is a new sequence containing the last `n` elements of `xs`, in the
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
    //! @include example/take_back.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto take_back = [](auto&& xs, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct take_back_impl : take_back_impl<S, when<true>> { };

    struct take_back_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;
    };

    constexpr take_back_t take_back{};
#endif

    //! Equivalent to `take_back`; provided for convenience.
    //! @ingroup group-Sequence
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_back_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto take_back_c = [](auto&& xs) {
        return hana::take_back(forwarded(xs), hana::size_c<n>);
    };
#else
    template <std::size_t n>
    struct take_back_c_t;

    template <std::size_t n>
    constexpr take_back_c_t<n> take_back_c{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TAKE_BACK_HPP

/* take_back.hpp
EWU8uiIW2lyAlxHTZv1Ip2nyD+AnTekUvuzGKRkhKnLMVoPytFJ8Zqd/wy+P+swNPtki+TUjAf5VQLRkRpLcbjTP6yUFc0oUdPNRxUxgSlFVFS54dOoG6A1RzZn7bGkFJqoweHYhPHzVH3YPK4bUNpuLlQ1nI/uSYeLH57K1bkrGH5QWz5Vm9AO5WG8VGQTI9t/bTCwSnKrRTldChekM+H5GzxsVVdSMydW1vbLDVEmzZyeNg13ykQUPZQHLeY8kQmp4vGAcJz3V2eF1DZA8hmA6gyo6eLt8ux30zAeXhDTvGTvQ27ySnRdNq5CuucEv5/CFpkAGtdYOLqG/Gy4FwZB0LoygsaAX9lEoiip5oeO0HrLtyFFgTHczZORRwMsc4Kfjh4UdkgHyno7Cft6zubbtSasK1o617btISdN1hRaPB6SbWj3KAj0YAyl7hqYxPKVmJknI8TfU0R4J/d0a5z32JQhVmsNTuf3Z9u/i4qJslgCab5sDSUU9QXIsHeL4tIpktEauv2iirBQP5Ab618JvrPuzkkzkkuYaOHZhJi8I0jqKqbc34UUmxg==
*/