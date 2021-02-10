/*!
@file
Forward declares `boost::hana::all_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ALL_OF_HPP
#define BOOST_HANA_FWD_ALL_OF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether all the keys of the structure satisfy the `predicate`.
    //! @ingroup group-Searchable
    //!
    //! If the structure is not finite, `predicate` has to return a false-
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
    //! @include example/all_of.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto all_of = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct all_of_impl : all_of_impl<S, when<true>> { };

    struct all_of_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr all_of_t all_of{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ALL_OF_HPP

/* all_of.hpp
0N7mdFXQcQPjYGqPKKncuDtGzLXJiKeYEYSFkxwHbsnoQbew4Us4lVHXWGOiZgzhEOJDR1u4TKnpuoABYjEoWw+1zXpkjgI0qk/wWUaNgKpkq8UEDFXNsEaZQuuEOR4esLXDT4EOu/b68RATw9yQju3GQDTiZgxkg6/ZgOvbqRDwcJE3KQoZGv8Fy5WtpCZceEl0ShsStOlElhud8A4cNbL68lJGQNumnLeAt6LVy5xDmH5UN6ARKM64YRVybf0/5d/acBYRTWGYPewEDoLyBNWBslKtRLQXRmqqtIGmsC5sUXjdfjOkwkzSx40sSh1xCGDqmhF00yP1QKlkmu+1vF/cfHN2Kpu+HZ8E47xp3P/Cb6W3e+Xu0VtAlWNpd7vfnF2NxqOLk/eD8RfXtnK3t4Hfkcrd8Pf+f4nuigQfO5EpLJF4WYYJ8BFt4IrZTCYoqDXsTIK3AyqOfrs6Gw/wW+ewqy2VhxGH6t0nDkt+Bm1Xg+NTj7SdRpXX58fD97UEfjNJf1JuyIZ8wI55Jl6AuYUWlHDKXlE43Ulzt6IJaqo1xeaByT2AysuZcdz9m1U1y++yn5soE+AJSI0T5oRWI2o23MGWRJPRu4/j04vfhtGb47PzwSn7du05I+rUMl3fUFGuIa61eQHyCIuQ
*/