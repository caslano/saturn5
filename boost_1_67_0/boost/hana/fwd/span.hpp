/*!
@file
Forward declares `boost::hana::span`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SPAN_HPP
#define BOOST_HANA_FWD_SPAN_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Product` containing the longest prefix of a sequence
    //! satisfying a predicate, and the rest of the sequence.
    //! @ingroup group-Sequence
    //!
    //! The first component of the returned `Product` is a sequence for which
    //! all elements satisfy the given predicate. The second component of the
    //! returned `Product` is a sequence containing the remainder of the
    //! argument. Both or either sequences may be empty, depending on the
    //! input argument. More specifically,
    //! @code
    //!     span(xs, predicate) == make_pair(take_while(xs, predicate),
    //!                                      drop_while(xs, predicate))
    //! @endcode
    //! except that `make_pair` may be an arbitrary `Product`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Sequence` `S(T)`, a `Logical` `Bool` and a predicate
    //! \f$ T \to Bool \f$, `span` has the following signature:
    //! \f[
    //!     \mathtt{span} : S(T) \times (T \to Bool) \to S(T) \times S(T)
    //! \f]
    //!
    //! @param xs
    //! The sequence to break into two parts.
    //!
    //! @param predicate
    //! A function called as `predicate(x)`, where `x` is an element of the
    //! sequence, and returning a `Logical. In the current implementation of
    //! the library, `predicate` has to return a compile-time `Logical`.
    //!
    //!
    //! Syntactic sugar (`span.by`)
    //! ---------------------------
    //! `span` can be called in an alternate way, which provides a nice syntax
    //! in some cases where the predicate is short:
    //! @code
    //!     span.by(predicate, xs) == span(xs, predicate)
    //!     span.by(predicate) == span(-, predicate)
    //! @endcode
    //!
    //! where `span(-, predicate)` denotes the partial application of
    //! `span` to `predicate`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/span.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto span = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct span_impl : span_impl<S, when<true>> { };

    struct span_t : detail::nested_by<span_t> {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr span_t span{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SPAN_HPP

/* span.hpp
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
*/