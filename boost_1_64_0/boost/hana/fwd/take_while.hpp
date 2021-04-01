/*!
@file
Forward declares `boost::hana::take_while`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TAKE_WHILE_HPP
#define BOOST_HANA_FWD_TAKE_WHILE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Take elements from a sequence while the `predicate` is satisfied.
    //! @ingroup group-Sequence
    //!
    //! Specifically, `take_while` returns a new sequence containing the
    //! longest prefix of `xs` in which all the elements satisfy the given
    //! predicate.
    //!
    //!
    //! @param xs
    //! The sequence to take elements from.
    //!
    //! @param predicate
    //! A function called as `predicate(x)`, where `x` is an element of the
    //! sequence, and returning a `Logical` representing whether `x` should be
    //! included in the resulting sequence. In the current version of the
    //! library, `predicate` has to return a `Constant Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_while.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto take_while = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct take_while_impl : take_while_impl<S, when<true>> { };

    struct take_while_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr take_while_t take_while{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TAKE_WHILE_HPP

/* take_while.hpp
8wx5gKHR8oKDHma8JGDnpLD8JGdgJ1SI4T59nKb+gKcGh/GBir0ZJIZ42N/4F21DvnyF9dQe1yH2Fj1aJaAIFKU6RbHtD4J6FjjK91vDoE+FSQeH877Q/YE0rN9YJ6WA5p+UMZBBqClmJ8tPltQiP/CDK2q7Oyrnegkal+7vqYOwgNFBi21zVjM8tJutGRPXMndW01mH2bBN76opEQ7iUVRgSkJoCVoVI0oyBC2pQUlMKru+ik2wmSlLnRW/OKNXzrf5qcH3S0Ii4oaOnNo3FMLj5SvvXjBVqu7tUcvK+fJ3H42s5Gl0jglxEg/757WaQQBQkSkUgN3OCN6tYAuz3SJsoe1rdLE/FHPRhoahQWL4KfKMo5jCwe77MRDrBsZxbL3XQXCeR+9p6L61l69tGbkG/eSucLuz9Fx7yYQnrIQTC3xa3lwYC6VnPh702Mr88Sf0o6jk3NnEq5FZ91smjLBcuC7f9cR4r9WPoO8Fw2Fq5kyU5GyiWy1bHhXVLMZ1DkfIaCkXlhA46ZIPS9S/+jZxbWEuDJtsXuoMH0K5Om20JVrkavFzeg0NAg==
*/