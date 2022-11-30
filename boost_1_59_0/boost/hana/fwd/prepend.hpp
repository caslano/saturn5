/*!
@file
Forward declares `boost::hana::prepend`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PREPEND_HPP
#define BOOST_HANA_FWD_PREPEND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Prepend an element to a monadic structure.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and an element `x`, `prepend` returns
    //! a new monadic structure which is the result of lifting `x` into the
    //! monadic structure and then combining that (to the left) with `xs`.
    //! In other words,
    //! @code
    //!     prepend(xs, x) == concat(lift<Xs>(x), xs)
    //! @endcode
    //!
    //! For sequences, this has the intuitive behavior of simply prepending
    //! an element to the beginning of the sequence, hence the name.
    //!
    //! > #### Rationale for not calling this `push_front`
    //! > While `push_front` is the de-facto name used in the standard library,
    //! > it also strongly suggests mutation of the underlying sequence, which
    //! > is not the case here. The author also finds that `push_front`
    //! > suggests too strongly the sole interpretation of putting an
    //! > element to the front of a sequence, whereas `prepend` is slightly
    //! > more nuanced and bears its name better for e.g. `hana::optional`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathtt{prepend} : M(T) \times T \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure that will be combined to the right of the element.
    //!
    //! @param x
    //! An element to combine to the left of the monadic structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/prepend.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto prepend = [](auto&& xs, auto&& x) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct prepend_impl : prepend_impl<M, when<true>> { };

    struct prepend_t {
        template <typename Xs, typename X>
        constexpr auto operator()(Xs&& xs, X&& x) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr prepend_t prepend{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_PREPEND_HPP

/* prepend.hpp
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
*/