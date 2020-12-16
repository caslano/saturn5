/*!
@file
Forward declares `boost::hana::replicate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REPLICATE_HPP
#define BOOST_HANA_FWD_REPLICATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Create a monadic structure by combining a lifted value with itself
    //! `n` times.
    //! @ingroup group-MonadPlus
    //!
    //! Given a value `x`, a non-negative `IntegralConstant` `n` and the tag
    //! of a monadic structure `M`, `replicate` creates a new monadic structure
    //! which is the result of combining `x` with itself `n` times inside the
    //! monadic structure. In other words, `replicate` simply `lift`s `x` into
    //! the monadic structure, and then combines that with itself `n` times:
    //! @code
    //!     replicate<M>(x, n) == cycle(lift<M>(x), n)
    //! @endcode
    //!
    //! If `n` is zero, then the identity of the `concat` operation is returned.
    //! In the case of sequences, this corresponds to creating a new sequence
    //! holding `n` copies of `x`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given an `IntegralConstant` `C` and MonadPlus `M`, the signature is
    //! @f$ \mathtt{replicate}_M : T \times C \to M(T) @f$.
    //!
    //! @tparam M
    //! The tag of the returned monadic structure. It must be a
    //! model of the MonadPlus concept.
    //!
    //! @param x
    //! The value to lift into a monadic structure and then combine with
    //! itself.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of times to
    //! combine `lift<M>(x)` with itself. If `n == 0`, `replicate` returns
    //! `empty<M>()`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/replicate.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto replicate = [](auto&& x, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct replicate_impl : replicate_impl<M, when<true>> { };

    template <typename M>
    struct replicate_t {
        template <typename X, typename N>
        constexpr auto operator()(X&& x, N const& n) const;
    };

    template <typename M>
    constexpr replicate_t<M> replicate{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REPLICATE_HPP

/* replicate.hpp
ObNb14xATYfCDYLrC2eFe2eJ1fUa3KElZ6fDupA/7fxTMEngxbwGWq2Q0oYIq/ZVPpkb2IdNVNhMhMbkQ1usiLqIeKhRdqPCOpHt1olMJIksrYVUDZF4G9ol2xl9jhZ/Bfa4MNM949jd7ohzBN+nwIZ8oDdMMjN1eivW6a1Yp7diojdlZ9pGNLcbXp3qionqIs12ponstI3EiCtbiR68Qvkq6EESAlnRchurh6KwqjbK5vWZZPP6zJIeApaoLwWvFGXFk6JsIOgITvowouAcZ52f7GUBe6QdlwV9HzI0WsuhfPNzkUabskNJEMVPA7mHlhG5lyZuYlouwJNrJN/s2hs97kHAKx1J2vQk8i2tTdaM6gVqfxtQZPhjaAVR8RVSqnHtov14jqR6xWW94i2e6Awzoj2YSmdYODKFI6tQNY618UrCATurXG7tKWYulFa03NK4mIeQxzDpTd2mN/VGgJBDzc3tCCoBPXDL9yHcbGhzRp+lNvd1avOcDWR0zvcfPDYZ7T3B+dgiCxcJP7U3v1B78wuPL0dRjBsebu2jeOHWbsKZGNzaR3nZxRcuFT+QxIYyzZvD7R1Xyr3Z0ekGqn2RhpoiE9oV1Z9ujlZYOEI2OPX9Imu0whZZL5ubKoics51106nJAXrkBJr8V6iWhB+2i2USFzr8G3X46QWYIdCn2ri1gR6qBtOnW0JP3WSzJNT6+3ngymiYTgOX1/ysMsebF9lgo8q8EDlhWzwx4X00CoK6SdKrkZ8u7WnHM3rpTagGR3F1+MlR0dJEldbSnqVWVz84C9w791pdb8C1wh2A2wM3FyVUwE2HK4K7EW483Bi4kcsu/rj1fv3J+Xn5szyeZvH1FVLQEFCzg87adsSSNcE/5R1T6USmMPvFcEKNj96RNx1a77qHmbJMDR/RaMssicROD6YoHgd0OjPpdGZBJumgM2snOkuR42AnCsv7kt49XFSwHC5So2bZKSYbqUtMNSGFxm1PNUcnWziSYiankLFUdKqVWOF6i32M5ZKosSBqucRH4ZGXbVQG3WZGW7MRlFsVy9bkFFRxbAPnSYarjA9U7X4tffzn6n/nQlZ/4hfPtfqy7l5OYMVBpQR3ParvuGTMRqq8D7WPIpirJZEwugMJ50FYcwF+8n7E57a0d7sfcQ4R7SziBmchJBshoSC9NHzWhveFeM3Cszp+xEzVjRzPd973tpWv32Ge1MSDoc6D0oveSjdamFvlEVHnKNBUkl2gYqip9qDzLDU4a710E1+z83O3WukWj5UHsDpYcU/KTZFNbQUAb87vqbON2o68PHwaIPg9IoxRzQjJIqFvDKA2AGq850PCl+sXk+6DGU0xLQzMR5JMKaboZ2I0RU9PTGeOtAhPhlu+2bU3elQg4GBHkm16Eu0tbRtyV1A8si/3ZprfIpqjQiaikH+ikBkgJYzNVn66tKcdz2i/GXLYtvLTxU8t6hIgZr75rUhbRk0fdYu6t+VNFuzk16TRHKFubnmZL5nrWB8Xce548alNMgTTgwyZglw5ZDpeOGRGtNw7DZMeHjPRJbx6glKZYI63JN7qgf9mpRFL8ULQP8LIdoW+8OPDun0IL4YZAfxlkUa+XiKkNkJKaAYnFG8zYz9TiTnuV+M4iCkXZxvVl3tLMQvVz/cW11d7S+r2ybtg6rfUL/DeVD/HW1i/bseL9ejNOwT+e1J37zhIvvql3ikoun8UKZDKV9+kxW9D6j91Sf+P+g2d/Pt3vFy/vpP/6I6X6ps7+cWOV8gXXeAdGAUEgGJq/XpUpkiLb6vHNYr4hr9IFdGl3gFwU+qPAxJfFLWIohb48soovmzNQOopgHUqwUiiFfhvItEKnoV4wmY=
*/