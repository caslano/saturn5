//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_CONTAINERS_ALLOCATION_TYPE_HPP
#define BOOST_INTERPROCESS_CONTAINERS_ALLOCATION_TYPE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/container/detail/allocation_type.hpp>

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
typedef int allocation_type;
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
static const allocation_type allocate_new       = boost::container::allocate_new;
static const allocation_type expand_fwd         = boost::container::expand_fwd;
static const allocation_type expand_bwd         = boost::container::expand_bwd;
static const allocation_type shrink_in_place    = boost::container::shrink_in_place;
static const allocation_type try_shrink_in_place= boost::container::try_shrink_in_place;
static const allocation_type nothrow_allocation = boost::container::nothrow_allocation;
static const allocation_type zero_memory        = boost::container::zero_memory;

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif //   #ifndef  BOOST_INTERPROCESS_CONTAINERS_ALLOCATION_TYPE_HPP

/* allocation_type.hpp
dft5sHIdcPIu1OKbeB0S/voQVsI6rSda3Et6czA8v4R7cR/jMUp8CdR9QJH0JsYDM9FaGuCmCKEpjx5oSBvFHKpIlJSIs9tWepk1MVu5TNpJBFlMQRmYgFK0Uz+iq/i4g41FdrRb213gdfCHBLyaceHxQNT4ucryh/J1dMRpauEwFqEidKc739Hq6q30l3HB8oWVSys/e7KC0w39bCGqWVl44TOg8cLg8DF4uAfYb5X8T/17sMTHUQoWhHaF86bTIoT9fI4kdqcGzRHXoKxkSuulnczDBdhOSVSTBqCNY/J1PMl0OttraCL3lT+rb7E+P6RWHQU3FMSNq6bZ2jtoHL9TnRT0w6+pR/FGklHNCOFtrQ3crduBQxTCo/2SXqPBtaaSEjhgtbS72vfx4h5zasEoesEoxtCzlzlrQajfkjUs51Z1a7nrqCOLvAsw3c5+Fjhysb/CbxraDJ8MY6wIoQqP9eIJkFQ9qalUS274D0eO5PV5g/vUhRL8nfvmKKpxAW+lB5+6GBHw5Aw02rrw643k0SztBW0zWD/HmGwKN/J+pp00gBWlhD4JCfyJDH7mRRIaDhwwnN8M2Zecmf7vvhr+7/GRQi0ei0AkqxzXvfsf8ren2W1jAo4ZKaTyaIkD+ptUVf5VbqUMYYw/UU4rVdSFxgoYeC6+RT5TQpsfiwOyhnTVOSvO/s2+4fGDYqQwiMePkooLk6WWZG2so1Ico9rcxLVO0JNZI4sC/H/TSOC3pMNBI0BXvamhG2BG31pJdPLx9uNOfdTAY/CTUt5xryTMcxi6Xa4fQZrvWOhSwNMig74ZKT6OgvS2eEC8IOanH34hSbgt78lHwaCN2a8PVFt7ibfIx2dLcI8hpGjWhT9fL40S2hYO8mcqRBPzRXMrtaGZ9Sroriz88h37Ezsdbl8dZv8BKY1EnKdjKF/38MR6g6tX0ze/C/ZypDCWRwS8PE2cLK4G4/9K/egshbNF8+RNZO+/ln+RfWUvvCJCbQLSnaWeVn+kxlfQajE6P2mNQK/voEv1o36VhJf3piNe4G0+h2lkojT0wadcBlp5FXfiIjpcP28ubvAJv3SoN5wrMqj35UEJhWGrTdgtKbi+f5LfknerJ3DU2uPTZxjnzfAo93BOgDdV90mYfbg+RAppPGqhZv6ZLHE5NK1s+aZcV0lFL4zSB+iDUdxv6M8bF41qlmTXC1jrCnunfQytfAgI9qLTi+TMY14dbwO1jbv0g/52XfxNbIYftw1Fc4Nyi7XggiKHa1PA7G30DnjklY1njCn49m3RxwrZDZjxz+DCbegYxcFiM6mhxT3bW+J94lXGaVmC3lA8ZJDEWU6NiAwyiO+AjC7iz9egli2XCpKo7CXvkb/l3WcqHyqF1TZqOV3Vx6GAn9G/17cbaWYmeqJjNbf60rW/s8s4O5xTqPnFXNN9CrftbVehR2ej5V/3HnilUAka+P38aLzBvPGdLa2hBo/UFL2bLptvWB9anWDWX9sRzMxBpy+6dD8UqbDKvMP/zQ+hffFDaxkPHh+zIgSpoBSJPpIkVZFqSLVw6lXJlFyppDyKevqTXAmUvhNOpKgF4DhtcEDijAXGavLjE61fQD+j+bQ/OwWpPj6ILscdCWq7HuDHSKEDj2Ksvmfgb9upOQ/E1lIp5v+47IL3f1ersg9fJKdxUvsa3F7ArGS+CcKuYkXYZdAKVPSU9vZK+2W3C9xil/cTrPsAeDDv95YWG1CJPxcry33pvYWVxnDvfVTcv6hf0wWH47kvZOWeo77GGaUNEa1sML030prE2s2A/2Q4L1A9l5KQTUALPkaNyxvPZHbtOtGUOqCTz0EtOiHlyp8oyWpHvv8sLQ7OcNQ=
*/