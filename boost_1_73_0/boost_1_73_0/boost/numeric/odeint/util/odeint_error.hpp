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
ki17JKYpQvN6jUkVq+Gs04E+kN/3Bietntfq9arwYtkreTqlrKLcTyqbk4PRs+7r6IB2hxftqm6QiZVuxQtcVjTe1td3Wr2RJaA7tbkePZKu7unrP1BLAwQKAAAACAAtZ0pSTZRTpSkHAACTEQAAIgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliNTU1LmNVVAUAAbZIJGCtV2tT20YX/u5fcUJmMjYR2CZtU0Lp1MEm8dSxGduU0peOZi2tkBppV5VWXNrkv/c5K8mXhmDemYoxks6e63Muu2rv/ndXg3Zp6+Xan4sLdytxluk/pGce5nbdT1T+QeoK921G2rQS+eS2aLvIJ2paEbey8gM/u+42Q1fsG/9rs+SVy4+gQIwlT3R6n0XXoaHmSYu6h4ff0x4ddA46DvWFimRMMyPVQmbXDv3gW8pPobi728/ljw5JQyLer1TNwyinXAfmVmSS8BxHnlS59Enk5Mvcy6IFXiJFJpQURLGkk8nZ5XD8zqHbMPJCVnKvC8pDXcQ+heJGUiY9Gd2UOlKRGdIBxKHcj3IDhYWJtNqHbUlGZknOOti8iHNN4kZEsVjAkDAUGpPmb9ptr8hieN/2tZe3vTr8/dAky0gu4UQi7kmnhoymIpcOMadDifaj
*/