/* Boost interval/utility.hpp template interface file
 *
 * Copyright 2013 Cromwell D. Enage
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_UTILITY_FWD_HPP
#define BOOST_NUMERIC_INTERVAL_UTILITY_FWD_HPP

#include <boost/config.hpp>
#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <utility>

/*
 * Interface of simple functions
 */

namespace boost { namespace numeric {

    /*
     * Utility Functions
     */

    template<class T, class Policies>
    const T& lower(const interval<T,Policies>& x);

    template<class T, class Policies>
    const T& upper(const interval<T,Policies>& x);

    template<class T, class Policies>
    T checked_lower(const interval<T,Policies>& x);

    template<class T, class Policies>
    T width(const interval<T,Policies>& x);

    template<class T, class Policies>
    T median(const interval<T,Policies>& x);

    template<class T, class Policies>
    interval<T,Policies> widen(const interval<T,Policies>& x, const T& v);

    /*
     * Set-like operations
     */

    template <class T, class Policies>
    bool empty(const interval<T,Policies>& x);

    template <class T, class Policies>
    bool zero_in(const interval<T,Policies>& x);

    template <class T, class Policies>
    bool in_zero(const interval<T,Policies>& x);  // DEPRECATED

    template <class T, class Policies>
    bool in(const T& x, const interval<T,Policies>& y);

    template <class T, class Policies>
    bool
        subset(
            const interval<T,Policies>& x
          , const interval<T,Policies>& y
        );

    template <class T, class Policies1, class Policies2>
    bool
        proper_subset(
            const interval<T,Policies1>& x
          , const interval<T,Policies2>& y
        );

    template <class T, class Policies1, class Policies2>
    bool
        overlap(
            const interval<T,Policies1>& x
          , const interval<T,Policies2>& y
        );

    template <class T, class Policies>
    bool singleton(const interval<T, Policies>& x);

    template <class T, class Policies1, class Policies2>
    bool
        equal(
            const interval<T,Policies1>& x
          , const interval<T,Policies2>& y
        );

    template <class T, class Policies>
    interval<T, Policies>
        intersect(
            const interval<T,Policies>& x
          , const interval<T,Policies>& y
        );

    template <class T, class Policies>
    interval<T, Policies>
        hull(const interval<T,Policies>& x, const interval<T,Policies>& y);

    template <class T, class Policies>
    interval<T, Policies>
        hull(const interval<T,Policies>& x, const T& y);

    template <class T, class Policies>
    interval<T, Policies>
        hull(const T& x, const interval<T,Policies>& y);

    template <class T>
    interval<T> hull(const T& x, const T& y);

    template <class T, class Policies>
    std::pair<interval<T,Policies>,interval<T,Policies> >
        bisect(const interval<T,Policies>& x);

    /*
     * Elementary functions
     */

    template <class T, class Policies>
    T norm(const interval<T,Policies>& x);

    template <class T, class Policies>
    interval<T,Policies> abs(const interval<T,Policies>& x);

    template <class T, class Policies>
    interval<T,Policies>
        max BOOST_PREVENT_MACRO_SUBSTITUTION (
            const interval<T,Policies>& x
          , const interval<T,Policies>& y
        );

    template <class T, class Policies>
    interval<T,Policies>
        max BOOST_PREVENT_MACRO_SUBSTITUTION (
            const interval<T,Policies>& x
          , const T& y
        );

    template <class T, class Policies>
    interval<T,Policies>
        max BOOST_PREVENT_MACRO_SUBSTITUTION (
            const T& x
          , const interval<T,Policies>& y
        );

    template <class T, class Policies>
    interval<T,Policies>
        min BOOST_PREVENT_MACRO_SUBSTITUTION (
            const interval<T,Policies>& x
          , const interval<T,Policies>& y
        );

    template <class T, class Policies>
    interval<T,Policies>
        min BOOST_PREVENT_MACRO_SUBSTITUTION (
            const interval<T,Policies>& x
          , const T& y
        );

    template <class T, class Policies>
    interval<T,Policies>
        min BOOST_PREVENT_MACRO_SUBSTITUTION (
            const T& x
          , const interval<T,Policies>& y
        );
}} // namespace boost::numeric

#endif  // include guard


/* utility_fwd.hpp
fYdf39Gs0A9d6qGV6wSuSUYHq8P1seVsGmDo1oGwunHXYB2NGNvbW8L+vD2xMZH3ASsTbWnyX44OF3HQDvAP+s0m9MKAIX6pk6d2PexRvJox3nwCVZ8+JbYvCyC7pu1AZ2MwoQ50F9C05tbcSp3wznRUgWm30qlAgS1YfWfvdObSHDafaqM7FaNNoN1ydG4WQlgX9RyoxeoLKaxPbx/6amNPfhH8YvqPHUo3OTlCAg2Biz63eRPwwbflKzsWCF0Ppg8H4Blmh9TcW5PT8e8Ty+sgMX4HnDiexRgm/uCBBqAeTEtkx5crfrfAYQR+xqEjw9E1lzLpUR8RdzbQaeJF1oIVRTwEaMzaM3HBFQ0d9RcLfOc+TGACuh8AEbpoGAls8phrEBXhRAYV0EvL1HaEemGPwA2bE97RkVZSDCeLgpotpcakoGGBQVkQUF90ljhj+mN8c4vbRo1NVYN5ha24RZPAmdcrCPv3x9Hj97W0YFNzvBdAtQHrJgMMVXBuQ+2+VT51OjvgjnAMVzAqBnf0aWfnjn20+ccu+0A69nMfP5rs60te8pNgwPAM3t70+v1gngSfz4p7g4vfCJskmMyCIsuS6Mf7cW3dddRtqWXhxN+ZW9bx2LMb9EGDSJg2dGsO64uZ5TSrE3DQ5pFp
*/