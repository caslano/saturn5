/*!
@file
Forward declares `boost::hana::drop_back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DROP_BACK_HPP
#define BOOST_HANA_FWD_DROP_BACK_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Drop the last `n` elements of a finite sequence, and return the rest.
    //! @ingroup group-Sequence
    //!
    //! Given a finite `Sequence` `xs` with a linearization of `[x1, ..., xm]`
    //! and a non-negative `IntegralConstant` `n`, `drop_back(xs, n)` is a
    //! sequence with the same tag as `xs` whose linearization is
    //! `[x1, ..., xm-n]`. If `n` is not given, it defaults to an
    //! `IntegralConstant` with a value equal to `1`.
    //!
    //! In case `length(xs) <= n`, `drop_back` will simply drop the whole
    //! sequence without failing, thus returning an empty sequence.
    //!
    //!
    //! @param xs
    //! The sequence from which elements are dropped.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of elements
    //! to be dropped from the end of the sequence. If `n` is not given, it
    //! defaults to an `IntegralConstant` with a value equal to `1`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/drop_back.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto drop_back = [](auto&& xs[, auto const& n]) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct drop_back_impl : drop_back_impl<S, when<true>> { };

    struct drop_back_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;

        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr drop_back_t drop_back{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DROP_BACK_HPP

/* drop_back.hpp
zmJy7hbQ9Kr5RmRec956BGOa7MeX+SXrx/H8K/QR7D5mRQrITWsfGZtnyC5s+ObQTdTz12IxzsfOyjwnS/Za5TqbvNgSnsfXPNyEhmGsG0jsaN8glocS3YMr/csV/xTLIr6XmE/TARnkfeyrDtmoGFQzV24PL7aMATUKe63gacN1tvDXsranGzsi64IXEJ5CllCXL5WRN84NP9C8YktgTQ+zEBlpDfHTdpJi17+0erQ0W0vvX8qJW0Ri1GhGBiY0nAF0sKzh8KoBRe8El02FACi4VE3SETEG6GpG7pg95nl5JTLWP8Skr4/kGRvTUQ1tw9LWHsxtdOIln3V7WZcfT+nI5m6ktwIOn4KnYlSp6mJzvdBmmG0IZCIUXACHqPVK8/WWbtZaahbAUzP/NboBzTm8/8d9qfUQbdFqkrf2NSOUTArXbyWCWyD3J9wBYRxUD9EV9QMc4qbDLs5iwJsTqeYJSzdfh6AHlm7EoEMLBrYRa+241x/su3a1EZc4zkOcjxCI3AQzJsnv6ghVgm0OUcPd5Bd4r73xeiSWEQwO2AkcgUbI2SKkDG+59oYseoMsrmMrxnHMu+ajYfDDUQsx6eu3ooIsjGMZNSM3MJEkf6FjafYmMh/JtvFnEDLTLy3aXjds/Wr+dgNrZGSOlmC4irGQTpDHQCEGCe4/WxcK7DLwgQibUjI/7lZuv81BoOQSDUazzU9T9WPazZ3okOvfRcHo1GJCMLSr/u/ILB0zazgQJhzw0/l/pVA1XwRzy9ynYC+BRMUGKsze8CDbZ9Cz3aJl21Gp2wgSQ5GCX1Gv9Lae63Et1w1dcqWJXLw13CC2hlelJuoy6S4RKaQ3zVr4hVy8KzUnNb5mUbg/zw8O+qej+Mf6iPVpF8Sq7PsTy44p0UN2lvrrVH9z6Dc4XLrWpPXDGv8y0v+rUPuB1x9MGq9v7ZS0INHiYqguRzPk5RYZYxwOCNf2s6tDJ0/YG27lK0yrzpbCennXcXkvlavlCeYyV6UyZ0vf1RPWccJ7UxOS1qSH1k3cnvOzEw/9ehOF4sFFk7AYb8pjbAe1gPgWiZzbRpeQapahGXecYzS9yCanhQpEWdCOJomJm9fvXfayp10tCBL+tauoGq4C/8YIN81cVTGxaJfrtZwt3W7S8YfBf68sBfzQsViwL14yW/jVFQuddIh7+KGTA2CSlh867fXpeGBg7fWKgcLS7PUP8oPRXv97fki312/mBxirvIUfYNOWNLd8PuoY7pQ8DPjZRnoRUCsvH9eog4vYTRx3q872btMY6OA06UW9FdO4FeerrYgJK5fZ0ttaAvYJcfMUZroWsaUFFUHySF1suyXDQBuTdnZhsEPLJJHskgt+dnrq6CKXHCUzeuZXoyvRE8FJIF1mWLll83lXGWDnz81a7ULweRjzWJVSXYFB5ewfjumMFnPfBZ+QtuiV3qxVWpNaKVVHOcd0mj80Q3KlsgjZbhhjIMqq0J099WTgGIggralsZzjsbD+E96f+iz9iv3L9peLulAcbM42LlWfALDkkQqPkmVn4Ge7ulqPcg34jPjy0ynKCL0SyjcTgWL49MkD5y0Bx0iHc9YUnF40N2Ph4vGUg4xRZvWiqg7GAWOhYHzIVwPYs5ptNLJpRHTzumaOLKvcaWSXXFupMC2a0VVgIUDbVCvotRwAHzolyAyMlp76SbORrYGKdKJ8mhPYbkKMtg7JF7w1hlhgDuVKuvjL4teTZavJFSCnciBvCGdG1CZDdD7LZ/gUgZkLYw+fr0OZRRjvsFYwy4CnzcZxztX8OiUOdw4PndZRRxXOlWTqozyeAelOJqPsAoWZnjkhuRssu05P/OSH5lWrye2ngRoD7Kaw=
*/