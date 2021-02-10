/*!
@file
Forward declares `boost::hana::insert_range`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INSERT_RANGE_HPP
#define BOOST_HANA_FWD_INSERT_RANGE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Insert several values at a given index in a sequence.
    //! @ingroup group-Sequence
    //!
    //! Given a sequence, an index and any `Foldable` containing elements to
    //! insert, `insert_range` inserts the elements in the `Foldable` at the
    //! given index of the sequence.
    //!
    //! @param xs
    //! The sequence in which values should be inserted.
    //!
    //! @param n
    //! The index at which elements should be inserted. This must be a
    //! non-negative `Constant` of an integral type, and it must also be
    //! true that `n < length(xs)` if `xs` is a finite sequence.
    //!
    //! @param elements
    //! A `Foldable` containing elements to insert in the sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/insert_range.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto insert_range = [](auto&& xs, auto&& n, auto&& elements) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct insert_range_impl : insert_range_impl<S, when<true>> { };

    struct insert_range_t {
        template <typename Xs, typename N, typename Elements>
        constexpr auto operator()(Xs&& xs, N&& n, Elements&& elements) const;
    };

    constexpr insert_range_t insert_range{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INSERT_RANGE_HPP

/* insert_range.hpp
7eMDJgU0ydfFTmAPTlA+Uu9SfPLChTRc0v5A+6inVoew5AsUMbv/IGCX6VVG/4zeDtLdRwbkn+z2k1aNAUAD3C4iAnKnymDXvjmu1SguJZTOomTmj3FUn2i0BhCb++Kzz1k3DywNShcmMOp4dwxyNPExzxREZLKUZvpgRccUKjMkYLBIPgazGYqp0ooFmLSQRDGaZKqSgG1eRBNJEu5Ugb812VCOPIrYSEUtOgLTiKFPpH1ObT16RERTfReCy+ds0CPS7rog84EMOZClpZooHBxY3CnM8+wsxRjRMjCWpbD6Y9HGe3cGA7UE1ECEXWroltjXany9CNLMeGgpBdhaFtCWKQOYyaeSphYjCSPfvzOS4COUvOPjFn1O3PQh8CcENQHkdzriPIBxEhOQlgbpJlWj1MDz5+IJJsXLdQAoJfndaJzXFOUkfqsSC3FUNh6FPXNN3KQryFyOqcBEOZLIZvTzg4075S0NfG8+viIFi3BMZ7Xy0JpgMgmMNf4JtK+OeIQx+kSUZCIPggcJzv5ShttwRqCGHAZwBKDOkKJtFBJj+TzWVkKowU/L44sDOYyW1Ipn2GPwtKrxDOigsmEHIp41XkaLKdTH348f17SiYyJ0OqtmBWDoglZw7JE50nE8hcHNpyKpf5PqMjkF
*/