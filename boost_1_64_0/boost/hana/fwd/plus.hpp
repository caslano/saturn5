/*!
@file
Forward declares `boost::hana::plus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PLUS_HPP
#define BOOST_HANA_FWD_PLUS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Associative binary operation on a `Monoid`.
    //! @ingroup group-Monoid
    //!
    //! @param x, y
    //! Two objects to combine with the `Monoid`'s binary operation.
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `plus` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `plus` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `Monoid`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Monoid`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! The definition of `plus` for data types satisfying the above
    //! properties is obtained by setting
    //! @code
    //!     plus(x, y) = plus(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/plus.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto plus = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct plus_impl : plus_impl<T, U, when<true>> { };

    struct plus_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr plus_t plus{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_PLUS_HPP

/* plus.hpp
7RtihJ8gLzxnc8hzNuiWlqNQrvVquMZb1cJhM3Z9N6bSk7eUDALBYWa/OAKhZBPEdOM8KcvwInZUmPY0gVxMzOJRVPfdYwzHnbDM5NKOsih0LKL6kPe6j04LtBSCC2bjnC+xWXXDqlGQ6gNKESpmwBKEUZN6I63neVEjHhPvHyedEn/BHoYZubuDTiQfIWoYhi1XLKjjrQIoncDMVsGVE8WGs6WJMZgB5Tg0AoikFA9rasfgkFKxTPYITKZNccT02z+NUS1G3cCGqOa53Hyo1AY9dSBYF4v/xCeXXJHprjyaBvyzj1adZiMn2ISzUgA4PIru1LqfBy0HvLhEUzWRjkxv11C6B8lXqHI0+ZyqCaJXLIrIrss7+tEGJ6px2wxD0aIwreyYJOhH13CD7WRIPRNKBpeLCj2YBOQHf+JnHHbpYQ5U/ZBGlpmHUyt6+kWtz/S+6W7E/Tq5kvUEznv+ReY5PXRvMGryM7oOKSk4LJBEqmnWSo4PF2VRkleRBPsVi0yb7LOsrJiyBtpslvj1OSxtmnvREm1kOgZYH7gwU8ydaA6xIWQLzXfRePx8iCydLn04T1gvRAQWOf4yxaxVHkImsDTp+LzS/7aPOl1yabTqWDH1HMOnYiEmz5+drTwqZooXhpB48cF0c6Q4faa5XEtzLTrsLgmz1RH1cgislL514LUrh/KqVzqQKr0tc5YY3pbHkFfilMsUfHuFcnwQQ/I4d8VhHykh9b3tc3DxIM7wtWVyV+BRradpeUfd4byuTmJ4QJ3EcDS6tTbRGtOsMsjzroKFRqcPWvD5tYdILM8rItF29RJGgUu2c4qoHEx4DCQBkaniz+Q7NiIQlRnOnqTw9pNcPCmcJS02cNaLcDZwsnm0ppTC3fwi9VyDHsTKC0ije48s+XsLqQKrzkOkUfi+QXGFT1WFc2JuJRdeOySu8NCi+MKfvrR14TXnxBUeJRG4heD9nAs/Jq7w+fGF75wmC5eJh5uF58YXnpJQ+KA2Cj8yvvAlVPipBO+7EVT4zSNjhX9/Vlzh01XhnHhjuSp83eC4wsML4wt/7pLWha84O67wLghl7U0s4sKXLooVvji+8C+vlIXLxOeZhefHF+5IKPycNgo/Or5wUhkA8QFWer/lQz9pYAgi7B4OE2bYJKgE/WEUMAPGSr+Fk32iwQzLDeRRwJNmQD/k6usTd5kBxwayKMUKM8DswYffcf9NP6b/x3nG9oReON+otxzor9CWSkX1yJ+1dZ6sqy1MsD9hqY98//YIx8GA1k6RQLc1d9UnkAuhVZ/gKobi+PZVSgfPh393sZg3z3QXxKDal73jXl5gSPLTopXpPnGgQvFQz+IiccNVyiGu3jig1yceHsFhh3ynorRXT59p2IdQ3fBERtiAkWbbTmjVtg9Z9rto1sxWWWDNcIo+ohyBHAZPdRfWrzx7wiScP5pnKgTkLEWjVgb8JfnYah9SillzlYvg/HQsVH2ZJA9YuU/lq6pS56uMnGt4nOnD5fbFbrToI54dTi69vHOR34tzFc5cVFihX1w0T52+8kzzAKwy9vaLeReTRpohpv6cbEyXVkvz2t/Yuxb4JqsrnrRpG2ghAQoEKFCgQKFVqq1SKEJLIUUUCMQmKC/nA79FQISEx+TlQmdLzGTOTd3cU93cpm5zDqtTpHZSECbofOMDnI9bA4qihSKQ/c+53/2SlBYKutfvtyj9vnu/e899nXvuueeee0457ANmifPkQllzU1YUzBZVKzCvCaIge2AmXeRLN2p2MZjLPy0zdPTzcf0xsWr9E6sGIq2qNgE39p5Zrqr1GF03ph4hLzUVNfhDPfNLai9WMx5y7rdbt4LjgSJoqJ57WjY=
*/