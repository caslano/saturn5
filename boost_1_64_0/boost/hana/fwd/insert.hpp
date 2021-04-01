/*!
@file
Forward declares `boost::hana::insert`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INSERT_HPP
#define BOOST_HANA_FWD_INSERT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename T, typename = void>
    struct insert_impl : insert_impl<T, when<true>> { };
    //! @endcond

    struct insert_t {
        template <typename Set, typename ...Args>
        constexpr decltype(auto) operator()(Set&& set, Args&& ...args) const;
    };

    constexpr insert_t insert{};


    //! Insert a value at a given index in a sequence.
    //! @ingroup group-Sequence
    //!
    //! Given a sequence, an index and an element to insert, `insert` inserts
    //! the element at the given index.
    //!
    //! @param xs
    //! The sequence in which a value should be inserted.
    //!
    //! @param n
    //! The index at which an element should be inserted. This must be a
    //! non-negative `Constant` of an integral type, and it must also be
    //! true that `n < length(xs)` if `xs` is a finite sequence.
    //!
    //! @param element
    //! The element to insert in the sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/insert.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto insert = [](auto&& xs, auto&& n, auto&& element) {
        return tag-dispatched;
    };
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INSERT_HPP

/* insert.hpp
wIxwSwwLLwx5jfQhuBNVxkQacrbTM2Mj8z7K4DVERRXVhllE2oLMPRHFMF+bhR7rHJVZEMxizPNS5bqJR3ysVU1TBxG8zAPm0lWAX2vxd+Wr38LyA9Hhg3RdctzT5/7+Tw7kRjV+Fk5SdekwVv+h8XHws3TpHz6uLE1NQ+6VNYywZoE4exYVw9hGlFcdQCNzT5hvWfhG1VpxbLJ69KfD2iuUDrKn9xoX6+5/UuBlA/xvwZxRuNk/+zjUtUnvVKDvEtf2tcLy1yBn+am68RjK21dWlnPBaQukRKGnfysWC+6G3ZJZ3yy9cjH1kOy33e6qsJqVgApqxuZu04oq6vEEHYI/mJ3otUabc3zStzrwIveQ+G5GKy1/hPjgT3k4B5m2nsXTomsMiIOGxec7swBh7kZDkA3k7VNxOxhbs0vp4dX3ZhHLAFk1LHzZW5rl89Ge1w60I+id4ibmQRrJFkGuaXNu7viNlzhcifWaYL/l1IjebIiLVVdPRKJebifIgyGtLIsuePDv34IfMIhCT4KSbr/FbwMMcMiils7DZlTc7lJ4evjmhhz5wFdEOg==
*/