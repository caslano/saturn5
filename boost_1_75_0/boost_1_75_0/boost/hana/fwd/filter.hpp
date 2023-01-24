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
EL73sR/1BkJ9ishJZairyHQvugn1ccrWsiyz7ZoejWZ+okdL1OQgaP4/9mtoHKE+TlrWronqNxmSU5Rd15Rd5m6p8VWcVN9Hfnx/IVcUTrayYzeXXHxLMh6oRssvqWVVG7R8hrUM80bRWCNDvb1YGuLtysY+TmO3YxweoWybHo10Xg1vJK6OZYkc7wlXSzqnc74nNtI5kka3Ep2d2eh13rfCW9J5Gi37UUtFe7T8rbxx2l5sGm5ueCOVM1iWUTmRZel3ct4Elt1E2RiWpXXYa3ARR/R7Mm8Uy66lbF+WXUfZ7q2wsYqLe82Hfs14Ermi5DAQ90B5o1iO5/n8Yqm8o6UOiHP24Id+WcQQEmsHIAluQvLaHZStpKznjka28u9oZNZ9R6MI5uS1JLWCj/LLFj+p328hUkmOr5WJq0NL4piNf9jY5x3qc4RsfE4ZX3HuvIP3vdSd+6m6XHYyrfe37tz2q3P5alCV29Ln7ALG8Y24HyTc6V2AWy7SU9K9dRvv29jnDuqTT5L6vpSPl92d++C1rfQtIv7/1cj/v8jSQoj/Uu6vxog0D+7OeUtk6Wlvr1ZwkVz+/i//jD1DuFyEa5yIK7g756H6kdZ97ZRGOsZRXwX5qTtKWfjwM2ZwUzfKZlL2FZZdRdkvWHYNZbd2a6lIqT+zKQ5qRF3/AZk0TfGukmu+AAqI5u+pMqkH8V/CadZ04/54cDdOe+Qj
*/