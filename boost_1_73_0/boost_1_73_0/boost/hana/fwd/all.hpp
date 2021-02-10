/*!
@file
Forward declares `boost::hana::all`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ALL_HPP
#define BOOST_HANA_FWD_ALL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether all the keys of the structure are true-valued.
    //! @ingroup group-Searchable
    //!
    //! The keys of the structure must be `Logical`s. If the structure is not
    //! finite, a false-valued key must appear at a finite "index" in order
    //! for this method to finish.
    //!
    //!
    //! Example
    //! -------
    //! @include example/all.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto all = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct all_impl : all_impl<S, when<true>> { };

    struct all_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr all_t all{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ALL_HPP

/* all.hpp
b1p0xR2qgomkYxx8JAcfHCATvA6cnTI23JTBoyEoOiZEY3gXz2Z/yslyRv2h4SQREsvNjSmJZXdrU+2Qb+V4Tu2qkKSjRV4PvxivK08xxUQZh+G6+3op+qcscvYKaSHioA8Z9pzyozNc3DJXb2gL37UJWty//xFeHva57uKtde9c/8+6RY6b5vtovo8R5IpZsX+2K+f0LeDHtftpP+CNWeGyJxB08yYcaCsFwpx+gjZl9cZJKvJVpVZUP5TrG/3Ks2lIsyWmxYB38sab0M4mK2pFh/zahuk2PcDqvDo4fl+QYuMVh3tM1reRQmvOB2x8z8es1d470j7uML9D01mdHAJdXdPwtLBgEdFHAqU2GFWkroN+wa1KecdyVliohkBXAx6QmK4aRWjvbK7ODTVjmz2BscZHG/1sNTDbe9qa62sBG/62spjRtEtwcYXVdrGsYHKn4P/iiroCrwM+6KnTcSJfGzpHfdHZ3tJxHaOgrk++2MnnmUXJvNNSH3v5wllFrFxvXFkYWov72gVLhw60kKMXg4bVlv3Wdj3JFJ2AXaUp+XRk+Oyi6bHrMpmckkd1A7/uhQDBXW8abOoD0sBHPfAAKQ60EdwMJgolArnzQyntu6SU6b0OyeWF9D0Hz/zo2zrGrbP+nHoScjWF
*/