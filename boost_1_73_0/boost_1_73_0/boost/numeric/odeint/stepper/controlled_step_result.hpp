/*
 [auto_generated]
 boost/numeric/odeint/stepper/controlled_step_result.hpp

 [begin_description]
 Defines the result type for all controlled stepper.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_CONTROLLED_STEP_RESULT_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_CONTROLLED_STEP_RESULT_HPP_INCLUDED


namespace boost {
namespace numeric {
namespace odeint {

/**
 * \enum controlled_step_result
 *
 * \brief Enum representing the return values of the controlled steppers.
 */
typedef enum
{
    success , /**< The trial step was successful, hence the state and the time have been advanced. */
    fail      /**< The step was not successful and might possibly be repeated with a small step size. */
} controlled_step_result;

} // namespace odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_CONTROLLED_STEP_RESULT_HPP_INCLUDED

/* controlled_step_result.hpp
r3LLiHxybJU763JEaAfrdsLUup3Btsqdw3VhmU8w72x52lbjmWHKPbKeq97liEK7yJR7aJezLFPdau6Z51Bb5c9uuRnXCFvlzU6K7XwfbatcWX13Fk7Ouwml6QZjbIT/7fvb2KjxUOduY22/H79ku39ePx5nu7Y83jb4Jx3sNp8Twp/1uY62P2earPmnBOiSNN0k26Wbpummh8eUP7aonqvJEWYG2vBjgcAruo1Ztt9PFZ15f8rrp7M1/ZyAHBQ=
*/