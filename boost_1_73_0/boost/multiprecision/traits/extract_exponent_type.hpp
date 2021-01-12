///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MATH_EXTRACT_EXPONENT_HPP
#define BOOST_MATH_EXTRACT_EXPONENT_HPP

#include <boost/multiprecision/number.hpp>

namespace boost {
namespace multiprecision {
namespace backends {

template <class Backend, int cat>
struct extract_exponent_type
{
   typedef int type;
};
template <class Backend>
struct extract_exponent_type<Backend, number_kind_floating_point>
{
   typedef typename Backend::exponent_type type;
};

}}} // namespace boost::multiprecision::backends

#endif

/* extract_exponent_type.hpp
WC9VlGtF0zmyLyzrCS2TfbasJ7RM9oVlrdzt+2w6VL7DybMcm28/X6Z6xJjlRwtaQ1RPF+fOFsN2+RXgg1fSz53ow4AKDycXjxzhcSvE3v/6IyF2YtzIi0dEfvdxo+uFdzHybL1t48l+aDzEjo2zHWSPNHDavhaRr7YvnskgdT7MNwgjeXU2fa5aSldmUL5eDmDpAibXs4uXvOybVI5BLlM9c6SKEC78t4kXPKLbKF9e7RQn
*/