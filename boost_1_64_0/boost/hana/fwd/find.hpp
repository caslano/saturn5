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
xcdwD9zeyKeuZxoCgYOPpqNqIgdC5zgMSEQc3TmFUGtNlGLRXMoWhVmMPx49fBfw06b0VyHCQjQpZWnJdwxVM9y2w+q09BOjl557sy09dkvOvyu/NNFRE4R5fJCWKWhfZBghFcgdm3QaMlG/qFTiou4DpzygaY6CWRGSI1TbKeW1v0o99AOWxV+cKu5a4pwzaB0uoyj4SVypNIfPREJYvkHzpKtzYL2sg+LYa4UOssigPspoBt+eqogpyKMqIB74MsBsWEbeIJpudeu9rE+wLhZPzfPhY6KojVyq33OQrz01lX5LaMsa0Xoi9isy90sOUYg6GFstmY29OCrYZJAFhbQ+O5dyjGcls2VGbofShJiIw7jcTFCRP4FG7j0bYbsWD0QZPPFfsZyuW9dy9sCkl3IA/heW7tuIq9Jsf45RocvoBV3++mw9J08jGTK973PLpCKWwwOtpQXT/Il67vbxj1glEht5q9k8Po3sNUhke9TU6cKCSLkeEZI+tBpzewoR8is1vxETaA1o6ApmtaP8apOCgChoytm1tlXHoNdFehdXSCGMVkjaF0hb7w==
*/