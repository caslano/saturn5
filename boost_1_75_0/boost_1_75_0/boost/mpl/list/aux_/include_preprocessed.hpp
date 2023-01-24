
// Copyright Aleksey Gurtovoy 2001-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#   define AUX778076_HEADER \
    aux_/preprocessed/plain/BOOST_MPL_PREPROCESSED_HEADER \
/**/

#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/list/AUX778076_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/list/AUX778076_HEADER)
#endif

#   undef AUX778076_HEADER

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
nbVd1m2K+XX5/uHfr6BGZAmxBh3Gx4uNMT3JvW19WQliWthBO79BmiLno0DOHn0r1JVB4QYRY5WMGhnpA51yzY5+EHunPCsRGA72giVLx1BIfL3N2YPHHnM9PCLLKiS6Z0TFHcopPDwaMNqI1X7m83K3bd4cC470drVtdU7zYKvFUR4z4pUR3v8ZwlWcLv1r0rQO+hF9SET2xSYrOncoT4b2xnlPLBry6CncsUmzXn7RN8HSxLTgNQrdWt9F3yikyZfwdhtCpxLSGYKk/wiY6IOaZ1gk++mKa+TyfD32ZDPK2kBAUy79ZcSJkpuVb/pJOE9AzJHllMRyb0rcpvuWxFnZI9sQyMaZVPr5kWPOg2GlVrlPnqHXIdj2njVNhG38qb3MtMUZ5soS29fL1XCEdv7Oe+ZRZ9NPv5mhYEgCMlHLV9pHObTKqCqslXrWLXA5Srmw+j0Kk6vKDIVaKVlk5mo4BNlrWjQ3MKzY5WzzNwyFN/ym7QlcWVpNF7Qhqx+q6F46VMzOZRptVzaQ3mu8WFKSKDwNN4C3reHpMSW77SZpcAPs0eNwIQ2Ti6kqz7YpPHI7T39t6cx1IdIf0YfTLTnh4WznddL5QKhgFHYvyOr17ZZLJeXpxL8vuat87Pu+nzsUI2tmDswD0xeHPZW8meXKbkQRDS+CCNtHY7lYMoaUwRY3t96y3TzGQQwGdV34OkNMmlkbXIlqxrLo
*/