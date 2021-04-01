/*!
@file
Forward declares `boost::hana::remove_range` and `boost::hana::remove_range_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REMOVE_RANGE_HPP
#define BOOST_HANA_FWD_REMOVE_RANGE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! Remove the elements inside a given range of indices from a sequence.
    //! @ingroup group-Sequence
    //!
    //! `remove_range` returns a new sequence identical to the original,
    //! except that elements at indices in the provided range are removed.
    //! Specifically, `remove_range([x0, ..., xn], from, to)` is a new
    //! sequence equivalent to `[x0, ..., x_from-1, x_to, ..., xn]`.
    //!
    //!
    //! @note
    //! The behavior is undefined if the range contains any index out of the
    //! bounds of the sequence.
    //!
    //!
    //! @param xs
    //! A sequence from which elements are removed.
    //!
    //! @param [from, to)
    //! An half-open interval of `IntegralConstant`s representing the indices
    //! of the elements to be removed from the sequence. The `IntegralConstant`s
    //! in the half-open interval must be non-negative and in the bounds of
    //! the sequence. The half-open interval must also be valid, meaning that
    //! `from <= to`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove_range.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto remove_range = [](auto&& xs, auto const& from, auto const& to) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct remove_range_impl : remove_range_impl<S, when<true>> { };

    struct remove_range_t {
        template <typename Xs, typename From, typename To>
        constexpr auto operator()(Xs&& xs, From const& from, To const& to) const;
    };

    constexpr remove_range_t remove_range{};
#endif

    //! Equivalent to `remove_range`; provided for convenience.
    //! @ingroup group-Sequence
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove_range_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t from, std::size_t to>
    constexpr auto remove_range_c = [](auto&& xs) {
        return hana::remove_range(forwarded(xs), hana::size_c<from>, hana::size_c<to>);
    };
#else
    template <std::size_t from, std::size_t to>
    struct remove_range_c_t;

    template <std::size_t from, std::size_t to>
    constexpr remove_range_c_t<from, to> remove_range_c{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REMOVE_RANGE_HPP

/* remove_range.hpp
kD/CTlefmGk5tkungstliKxmbLOrTfVUrKQr+taOW69Nm7TJUIVlCD0Q33+G3rPn5yZWDTRkJ4EUhDrj5ofdcrMWg4iA7Cuolu/BdfN/0guAtn6jHpUH14856OHE8SKJfBbujmwUx2xf0mXFiwiWxjW5bO7TiNHj5bILdQ+S70YNLxe4kaVSWv9MK+fLyL5MO74TDMLKNcr/sWSaZaimODzlDGHfx5DwnL0luBclcRRHdDj60jTVmQL9beH+g8ngHuofq5Vsi02wG+7SgNBpqiddZUM/3crBb0wDblDFegxvrL8uDfYpfeVfxKxWKlWuYVgsWexp4E84NO6tT6ULOxALb8f+l2jorHGW4/0Y/pgJwiP8A1ZgwWU9wsRvf+fejaXzrFvHwSVvo05PK7Mca5l0gHI+xjAQQGpMvpDEzl7zNEApuJyLD4ftm1mB9/m3Ae4DlFxu3pcpIitRLceOG1rFmIEdkY91agapvzpAecoR1ZzOvPVBbsuojuUTJQ7CqCs5b56MfFgw6VBDyd6VHvp5HcKmgm1SVo3W2BG9pcxfDmxKPy6BDvAAMw==
*/