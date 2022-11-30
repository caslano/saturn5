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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr span_t span{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_SPAN_HPP

/* span.hpp
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
*/