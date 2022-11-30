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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr zip_shortest_t zip_shortest{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_ZIP_SHORTEST_HPP

/* zip_shortest.hpp
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
*/