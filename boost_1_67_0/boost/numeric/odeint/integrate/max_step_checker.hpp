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