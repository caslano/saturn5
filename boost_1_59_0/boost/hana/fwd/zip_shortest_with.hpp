/*!
@file
Forward declares `boost::hana::zip_shortest_with`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZIP_SHORTEST_WITH_HPP
#define BOOST_HANA_FWD_ZIP_SHORTEST_WITH_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Zip one sequence or more with a given function.
    //! @ingroup group-Sequence
    //!
    //! Given a `n`-ary function `f` and `n` sequences `s1, ..., sn`,
    //! `zip_shortest_with` produces a sequence whose `i`-th element is
    //! `f(s1[i], ..., sn[i])`, where `sk[i]` denotes the `i`-th element of
    //! the `k`-th sequence. In other words, `zip_shortest_with` produces a
    //! sequence of the form
    //! @code
    //!     [
    //!         f(s1[0], ..., sn[0]),
    //!         f(s1[1], ..., sn[1]),
    //!         ...
    //!         f(s1[M], ..., sn[M])
    //!     ]
    //! @endcode
    //! where `M` is the length of the shortest sequence. Hence, the returned
    //! sequence stops when the shortest input sequence is exhausted. If you
    //! know that all the sequences you are about to zip have the same length,
    //! you should use `zip_with` instead, since it can be more optimized.
    //! Also note that it is an error to provide no sequence at all, i.e.
    //! `zip_shortest_with` expects at least one sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zip_shortest_with.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto zip_shortest_with = [](auto&& f, auto&& x1, ..., auto&& xn) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct zip_shortest_with_impl : zip_shortest_with_impl<S, when<true>> { };

    struct zip_shortest_with_t {
        template <typename F, typename Xs, typename ...Ys>
        constexpr auto operator()(F&& f, Xs&& xs, Ys&& ...ys) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr zip_shortest_with_t zip_shortest_with{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_ZIP_SHORTEST_WITH_HPP

/* zip_shortest_with.hpp
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
*/