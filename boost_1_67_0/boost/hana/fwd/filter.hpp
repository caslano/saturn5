/*!
@file
Forward declares `boost::hana::filter`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FILTER_HPP
#define BOOST_HANA_FWD_FILTER_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Filter a monadic structure using a custom predicate.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure and a predicate, `filter` returns a new
    //! monadic structure containing only those elements that satisfy the
    //! predicate. This is a generalization of the usual `filter` function
    //! for sequences; it works for any MonadPlus. Intuitively, `filter` is
    //! somewhat equivalent to:
    //! @code
    //!     filter(xs, pred) == flatten(transform(xs, [](auto x) {
    //!         return pred(x) ? lift<Xs>(x) : empty<Xs>();
    //!     })
    //! @endcode
    //! In other words, we basically turn a monadic structure containing
    //! `[x1, ..., xn]` into a monadic structure containing
    //! @code
    //!     [
    //!         pred(x1) ? [x1] : [],
    //!         pred(x2) ? [x2] : [],
    //!         ...
    //!         pred(xn) ? [xn] : []
    //!     ]
    //! @endcode
    //! and we then `flatten` that.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `MonadPlus` `M` and an `IntegralConstant` `Bool` holding a
    //! value of type `bool`, the signature is
    //! @f$ \mathtt{filter} : M(T) \times (T \to \mathtt{Bool}) \to M(T) @f$.
    //!
    //! @param xs
    //! The monadic structure to filter.
    //!
    //! @param pred
    //! A function called as `pred(x)` for each element `x` in the monadic
    //! structure and returning whether that element should be __kept__ in
    //! the resulting structure. In the current version of the library, the
    //! predicate has to return an `IntegralConstant` holding a value
    //! convertible to a `bool`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/filter.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto filter = [](auto&& xs, auto&& pred) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct filter_impl : filter_impl<M, when<true>> { };

    struct filter_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr filter_t filter{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FILTER_HPP

/* filter.hpp
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
*/