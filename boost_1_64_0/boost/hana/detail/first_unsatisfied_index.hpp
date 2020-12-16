/*!
@file
Defines `boost::hana::detail::first_unsatisfied_index`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_FIRST_UNSATISFIED_INDEX_HPP
#define BOOST_HANA_DETAIL_FIRST_UNSATISFIED_INDEX_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/value.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <bool, typename Pred, typename ...Xs>
    struct find_tail_size;

    template <typename Pred, typename X, typename ...Xs>
    struct find_tail_size<true, Pred, X, Xs...> {
        static constexpr int value = find_tail_size<
            static_cast<bool>(hana::value<decltype(std::declval<Pred>()(std::declval<X>()))>()),
            Pred, Xs...
        >::value;
    };

    template <typename Pred>
    struct find_tail_size<true, Pred> {
        static constexpr int value = -1;
    };

    template <typename Pred, typename ...Xs>
    struct find_tail_size<false, Pred, Xs...> {
        static constexpr int value = sizeof...(Xs);
    };

    //! @ingroup group-details
    //! Returns the index of the first element which does not satisfy `Pred`,
    //! or `sizeof...(Xs)` if no such element exists.
    template <typename Pred>
    struct first_unsatisfied_index {
        template <typename ...Xs>
        constexpr auto operator()(Xs&& ...) const {
            return hana::size_c<
                sizeof...(Xs) - 1 - find_tail_size<true, Pred, Xs&&...>::value
            >;
        }
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_FIRST_UNSATISFIED_INDEX_HPP

/* first_unsatisfied_index.hpp
r39kdOaX07ZUMaypnHmWCowq9wMZnWcx7EaGPcmwFWBUXKT16HiWrMfc62FYOxhlyxBYERUXhp3IsAvXY+71gFG+PwLmINjLTH4rGLmfGbkCJ/MsgJOWm+Gk82thWA/DfE66fh7BsCWMnTcy+T3AsGedzP1pJ10/f2dscaxPx7qKYduBVRJsX4YdBVZNsGvAKN/vBiPfewBWQsWFkfuRkXNU0OfwMrA1qfYORvnQBEbltycYZWcQzEm1d7BSgl3O5HdvBfMsIyO3gpH7nZFbcwO6r6sDo3xvAaPKoQuMym+I0XkgWCHBjgOj/Fu8AXPvjJFbtgFzrcbIrWDy+5mRK6ykWQXDZjJs50o61v0MO7CSOYcz7EbGluVg5QR7v5Iu9++Z/Io2pNvRZmDlVFzAKDv32ZC5bwFWQMVsQ2aej2FXbcjMFzC2PM34voLxPa+KjmclGOVfLRi5hphhfQyLMuw4MCpmS6qYZzIYtozJ78Uqpk2DUbHO3oiWKwGj8qvZiHnmC6yCYEEw8v0vTH6LwfIIdilYIdWmwcj38ICRa7YYW1YwOn9ldBZU03LlDKutpuv1dtW07zszbHewfIL1M3IRhh1aTft+MpiTYNcx/t0JVkbVeSa/Dxn2fTXdNgs3plkVGOX7DIY1gZHrNxk2wNhyKBi5HhaMXA/L5HczGNU2n2Tye3dj5tqe8cGxCc2qGdYIVkzFE6yQqtdgVFyijNzhDDuZ0Xkhw65j/Fu+CTPWYOR+ZezM35SWqwCj5GrBKB8awcj3KDFyAwwb3ZSZs2LYhWBUvV7K+HcvWAHBHmPkXmbYh4ydPzMxc2zGXBdvxjyTwch1MWyAYQcz7DSwfIItBqPieSWYg2C3M/k9uRkzf7YZM7bZnGblmzNz22BU2TaCOahYM/ntx+R3KMNOAyug6jxj5zWM3O2M3HLGvxcZ9iFYHsE+B6Pqy48My6yhfSisYa43wUqotlLDtBWGDYCVE+woxpZzwIoIdhUYVQ63MzqfYPx7n2G/Mvnlb0H77gSj5GrAKP8aGda9BfM8yhbMuAcshyoHMAfBzmDYpQy7mfH9AYY9vQWz9oORW8GwHxnff2fkCmqZ6w4wB1W2YOT7Kmvp8tuT0bkfI3doLe3DiYwPFzJy1zC23M3Y8jTD3q+l28rPjFzhdObaAozyrwGsjGA9DIuAUXYew7DFYJQPSxm55Qx7fTqz3gmskIonE5eCOqZeM6wWjMpvB4a1Mzr3YVikjikHhi1mbLkKjIrnnWAlBHuWsfN9hn3P2FlQT7OKembul5Frr2fuU4KVEuwIhi1m2K31zLPEjA/vMj78yMgVzGCevwYroernDOYZT0ZuPzDy3fSMzkVgToItBSunYsbIfc74nrclzSq2ZMZ1WzLv89iSWSfM5Hcow84Bo+rnzYzckwz7mGGZM5m1EWBUXGrAKN9bwKj89mHkYjOZd/QwOq9ifLiXkXuZye9bRq5wK+Z8uxVzn5mR6wGrItiBjNxpDLsKzEmwxxi5d8EqCZbTQM/BVzfQ8WxpoHUONdDt/RiGXQpWSpV7A+3fi4zclwzL35pmlWBUuW+zNdOHbM0808bkdxxYGRUXsAKCLd2ambPamlkHDVZEsLcZuS8ZW35lYla0DZ1fJRgVlx0YtjsY+f8PYNjhYCUEO4dhSxlbHgOjyu9DMKrOZ2/L3FfblrmvxrAWMCrWvdsya4zAHNr/02wra8zACjTWYGEngun1Zb6FLQYrJNhVYAUEu9Xkg5U9wsg9z7C3GTu/ZPLL3A6xJlgJGOVfFRiV30wwys4msBKC7cnYEgErJthRYHkEO5Hx4TzGh6sYudsZuUfAqFi/yrDPwEoJlrM9nd8=
*/