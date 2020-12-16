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
V51XFtsjeoqycMYiR+7iR9ujbQSDkiw0fzXWh0as9YWeI541FYOr8KLqdT3EPbrrIO1XUk6PtsbreBBl8RRsnIybI/+UPzDj98lwvZz7nYr7He2/fkSf4PmW/JI0i2BVRZxFi3ke17MVei1Y/GF1WkQ+3mhgLx0etbYeOXKqE15CMjWTcTFsEbst39MFl6SfHLrTUn8ORx++BTPa0ShT7H0nhS8D9HEr8YV1GwPjTsmPJGqidxtrZ+6h03TeUXzuPkOmWpsmxp5K3/i72KWFJf2tb3xx0vuVKK2WxeVKSlgs7yJf0KowthYOPWLt3tyrjnqq3Y208kVr294cUuB49Rh1Tr43co54IywuAOvwUpebMOdNPl5BvEsP905jHQca5y7Y4vPHftdDt4Wl8WCKe195xfr+zJ/Pi4Oamssz9aNv75WT71tCDwJv2n+nTt+z33g7FJtrJXFIxRT6+dflx+pIXqZ4w9bwE16uHqjfPXVs/fZ2Dvld8GKjr6uHR5Pl0JOq4ax17bm/JwZike0EjUArnbXGw67R1xVg3w6eBeysDauv642z5wjOdjujssQaiNlv0+xhWr/gHMQD72/oPi+s3XCvd7mMi1YY/9t8AB5zsmjvo8UzzLHG6nBAVvzytzHA5zfEpdVz2KbWgmcqV8Gabuvc96FaGiD+iejBtPC+lhy+DKfE5fEyYytDU/NAr4yBhQ/l5gRYNgwuvK8OitNHQ/ho5tBjl7/H6NP00fGL8V9gY7xi4tFe/EvpgWiYRPZGttIPo+iahGonJU/lDLxvwSsqVRCWq8ehxrQnkV7M/ntb+RYvhp7Ce+VfldPWeVpvPsZd+L8l5HnM4DyidX4TrvWg/+VGhf5yHdYWyUwXwoD+MHtvGM/gym2D4GAq+T5GrNfiU77U/bHqqrp4yr9NtMeGzGIM929Ocb+WNMgMOfESfSnvG92Rg5tp82P+7ssfy8gzmeh8TH25riZO3VN7tGPMKnkhftsS49wx/K3LYvavWpJ7T+RxycfWrDONPZX20FOdo6v7WL8DfOqaaq1/Yv2IvvS4mO7a5hljry2HuRXlSNm8sO1189mjXvXU0/V5I6vLaT3FKpiddCENeFj+9YG75/Ay7kzTHv7qFw7UjHSGFBYO4Zfj32yp5U0CGNjcff62Z+WztfShC2nS3e9YY5ox8oT3/uF6z3HC+XDs94C/FOnc6205/IsYXINZJ43LfWZdxCviu2MXvSyXtjrPMA5W9l7DH0xGA7r+kZvW2HWvbNIj2g+J4bFd0gs0OQRHzW2lPf/icCU3jl3zhbXjQ2grYs9Fl9TPDnlE43ntZ3zf57rXP9Y//IvTKtLPafVT1dTMT/qNeq6hf880zvWciaiQmE5UH4VawN9tOJ2Xs+aqWl4Wop/g6QvzmSGmmVx3Bo5zr0TBcwvv0lM0aLNyMA0+ZXXuaEb2EPzTJy+D6ZvUKo6PiuGNy4HF4tQoIVyzrj+orRUweUo7a3HAmZURejhYM1Me5At+F1YR3nNq+WAdLrfWp/+l5qfDtw/lHc6qVdO5Brq8Ihzp1xy+++yb8HqgXumUvcP0jdTqGdj4mr/nOhc4GC+3kVfy82ATPY2YLIbFoTl0QGF10tT89/j3c9dWO0v/oIXo32bmUveMuiyvb6TNztPlXeihgodhyjJ9ETxIlMDZWzqnQV3YS/OczRyKfd7v4TshiQ3Pg5rRxxX7xD61nDC80JoufOrccje5dX9LLib2/zpet04tae+IFd5HDyWbCZvy6oPq65dO8lV+9t4vxTcjbtwhv2DoHPM480J/2Zguz+t9hWD093wvtfPsAb3OE5krp8q0to8GN+6stk64dwef48GH1lg=
*/