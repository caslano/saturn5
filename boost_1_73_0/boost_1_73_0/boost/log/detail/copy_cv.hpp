/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   copy_cv.hpp
 * \author Andrey Semashev
 * \date   16.03.2014
 *
 * The header defines \c copy_cv type trait which copies const/volatile qualifiers from one type to another
 */

#ifndef BOOST_LOG_DETAIL_COPY_CV_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_COPY_CV_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The type trait copies top level const/volatile qualifiers from \c FromT to \c ToT
template< typename FromT, typename ToT >
struct copy_cv
{
    typedef ToT type;
};

template< typename FromT, typename ToT >
struct copy_cv< const FromT, ToT >
{
    typedef const ToT type;
};

template< typename FromT, typename ToT >
struct copy_cv< volatile FromT, ToT >
{
    typedef volatile ToT type;
};

template< typename FromT, typename ToT >
struct copy_cv< const volatile FromT, ToT >
{
    typedef const volatile ToT type;
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_COPY_CV_HPP_INCLUDED_

/* copy_cv.hpp
YTw2Qug8VZ3OMeCrsuqcn2lsb22w+/CFVQnDCm3NUnGYCUPk/KRyKPZpSNNn5+d69B0tRsJxvTnr4SYkYpd49oh3D3HVkBZYa6+7D/m1OnRYipKFgKiFb7OZFQOoCl9xpvLqBpn8cx2rYLX41bT949M3nX7AH8Xe3w/6jAogIeeq/sxEeXXujoPw1C7gg1PH2QKnebBp9lHHavMEW/LZMOuptgTHqNLT6wp9lpNpIIlz6kZyw12DWeHFHUz5QdqVjCtYknKraXvV8+HGqn3qaAnkQcof2kGCYbFjoblCvNEIxiivHEDd1TzxWCNkVHmFoqej+DwuqQixt/3bVcoHervaxt+y6dtVrlL4Ngfuk3zoAjUC6QlvNzK8gZGTFC+RhnG66Z4xOseT+nGi4py//HWDuXcuiiDoEmWkT+0y0jwEQA7uamEFOavbKAhDry8tjkYURrSGVDydgqmHjOixow39K37Tiz3zBTDVyOVVkcmsRCq8LyTpd10MG75JYyMkE0sB5gc4/LzgG7ZlOIpg0oGjmGAdCF77TTyiR3VhNqhSRNWYhAv5jRdp0djTxYYPdpPb+PToqThWaff4CVAh9jUZncL9NR1FqDejtNS7yvKRiGlx2midUKFbDAtFoLiG+gan3RFUpNZEq8ir
*/