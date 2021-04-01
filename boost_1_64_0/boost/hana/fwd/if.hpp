/*!
@file
Forward declares `boost::hana::if_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_IF_HPP
#define BOOST_HANA_FWD_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Conditionally return one of two values based on a condition.
    //! @ingroup group-Logical
    //!
    //! Specifically, `then` is returned iff `cond` is true-valued, and
    //! `else_` is returned otherwise. Note that some `Logical` models may
    //! allow `then` and `else_` to have different types, while others may
    //! require both values to have the same type.
    //!
    //!
    //! @param cond
    //! The condition determining which of the two values is returned.
    //!
    //! @param then
    //! The value returned when `cond` is true-valued.
    //!
    //! @param else_
    //! The value returned when `cond` is false-valued.
    //!
    //!
    //! Example
    //! -------
    //! @include example/if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto if_ = [](auto&& cond, auto&& then, auto&& else_) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct if_impl : if_impl<L, when<true>> { };

    struct if_t {
        template <typename Cond, typename Then, typename Else>
        constexpr decltype(auto) operator()(Cond&& cond, Then&& then, Else&& else_) const;
    };

    constexpr if_t if_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_IF_HPP

/* if.hpp
MpoIyGVzc4KRgjO1NOP5RQ/3ARxHnQ1YEZB7htui7lrTsyBTQ4Mv3cgm8gvxkFoSKnVGhuwvLUd+BC7092JPfK7Acxi2XNcGwIqdTdQJYuQ7EKkX5IGOoEX7cB5mum7Dcjwiw9CZgi5yEKwX94kLCAtJgSHX/iktSgFd4VhDOR/DOOHAparIfWc6ls2iEWJwWCuidPuct2JJnqRB1WtUKEW7CQpjXY5OhQfCEIWOyvInq7iowvJsL8ylcXbQsewaPsbiqXzu8flLvBNbIw0wgV1BJpAKvV/R+f+YJTxQPw8itkcRKo0HGozEy1PWpQktVB7nVZOBW3DjGP6swGTfKuN14wxRnMCg9RN9bovPNkT9/EbqhwI86TTqliVMylyYLMj+4okT+kJwAEVFLccB2O6usx0W0Eu/DMA4ACsSdZelp4eHUXzhvQSRP173UWsprAO3/zEPvulGAtGVdM3EoDvKlwcZrvO+gKQEfqMIRpYdK+rpmxwNov8cYlUuY9yKWmzYQw/aBhUBcb36ZUqIDg+MurdenCrOIvBgDjU9uWsosF+n6g0sWwOjgA==
*/