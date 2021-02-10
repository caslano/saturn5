/*
 [auto_generated]
 boost/numeric/odeint/util/state_wrapper.hpp

 [begin_description]
 State wrapper for the state type in all stepper. The state wrappers are responsible for construction,
 destruction, copying construction, assignment and resizing.
 [end_description]

 Copyright 2011-2012 Mario Mulansky
 Copyright 2011-2013 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_STATE_WRAPPER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_STATE_WRAPPER_HPP_INCLUDED


#include <boost/type_traits/integral_constant.hpp>

#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>


namespace boost {
namespace numeric {
namespace odeint {


template< class V , class Enabler = void >
struct state_wrapper
{
    typedef state_wrapper< V > state_wrapper_type;

    V m_v;
};


}
}
}



#endif // BOOST_NUMERIC_ODEINT_UTIL_STATE_WRAPPER_HPP_INCLUDED

/* state_wrapper.hpp
bGlidGVzdC9saWI1NTcuY1VUBQABtkgkYO1de3MbN5L/X58Cls9lSdED8+KQcZI6hZYS3cqSS5J3k924WJQ0tCahSBWHtK293e9+wMyQnAfQ3RiMVLV10dbGFon+NdAA+gU0fLDT3s8G22HozyD9/0D8iD9Tivez6e/RzVzdejD4F8v+J6h+E39iTA7YmuRfg22Gk/yLbaUkg5zLd/LvgwHG6DfZN/mfA0n520D+VXwiyCRlf/rwOIs/3c3ZVn+bOb1el+0xl7t8l70dTuJozC7n0eQ6mn3aZd/dpp/8993w69f9JPphl0VzNhzv51BXd3HCkulo/mU4i5j4+zi+iSZJdMuGCbuNkptZfC1+iSdsfhexUTyOWP/8/a8nZz/tsi938c2dBHmcLlhyN12Mb9nd8HPEZtFNFH/OMB6GszmbjgS5AL+Nk7kAXMzj6WRf8I7YPJrdJxJDsh+Okykbfh7G4+G1YDScs7v5/CH59uDgZjEbi94f3E5vkoOb5fD37+b3q5H8KjpxP3xk04c5m0/ZIol2mWy5y+6nt/FI/ikEIj58WFyP4+Rud90bwWpyezCdsSQajyWWoIujJOt2xC5z8ezKZuxB9Dieyz+S6SSRrL7cTe9LDYUcJcpoMZsIRkIOotHtVIh5ly0m
*/