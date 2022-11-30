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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr filter_t filter{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_FILTER_HPP

/* filter.hpp
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
*/