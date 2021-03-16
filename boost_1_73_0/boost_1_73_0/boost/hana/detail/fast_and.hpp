/*!
@file
Defines `boost::hana::detail::fast_and`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_FAST_AND_HPP
#define BOOST_HANA_DETAIL_FAST_AND_HPP

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <bool ...b>
    struct fast_and
        : std::is_same<fast_and<b...>, fast_and<(b, true)...>>
    { };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_FAST_AND_HPP

/* fast_and.hpp
rcnRFjja6AxLOzjD0s50tHMc7WFHe8TRRkUs7aCIpZ3uaGc62pWOdrWjrXO0hxwt7UZLjgs57A6eXpWdiZsrSyo1qUs2RXK2Xef9oafeW3UIe8UPNz9z06NeEkvvORKecUybm9u3Rpb3tA2DMy4rpLztjcNhue2tEW3A+4AaEb5aLqAa5YmzOcSZeHcOQ+l74uaH7JfzlXw5v1Mv0QYtMNuV8mybXDtISujJanv3U2gH/+7J8sDqmt1DuCkzaE8=
*/