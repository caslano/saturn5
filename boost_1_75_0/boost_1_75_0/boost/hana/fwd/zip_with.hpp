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


BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr zip_with_t zip_with{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ZIP_WITH_HPP

/* zip_with.hpp
D+64BuaCvHhQ2Ig3Qo+EhmITOJWQBwtOHve14XgGRuSrUH2WE8PbCGAhDKhmlA1h5QxgDUEJtJmPQMqFtkAUAp0IcxUH0NGq65gwoiGDlQJfOZoNTxES44YQaZDQgGq1DKg4T2VQXDqggD4C+fDQBerg4QMouDRu6EDXWFro6/gHMguFocP+u2BJuNsRrAaMPpwBGEI7BCeSLSFp1UPSiPD9YWwJj+BnQwM1IpgWKBrDA6JBeEbMF1okPCb+YASgJzV0gG69CBwcAMkulDaoFBp+BE8FOhQ8HMOnCOEF2K4JK4aaUUADg21ESEMhim2rEbgFDjWYDBbcZrDMLAr1CHgLNIgHjD5Un6vaJtQ02Uc4xPBsgTNQwYGYeKrnkqPnxSpMJgMiYR2hp3W4r4jjwGN2BIQySJ+hBwHa1R2K2jzqKTRNFFNBzyD0TdAcAEJ8UBbtw1s0Sc+BNyLIEKJkkinwKMUdYDlEb1A5MPGINMEoYUwKQHU1B8yFMMWA9gRrRRB0qAMD0XYApgnBUCCzi4jFILcigH8EK4igEZrCdeGO4JFrgmCGCZwjglZ1GFUN0TD0NGLxyADlTYvcQt2II0ScnUVUHNwZhnGKW3AL7hDc/cfd3d3dGZxA0GDB3SG4O8EGd/fgPrgzUzvt6Wl7uujiLt772d0+d/G9EfXiP44HRICshFbROpjPItSxhH+4o6DG6q5R+kyGJN8F
*/