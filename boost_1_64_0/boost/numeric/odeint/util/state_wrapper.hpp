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
DJBpOy/ahyhDUI1uC4N+vaibB3vH6q/IMFfdSDaZBrJNHR3A9tFH+u1VR5JEKhPHJQABu2X0+nYS8zp+I2oW5mSzcvL9DzQiwzua6uVMQeka4y2EqwC9fAs6y+vYjEmmsD8DuD99vocMijNopTNkLUBxHVXW97faukivL5Ob4N+9LjiPjDcRM/qnFvcAynLzD3ZXlj5hCsd6X8u4JelnL5bt6SAp7hJaj9WEtM335vdYRNaeqHGIRGm2gfbgzpyPltAnEvky6fw5gTJfWhOu3MqtahDgm/vDmO3QNfOSB0mRYhbgopG4ypBR9liYFSzhzkPZXNaOY0Hiv9QlV5SfkVRRiKqt6EKT3/zlPV/6O+AG0JqgATslCgq+yrQpbF76OxabT882zhMRlbzIeQ3HqSL3ivu7Z3hVbV6bkV2WsAMrBdTiX+tDyJak9hoQArT2AVjH2Cn+DMGQXw6JMZc8JtO4JKvskJv15q5S+eAa1p/2GjQEKxS429X2c/HXzeftfFxIOYxmE+y8DHlePraS0rhxMetSHRXtPT1Hkxi1TQk4vOoipTNCNjFhwQ==
*/