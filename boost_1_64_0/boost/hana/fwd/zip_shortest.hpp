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
thNAqCr2VLky+cYg2iNGpXtBKYMDmemPPe8yKFEdNKuYDIDXStkVIGebK5hmTCRjKdFS7KH77E1EzNs5itOgQ/rKOtgImfcRWbtxGLR+in223rQxdtDlwjtx6wROImb/P0JBbEsCnaFlWVdVoSQ1Y9xk/PXz53WvuaqDPxSW98aFgBXsmOYE3f2Q9pMm/7ngrVl4QNaR8roa3yMqyV2qI5WsHP9Q1jNheFs276y5ukyiCBAv5s/R+WYZ/px0+osIV36y11ygWMXykvUyMb0LsEwXuzycZZ3oRkjBmytfzxGuyQlLdGPj+3kuxc63uBruiReufXOql+omiYkxKEckrQ4HaYo8KgMFh5ycd9vig5TCLEybIdcOTU3SgYnhnf/lPRHA2SmFcrLBxFE8sKvn7Nhbfda0G7TF/x/oJrFNHc1lWnGbZ8yvHo3aKJhvBjQVZA1m/WcYv2DBB+rHkMDLXs5/58i8Ng5JvHUjLfK4bfTaONtmUuPTKu6DOdFp1mtmdq4B97O5upgkTljC1MFXy5k7ZtlZ/ylIArPs1giW3APnsZpKaDBHHNLq1g==
*/