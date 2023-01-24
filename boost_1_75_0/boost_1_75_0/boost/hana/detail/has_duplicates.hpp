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


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
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
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_HAS_DUPLICATES_HPP

/* has_duplicates.hpp
8LtCjVlHHNk4kjvmo6LlxgN2wH6y7E30L5XRu2EHGheJpEKgMwoqlTfFVhThE2zOHu/9mO39kK2L2nUU7d3Sn6xUr8hFovLjgLNBuE8mTokUddePyl8mOiU8DIWeEqJCo144ogv/EspiVw5DZXRprxtyXSUtwaVQZxSjNqYGubqRePgQnQ9lxIofSauHN6LrIoN4sxWKRBuWOm8isePZbNmxUb28GT8UHqdwNlL4LqDwXSqF7/tdjMLPv0YpfN3FFL7rshTeOI9R+OrfDadwDqXwQkrhbrGmV0vhXi2FB8SiqIbC38Nsx8+jYyGwDJAZRjLpd/MokfOQo/jJQk2vznsNatl4+Mjlt3e7QNEcv5TGuZYURfEQM6P1s5TWuFYZuouqrhLmH7XjqjNGY6ROuCKpPx9kl4jjpO6mpC69EqkvZuazv42Ret5vKamvvzIzT1dJPQJx/iobBWy5aJRe/22M2G9fzM7/DLEfxIz/MzvOzpI0mK1S+obLUvo2+yUo/Ryl9DqkdFGc0t9fMpTSiVektKQy9ShKaTNQGk26mf9ptva/GqN1828uR+u7LkvrZ29Uab3k1eG01jL2PyM6KK3zbhzC2N3Sn2+kpFxI+WsCkx5TmfQoF0cJQcOlBMjzlNS44REq1giQaYuHCpBvQ+tsDa0lhdYX8XUhcUJL3oDeuNAZ1xiZT4O5ucdcAGyhTsJPkti6UTFGL76B
*/