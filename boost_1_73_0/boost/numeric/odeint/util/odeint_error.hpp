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
jqjz9c7ILwG+qca3pcyjUd9j1ibzrO6on+c65Hks8pzZ4MbaDKXl/UzusxYW7QF5IcDW2Heh2UN6QLjDmxujs1RO2vpWxV0SpTvM+PTk6MziHGjmCdZl7u9MdABbINjZhiLMUgDe8eMzxtZHsG66b1qslMnBpYMdJ9i5zsfn3OSM9aXq4rERfJOZJ52cWfGB+SCCbTbjk/POO9PiQnl+ktyFLni78QcTfouN5UOGG+UxDpUr
*/