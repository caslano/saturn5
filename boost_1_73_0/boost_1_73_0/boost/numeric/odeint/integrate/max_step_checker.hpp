/*
 [auto_generated]
 boost/numeric/odeint/integrate/max_step_checker.hpp

 [begin_description]
 Throws exception if too many steps are performed.
 [end_description]

 Copyright 2015 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_MAX_STEP_CHECKER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_MAX_STEP_CHECKER_HPP_INCLUDED

#include <stdexcept>
#include <cstdio>

#include <boost/throw_exception.hpp>
#include <boost/numeric/odeint/util/odeint_error.hpp>


namespace boost {
namespace numeric {
namespace odeint {

/**
 * \brief A class for performing overflow checks on the step count in integrate functions.
 *
 * Provide an instance of this class to integrate functions if you want to throw a runtime error if
 * too many steps are performed without progress during the integrate routine.
 */
class max_step_checker
{
public:

protected:
    const int m_max_steps;
    int m_steps;

public:
    /**
     * \brief Construct the max_step_checker.
     * max_steps is the maximal number of iterations allowed before runtime_error is thrown.
     */
    max_step_checker(const int max_steps = 500)
        : m_max_steps(max_steps)
    {
        reset();
    }

    /**
     * \brief Resets the max_step_checker by setting the internal counter to 0.
     */
    void reset()
    {
        m_steps = 0;
    }

    /**
     * \brief Increases the counter and performs the iteration check
     */
    void operator()(void)
    {
        if( m_steps++ >= m_max_steps )
        {
            char error_msg[200];
            std::sprintf(error_msg, "Max number of iterations exceeded (%d).", m_max_steps);
            BOOST_THROW_EXCEPTION( no_progress_error(error_msg) );
        }
    }
};


/**
 * \brief A class for performing overflow checks on the failed step count in step size adjustments.
 *
 * Used internally within the dense output stepper and integrate routines.
 */
class failed_step_checker : public max_step_checker
{

public:
    /**
     * \brief Construct the failed_step_checker.
     * max_steps is the maximal number of iterations allowed before runtime_error is thrown.
     */
    failed_step_checker(const int max_steps = 500)
            : max_step_checker(max_steps)
    {}

    /**
     * \brief Increases the counter and performs the iteration check
     */
    void operator()(void)
    {
        if( m_steps++ >= m_max_steps )
        {
            char error_msg[200];
            std::sprintf(error_msg, "Max number of iterations exceeded (%d). A new step size was not found.", m_max_steps);
            BOOST_THROW_EXCEPTION( step_adjustment_error(error_msg) );
        }
    }
};

} // namespace odeint
} // namespace numeric
} // namespace boost

#endif

/* max_step_checker.hpp
+wenGYwfRedFwSpqeIlRA+2m+6jRhPZAqU29nn/1qFzRkC81lUCrTRVQty6Vgc4PIn/sBH6dfOVMS6e2t7/iEpLfbpgrC58HvQzy4gl0bYTDJxje5NhEzC9YzW/Kwi/hzk5QAfBxn/19cDrvvoqUvd2naGD9EQ7ECU4KB+6KouZEP/4Bb+PEKEWNJSwLErkpYBQQBiFmGIUwNArCe8l72IeJi4dqoymtLOVF36uWG64cxnNnibAiUjpt/HbHr60vJ60rtfAAaJvGcqOkSzKsUTfy/A7jl/Sk1NaKnlvp/9EwzxABfAu9R1vsfWhGtt4npWZe6E95aeXLLvn11rULhUtXltLXdOArx+mS434/EwkBdPSUJh3sfvNA3AxZJ13RK2ouugeohKGzSBIF2P5QcMcHkYTyCSnkErlqm7dePMWmK0DnbY3Kn+Npjlbga4sqR7rI3W2DcD5Ji/Mgz2S7ORLSZNjZ67n1Hk1z6aRZz8YSUy1IYG+jmz4CbtDRjQVi16tMH/HWV9Q0CQiFIWnfOt8BUEsDBAoAAAAIAC1nSlJ+kELBCwUAACwMAAAiAAkAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWI1MDguY1VUBQABtkgkYK1WbW/bNhD+7l9xdYDBdpU4
*/