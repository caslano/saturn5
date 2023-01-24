///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_ALLOCATION_TYPE_HPP
#define BOOST_CONTAINER_ALLOCATION_TYPE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

namespace boost {
namespace container {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
enum allocation_type_v
{
   // constants for allocation commands
   allocate_new_v   = 0x01,
   expand_fwd_v     = 0x02,
   expand_bwd_v     = 0x04,
//   expand_both    = expand_fwd | expand_bwd,
//   expand_or_new  = allocate_new | expand_both,
   shrink_in_place_v = 0x08,
   nothrow_allocation_v = 0x10,
   zero_memory_v = 0x20,
   try_shrink_in_place_v = 0x40
};

typedef unsigned int allocation_type;
#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
static const allocation_type allocate_new       = (allocation_type)allocate_new_v;
static const allocation_type expand_fwd         = (allocation_type)expand_fwd_v;
static const allocation_type expand_bwd         = (allocation_type)expand_bwd_v;
static const allocation_type shrink_in_place    = (allocation_type)shrink_in_place_v;
static const allocation_type try_shrink_in_place= (allocation_type)try_shrink_in_place_v;
static const allocation_type nothrow_allocation = (allocation_type)nothrow_allocation_v;
static const allocation_type zero_memory        = (allocation_type)zero_memory_v;

}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_ALLOCATION_TYPE_HPP

/* allocation_type.hpp
qIXxggspt0599fmgAz+1tAgiVC/AiRE46lMYmZ8mIoFJSkhg+g0kOKMaCc3vRCOWAhqxFkc10J8UAREr4vvB4wn1wuMJ98LjifTC4w3phccb2guPxzvK5t/A4xGMUn/fi38Vp8QLYwmATJ8vraVlHOAt0JMOCDDTUp9PfSbVC1N0KYqBAN80KboUVbkFltLCoQsSBosWXDeHjrtfoBddSEOAolMYPH0pwREaHDqYtbe0twsKCrE5dBPN8HCLcO8eOhhraGpo9NAtWiiGHjqbwsT10Nkj9EjooQuxqcChW0AfOh7dbjpJW7RAL7qFBbsX3QT0gEunBONMNnDoXIE4cOg96b+gc+v/1/3j4VAiiKMAjpSdJe9iyTtZYn//tm88/vjf8o/39+b5WGpqiyHhADN1AfGxePIZe88XH9tigtPzETddP7YFT0J9fMWTryUc4TSZlfokDfX4H07Xkx8f4HSLHrniUSYk8RFUj9Z/6R8PM47Q0tIX8pbSF9QQ0EctJhwMnr6UPtKg/OHpI7N2fdQuqI/YFD0CaYZHoHDvCEz/jsf7/p77+3vu7++5vx2PZ2Cgs19+v7y8/FeQO05uCQm7HWMcHTX7p7sluiXuTnCNcdSey5erIEoc1ZD/ElNSE/cluiY4au/mq0GBYWRkRKfT6DS3FM+U/YmJiZiurd1D5zpDE2a4paam7E9xS4zpRacxWJQrsCFD3FJT
*/