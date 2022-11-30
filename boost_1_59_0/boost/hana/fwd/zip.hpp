/*!
@file
Forward declares `boost::hana::zip`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZIP_HPP
#define BOOST_HANA_FWD_ZIP_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Zip one sequence or more.
    //! @ingroup group-Sequence
    //!
    //! Given `n` sequences `s1, ..., sn`, `zip` produces a sequence whose
    //! `i`-th element is a tuple of `(s1[i], ..., sn[i])`, where `sk[i]`
    //! denotes the `i`-th element of the `k`-th sequence. In other words,
    //! `zip` produces a sequence of the form
    //! @code
    //!     [
    //!         make_tuple(s1[0], ..., sn[0]),
    //!         make_tuple(s1[1], ..., sn[1]),
    //!         ...
    //!         make_tuple(s1[M], ..., sn[M])
    //!     ]
    //! @endcode
    //! where `M` is the length of the sequences, which are all assumed to
    //! have the same length. Assuming the sequences to all have the same size
    //! allows the library to perform some optimizations. To zip sequences
    //! that may have different lengths, `zip_shortest` should be used
    //! instead. Also note that it is an error to provide no sequence at all,
    //! i.e. `zip` expects at least one sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zip.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto zip = [](auto&& x1, ..., auto&& xn) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct zip_impl : zip_impl<S, when<true>> { };

    struct zip_t {
        template <typename Xs, typename ...Ys>
        constexpr auto operator()(Xs&& xs, Ys&& ...ys) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr zip_t zip{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_ZIP_HPP

/* zip.hpp
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
*/