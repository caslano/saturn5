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
aBjUdFQN50kpwyzCZbmqyiKnEyNMM0y4gvblZNhy/jgAPVqFMrL3SXfrZ2jbq9B16FHETbtmq1QuecpELkzTQtj5MDj1h8wfDluwd1K19Vlw0QJLChAXihTjpjZ0FMqFxguWFsR0BzFa5I1Wt+pRaOgwYdafzlh/MmE//R/BhJ36Z/bve+vGksBJNTHkel0zdTdG92z9bQNPml7IP3UYpsjzsmj+tzMbLdNo6MWoAnOrRILxjNHkgo27+zZsPAx8uj0Hu4C/+pPTYNqvkY41p59lQi9NLFVWtVlERVVv6Gib4ga63WYNfTUD5yGCJoXaqq7KvfMXUEsDBAoAAAAIAC1nSlIoCSO31wYAANIQAAAiAAkAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWI1MjUuY1VUBQABtkgkYLVXbW/bRhL+rl8x56IJ5aMlO0AOtZ0Up9iyK5wiGZLcIG0KYkUuRTYkl90lLfua/vd7Zpei36Me0CqIXobz8swzs7Pj/u5f9+rQLm19BfZ/gBc+rcWFVr/KsHpaOwi+kPsHq0/43BakT7cmX4IubTf5Qp41CZoob/h7EGwL9Imx8VufLT8F/BUSmLHliSpvdLpKKvJOunRwePgd7dGr/Vf7Pp2KIpUZzStZLKVe
*/