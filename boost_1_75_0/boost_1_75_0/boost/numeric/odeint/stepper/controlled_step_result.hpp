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
dlNi7/EaU1PFqEIYDyB4FllzndfZEEzykPSg7stOAcCYAK3NzGch7Yv+ZED8FRZNVjzmYBKtG717lvTY6666gRPWcKTusE2sve2ERdvaV5Dr5fUfExdU67ecMgyRtkbirZeKzzIqOn1+MK7b4FniSwSJV1XawTW/5IkFb3ZwOsMRjVmLlbzNt13fxSVxhoafM3lfMVVddO7zPO+t6jskq1aROnXeR2UMImjbCO6PfRYAuro3kPUNVYZwvukvGWix86rRWcxnRQfeyNqV4UXY1Mgh3+X1/QKUC+9Y9PF3yarlmU0QHib2rECxibn8txvIAWVH9Xt/SeNKxOY+sTUjm7Z4O3cWCVmnn8yMsQaJz1O4neO8/ZnL93D1fQR1gdcPBH1W3QZvtV7KVfF3I4pEmr1Z/d49Pvz36cpmMSidLNC2U+rVzxjALm7vTh99q4OhZels9c+sPNn+xKu+UUaERWXYvHf+kl0QFR5kfCSOu1ELt7TeJsYXmlByY/xScQNU/g+4C19PJoYR7KMVKbe5u1W5bBh7laA8L7qvmHGtmdGtz2fLT2bdzUEgvHP0SPviRm0ZZzPt8tT36DcQ3iu0NBCUqRxSOrg4q7O7dbtRKb/m3qlpNN94RL3B+mkNdIDXNNe1zJe1a1RceqBh73MxOzROsWtDjnXsRN0Nf7a0cEqO6qRxnvvGk4LCq84qBvUeNOCj+KuCut8LWKxz
*/