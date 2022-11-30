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
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
*/