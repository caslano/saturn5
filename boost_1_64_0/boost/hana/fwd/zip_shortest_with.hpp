/*!
@file
Forward declares `boost::hana::zip_shortest_with`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZIP_SHORTEST_WITH_HPP
#define BOOST_HANA_FWD_ZIP_SHORTEST_WITH_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Zip one sequence or more with a given function.
    //! @ingroup group-Sequence
    //!
    //! Given a `n`-ary function `f` and `n` sequences `s1, ..., sn`,
    //! `zip_shortest_with` produces a sequence whose `i`-th element is
    //! `f(s1[i], ..., sn[i])`, where `sk[i]` denotes the `i`-th element of
    //! the `k`-th sequence. In other words, `zip_shortest_with` produces a
    //! sequence of the form
    //! @code
    //!     [
    //!         f(s1[0], ..., sn[0]),
    //!         f(s1[1], ..., sn[1]),
    //!         ...
    //!         f(s1[M], ..., sn[M])
    //!     ]
    //! @endcode
    //! where `M` is the length of the shortest sequence. Hence, the returned
    //! sequence stops when the shortest input sequence is exhausted. If you
    //! know that all the sequences you are about to zip have the same length,
    //! you should use `zip_with` instead, since it can be more optimized.
    //! Also note that it is an error to provide no sequence at all, i.e.
    //! `zip_shortest_with` expects at least one sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zip_shortest_with.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto zip_shortest_with = [](auto&& f, auto&& x1, ..., auto&& xn) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct zip_shortest_with_impl : zip_shortest_with_impl<S, when<true>> { };

    struct zip_shortest_with_t {
        template <typename F, typename Xs, typename ...Ys>
        constexpr auto operator()(F&& f, Xs&& xs, Ys&& ...ys) const;
    };

    constexpr zip_shortest_with_t zip_shortest_with{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ZIP_SHORTEST_WITH_HPP

/* zip_shortest_with.hpp
XIP02mxruHtJ2trMLBLU3LmJlxJ/+whOBsA1CoMP9fI1L7e11ZSGuVjqesHb29jdWUaXVfm1dWoCBQEVVDP69CLz95Gh/1fmTP//ZAhIvd1TfHbH74kk9VXZXln1kkRnGZZUVwvOblnkqW9mobZpGjGDvME/iTI2JoETbKFKTxM3sLdETj1CgvdqOnjr9B4zcyNR1VlwOiJ2yf5NLk35oLi5dbNdgU96dmgPYO/sz3RaiVWv9Y+Ss4MIyjVnXuPPlFwkJNHYLZkss8InYEQ19T0wgPLosu5YA0xetm3fF9CFAC1JrDnkuwqtias7DGyDkNQZm46QffO0LSw8ulcTd2ER2IR5hKT8j+OO70hlhUFss2EQfAzEN4PvY/cpIzA9r+AwMu1mVJQ2bC7fkP8zAM4EOkskgbxn7NxFhfZAaIXDUHeg8xgphgEdFxTncWoFVBet0H1pFDhapw4yl6URA2jWxanwod/FTLCcDF36zDjw5/puJpADKkX0+1eEXxvcCeG5WvJAQ4jCWlUa96iZdbpp3X5Mu4jUyq6oi/R8b6lvf8subSU7XHbKLw==
*/