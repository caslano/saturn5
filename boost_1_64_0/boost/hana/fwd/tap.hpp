/*!
@file
Forward declares `boost::hana::tap`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TAP_HPP
#define BOOST_HANA_FWD_TAP_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Tap inside a monadic chain.
    //! @ingroup group-Monad
    //!
    //! Given a function `f`, `tap<M>` returns a new function which performs
    //! `f` on its argument and then returns the argument lifted in the `M`
    //! `Monad`. Combined with the property that `chain(m, lift<M>) == m`,
    //! this provides a way of executing an action inside a monadic chain
    //! without influencing its overall result. This is useful to e.g. insert
    //! debug statements or perform actions that are not tied to the chain but
    //! that need to be executed inside of it.
    //!
    //! @note
    //! Since C++ is not a pure language, it is possible to perform side
    //! effects inside the `f` function. Actually, side effects are the
    //! only reason why one might want to use `tap`. However, one should
    //! not rely on the side effects being done in any specific order.
    //!
    //!
    //! @tparam M
    //! The tag (a `Monad`) of the monads in the tapped monadic chain.
    //!
    //! @param f
    //! A function to be executed inside a monadic chain. It will be called
    //! as `f(x)`, where `x` is a value inside the previous monad in the
    //! chain. The result of `f` is always discarded.
    //!
    //!
    //! Example
    //! -------
    //! @include example/tap.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto tap = [](auto&& f) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct tap_impl : tap_impl<M, when<true>> { };

    template <typename M>
    struct tap_t {
        template <typename F>
        constexpr auto operator()(F&& f) const;
    };

    template <typename M>
    constexpr tap_t<M> tap{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TAP_HPP

/* tap.hpp
5/A5njx0PZaN35HKW0cD7g/yJoKDVBXJRB5lfvXjRiFPDtE1MdVWF4PEzyeXBYEnInBFgFx7HmXamAW6L1EDHOvtP6hYVGE58RENsgq+FlphhAxzyG6E5I5WF2qUHW3hTdzRZF0sTbQPB79JJnysD9Me8qfkCU5tb3uVieUzQ8taO5r2aSfn4HUt39sh8VPQE98oO68vtPTizASI5zaSwePbJ5tCm+iMrWxIX3ru1vYyU+hFExPNU9RDxloBjmGrQoS/F76e2v9uVRrIFVj8EGrmETEGQgJWcCdEaHlbJvxGKL9jFEIc4Se1Zp25WyUPcg0AN76nhW40GdXNL2uBxjMNGmncac+0TzItWmAqpvryrQ39SkVoL8ZEdttKOh5hRX7wEr8BTs0J92lP+55ZMLT9KlNb6dg4Ir/bS5sVurSAsJM42USqPx+Q6sSkVIeFbkqk2jsZQqaDE36eb57o16ZPTUMuco2gx/SSIo+Wj+UGBV3VU9PYl0N/SARRVXA62HIYFTdG5e18vOjRq6TlPIh5yBp+04maOZqmTbBASqlNsEbLrdoEW7QcVv1cxFtpE1zRcpc2wR0td/eduCClsD7iKDwrYmN/B/vjpXi8ywcfT7Tco03wRsu92PnTPTg6DRShrgQNJ4OGULeCq8XxgPk5uKkff3r82L+VdGdIXPBA8v3TnFR5X7QQ37pQK4iO0t5rxFy1AuWFjk/l4jBD/SNZ9Ut/b/Q+bSGngeseeSvougfl0YmV7os0t4SWUK3En5dWU/WFIzQCQfrGhlZLXOg5+kZJje557P346mR8I1oeprnPVFHOOJgGr6Kh77J2ROnGH5214NC3hi+uDq+Oj4ggrp4EwhUH+ST4ebZm7KVIHNitRTjCjoMiOAb6aF0obBHyoFNmFHjCg7LA/677LSsr7QPOT5NN8YTjvGPJ78GghAFDS8sTpknxEUsXj8ZLZdLeqb0iNohMyc9LfVA6K6UVaIGpFQy8/bGO8d2RjJLi8Zuu2KlvIGIHTe29z60cyO+8PAi2/2Yg/M0/D4B5vxtOSSL/mu4PQb5+32AO+G62PZfbUZu7E/3sdGZ51Xx5g+wte5bovUWq0BeYUdwJFojRC2Y4mpwFM1xN9oIZnkhGn7VggjViwRRRZJ7gBDKSQcghhDTByw0oMlRBXsynASOz7/f9JBiqAVikLzOff0BfZqJyJveGgolpTFFWryjTtfu14yf/bLSjwBf56iW3L8eadkl06G0r8G0rS20vS2UZeSD+rDbDgnRb1qS2XOfA3NRyHV4lHdpyHfHqXZYv1fe5NH4/fTjsIgSCFNyG4MCM82vnO7S3tWqITX0xeoyibvz62dNZ38r8bG4H2eTTDvg2RTIvWbTAjkdYMubuOyuSXlQ+ftUVu2h1ZqHiXt/uYACuLPMaPH5J9ALINr/VfrVJltbRZcmq17qQlx9Z+WLj18+5XTvfRRm79YwdyPeiAVkO+yQydPmRBWd4Z/xKr0a3A6/0tFu+pKJN8CKCuWsqwqdoXf/mGxUf7lfNQ1N7BT3HE9posFwzQ22y55x2h+o5YFNCW4wAWeKUBxJbsFNDLxmYYhUVQvwEi7Ng6MPollj5mobkl+FBqcKzmpxwNNlzN7R0pWqvRM+R95MXnGB/LNbSX2+/4Xf6qeodfKo6GZ+W/Sb7fBikR51Gp1p9nQ+nwl2GZRbRr3b1XTN/A9bhLvb1dbZPMdFi/G50qqtvKlgzXyeiNw0HyAEY7dbe7ZtgKncDgKsAnaYTaQxBvD56OCFLvm/ioojpiNhdzmbrKBgi9R0XnYrF2ttnKmt9wj5/AniKljkWjJDuNArVMscGCwbd5VYJuBlwScDLgIc=
*/