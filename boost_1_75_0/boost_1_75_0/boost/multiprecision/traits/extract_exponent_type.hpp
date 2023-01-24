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
JMg4I3V6rWvJb7CgAWICUKGIRXD3gP7r9Q2XfVX4TnwJ6EL7q7vI2g6v0voAWbo3oiFW/ejVMxpSGFYi+y6r7ABOKwDvLd/bvDBJvYx3WZDBpJUFXzBnGz/3ANxBbZhF6bbnQ/a2RPa9mG2uPIE14KvGtDdqs5JMjUaZGkPLJlhLWGXlK39xLYi2Z4n/QJU4PMQueTbdTChKrZkJ2r+Nru+D6/n+2ntmYGU5mJ8n+KbDAdUkTymsnTsqONeCnKS5X8SG+Gh7ehQvrdCfvci4NHsIBQq2pc76R04oisSf3ugcbGOgpxbWlryCk3ax1yqt12eWHeqtXrZw0K4ArbRLuLC5Z3xFk3OHoSr/q5thlMpUvodpI0P5PSM405Ie8K2B24unkaUIdEdrOkaMlz5F/i32OFJYEnZSwZGRa9Ev/tdZZLTY9DtOvllrNffX6VwbHfVM/y6tOlJO8K2V955DzUD9lwzKifIhPOg/p/muSA/MWWPqFuWP+sQs0qlJEq1ST13HGnZ5dfd0WA4FR25TZ8/Sd8zh/lfiPshm2coa86XzxMGuIayTd7GwTp6pnIZlyknXOls+2mySDsDiA/TuwSQHQaWqpJrsGUBdtdUgOE57AQUwVUZi9P+n2AHACaOj2sGkcK2ccFreqwVmQ1O4rG1Nt/22CWvOcAYEVOjbp+MGG4w6PTi4JYx8D9ZXOj6ItPI9pL3dikNWMtbD
*/