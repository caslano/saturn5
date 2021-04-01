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
48nIK5imjl1oTNFxCYkWoUCqe5f3GnGIIthg+KiDvIf4s6MWpYV7qujpVzHEuWhxp761pzQBzE/qwXhRXveQtGCNg+EL/bNU1xvYA40gX1HezyxJWXKB1XchnOIKS7iOP169PqOrsAeiBD/dK5gHm8hYNraG3yQSO63LCtF9cZOU1XLqQEIh9RcuH/GVQDkjNyx5Fcn5nq3ct2Kr7g5ZoGGo9XVh1mIz+3DbXN/SFqqgfwYuvTd6MESYGk5FKGzM5/pH2B74OYxbkTtIIJ1uX8TI/O3MA5wbSfNVVs++aMMff7p+CYeUwfBvuE9nWsKfK/b4ug0ZyiP5XGCkvOXKFL/QXmOc8+QUN5MVFueyguKswZxFmVKxaPijlAdxuVZ1tAFtVa0WLBw4FA0/am/JGG5+1rw7iQRSy6ciwyKLSx/G9TtnRzEPFMrJZYiesSIfPW2SFxeoDe19Y4LKWfV/77NzxqeXOqOEImEF9zGgNJVJYybaWavsYBM7UJ96QSQFiUz6qP4RfWjLnz+JZL3okGKrLnDk6sQ+gBDR+ES9PuTRRbr9srBtD34Psg==
*/