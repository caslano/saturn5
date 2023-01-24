/*!
@file
Forward declares `boost::hana::all_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ALL_OF_HPP
#define BOOST_HANA_FWD_ALL_OF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether all the keys of the structure satisfy the `predicate`.
    //! @ingroup group-Searchable
    //!
    //! If the structure is not finite, `predicate` has to return a false-
    //! valued `Logical` after looking at a finite number of keys for this
    //! method to finish.
    //!
    //!
    //! @param xs
    //! The structure to search.
    //!
    //! @param predicate
    //! A function called as `predicate(k)`, where `k` is a key of the
    //! structure, and returning a `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/all_of.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto all_of = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct all_of_impl : all_of_impl<S, when<true>> { };

    struct all_of_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr all_of_t all_of{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ALL_OF_HPP

/* all_of.hpp
naJKJxRNgCz5K5SLBOSH1jDOeDieuMZFozVw3oaBNFR3ufiUBKRNCAkvoyWObYl2Rujc2o1pjnVdpX35btp3PcgtGlU/KOVqEw09m7qhwhutT6D9BxhaM6hrtWxC4SBX66ixPvkLsWs5Gqir8MPaVdcKyv4sZiOqbnhgo6DqqnsjhiAqI4fillUu5d3Fj0/qJvMXWQQcTx9R/4G0nWhlPs5eX4un3ppiacFKi7TSIK1ESzaSCfraZSpVCdowZyZ2Bwu698rr0tcEcQdIHQJrFZZCJcf9Lk4+YFCO/4oVoHFpdk3Ecqdj36pBwOg3+nWsZmnpgM5TgFv6qqGE25qBQhGrsvMUIvi9imBLxDAZT/X57Lto7I09l2RaLw+Srs266dCFBgDU2iWlU4hiOSovTvVEJs4iR5t23n2nwk32eugfTA9dxWiPKhwjuPWwyq11ojZfkP4mGxZZ3R6aqS0di3uZt4gyh7JcQ8TgpDnUDXPDSwDdwz8RUyg2+zJFnZTWCnj3LaHG+ZPQCA3qTsxaew+bgh0LuCe3qzSHLYxLeRZHVYmOVeH5du1FKmkiAFFLwlloMuJhwhtS8+PE+fdhr5wCxUp20hMSzbYseVLPJ8kEaRhdcVf0YWng7gMjfE6c9cFupahM0xYHzWZoXZzad4lkFBsbeWZHb5zAAv3EvoB2fji60ZTPV9u7lRuiOJY+IasC2MJ/JMdizJxn
*/