//  Boost version.hpp configuration header file  ------------------------------//

//  (C) Copyright John maddock 1999. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/config for documentation

#ifndef BOOST_VERSION_HPP
#define BOOST_VERSION_HPP

//
//  Caution: this is the only Boost header that is guaranteed
//  to change with every Boost release. Including this header
//  will cause a recompile every time a new Boost version is
//  used.
//
//  BOOST_VERSION % 100 is the patch level
//  BOOST_VERSION / 100 % 1000 is the minor version
//  BOOST_VERSION / 100000 is the major version

#define BOOST_VERSION 107300

//
//  BOOST_LIB_VERSION must be defined to be the same as BOOST_VERSION
//  but as a *string* in the form "x_y[_z]" where x is the major version
//  number, y is the minor version number, and z is the patch level if not 0.
//  This is used by <config/auto_link.hpp> to select which library version to link to.

#define BOOST_LIB_VERSION "1_73"

#endif

/* version.hpp
b45RGK3AzjJL8x5BS0778bz+Ou7zmT6XiQEVLwIPKDZ0WHPA5QE595fRac+dYbvq1eBFYnECDVC+ZTBf0J9Pr9Yd9Q32yGDUaNR7EXOvsx2gmx/w0B2kxD90mVkPHBrKOdRF6shdHGbdWysVC+lYev/hYLXtYbajLeVfsDnxxnPg0aCms9oRNlblSrUUB4ZHhUn/WSEEnGFptSBYNAdgA+h3DLbPpKb/5/pjAjyvs53cHgwTrqRno1g7Wy14YlkHkoYZodaoRKWS2ghsV7+MjrsQl7r3kBR5Svn00EBL30tXre3Qoyh9U68MNL/RRlAZvDRn0JxzrAusrfHk0pyVZG7KiskX7UQa5eBM8A7e1WtzQjDaytxAdFjw3R6yFHcBMndYYTEC6aa7+3xAjG4JJMvtJlJ5G2SqCStjIzMppFzaKUvE8h2SMk525V+UBcFORtX3ZO+2NeL3i5jZmJ+ImFZVEIfnxDKuDkZ4SgV7gq9cB4ElIvnmjlJMWmbIBFdF2sirIcB7GQ/sJ1f/kTsV7cfiHWHKF1u1teYq2U9Zf0LQUBfd3GP98GSq9w==
*/