/*!
@file
Forward declares `boost::hana::minus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MINUS_HPP
#define BOOST_HANA_FWD_MINUS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Subtract two elements of a group.
    //! @ingroup group-Group
    //!
    //! Specifically, this performs the `Monoid` operation on the first
    //! argument and on the inverse of the second argument, thus being
    //! equivalent to:
    //! @code
    //!     minus(x, y) == plus(x, negate(y))
    //! @endcode
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `minus` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `minus` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `Group`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Group`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! The definition of `minus` for data types satisfying the above
    //! properties is obtained by setting
    //! @code
    //!     minus(x, y) = minus(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/minus.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto minus = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct minus_impl : minus_impl<T, U, when<true>> { };

    struct minus_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr minus_t minus{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MINUS_HPP

/* minus.hpp
4qEs1HwxhfAy+wHWICRlgq27r1ljdZufN0f7z2gLqMCnh6RhxSvcEBcd2yPV2xB7pskedu1GjXLxSYEJdk10PLLYdGkJpuS3kTqs3TTsHA8xjIbN48fjr9ZyDQUcAAvti8ggohixbnlQKeOZTtfzlME1GJSeZUkIYT0ZMJ5gM2kR6KsNpfvhxlJbpzdVcC3Sj5yt7Yylsg7jJJYXiDem/O5wfPIj1inTWGu6uGTHjjRGPQih9FHrlMAnv4TIJ9US3xKo2oOKK0CakO1AHCS5qkG61tjR/uqrY0UbC9tHV9O8uW4mYUWh6q3dae+aYRSi/ebYNXP7Xmtv5wItHK4TqmJ0cJzGHDM1ZAcEVdjeDa04wMU1Y4smLxMF/4cMimxeYdnLAf7czGtqeGvekwyuVcdW9BcfMEJqIvc26utbTrV4AyLTBMsoD7FQiaTf4fXtPQEw7X+rPM5GrhhKlvPmquYCfvxaQi+Ku0Cqcu3MDWIscFMV7vtjLw1DIdEYImFaTYMWnSgqIjHKue8WoV/zfBzpmQvWvMvw19kVtPlDt7t92ixbIM//xvvF+Q==
*/