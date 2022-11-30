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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr remove_t remove{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_REMOVE_HPP

/* remove.hpp
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
*/