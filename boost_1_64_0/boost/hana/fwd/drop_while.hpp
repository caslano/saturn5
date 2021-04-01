/*!
@file
Forward declares `boost::hana::drop_while`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DROP_WHILE_HPP
#define BOOST_HANA_FWD_DROP_WHILE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Drop elements from an iterable up to, but excluding, the first
    //! element for which the `predicate` is not satisfied.
    //! @ingroup group-Iterable
    //!
    //! Specifically, `drop_while` returns an iterable containing all the
    //! elements of the original iterable except for those in the range
    //! delimited by [`head`, `e`), where `head` is the first element and
    //! `e` is the first element for which the `predicate` is not satisfied.
    //! If the iterable is not finite, the `predicate` has to return a false-
    //! valued `Logical` at a finite index for this method to return.
    //!
    //!
    //! @param iterable
    //! The iterable from which elements are dropped.
    //!
    //! @param predicate
    //! A function called as `predicate(x)`, where `x` is an element of the
    //! structure, and returning a `Logical` representing whether `x` should
    //! be dropped from the structure. In the current version of the library,
    //! `predicate` should return a compile-time `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/drop_while.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto drop_while = [](auto&& iterable, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct drop_while_impl : drop_while_impl<It, when<true>> { };

    struct drop_while_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr drop_while_t drop_while{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWDDROP_WHILE_HPP

/* drop_while.hpp
E0Dl7eNkBB5fofnO6PRjzjGCFzZnil5D4rrLF3c3UxIbWy1Fcjjk1LwZDAiFuj4nCKJ4Ety0cuJQIxz8QhX0bFJckb1WDSfwN06CXD/RBSzxEoJURvlItF48vywKYFZMPzFzt1N1UOBm1ai5zHkRbJHosMwsq65DTIRNYBtpl52nDLpastMtB5y+7wY+6Ff4W4WCWax27G/i0oNIB9OAUK4mT7m2caMwTYTHmFqq6u5YB6SxbMgaWfbWCGdG5wV4KZU89CFGl/z1rL0Do6Xlp7NgOJc0devVNN/Ju5YAgSkOWz518vAphWzEh9HEJC2gYxmBX3BZWQm29O9fSBpW+jZQJhguDfJUvxu8TKygZoOxrjdIs88uDNZEAtZ0sQSYGoXZ+uILzSzVykpGUNxGLH5U7sp1+0jyat2huAgaDeAv01UHuvEXo6VeJ4rq+jQNUQA0G0PAYWZALz1+BZ9o0dSLSrta3rQ+Rijr7aZ9p4LnrW8mZ4hokjfAvyAJ8x32BaNdUtqZec1RECmSnuQLbb8lspmqehbvSbjzAAuszuaz2YaU8/yQ1TNrqQ==
*/