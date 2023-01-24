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
fGFRiNZp2dGs8K9ZsuA1v1AvVA0XLM+zvNCg5r6kGF52yxaAin1ZFld5ucDjFYBNi2U4ixYgwaIIogBP+cImgLQC3ACsuPIjNrvK8n8S7NHlnOt9XFzxgrSlOrq8blyjaHIp9tXSm9bdFQ1N4xXogvZPYDz+IppdJ+zmc7KINH5VhH7KNHjay8sgj/Ir5kfyMs6yclYs09vyZpHQToRyUV9flXN/VRZLAJEurko/+gfAIj2eloGfLmb4Dw/QyQxV0EOIuxt+g4u8vMxn6QJWEJAzNIGrm5ySRbNi4S/L7DJPomQRsjQFRefgsCJbAOWQQjScZjdxwlJYv6jg+T5UXa4WYTnzi8SvWyWDnAMCGSrPFuwGHRTlLd4W6PMyz24AQhYnJXUSleWcxr8gOpS3IAfltlAOMCxgsMtiFjMaM0vZNR6HX4olX/UFQxuBtDf0nBGp/TiEnBEwfswLr8Cu6eyKlyB8lsvLpZ+jZAkh5SgsMWiqFOeEJ3pw7Zdfgi+zz/limRcLVs5CH1IKPkyBXpIYsFQCMV36pYKB0YK4389uwN/xvIyTFPKl6HAfv5LhhQcAJVZeQXGVIPUsSWNoE2jAMF2slrwmSFuwJV8ah6EpEOscXJD6yaJ6NvslVeqkG8Q1LFN6Sp4IvBIf/A30L/10eeXTxWI1n8U+4XcG3ljR5pbLKyCa3JiU/hFZPDThNyMdZWO1nvgEH7w9
*/