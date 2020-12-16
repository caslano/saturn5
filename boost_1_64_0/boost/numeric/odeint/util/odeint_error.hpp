/*
 [auto_generated]
 boost/numeric/odeint/util/odeint_error.hpp

 [begin_description]
 Runtime Exceptions thrown by odeint
 [end_description]

 Copyright 2015 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_UTIL_ODEINT_ERROR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_ODEINT_ERROR_HPP_INCLUDED

#include <stdexcept>
#include <string>


namespace boost {
namespace numeric {
namespace odeint {


/**
 * \brief Runtime error thrown by odeint
 */
class odeint_error : public std::runtime_error
{
public:
    odeint_error(const std::string &s)
            : std::runtime_error(s)
    { }
};


/**
 * \brief Runtime error thrown from integrate routines
 *
 * This Error occures when too many iterations are performed in between two
 * observer calls in the integrate routines.
 */
class no_progress_error : public odeint_error
{
public:
    no_progress_error(const std::string &s)
            : odeint_error(s)
    { }
};


/**
 * \brief Runtime error thrown during stepsize adjustment
 *
 * This Error occures when too many iterations are performed without finding
 * an appropriate new step size. This usually indicates non-continuous points
 * in the ODE.
 */
class step_adjustment_error : public odeint_error
{
public:
    step_adjustment_error(const std::string &s)
            : odeint_error(s)
    { }
};

}
}
}



#endif // BOOST_NUMERIC_ODEINT_UTIL_ODEINT_ERROR_HPP_INCLUDED

/* odeint_error.hpp
73yRnvzvedT+xA0hzDSptbBxjQ0mmzQpZXNLG25Mq3dIh6x1drLlonhcEzZ3rX/RKeW/nlLrrcenP03ZIOwyHRQNJ67HHewIzBXzElCjyu/ajHFBbgrFiCRr29wQDpX3O3tFym3mTrOf18B137pVcarTW9MUAKqS4nHFUbhUzFUb5XApsaJRmLTycy1tgSuZOmSKvUmzT5EishtWgRrRN0aNUBBbTydJwmFY+ofaU4Pp4lXkuDVdt9daiH+n676MekWVqBjlDvQCm1ZRJFpTSUAYTjnXJlavnFPkcCZWPIJLjZr7sj8ILcoodE0QrcMwx4KkHJlKwCnUUwWLmAbLBEo2j8DM3AMuK+lt09O59XcBBBUoeLzCLevDjgOZWVhauf8nhNAt8j4Ri0IPsKjvUhnI0nvom2PHpuBeT6L3QSvNK6Uc2KsRm1RzfR/jLvLYgycin1ZcaDQV20jx6ipTOfpN8CyUnjZ4avR8NuZ5Rc0iD1keMf+l9L895l8Qi+yG5/30XBjzzDIjD5T+J2kb6D/V9A+g7VXVxqTz2dSwGP3NNPzXDMnk9RnyDT40uoe7H25VRp0X6MUumrdl3sdS0WCn8Zcj5f9/gfHHgVaY3UA9CfJAKG9/W5G+FP1lLIZxhU/Kt+QPDw5cn6IYV4P5L4EhiwZeeddC8b38ocHM9XYjiN0MYjeCtN6Yfxr8bYa/zfS3mf7T8gvhn2r4p5r+qab/KDozf+v5oZfV8Mof7VpanYIMACldyH+ea+lc/oe5lmr4Zzdk70HpclhCvMPwDsFbyoLqL2d/QEHNFen5RVX2/MsXZeaPwH/UIk/+lfjftMiZPzzgyP9qwJ5fELSXTGh9nXj8hxxIn6ZyVpDl7oXs5FuZ5VYHjQYaOCV7D/TKArvG2l2ILcnX9P16WgWYImXR/qSyKGJILz0NlJ/qfKD7WYw0LpR/l6SNRHLuClL+u1BHRtHApa3n4TtFXUrluUcfy430NxEyB/PD9EHNYZiCfgbObmNwwghVoQpdtYetPEUY+szhqp0FY4W2G4MjnguO3GVKet/LV1yboqbY/S23wpmVp4/lDPsVYzbqidRgCnyv1c5a1cd64HkyPIfBs4/0ROVfjwmDATBPjc1gALmb2YMAu8MwuZZ6zQBD9IuH6ZuZ9dDegYHT2xoHBk7UN4ea98qQbtiDvbPbWs7kIixd4Lk3K3BKW2NWwB3a8fagN+hI2xutab1kiNBoS2CgPtZBhR+sDdREPia3PxMfZ5e10TA2E9n6A70xcux5u4IOfVeYNf0KUtuAEPSC8VkYtcwY9SnDCtO7ilQ4drmNVbtVImglLSGEDH3WM5gHote+pEoOnkn6lmtjYY+QGIH1YYGL91RHggfCNZRuaz1De8Yuj0eu7zKl3csMOhfQvgnU4I4XAxX1OmdV/uiAJx91kZ8XcOYPCzhWlFhLcPpfVF+IPVDrHGrBY8NygeFfEmlGlE+mQyk/Xn6m8gONQ3/dTxWYw1q3SOjZxO8B/xnAfwLwHwX8NSZ8Cs8oYeGcxhIER0d6BbusRGdIkfL/3zmv/qsehQ+Ne6RDXkqGrYneAyPpRKmJraduxZYhr9E1abd+kROq0Fo0TsUR+4/sFqOfeMXAWpuFqoi5j+Ue7HRtQ0qcTP9n1YPuqDV6kEJzSGx1IJlT5qySCTlkQlH7EpVMKwPgLFiAdJD8eyyLvo68DdZzw7xw+ewwDocBZ7hEyT/qB4CqDdUXOxE+HWpIpuYET5Ib8H6JG/C177NjOfM+wbxGIAChcyOJyZygw7nhs0Ot1hu/h42x9qqZ/cnioqXMtrp85UtaoiUKqT1xhdXtbUqlWdIre9YpwY4u2itTCuI=
*/