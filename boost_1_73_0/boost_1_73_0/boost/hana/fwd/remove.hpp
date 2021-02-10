/*!
@file
Forward declares `boost::hana::remove`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REMOVE_HPP
#define BOOST_HANA_FWD_REMOVE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Remove all the elements of a monadic structure that are equal to some
    //! value.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a `value`, `remove` returns a new
    //! monadic structure equal to `xs` without all its elements that are
    //! equal to the given `value`. `remove` is equivalent to `remove_if`
    //! with the `equal.to(value)` predicate, i.e.
    //! @code
    //!     remove(xs, value) == remove_if(xs, equal.to(value))
    //! @endcode
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M` and a value of type `T`, the signature is
    //! \f$
    //!     \mathrm{remove} : M(T) \times T \to M(T)
    //! \f$
    //!
    //! @param xs
    //! A monadic structure to remove some elements from.
    //!
    //! @param value
    //! A value that is compared to every element `x` of the structure.
    //! Elements of the structure that are equal to that value are removed
    //! from the structure. This requires every element to be Comparable
    //! with `value`. Furthermore, in the current version of the library,
    //! comparing `value` with any element of the structure must yield a
    //! compile-time Logical.
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto remove = [](auto&& xs, auto&& value) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct remove_impl : remove_impl<M, when<true>> { };

    struct remove_t {
        template <typename Xs, typename Value>
        constexpr auto operator()(Xs&& xs, Value&& value) const;
    };

    constexpr remove_t remove{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REMOVE_HPP

/* remove.hpp
u/ChgHXtB3ZI4fQWZm21wkiGynB6hUUEZCdEiQy5R5H1qmWUdaIw1ZJh1I5N53pViqumiO+5dkCbUPKrZWmOKS2lFqYV6KRJkNEDZatJCnfK8O99Csm63Nr/GAdjqVdtfHW51U7epGIFsDJNEPR1KalPTsvLNqIMvKJfBSwjRT7LOU0qWvBzedLBK0+M3ksjJkby6Kx/IR9vwn50f9tcRI/j9kyG0cnZRvwkEovLyLyxEwD1RO4ANaEILY3Qlsf5njytARyH2z1xzVCBzfFCZUknWSH9bhuHvImjm3Z4Lg3bsg3gjFHXbW8dNJtPAcKBhCAeHjabzctYF24d5s/X8c1bn1Mh3LFkdy0gPH4XA4kph2OBFsGXtnoqmqQ5XIp6/igRCYrm1/x4Mzk+GJY8n3NbeM9KhFkvn1IAn1nO9QYK5TyH0ZJ6ufE4S93dyjxhEsF7cWtKp6DLWC78lqNg48hOJNYyVHJmyspYgtg35t7cgwRsW34zTnuDiyY767431Ls1uXoVb+sNEoPrbSKfU1XJ61X5XASG2qC3kN9jI0EFwBOHp9qhOyvl/Z1UWdzMKU4S2ezKsdTlmGC56igvy0QuYdeSD4pVjw9aaFIiu5Hl+IxyFAhDw5SbYUvVMt6rr0vxZfl6s4Cds9ht
*/