/*!
@file
Forward declares `boost::hana::zip_shortest`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZIP_SHORTEST_HPP
#define BOOST_HANA_FWD_ZIP_SHORTEST_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Zip one sequence or more.
    //! @ingroup group-Sequence
    //!
    //! Given `n` sequences `s1, ..., sn`, `zip_shortest` produces a sequence
    //! whose `i`-th element is a tuple of `(s1[i], ..., sn[i])`, where `sk[i]`
    //! denotes the `i`-th element of the `k`-th sequence. In other words,
    //! `zip_shortest` produces a sequence of the form
    //! @code
    //!     [
    //!         make_tuple(s1[0], ..., sn[0]),
    //!         make_tuple(s1[1], ..., sn[1]),
    //!         ...
    //!         make_tuple(s1[M], ..., sn[M])
    //!     ]
    //! @endcode
    //! where `M` is the length of the shortest sequence. Hence, the returned
    //! sequence stops when the shortest input sequence is exhausted. If you
    //! know that all the sequences you are about to zip have the same length,
    //! you should use `zip` instead, since it can be more optimized. Also
    //! note that it is an error to provide no sequence at all, i.e.
    //! `zip_shortest` expects at least one sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zip_shortest.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto zip_shortest = [](auto&& x1, ..., auto&& xn) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct zip_shortest_impl : zip_shortest_impl<S, when<true>> { };

    struct zip_shortest_t {
        template <typename Xs, typename ...Ys>
        constexpr auto operator()(Xs&& xs, Ys&& ...ys) const;
    };

    constexpr zip_shortest_t zip_shortest{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ZIP_SHORTEST_HPP

/* zip_shortest.hpp
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
*/