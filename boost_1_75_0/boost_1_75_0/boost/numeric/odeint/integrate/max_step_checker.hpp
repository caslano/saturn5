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
mFe1TVNMHJO1dfiuzLAATAvFtAj62qyXvgbeE+SdaV80GGnNX5eIhldjfNVXDTLS1xram6nRNYn+d6HxpCnDzuorFs4EIz+oCw2SF76fKNZOxPirMiygWvmuSqyVxlQOpp1Wq9L9d7JhC5kjpal7Boy201ellJB+IvpvY2PllLwJNZfm1dVMGAubcsSEiyfUXzohr2ZyVU0DVGO5Rnx265v7dxsef37Ej/q9WDt9v0s31A2uef6mwp/3/t1xD996RPPqM495bdWKt7rO9xr89vKP+o6vbOg3saYpr6m+Pq/O4IBMXv7MEFqltPyiQqE6A7eEQbkaoWdfg0qVCk1aKnVtLZWRbvHG4940+P35jw3+PuLNne4U14Jz48ZXDUYO9UZ7jmcOecaTSoOiFxv/jpW2y0vx2U1Dzy344oZ3Sh47+dH3Xk5Mfznb9+Y14+T537z0j63xh49rfGrWd+9+NXXllFdv6n1A/LGBczoHF3X486j9z1zyxvwOgx89sfO6Q4a+vPGJyZt27Dr+1ujC45f3unRHctTt0yMVPauLIisrrvPuHPDCcdMvmvv8z058KzrL9/f7l5YEusefPGjI+QNGD7l70kn3/2tOYuDTF7/Y7ZGrEtHFt793W//ruv91ywtT7hxfZJp3VBJ6G8ez3q6VqaWVmamNW1auzNwKt7pllkJl7sE1MzNU3LiAhmXDUWni5qqpmQPLgYqA
*/