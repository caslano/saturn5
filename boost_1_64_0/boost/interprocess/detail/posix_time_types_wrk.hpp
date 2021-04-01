//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_POSIX_TIMES_WRK_HPP
#define BOOST_INTERPROCESS_POSIX_TIMES_WRK_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//workaround to avoid winsock redefines when using date-time

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifndef WIN32_LEAN_AND_MEAN
#endif   //#ifdef _WIN32

#include <boost/date_time/microsec_time_clock.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>

namespace boost {
namespace interprocess {

typedef boost::date_time::microsec_clock<boost::posix_time::ptime> microsec_clock;

}
}

#ifdef _WIN32
#ifdef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#undef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifdef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifdef _WIN32

#endif   //#ifndef BOOST_INTERPROCESS_POSIX_TIMES_WRK_HPP


/* posix_time_types_wrk.hpp
o7/DwrKw3lpwvpknMOccqyHQAQxxhLywYI5OQFnDVs6jTOOJdORNaihdTCBTx/YgZjSHeNBcz8tP33juLl4LcFgE+hI4lF09m/1LTX5kNMQAljia/cltOHswyU+IgF3az663z9/+9d9923NhkqtZU3/FHqV5H9fM9qRjJTUz+hDvataNYdDOes7ylREIvDGgehmVnzQybjMVPfcqsag3wAt8hAUQhkYOWslyRq7gbACkV3JfwSzzgVPh27iTCyYyujCFNxY4TTiZwrwgZEwNsHA0oQPkhUBDAq/asW1dXzPMGZcAPh4VdN+dFKJ5tlgo8kBCKNiEpJr7mJQwH1UJfP9kelfI0Cp1PDz0IFf9POSNCrEnhj3cxNLCmel6tbudqrMeVM4xxUYOT7rZBULGdkZIBKN5CSspxmk0IIukaqKS5wMofXEjS0bxRbPP4qjH0QTYX/nB3EFUNQU3DwDmthT73SdGw/DYYRu1Ic/RU8tPaEjPskGZf6037kh5155qk+3Dl+a26DKQEcA6f8tOEyuDMaLSRiuNlbNceAdrnKXYulhnwP+h4CEszA==
*/