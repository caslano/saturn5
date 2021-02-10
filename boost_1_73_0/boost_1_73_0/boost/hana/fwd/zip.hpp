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


BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr zip_t zip{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ZIP_HPP

/* zip.hpp
jfIGweaythTGt4LNFcyyRI8dcSwdxgiGpeHo51cyHOjcgoY8KMMAqOOzMIy9+bwijLuxPRaaeVD3J6IO+X/COcC0TXcM7+bfRUJC9SEUwes0OSGDx5IT7cSE/nAELDHhurnAQcuqwcXRM3CCglkBkaawy8OSFeGr6E0+bjedkdDo1uYkNJt0tU/G5ieURmIsHrd/dp6rsMEdu5+G5C1McOHzFmZLIfa/leUwlMUMl8mw7IropIbZ3JH7HibBcXTY5x/s7GS/m2ZF8xHhW5/WqLXVH7moQUHtk3Utf/riQ3/AJY0JjFovS+LCXs5nn71cG7flozjmctsq0dg8Ln1Rt4NNXkjqopMWUl1AsqKWhm44ynzwpCia8VsTFMrnzZEpijZK2NRECytISsIJmemKerUC+NMnDdKr/fAJ/BPztUbGTEbnHzUx2beSaE3riA+aGLwA8k2bjsy6c/vMerssu7NSy3rXONBnapxrggOWTj5SE7GGo0IFqZ+I0MBke2QoYDCrn/o3g4Yl1Nqo2hNpMFmbteyBA8Sy8EChZnPQRFkDGfBjNHUP7U/RNMy0bgD6IRqVRrk+QyPhBfgUTKOt+BBMsxAaPwNj/gCN3ucOsM8dW587sE/PtOcRLsZqTSJnTHWyv3fEP6LaTVRF
*/