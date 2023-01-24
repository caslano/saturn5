/*!
@file
Forward declares `boost::hana::negate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NEGATE_HPP
#define BOOST_HANA_FWD_NEGATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the inverse of an element of a group.
    //! @ingroup group-Group
    //!
    //!
    //! Example
    //! -------
    //! @include example/negate.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto negate = [](auto&& x) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename G, typename = void>
    struct negate_impl : negate_impl<G, when<true>> { };

    struct negate_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    constexpr negate_t negate{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NEGATE_HPP

/* negate.hpp
pFr/AIqGT4QG3mrAxxVKtOflD04jIE9G58hsnFIeBv2jJGF8pWK1Q3XLOUoNvk7Rk9tfl8maKwT55sYE36Ar3sdGDMKB9fH01eZnH7HOqOIxzv88E/fGOvKMuMKq5ws+5ewoPKdr3eB0z8oOlLI1qy6bD0rhz9vcNrfkRL0jGxC4rJN7cDinGa6pV8heXnFwNdTzaL9NuDxTSxXm8DC0aW/BM5Yb2rZun6xp0bdvlz9hWy6p8YIt5EJ7Nr3sOrJcmg9xxg00v5qkYV2jhc2OSFqi+1A8Z4gmYNRtRhNJdBO54FaZ4dO8tzVdnwWRA9GaoK8PChc7clQQdaDaIY7TjR9UxZnZBD4GmKAp9fueuwQeOJc1TM824WgsO1b8CWyzz1dIAaZdvleMf9HLIii1KLAQR71I83QqWD9xtxe4FITvfFfCjs5I1T8QMXp160omdKL8TmyEfmcZQpy4y/sCw8NdEpmPT+6G31fmwhos2x6yHZIbo90CXlrvuqEcbS9gJYbIZSvR/aGupWIGr+w8ch1XnjDfLvW7AjzJjeWb+6vU64u8zY2Z5YbUJycYV0AI1hVRLV7TSojMZt/nrWEkHStJ/C4S7bes2LuEnjQv7N9q8+ZfiMT6C/UPf+pP/HW4szvPQ4O+NmTgycMNULxs3LTF6hwDfIOP2j5QQQWhDA8z5wSdUzC6CWpAUEhTA0N7kVBqDnI1YnNgS5Dm
*/