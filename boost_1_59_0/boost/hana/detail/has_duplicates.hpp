/*!
@file
Defines `boost::hana::detail::has_duplicates`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_HAS_DUPLICATES_HPP
#define BOOST_HANA_DETAIL_HAS_DUPLICATES_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/equal.hpp>

#include <cstddef>
#include <utility>


namespace boost { namespace hana { namespace detail {
    template <typename T, typename ...U>
    constexpr std::size_t pack_count() {
        std::size_t c = 0;
        std::size_t expand[] = {0, // avoid empty array
            (decltype(hana::equal(std::declval<T>(), std::declval<U>()))::value
                ? ++c
                : c)...
        };
        (void)expand;

        return c;
    }

    //! @ingroup group-details
    //! Returns whether any of the `T`s are duplicate w.r.t. `hana::equal`.
    //!
    //! In particular, this does not check whether all of the `T`s are unique
    //! as _types_, but rather whether they are unique when compared as
    //! `hana::equal(std::declval<T>(), std::declval<U>())`. This assumes
    //! the comparison to return an `IntegralConstant` that can be explicitly
    //! converted to `bool`.
    //!
    //! @note
    //! Since this utility is mostly used in assertions to check that there
    //! are no duplicates in a sequence, we expect it to return `false` most
    //! of the time (otherwise we will assert). Hence, this implementation is
    //! biased towards the fact that we __will__ have to compare every pair of
    //! elements in most cases, and it does not try to be lazy.
    //!
    //! @todo
    //! This implementation is O(n^2). We could do it in O(n), but that would
    //! require a more elaborate setup including storage with O(1) lookup
    //! (which could be based on a compile-time hash). If we implement such
    //! storage for associative sequences, we could use it to optimize this.
    template <typename ...T>
    struct has_duplicates {
        static constexpr bool value =
            sizeof...(T) > 0 &&
            !detail::fast_and<(detail::pack_count<T, T...>() == 1)...>::value
        ;
    };
} }} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_HAS_DUPLICATES_HPP

/* has_duplicates.hpp
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
*/