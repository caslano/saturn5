/*!
@file
Forward declares `boost::hana::append`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_APPEND_HPP
#define BOOST_HANA_FWD_APPEND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Append an element to a monadic structure.
    //! @ingroup group-MonadPlus
    //!
    //! Given an element `x` and a monadic structure `xs`, `append` returns a
    //! new monadic structure which is the result of lifting `x` into the
    //! monadic structure and then combining that (to the right) with `xs`.
    //! In other words,
    //! @code
    //!     append(xs, x) == concat(xs, lift<Xs>(x))
    //! @endcode
    //! where `Xs` is the tag of `xs`. For sequences, this has the intuitive
    //! behavior of simply appending an element to the end of the sequence,
    //! hence the name.
    //!
    //! > #### Rationale for not calling this `push_back`
    //! > See the rationale for using `prepend` instead of `push_front`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathtt{append} : M(T) \times T \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure that will be combined to the left of the element.
    //!
    //! @param x
    //! An element to combine to the right of the monadic structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/append.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto append = [](auto&& xs, auto&& x) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct append_impl : append_impl<M, when<true>> { };

    struct append_t {
        template <typename Xs, typename X>
        constexpr auto operator()(Xs&& xs, X&& x) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr append_t append{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_APPEND_HPP

/* append.hpp
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
*/