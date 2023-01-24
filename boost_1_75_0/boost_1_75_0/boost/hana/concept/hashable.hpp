/*!
@file
Defines `boost::hana::Hashable`.

@copyright Louis Dionne 2016
@copyright Jason Rice 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_HASHABLE_HPP
#define BOOST_HANA_CONCEPT_HASHABLE_HPP

#include <boost/hana/fwd/concept/hashable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/hash.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename T>
    struct Hashable
        : hana::integral_constant<bool,
            !is_default<hash_impl<typename tag_of<T>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_HASHABLE_HPP

/* hashable.hpp
eDJwlOXE8/FUj6GMyzPRtmiTSrdlw091PT44HTCZXL9rhICf65Lx89VAOLvw2/QGZyF7BSOIYZWmyZvTDPdP0qh5uxC8WIX5xWBvrZ4HYAPi4w1qA9K8lmD2ORwL+22ihRAgYpRqaZg9sAtJ6sc63roJb/FVFVaDNIZC+X5jIBZkTcFu1PArL0CcoK4CJLIgBCQyguNyG9yX9LeXkNHQYdE2IFhYC1SHv27PL23MGomz60nJeLLxZFdDAjmBROqJG13+VVp4shEqb3/3JDsIWU92/Z1EhG58sYdetGI42jXhuZjJvzjNOn1NmtXlLlbSVabvNAhLA4AJ3BsR2XNwsvE/5IFJ+r/Kdtt/l83Rfb6c+2P/FfqvT7NMb5E/EU0NE1pHNJR0XYiLMvrbBP0tLtXo6c3TW6gXWtR9Uw094XBWy8n1I9SGksdVg2JOO9k4E2ZPQ60h+Bl0UZ/DIrjVE83xGcAJfcO9IHWi+yaImU20g7zrfWAUMG04kaDvMqEb42cUrRVmGpv4p2YYYSZg0DxaWPNypQJF+KTpoN5YgCtwjgBMtSgx+AmGz4hMzxeRA9AQGt1ro70epejSTI4w0oiwlFjscjOUFhq9yZ51WInPjTxC6wCqV9KxLMnmu3p6hVWpiCnwIBSYF/wExggJZh3QcBTNOqvn3brhjg7ftGZHu4GHVogZNOdWh/2Fljc6FQvCWGdmL8KzksHG
*/