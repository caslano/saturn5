//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 20010.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Based on the unique_threader/unique_joiner design from of Kevlin Henney (n1883)
//
// See http://www.boost.org/libs/chrono for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CHRONO_TYPEOF_CHRONO_HPP
#define BOOST_CHRONO_TYPEOF_CHRONO_HPP

#include <boost/chrono/chrono.hpp>
#include <boost/typeof/typeof.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::chrono::duration, (typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::chrono::time_point, (typename)(typename))
#if 0
BOOST_TYPEOF_REGISTER_TYPE(boost::chrono::system_clock)
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
BOOST_TYPEOF_REGISTER_TYPE(boost::chrono::steady_clock)
#endif
BOOST_TYPEOF_REGISTER_TYPE(boost::chrono::high_resolution_clock)

#endif
#endif

/* chrono.hpp
fR/Pauulw9yWZkc6790BEBMCxC7JM5st81E2nY5HyzybTi46jg3DjDRVxsqoEHWNrO4rArscLjb9AXu/2rS1V/vLCUyNlyHZPSNcJ8FCaVC62iDQxl5Tbe4idh0DEhkurBTU3EiipvURXyQhXEqbMsVoe6w8NllCklId58P3w3TKFHFfDR1Tm0AMAoymS+wUuBQ5U1wTQyTocOdpo5+uanxNSDRU7qwVFHW9TeB8Lb/ryEUhCFnGLGuWlUFwUJpox22dlw1UolBYG3Sx1OqauE/xysHkD076krsVykeIKATFUaJdjFTAWE9m5YVCP6EC97lCsSldmQ5pgi7q+E+n77J8OFqmn8eLbPRxvOwIi6JzdEg0+J0no7FUEbvHKAypuoc4JEwMwov3IlASzBpPGKGMTbj1qMrxlRV2y2ntEEZWCw6kkVxzcSCQ5Pn1vMHcPxYeliHeJLSDCWdukHAeXVB1dL7v9EJ3HsuAdxS9ay15bMhh16ZuHyJEUwA1UpwXHO+5l9nXGosfLQJK+geqDSwEc1wVos8DxyvCtgeN0cRuWOAdjooIIwqq3XCL7yDYDVeYI90vw8/DdDJ8m07S5UU0LMsg/nDfJrxjPl6ezafweTg5G0cZ9tO2IBfxQ/qzjxg2thuPoLm9vtm5
*/