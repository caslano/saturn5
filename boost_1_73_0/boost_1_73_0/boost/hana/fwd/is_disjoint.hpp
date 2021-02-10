/*!
@file
Forward declares `boost::hana::is_disjoint`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_IS_DISJOINT_HPP
#define BOOST_HANA_FWD_IS_DISJOINT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether two `Searchable`s are disjoint.
    //! @ingroup group-Searchable
    //!
    //! Given two `Searchable`s `xs` and `ys`, `is_disjoint` returns a
    //! `Logical` representing whether the keys in `xs` are disjoint from
    //! the keys in `ys`, i.e. whether both structures have no keys in common.
    //!
    //!
    //! @param xs, ys
    //! Two `Searchable`s to test for disjointness.
    //!
    //!
    //! Example
    //! -------
    //! @include example/is_disjoint.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto is_disjoint = [](auto const& xs, auto const& ys) {
        return tag-dispatched;
    };
#else
    template <typename S1, typename S2, typename = void>
    struct is_disjoint_impl : is_disjoint_impl<S1, S2, when<true>> { };

    struct is_disjoint_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&& xs, Ys&& ys) const;
    };

    constexpr is_disjoint_t is_disjoint{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_IS_DISJOINT_HPP

/* is_disjoint.hpp
PgUF8bgpCkx+uoiXSM8BaPo5liKvZu9Quu6Pf28EyhD4tCRDtyhSN0A8vlwmhTe1eyWnuZmXsZcvrKIBmmajAV5N0FIijk6lsxznwAKFDPjlAdcpUgfXW4TIcps4+bBfqV2xO8UO6S4x9ZyzHzfW3Edh6kMPcasxSTUFYMGB+4ZmPG6phW+Oa/Ysx61KlBxkHcpRfQndb2pqEirxS8o6aX9TW8UCqdH1S+0DLQCZnschqudfP6S6xlRAa6VsG5AnjkONbm5UNfIKclLQkkLLvGgVRBukGZWbhOSUMlI8m8M0A1AJiiJO1JA48oV/A7rBzi+Q6jd/HnM+R3u+Mk9tONwZIpYpKMyIMs/5ccZ4MzTQhLHc+dKJI4CRzTnlfX2MWWf5uKAkKmCqyLkNY87IKpa5t+rXneU23p9GfzMMpv4aaVnzZvobzZPZeS9vPNMZqsQft+v43TESWVgkNK7T38I8lMRHOlYqykwWdO4NLR0MycVKoQP/qQQ+Zgyoi3LCVPBFNjnP12DG0HfJbjyHG083ZXE1bWguv8HpwWiSSM9Pmn4knyBQRl6PAfLMWEO0O0aOryWTckDvrFo+LdfRhRA2Qftno/MvLuoK2mWQboKWtdr/yjXgypUp83EnezvApReky8C330C9cfOR
*/