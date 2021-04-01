/*!
@file
Forward declares `boost::hana::min`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MIN_HPP
#define BOOST_HANA_FWD_MIN_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the smallest of its arguments according to the `less` ordering.
    //! @ingroup group-Orderable
    //!
    //!
    //! @todo
    //! We can't specify the signature right now, because the tag of the
    //! returned object depends on whether `x < y` or not. If we wanted to be
    //! mathematically correct, we should probably ask that `if_(cond, x, y)`
    //! returns a common data type of `x` and `y`, and then the behavior
    //! of `min` would follow naturally. However, I'm unsure whether this
    //! is desirable because that's a big requirement.
    //!
    //!
    //! Example
    //! -------
    //! @include example/min.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto min = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct min_impl : min_impl<T, U, when<true>> { };

    struct min_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr min_t min{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MIN_HPP

/* min.hpp
oXhYT9V7i2+QBwxyN14mRu7krw+YjDlb2bJlVDqTljr39leH7jAgcxim2079VR519iIADLiDNgCjTJZBWdCQ8xkfA7wN9ALcmRTF8ijUAS5+PQ7hsif+gD8EeENA/35kkeSQhQcvbxQiVkFC7BXSnOUx4ntRH5r75/Lu2V0aE8Id5qK3GgMTRqUIOcJ47D30AHtDA0S011fxPDDEw8EK7aJbUrrd3Gt3yMnaL8XdrOehjWZ+4kqhx4oxHiJVsm0MT6eLPlTwXgPJmWiDgswFzfpPEGI5Ou5yrSyR9CbY1W2a4jadzTUPu96Uwok5y+XVcpRSL4gCmp+pu1mhQv32WHNIWKCcfJ5UqwFwjCLvQcrwJcbIrwK2a0ZED4ZDWbO+GJUmB1D0qoQ6Ojc4SDX8QgyglhSOJNBDZx7u25c2hNMqw3zS9EE6ipj/QFE00xq3WlJbR6sfrBqsHkeYC33KA3wHYk+YW9Vdcda/rrpJflhccr6a1SxbFMVWMbQdPom78tYYWR/0jlv1IA6rGVQOa3IQTmzFYMAOu+DlvUnwkTS8YxwDr3RadqGUvQ==
*/