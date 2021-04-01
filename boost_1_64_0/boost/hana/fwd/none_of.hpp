/*!
@file
Forward declares `boost::hana::none_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NONE_OF_HPP
#define BOOST_HANA_FWD_NONE_OF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether none of the keys of the structure satisfy the
    //! `predicate`.
    //! @ingroup group-Searchable
    //!
    //! If the structure is not finite, `predicate` has to return a true-
    //! valued `Logical` after looking at a finite number of keys for this
    //! method to finish.
    //!
    //!
    //! @param xs
    //! The structure to search.
    //!
    //! @param predicate
    //! A function called as `predicate(k)`, where `k` is a key of the
    //! structure, and returning a `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/none_of.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto none_of = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct none_of_impl : none_of_impl<S, when<true>> { };

    struct none_of_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr none_of_t none_of{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NONE_OF_HPP

/* none_of.hpp
djYgYNZzykJoesKuZmQM6ekpKT13A54oLkxYaaMPjx79Cc+mI1EpSMjST9JPLEgYN0xzAM9VRjqj9wQyyIJu4UHCadz1C08amic1vH0vaZDOmmJf21bdDEpiJOzdYRGCBYF5CIHiWtqjDYGbTYt5B1ZRTlUIeHlkXTwz0DrCvBqt2qKvF1nHW8jxnBBOJO6SzmI7xrWoXvhjMWssuPwnqV9BJt9YZFb61/yMYj2y/i21QW5cF248/M/Meanxhb1JetbTQ/PaghLxvGqv0BKSS9K5X+kjSnsd97V1LS82Pe1M1+/Wdnn2G8MlGWPvgU53k1vJSK805ZyFQeVfPoDYsPLreDQLV/kyr2y7BC8bbvRKH2SLph7Tnqn7Ufrek5Bz8KG1/7k+bTaD0OYx8SVDZfJokqwNbWKF3Qrk6AaLUmXvkZ2tbzx3QdtWJ6tYtX1ZPnsU3XjMviBplqpexkgeGt6RWihfPDXB80BYupjI7/IIy+bnUZwtszH6rHuUSm6lq9Kaxy75F2b9TrpRlLEzelqlUySjw9OIZGggJticvgX0MIfmhvQY+WAupA==
*/