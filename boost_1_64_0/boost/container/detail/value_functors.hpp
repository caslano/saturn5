#ifndef BOOST_CONTAINER_DETAIL_VALUE_FUNCTORS_HPP
#define BOOST_CONTAINER_DETAIL_VALUE_FUNCTORS_HPP
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2017. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//Functors for member algorithm defaults
template<class ValueType>
struct value_less
{
   bool operator()(const ValueType &a, const ValueType &b) const
      {  return a < b;  }
};

template<class ValueType>
struct value_equal
{
   bool operator()(const ValueType &a, const ValueType &b) const
      {  return a == b;  }
};

#endif   //BOOST_CONTAINER_DETAIL_VALUE_FUNCTORS_HPP

/* value_functors.hpp
KDQuX8aQ5DXkuab5/BmhyExI423Picy1VAgARkQI96AFukv9+rLTaNqF4fa74chD1ge/w7p4BxwyGtODRnAoTaHg63Y0x/FxvlfSNk/hHrk7Jnd+5sqWYLAiPb5N9MPRrMyFpKrWq90MniPSsZMkxmJZCT2c4C5BKNxM82BlDTrKnw8UJSobQti8uisbgNw7wsK96q/YivYIPCz9Fu7R2qDLWPhb/gZspPnMNRDfwrpF/+GbXQOFbS2Ss4pGJViCcngPkKYEBYOvhQ0VTqBx2+8H8blfswf73w7187XBTNjSrXjLXu6mQZEJoWnySVLjozFOc2RCllks4ETwp30RyA4S5ptDAvjlZXb/Y16dGCm6p5y/W9rTB41oJOD5yVhbpp944j3yfJnaPV+1mKXSV1XYSPpSqmPJGVMRtJboZ9oRfKvpSEDAAuC3jruCBVmN8IvNoq99/FCLUx89hW0oiygsxr8RXNqx3LTalOk/l5hSI93NV/16YW35eI2F+yenxNL/JcugHPhR3RnhnKW7yvqKCdRgtLvuP8FWrAOxJRQI7/Oi8FhK5GmY4A==
*/