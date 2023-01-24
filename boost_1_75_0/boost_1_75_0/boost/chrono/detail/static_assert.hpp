//  static_assert.hpp  --------------------------------------------------------------//

//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt


#ifndef BOOST_CHRONO_DETAIL_STATIC_ASSERT_HPP
#define BOOST_CHRONO_DETAIL_STATIC_ASSERT_HPP

#include <boost/chrono/config.hpp>

#ifndef BOOST_NO_CXX11_STATIC_ASSERT
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES) static_assert(CND,MSG)
#elif defined(BOOST_CHRONO_USES_STATIC_ASSERT)
#include <boost/static_assert.hpp>
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES) BOOST_STATIC_ASSERT(CND)
#elif defined(BOOST_CHRONO_USES_MPL_ASSERT)
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES)                                 \
    BOOST_MPL_ASSERT_MSG(boost::mpl::bool_< (CND) >::type::value, MSG, TYPES)
#else
//~ #elif defined(BOOST_CHRONO_USES_ARRAY_ASSERT)
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES) static char BOOST_JOIN(boost_chrono_test_,__LINE__)[(CND)?1:-1]
//~ #define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES)
#endif

#endif // BOOST_CHRONO_DETAIL_STATIC_ASSERT_HPP

/* static_assert.hpp
ojou5qrb/fHxOP6Qumnh93P90BXPsnzs/xEheNJlETaXUWRt9bEHbHDxQVS5A10yNxA68/I5X7Tz01e7qq9+unrzXD9km3aV9HRvPT2tmBNIT/8469tTtf+QcVR3OoHzzIjarTgWeimY9Typdyr/R1LsSYygsx8t7m9KdU/rxPHufMnNwbhOzFB+E6ZPI7LoJNh5d8FtQI/9lBCfIDnLSGqtdZRhP8WMkhvNoX4yFmC06L9JLetJamu8cDGEVnsGJd+kM+AnuxcKvnCPB6Kgn4FKImgWFHubcLzzDOd2rodvfAlUHEwruYiXwcZdpPeKodOtjOzuzqS1JP2IFPddJGO3kN6LZN9/Bgl00kXkOubgsO1HgItpi24Bxh1ReQUoM7BkDB7ejXRYVEdJN+FFqGNwqFvCWpXQyh6Co6UW8dNO0NGeIKMdNUAW82G0J2C0PWkWHG1n6YL8pBNYn5tmacRqAYBAsX8MXo2HEX01GyzVp51CPm3cKbwis5rZgLfCAcw7BQxEV8nzU2J81HAnhGhoQfpzDW9jlgkjI9DjeGtk/3dcAypTJloTSN2V3+Cv7WyEqIwl1Y3CDJ1Ihqph8nW6WXDHvXttc3KE2bRPOyLfooMBnM+iEZqPSANlyfb4aTpLthtV5mR4AHxXh18WYSZs+fNpiPATQpvFVNDggthQQXsx7gQyHnh9YwAmyB9zy1X28SC39EDAPoL7
*/