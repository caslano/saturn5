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
bQC4NAEQ9ItOnXF0f18SdtD5t3OdR+D2yzPB8szt07P5YCmdD7LJfBo/tZTPLi8E6aXkzEIaLuO6DY27mDwWzCSXUkfnU3nbXrGh8VO52UyQTx6ydR4dGtc0TnBwIXkoh+18R6x/jOt/pwQMS8lpTFv8x2jULptG+rTL/HLfZjFtMixeLo/tkVxYXkoHR5YXVhbTtq6xYWkOLmdn08HK0nw+SM7OpnO5ALvPphv779ItLwW5
*/