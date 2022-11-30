/*!
@file
Forward declares `boost::hana::zip_with`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZIP_WITH_HPP
#define BOOST_HANA_FWD_ZIP_WITH_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Zip one sequence or more with a given function.
    //! @ingroup group-Sequence
    //!
    //! Given a `n`-ary function `f` and `n` sequences `s1, ..., sn`,
    //! `zip_with` produces a sequence whose `i`-th element is
    //! `f(s1[i], ..., sn[i])`, where `sk[i]` denotes the `i`-th element of
    //! the `k`-th sequence. In other words, `zip_with` produces a sequence
    //! of the form
    //! @code
    //!     [
    //!         f(s1[0], ..., sn[0]),
    //!         f(s1[1], ..., sn[1]),
    //!         ...
    //!         f(s1[M], ..., sn[M])
    //!     ]
    //! @endcode
    //! where `M` is the length of the sequences, which are all assumed to
    //! have the same length. Assuming the sequences to all have the same size
    //! allows the library to perform some optimizations. To zip sequences
    //! that may have different lengths, `zip_shortest_with` should be used
    //! instead. Also note that it is an error to provide no sequence at all,
    //! i.e. `zip_with` expects at least one sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zip_with.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto zip_with = [](auto&& f, auto&& x1, ..., auto&& xn) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct zip_with_impl : zip_with_impl<S, when<true>> { };

    struct zip_with_t {
        template <typename F, typename Xs, typename ...Ys>
        constexpr auto operator()(F&& f, Xs&& xs, Ys&& ...ys) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr zip_with_t zip_with{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_ZIP_WITH_HPP

/* zip_with.hpp
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
*/