/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 */
#ifndef POSIX_TIME_TYPES_HPP___
#define POSIX_TIME_TYPES_HPP___

#include "boost/date_time/time_clock.hpp"
#include "boost/date_time/microsec_time_clock.hpp"
#include "boost/date_time/posix_time/ptime.hpp"
#if defined(BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES)
#include "boost/date_time/posix_time/date_duration_operators.hpp"
#endif
#include "boost/date_time/posix_time/posix_time_duration.hpp"
#include "boost/date_time/posix_time/posix_time_system.hpp"
#include "boost/date_time/posix_time/time_period.hpp"
#include "boost/date_time/time_iterator.hpp"
#include "boost/date_time/dst_rules.hpp"

namespace boost {

//!Defines a non-adjusted time system with nano-second resolution and stable calculation properties
namespace posix_time {

  //! Iterator over a defined time duration
  /*! \ingroup time_basics
   */
  typedef date_time::time_itr<ptime> time_iterator;
  //! A time clock that has a resolution of one second
  /*! \ingroup time_basics
   */
  typedef date_time::second_clock<ptime> second_clock;

#ifdef BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK
  //! A time clock that has a resolution of one microsecond
  /*! \ingroup time_basics
   */
  typedef date_time::microsec_clock<ptime> microsec_clock;
#endif

  //! Define a dst null dst rule for the posix_time system
  typedef date_time::null_dst_rules<ptime::date_type, time_duration> no_dst;
  //! Define US dst rule calculator for the posix_time system
  typedef date_time::us_dst_rules<ptime::date_type, time_duration> us_dst;


} } //namespace posix_time




#endif


/* posix_time_types.hpp
KiZ2UI20gyJArjuoRocdVC/YYG9c+qkKa+yVFdZB6t9z4t8v1L+2qyqsjqv27J/2/P67fjHXePg9vbhfgUGOwUkm6eAkj34Ig5PUnAHBSaZ8EIOToMXbZu1+4gW6ewrttxyV/vNluFqmGyuEGp2SGs3XbJKaOKkJIVV13ihP9GIJvu0ppANphuC/cJ6pPQmWX4pcWx7nyHZoZO5mIzOEIThM2t6Lw/YMBvaPpRtacdje0mF7s1cyYF9xwL7BAJ6EHj1sEm/KN5dnFkPwgyd9uiJHBgwriX2XvY8aDUl8SwBQBZK5SD/BND/Q0+B42U+lwfcMBv5rsq9Kg+8dDPxrBXxfafB9pcP3Zg/mDsEZSwZIlt13iuo+/VGt3UpgMF7s2lfoDeLCwAqCAyp7UnvDH2/qWPjjSy3KfN5ydVbBxRMfQB9I4nkD3VBKqXaok4OJe7VC7aem+xwjBBSnpSzzzC42vgwv/N219jcOrv1cbVLBgfAvfbJ/kHeR7Pm98z91d8xfTqX7k+n9vg/mvzecnv8+1/Z+Gr27n3/vwvjv3TjfxzvKup+qs+L1T8XJWCuimMMUYAty3qwwnKoohNK8mYHs9HPP4h0PtWrN8AdFsUm/7DFIXzI10cHmNK64DguYQMkfVJuBzBfLKEdu7A5TIIyBZfE42EJTnT++QMGVM+eritkmLNF2lqF51kostzgXXGvmALzJBzGqZ8ohDBiojTBuJHw0fiDNBjh13CM+CesVOBNLocV/4sfyMmp4tKELips7vKLp6UdZlrhELooKx7RP7zlW9NQ2PAwVYrhzgttEWtMXqRrmRsEw3CvSivNIl19e8UKzSzAvNWSL/SUL+N0LSLiK8uDqGlUIY9nvDFIReelMARieYkjKihXwFKfC60DF4Hjhje8us7zFyfTFd5dZvvjuctNXnEy/LvJOMstfnIoyXeSd5EWZIxV0dW3EajtSJUXgIm1VVgm5kS/MHUee4vobpTO8Uf1d36O8kqAuypKIB6b/Whp9qu7NbnU7KQhni6pe/wwdtePtUcSk4AJyci6zk3TSZgVEFwq0QCEqP/BCgRYjjaAWUH37EfBqbtDIE23+G0DUUgrOE/XPpc9Qm8Y9ce3/h36O64EXcf/fxeuBex8z64FuWg+kZaBneDVTWlytB6pO1OuBrTQ6IDv92EazHvgz5HP6x7+TWw/sxLFPFclMyMrb9DHPq/XAaeX5OVAyPVGB4A+T1gNU55fP8nqgtpzWAxFaD6Rp2u7j9UCU1gN2vNFv5dYDs816YDatB2bjLI2nrwJQSQLG9YBfwnrhmdx64Foq3yduEWlA6SOuFRhfz+uBOF/aEqP1QFyvB/xiPUAno86sz9t9r/RDarwnHeQtAyCrbDJFxNZlTaUu+zLsHP1NSjI41/E4gfXkF+FkrxNY5zpeJ7De/CKc7HMC61zH5wTWR0XkhPFIv/rhVnzyxoGHEnI83bTST0e8xdZR19U58cmScSsrIc0wxqm64RasRiqboE0MS3LLDsvSDZfcshfxmspOkF2reQZA9nERPegSnStF0Fccrf9m70jAo6yOu5sN2RyQDQQIhCNC0HC6laiLHG4glkVSurS0xpbWiFhCa2uUDUblEEELhrRYqcXaA9taj9pqrcVAqU2olWhti6WHvdFeu24Pa6Gg1aZv5s28nf/P/2c3ENH2Y78P8v/vmJn33rx5M/PmvX/8d3AiVpyUjvL1qaN8feionD51VI6g0r1rAo/h1kYFbW1U2HoDiXPvCumY2AN4sBJSOf4pQaR7V0o0br0kvRhZoenZyxY0mXvalxWanl1uQZM9f05UhqPxaclbRfs4CNmR7cmObIdBsE0Q9+4=
*/