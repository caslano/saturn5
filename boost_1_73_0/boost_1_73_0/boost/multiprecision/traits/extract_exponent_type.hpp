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
yNsbory3AHcwBHnfhygv7GkYI0/z80DyRjzNtI8/eWmAywxB3lUhypsDuMYg8hC3LkR5DwBuSwjyXglR3gHAfRhCfU+FKC8CJofY7fw8kLyR25n28ScvHXATQ5A3O0R58wDnC0HeXSHK2wC4R0KQtydEefsB90EI8k6EKO804GJ28PNA8obsYNrHn7wkwI0PQd4VIcqrBFxdCPLWhCjvbsBtCkHe8yHKewVwB0KQdyxEeScBF7GTnweSN2An0z4=
*/