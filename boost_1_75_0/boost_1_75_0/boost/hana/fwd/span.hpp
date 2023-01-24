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
/02dWX8H0f/jOLP+4aL/ezqz/hFG/8fNTN3zsSCHcObIM+sf37EgEzmz98z6CfG/a8J/MHWn58ywZ46taWQ39T0ewt0uUtm7O/vAg0EcsTnb6dub/Zg2oh96LMh6jcE3sBH90GNBNHF4BP0+/vMUDjwWRHfF3jD6ffxsfOixIJbYLE6/j5+NDz0WxBD6iX4fPxsfeiyIKhQU/T5+Nj7wWBDLEQqKfh8/Gx96LIjcvEq/fe6Io+oepSV6Ehaaa+um55rHnY04xkS+ZhuOrnuOZ4/KWDQ2WY3dJvFgkdM3uVjh7vLCj3CxQjd8U3PD39BihR7O7Dlf919nsUJ/smJjLv/h0xV9vHkHyYpvd2b34GTFoz9fd0KyQlct09boAJSeZIVmmCYdc+qo3ZQ/xEsegJ5HcWxYN+SP8VCLY38n5gEhf9ANld1wfzMnWUzZULlh1B75mRXHx8bOac5//Q2VTfAf7GiKPeDf4YbKFvj3fS7FUBTc0YbKFuz3fSjFUNjvaENlBfvEEyngPjmeAx3Zt6HSsj1bd1XDfDCh6fOdNk/92UwxBdv+5V1O6Qz3iL6fkDBrrmDaf2L9/ZzYNQWOMXNOTYt0J6ELfJXv6J8uQPQjnql/Dyf0ckDMwwDZPzF2t3zFE1EcEOtAQO704P8jW/uYC/cDTN4NhuPA6Yz9Xya4pw93Tp6p6J9d3DCmmmqrqmq4zle8/z1/ml2z
*/