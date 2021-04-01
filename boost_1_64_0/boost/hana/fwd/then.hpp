/*!
@file
Forward declares `boost::hana::then`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_THEN_HPP
#define BOOST_HANA_FWD_THEN_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Sequentially compose two monadic actions, discarding any value
    //! produced by the first but not its effects.
    //! @ingroup group-Monad
    //!
    //!
    //! @param before
    //! The first `Monad` in the monadic composition chain. The result of
    //! this monad is ignored, but its effects are combined with that of the
    //! second monad.
    //!
    //! @param xs
    //! The second `Monad` in the monadic composition chain.
    //!
    //!
    //! Example
    //! -------
    //! @include example/then.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto then = [](auto&& before, auto&& xs) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct then_impl : then_impl<M, when<true>> { };

    struct then_t {
        template <typename Before, typename Xs>
        constexpr decltype(auto) operator()(Before&& before, Xs&& xs) const;
    };

    constexpr then_t then{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_THEN_HPP

/* then.hpp
7NDS4iNzTaJLFBLZgrx9E9cUj3t+QD9VlDB6UXFJLe4oOSuQNqRwBZgmZSmsclrkMBg3SD7+qbuOGIUw6LNBr/pIRZ9FP5S2AdryM3s7sAL5mKX68PsNPCAqQA4xoqDWsjb9/x1Nb2hDQkvTE2c5fIqRmBm9vstDlT1GLaqd8r48iI3EhpRakTNN90WOa6IxXFZJ1kQdkJG3ieuIvoeAtkG22a7z0I76nMIP4eBJ7bCbYVgKF36b1b1PzUT8tNe7y4yGtCrb5FrtokAphpZeYmvGegDi1jzVSWZQ/nnhsBYJKLelfRWde7cTYyNV2tbn8oRFK6pqlf3xtvFfDRIAaJlLUJHIHTtm158y/LQi4an+vaRDO5FBco4xOx49MFFZKMi1IjknRxz4tUTcd91GAxxHa5hendmPpOj3qqPl3qRdCuSUUghnOfy+0D36i0v/CTCkjxav5bA4064+2OpX2cELdfwokhKpUzUAp+jzttmzFvX2FOrjW1I1nby508xrn6IxdbzPg/jnFRrDpX4DQ6e2agLeEWCvsyOYyVIk+DA02gg445hr/CHjUQ==
*/