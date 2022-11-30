/*!
@file
Forward declares `boost::hana::remove_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REMOVE_IF_HPP
#define BOOST_HANA_FWD_REMOVE_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Remove all the elements of a monadic structure that satisfy some
    //! predicate.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a unary predicate, `remove_if`
    //! returns a new monadic structure equal to `xs` without all its elements
    //! that satisfy the predicate. This is equivalent to `filter` with a
    //! negated predicate, i.e.
    //! @code
    //!     remove_if(xs, predicate) == filter(xs, negated predicated)
    //! @endcode
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M` and a predicate of type \f$ T \to Bool \f$ for
    //! some compile-time Logical `Bool`, the signature is
    //! \f$
    //!     \mathrm{remove\_if} : M(T) \times (T \to Bool) \to M(T)
    //! \f$
    //!
    //! @param xs
    //! A monadic structure to remove some elements from.
    //!
    //! @param predicate
    //! A unary predicate called as `predicate(x)`, where `x` is an element
    //! of the structure, and returning whether `x` should be removed from
    //! the structure. In the current version of the library, `predicate`
    //! must return a compile-time Logical.
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto remove_if = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct remove_if_impl : remove_if_impl<M, when<true>> { };

    struct remove_if_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr remove_if_t remove_if{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_REMOVE_IF_HPP

/* remove_if.hpp
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
*/