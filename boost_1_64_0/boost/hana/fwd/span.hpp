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
NNmIzcyGeqR+s5pXyXKsPzBM78s+PjWgZhJbOfnyKS98jRYkFqAiQC1Ieux+oSc6Gq71MpoCsPr8sKZAbfWEfpuMvpUr+vaHNONPAcoJipHMeNnngu1tOn+2WT39aNLpyYlFfRkZXcuW8qlISbqxZ1mTbg+VIQ5O4IY9KdnaVRgdm7qkd6glPDFA+JHY3yUzXd6oGQ1Nzi8jTEIEBERr5o7L8iqIKVtLcs9GG0rk01myTPHjZvWvo/5et2+ZJ9hgUQL+xKDcLw1xYb0bEP/+dJqBNuuuB37PsKbg+jB8xGaDt+65vnYx9hT2X8yfg+Df2nZFQXr3WN0ei0YyMukETcqZxZcbhvrp6GDd5tNucN4XQwKQnDS2sjKpgXILxQiw3Q2+PH8gbBWNYD6QiXgRknDqXuNH0tMhxvDTK0byM1N8GE85tjQ+JcWk9lSKyRF2TuEWBn56RNsIpKzXU2J5wGu7krNa25wSn/mFyc/5CHqIqrA8TFFvdMeMCHBIjydm7HF/sx1JSBGUAoKJmRDgkB4ve1zS44iZegTxuwunD6FRO1XciXXH98nXJV0E8OW1rAGn1RnejjRYjT14uK2jqQPhcYyZ8DQxY1iHcfil4TwZXBC+Dd073Z20bGz25VKfEA9dQsZ3dIzSVeHJndMeHYgxqVBD9512VlXRhx2QP56hQc52dDGiCU/Mlw7N92VBcW2LPl2lhafLfK9qDcWWFbbaxfE321BmoeorJMkE1phmJlrkwMkDevJxqp6nTlhNqfoIOILjaGobKWmQTLTCH5Of+rgGVw/UzHs/nyMX1G9WqRvOmWJO/+P+o/q8tBz3i1+75Hp8Y2ua6nNFNiUwxRdtLKWu8BUZBQZAqkh6gqervSYbHNjqEqSUaAJyHX6x7TKJsGVuEk4irB/1kd/roZ6qMxqqliUNIGHpSOZtFsqFzhsg1WVNKtgYaxVL2GSJlXrednzikSV6RYkeilMaKMQhrtdCKh30XVD8yMl+1lb0RllB9K73io7+8BUIqLqOZ30wmunpWU1RoosnesBnT8PWXSY2UHDB2+wrZIaeCasj1Rlx2Wn8hWV15wnAvC7eZm469fiTfiWqkIS/YRrlURJpzC0NG2GAMEgThy6HGSvYdIy/FqPz24095hcIjwwdJdL3ir9e3mFJP5nGqfA1HOV0mZz9rU7XjS5nf59LnZIRm5GRGMPiIiSmLQ7VFuofYYWTB8RSC8eEr4efh4UadKo9Tu5UvbH17TS/QNZ7JecG1dFlyD7s1cpycVkezvQ0+Grq4kcrd413NHX127v53d38nm5+Szd/Bvw9j78wKNPx/behHfjOoWkjPIijiDeLzfCInw7tjuBLtUoPMUsEp+sIvhsIXtLvbBDcQe/pPdJ7MFygA+EWmUOT2zIwIxTqpS1Gaal6aVVNPCKES/TmWWZi4M5KG9sZHoeE55Tx9jPEu88Q7zlDvOUM8RknxZ/N+EHxAXWhm/jEiUao7paPrHZFBMxGb0VybYigcWSiAe/OVX78j1m18JQTR6AVbnM4vzAOAdiou2qszRVZZodKKRMB9BlUjFpiDq9zJcMtnTKH6tX5hTd4jLLrwVgC49wtjtlHMTPcXT44UWN1/tGXgXzbjGTOAojpbpeoL6MjmRuqzU4+dUZmZUzmz5mQ9cUKLjSnS6qcZKoQZRnKflrycIWG5L0/yibWYnMqZ9E06hDZBDM+D2TF+qs++Ggi2TmCP/HwVOHtUoo3WYp2BMua8PU214NwN8N9Du63cHvhBFwbXD9g93K46XCz4arH2t7z/ZU07j4x/2m6ObbMOTTfUO8Zf2nN4Np91QPqZxnH32Ks6RdpNEXiptp9Nf9QGls=
*/