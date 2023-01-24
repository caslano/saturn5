/*!
@file
Forward declares `boost::hana::chain`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CHAIN_HPP
#define BOOST_HANA_FWD_CHAIN_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Feed a monadic value into a monadic computation.
    //! @ingroup group-Monad
    //!
    //! Given a monadic value and a monadic function, `chain` feeds the
    //! monadic value into the function, thus performing some Monad-specific
    //! effects, and returns the result. An implementation of `chain` must
    //! satisfy
    //! @code
    //!     chain(xs, f) == flatten(transform(xs, f))
    //! @endcode
    //!
    //!
    //! Signature
    //! ---------
    //! For a monad `M`, given a monadic value of type `M(A)` and a monadic
    //! function @f$ f : A \to M(B) @f$, `chain` has the signature
    //! @f$
    //!     \mathtt{chain} : M(A) \times (A \to M(B)) \to M(B)
    //! @f$.
    //!
    //! @param xs
    //! A monadic value to be fed to the function `f`.
    //!
    //! @param f
    //! A function taking a normal value in the `xs` structure, and returning
    //! a monadic value. This function is called as  `f(x)`, where `x` is an
    //! element of the structure `xs`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/chain.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto chain = [](auto&& xs, auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct chain_impl : chain_impl<M, when<true>> { };

    struct chain_t {
        template <typename Xs, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, F&& f) const;
    };

    constexpr chain_t chain{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CHAIN_HPP

/* chain.hpp
8J2RAcN3oRlobu+4Ptjlq4CpgJ//Bluhmd+/H385v3c/yf96u4xrbdqFhzbamabRlEcD95HCVlxT+sV7WyFzMbMVO/oGhxZDhfoXM5eu2JGvC1pDUUOoygCBwX+ibvngaKgOJOXgW1C3efDn9TVPxy3CKd+Rzbu9mSC1/trDPb/BfcDNWIfP94k6fbpPcIgfrZ7AArhBOabI+e3VTvR+/ZI4pmA1/EEzXkwaXzlZD6hb0xXUDwjU70HU5VaB8oNUzAn+431J1E/Q4QOk5zD/afCqZzVph54g9P/13sP/Z/TfQIy669FHWzOdsPs60XUElDBCT8S9h2qFujOPUyo6/3bh97dQMf8K/xiE0Po/5GwECNnkJR0HN//2myQhQfzv/Z906N3EX6gnMlKvehreW1CjFxEl+ID4o/R7gGd8I+hbp9D35G+uRt8zLyfom24S9H0c6fsWfDB0FcXFKjV4gO+skxUvUw3EaeT/4smYaNmOOvwFzOrEanN3I6IOA6ZguAa+QNDkUeZs+n9nOOZsZof+b3lGkO2KD5TqLakT1c2n3wZ+Eqofu13pBNbwXTK1pguzOCBJy22ke1fHX/rPq62AJv6eCHhARnX3Lg07SJ2BP85Fi/BakCzfSkPKjq08iJQtMJLMBaV/gOxh76B9+NtPifR/rRUV/UOtYF1BQk4kTNddSsL/HdOymhQSuhH972tUfjS48LuoTji8
*/