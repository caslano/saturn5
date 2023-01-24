/*
 [auto_generated]
 boost/numeric/odeint/stepper/stepper_categories.hpp

 [begin_description]
 Definition of all stepper categories.
 [end_description]

 Copyright 2010-2011 Mario Mulansky
 Copyright 2010-2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_STEPPER_CATEGORIES_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_STEPPER_CATEGORIES_HPP_INCLUDED

#include <boost/type_traits/integral_constant.hpp>

namespace boost {
namespace numeric {
namespace odeint {


/*
 * Tags to specify stepper types
 *
 * These tags are used by integrate() to choose which integration method is used
 */

struct stepper_tag {};
// struct explicit_stepper_tag : stepper_tag {};
// struct implicit_stepper_tag : stepper_tag {};


struct error_stepper_tag : stepper_tag {};
struct explicit_error_stepper_tag : error_stepper_tag {};
struct explicit_error_stepper_fsal_tag : error_stepper_tag {};

struct controlled_stepper_tag {};
struct explicit_controlled_stepper_tag : controlled_stepper_tag {};
struct explicit_controlled_stepper_fsal_tag : controlled_stepper_tag {};

struct dense_output_stepper_tag {};


template< class tag > struct base_tag ;
template< > struct base_tag< stepper_tag > { typedef stepper_tag type; };
template< > struct base_tag< error_stepper_tag > { typedef stepper_tag type; };
template< > struct base_tag< explicit_error_stepper_tag > { typedef stepper_tag type; };
template< > struct base_tag< explicit_error_stepper_fsal_tag > { typedef stepper_tag type; };

template< > struct base_tag< controlled_stepper_tag > { typedef controlled_stepper_tag type; };
template< > struct base_tag< explicit_controlled_stepper_tag > { typedef controlled_stepper_tag type; };
template< > struct base_tag< explicit_controlled_stepper_fsal_tag > { typedef controlled_stepper_tag type; };

template< > struct base_tag< dense_output_stepper_tag > { typedef dense_output_stepper_tag type; };


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_STEPPER_CATEGORIES_HPP_INCLUDED

/* stepper_categories.hpp
HfJZ6Hj+MB3lsfZ4usLF+zbw4q2esoMjHvR6TwXjYa5x6t8qVIAqarf8GHLoe4+yiB/S1sW9w7/Y0jdr/7iBf8GjwHGSsHlmmG2DEDrdS8XG0J32k7qsvdJuj74OEw/jYNHEtPkgBCmSmGzI97mYzrINBDysYkfP7rjc8xPa83n4WHcu8kicDEBGUbNv0P+Lhl8LJA2Vzby3svCbaTOcY1E/5z8574RYiyTWc5zUbnyZlky6S9sWfoulM40a0ohQ7rhQ4OGYOUGeAXESI4IRyBZGeEPiae1LCZVLY2kyRguTBm77Pb1p2//9aYWcOV9WSX7mnjBanz3tWQmlirWiExZ72gdt2adtnulv4iBe5FumTbCIbZdKnSvr6wJjGOzOLC0fU/57jxYAq/2oVwkUedP17KF/6rI7RTRfVEDFN/RD2vZ/edD2J69eKKzsac3LU7X35Km5oo93ondOGk6/giyPT7V/Ed2wREA7FRLZxPYyqxbky01YvEMi6VTSJw02D+ufepWTZ1gfZzX8EX5Z09E1Rr4VGBGOK3JG24nFCFzwh/iQVfsazuMIYfT5v50rjbff5wjY+YZXgRsEU5ecO3c8Zp/T1sr2O/Q69ROrRq1fCWDKk/srLzMJS9HEMjKkn4JUw/GhnYu5Ml9Tj80NNCPZaU68zcsajtcu1d46dbgOGHORFvYPoiUp9qaMbWDvbX8GgTaFsaSVuKyX
*/