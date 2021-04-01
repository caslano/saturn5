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
DPyC/+/yltCl7VzBDXcYpYLte5HkEWZAwaqfcyPYLmAgSm/qC4pjXV2kqbvxfaQLvIchI8g0t7l5YJ5C1D3u27Tm4FBPX+96zHVDWMYQ98HQ9Z3mcV8gKG1kSSoZmpEjXHxDEDvN3ftvahEnZ3FPAaPJ95pjPsfzC4ZhQ8S0zTMY8G4g4ikfFJbmX/E+j4E1ZA9OTWyrBYGULI1Xc6wQgqA2XuXOriA52cmXdQP76cPNkbS/tvY8BDaJQB+6b+4lAhsXinBzJPFY77QtugCdcH6XyrlE7lPJRUfNZnpDbCD2o7tbc6gtLQp0q82tptaBrISZOEgi4g85NqxNYlK5NLxMIcB5FBZldIcsjYn3NTNE5xmqTw1S7rk3CR2XDgMbNPl2nmHKXRpPb+15oaK9nla9iWpr9RfcOrE1EgH4l9zNMeXJGMakZJTUhABlhsgT+Fsa13Lj6K1EqakaowDgruCUTZZjs5/iO81qxKnxyv7xoDCLkO5tF8ssneUYB/zFdkNXHqGXShPWtjPNjBNPklXYLpo1LTu8g1UF80ULYEVJ6hvTtqcq65MplA==
*/