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
zGw6kjgG8snyUhmqH3SUl8di4DIdewrOstdmtFCmnQI/BY4h1w/aiGxaKaSg4LZkNVNxR6R//GCq9e3Rvba12i8lb1TD5c2tsB7JsGgS0bSuE0WI5p/rufW47ikK0yUjnfNL3/XXUHF+OwnXsNFn5/Nzl/3KWaW8QfGLJ+it5VgheH8HWV/Tg/4IepDd3iVwgOYHLhN+FyR7ADsYq0pjWtgJZ++NaZVHXU30nwdO7XdWlaSh4jvSQU1KLjwdjGg3XKaNahrcOluLq0URLW8UzDkosuWMLKCyoZoWGE8zZtDECISxHdcCSHaVXimmzk/AS9hsGLxuEtC9eTY/hnvtzw15Llbors/pSazv0RZJDvLWNBld7+gtxroLBetzTZ/qpIzWrLed8dW27mcl88Z6C3fsj/3yapLCoI6X60vMoirfOKyd2DgzH2SWSv419DS+uqRVM4eOy4Cy31Ju2cQwufTQ2Py6Ub/MS76VfrJz3dLslD8ztJNpLDD6AbW9bnEIKDSwY4qSmwXU1OH1YdYjzBrXtL84XDJcXWOgm7G/0KtrjtVrdTwjWF1jQeXrbPboXzLMOZMQWQ4rYp6LVncut1/oCCS9rnux9eg10hm/4FWKYQM5WNK3a/qq9siza/Q4IEBsicRquQIqM+RbfXP1AMrVRkrVWuNaY8Xjj+x/GmWkZP++VOs5Srl0G3tsuPRa/3HS/94eE6PLLmrU
*/