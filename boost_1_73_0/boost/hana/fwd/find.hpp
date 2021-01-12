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
SX5xyxPk3IcCUZl78mNT5SSVMn1JSgiiBXwNSzdDFJVvMD6z4UXKLDkLchdyKK+4datKVyRS/RS/57OVz231oIGp8QY8m589HbslZ7Gfl1niqpEMvJKayVR2i5ZmV+qNhfS78yB58ESnlPUbhK4E2zLYcZ4Q64cupLd+uL9hXZX1M40q1R5bhGROvTza7Vju51gu2JIdy/2esewcA7BqN97taWfQ4KPgFt4VSbTcXYDpuU6E
*/