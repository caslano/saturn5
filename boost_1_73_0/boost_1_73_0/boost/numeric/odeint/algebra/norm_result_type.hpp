/*
 [auto_generated]
 boost/numeric/odeint/algebra/norm_result_type.hpp

 [begin_description]
 Calculates the type of the norm_inf operation for container types
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_NORM_RESULT_TYPE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_NORM_RESULT_TYPE_HPP_INCLUDED

#include <boost/numeric/odeint/algebra/detail/extract_value_type.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< typename S , typename Enabler = void >
struct norm_result_type {
    typedef typename detail::extract_value_type< S >::type type;
};

} } }

#endif

/* norm_result_type.hpp
eP7PH4VZ7qajsgW6AGyAz2PDpshf2hW+pRkN2863yuWDbMZeADYg5+4R5htOsQPn7lFTattxzPriuQvTGzsx9NEOrb0Az33mh88A4og75oOrny1IIm7KxZXPHYTMtGw/Fkuiz2S0dp3Q2nUS6XdqegCet28EyS7E3a3IGlZk7fGxBeSoPC5HHrYPrn6OIYu4U5oNBcPr9zziORrew4bX1mnEm0E8/73Dee0+tFhQePfxg8aVyHtkoTgeWiyQh7Q=
*/