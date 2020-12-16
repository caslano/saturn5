/*!
@file
Forward declares `boost::hana::find`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FIND_HPP
#define BOOST_HANA_FWD_FIND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Finds the value associated to the given key in a structure.
    //! @ingroup group-Searchable
    //!
    //! Given a `key` and a `Searchable` structure, `find` returns the `just`
    //! the first value whose key is equal to the given `key`, or `nothing` if
    //! there is no such key. Comparison is done with `equal`. `find` satisfies
    //! the following:
    //! @code
    //!     find(xs, key) == find_if(xs, equal.to(key))
    //! @endcode
    //!
    //!
    //! @param xs
    //! The structure to be searched.
    //!
    //! @param key
    //! A key to be searched for in the structure. The key has to be
    //! `Comparable` with the other keys of the structure. In the current
    //! version of the library, the comparison of `key` with any other key
    //! of the structure must return a compile-time `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/find.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto find = [](auto&& xs, auto const& key) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct find_impl : find_impl<S, when<true>> { };

    struct find_t {
        template <typename Xs, typename Key>
        constexpr auto operator()(Xs&& xs, Key const& key) const;
    };

    constexpr find_t find{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FIND_HPP

/* find.hpp
V+k3KDGatRmyEm6fFYYLU78E/onBqIZAEdZ1EMV49w5OIkfqtUzWqZmQqNs4xK7zsnSO0a3ceR9qocCVS66DDYL3RgDMQcJgD6FQOi7S0UJ+qnUVOLga/zb/mdbPCfkx03R2v9BabpKsyN28nWvjVpohQsT2McOk3mWx/FvB/zW1zjNuMLbONCLZYXnq3I1VxtZmcvSweaI9jd8ka9kQICHEunGzmr88Nf/ZuVQeolfBo48ORHSCML33HXlP6Hfm9+7vvlCV8cnQe6Sce+S1L5I+wz9KzFoKPRmVsrQIdUoNtgvpLM3Nc3YqvBBRjjQsJPYFs4in3MddeNpn64f/Cf3pN26BfKjPSDOqE9NbY9E5dH5dlPjpT0c1t/LSJpUQE7DikM5qxpV3P61KiCKlxc2GaY2aRQhl+Ne4F5DgemGjevZSnqHksCn3/1h3QM9oSDiUr90rNHQ5QidgKUXfMUX6XXeLWB7ls1s0wWYbtJ9ez96oK2JZlPKVGI+3tcnOTNofrYfXO4b4IbqXKV046Z9+fekCftjREq8mGl4UVXZeI4T60rBhEaTQesxEwkJcpd8hBfeXfT3pvebG9Nwi2tZngsa3i8WU/KzPhyk56wvMj+dYc1ZwLLlTy9kq5I1typfvUjt2q6DLYfu2WvyZvgmclWR9DLS42mUcxMmQKFuosdUSrhMJf23UqvS7pvjCWEAgD9kAmGxezVERcjqvO2j2/zH44uIk39WwihMuBNsrRa/chH7JVSberoswXx1R5jWI6XmI2yY62wPRrBX3qD3tD/DE2rxO7+VxvrmcH6so4yz/0MpZcsQ/BbS2I3v2KSbxZSWbBwNS/ZoUI91A07rMCqaG8oP4lB6tx+o/p/VY/emTV6VRimZtUa92JOsf1vUfYYBpDmoC6vyNbrKQQ0qjCzhRbBm8mrPuQ2YgxaSLrYNGVx54v6M5ZvAPl/waTJQ2Ec6+hgaBSsihEki0IVqonHdfDCREs+6nzPuigRJpsTFps6LeuhoQSPLpudJpnYcJgzSVgVMehPCp9Jymc6WleryWuHhnbdJuPXx0NfGhKbsgwGcISNJmIzKFtTA4O1PIk/JUsv/E1Gz2lkwmEuK7i/vPP1G0hkUexRbnG4J23SKjXV/U/Hyf8y1DTZfI3CKA2g9bVU+CAE/WAzQdDwHHHiPtTUYBUlC6WeYuGVh5JVugU8VPbG4p2GhZl5TzqP5zfnCj2tktPfX2O9sjH9yffrUPWePi2JdjN5PanLz+vxyPD+XSvorrFR53y25tTlH1YKAdmNDX9ElVHM3awLXEfhKocysPLOMgspUk9VCdCx9LRIj+FsZY9Goh0JsYFhPnlbA2HPWEv2JDX8IQ0hmhm4/QABN63YiN6S2vpsDxHE80ax2yjUtxmZYCSBW6Gz55wufUx5Z+/a53LosN8N+dKJGq33+AGDUrXqM9iSYUmSHL9c3jdgqrdxtFUw9v0G4LXB0h3hLwGLV9XiVDb59lPoI98ie2odyeiMU/xWfBAFAvMtzwRp8nOQbf/IQeHoYe/hKy9y1gb+7cLlqaPRGH/5NaDkZfqkg+1veZk5JfSckXsTdXuLuG7il4lBKvhhyM+pL48kL0SgUoM9zKj5ZqI3+Jb0lCribkeuI25HqDGPPrtY7ogifGHOgbugLIsCB+nT5A3e9Pl/+6Q9X/pY2XBpxpJo+ViNQYN3SyqPEnb9MsKOiIAFu4kawaPPdowNze8hxyZXzA3rILnzTUOXJEn8rn1WlDnTqfs6uTL9YGuyxhsJHpbzFa+WyX5qQB+zbhx6SFKjbk3WU03rVx4y1yKJee6C+HT1MOO/QcNsY12IUghvsLRR1phueSJas=
*/