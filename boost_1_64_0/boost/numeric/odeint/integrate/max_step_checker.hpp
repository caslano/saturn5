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
ok5WzmZ/jGX/Y/rH8rX9U1AVlZtQZcoZnrZcIcvtVJWfH3CHlZvEckVV3jbCD+LcosoOsY1vY9ldvTwl1rPluRvLvT1PuTv4Z8uVsNzkKmW/TTn7vbE7y5RW6bVAKSP43DMj/l7E17pl9fCdxJ1qaRPX0p5G/L1N/Ynvrf8+LFNeJT476m3LOzlPB44tP4PlK1R58NHvhmsdcXT2Be6BFZbWpGA/0ppZZe3acJswi7j7E9fYp7z6P4flKrWMTDnbxiqWqbb9wDK2H2qIX2vwbxRdFz0H/jziv9/gPzHVH8/8QOIfVKXtIegbezifeB8k3huF6kyHOXNYSJ/eOeicb3/jfIzI4XaeBuFPAV5MOD2OHLyE8PDA3iBzs+V+h/xS5juvhPA/AF5GeOhxuC8o+hB/Qt405q0xec+H8lR5Xak12GMIcnkVzHNfbSpG31+RN5N5bmU82dWd7hzsxodRe/a+2N+AM5urTrrtrzhfxcGl7YTXEu5r+z+QfwDzddvfAHw+4WHbM/1gFxbNbHZ98y/kL1D5hw4M9q9DrM/ujSnQQctQ5wzCaRyyeMDho3LBIuKvGQP+ROAvUfTbV4O5RqXMdgbeUqGbF28X4K0Qeu7rbjCVxosrw3GLgdsW4Sb6eX7oHYAdGSCVcHAHmwLYRwJsTbDf90D6uKCro4fpMqS7gm6s/smdy3cBtjaAZ9aeEYEy793I6wmc1xbTp/cAPpDtI3yUZmlnsM+1PsUmE/e9gG+KcNNJnU0e70P+R4PeoWwdZyN9UgBRZN1kZGWUHm/FW/roIoPAd2FQ9hSOT0BdvRKAnUZYesNgkMU7k7Cu7o05vHMJ443Jl7Lw87O4KYHXAX4x4dTH/j7mHYC8y9w6J7qLdfsAYFdE/QU4YPymuNJ+U/Db4Rrz7XAwyl8fwqItqhzeTcTD10eQ/Za51eFh8IT0+M1zewjjUOO3SHhPqxOn0vUHiVubrMbE8aEq8c23j2Ft0sW+4XtAQcDj3upeb3mQPRousW/qFY8KtQfhOEgy/5r8SGW4XtpQJd+bi6pk7m3gb/2Wwv5T5Bv09Lnx+fCQKuKad7Gm7TUct6mKZyJlr53zorrzqH7Xut9qPXarjjcQzZ92P39FleBsK/XjtFTRNyCOXZ9pExrM95wbMO2eXCJzrb0nfSRw9X2tT/O95p+zTVwL0O2jvM26A/geUyXrDvIWiX+txa47HMey9yi+9xk6Zr3FG4u7i3S+H5Wln0a+rIf8a+OgTArWVGm/KfKZtK8b/nYvWxk8yNiLt171hf4u0L4Vfru+6BWaClfwBgojmv1VyOPYXePimsCYyLoH2gQsiaEAuUUxAHRsq4FAr/Eme0MjmYXvFqzvWi3vcjh6JQ5GmrQPpQ42tJ6xibgvRJiL1SXwaQ6OEA4OLnEBNih7Uh40mpfjmR4pZtHIZZwupJUNeTvHra9PsI4o32kcHxupT7uq8V7E32ezD0AD/1H+Eisj3LxKd29J5WBFYVz0CBxInIzj3e/poFnCOVfLrdTEUi+z+2lcz57GvbKDeM92i5brGPdis772lbQ5+Dfam6/S6w1MM1+vd0wXnx17I2LDP6Hk/4Ia30/yt3xzRH/2m+PT7INnVdmn+TvEwxhgPfg26vR4Gv0bS0N3zTqN0OqZEcc9V5elXuj0RSo/Kz/AYvU6m/V/QtV/f+qQ/g60b3V8EThcp5Jzi8RFm/gdaO7IVcVpov4xmhfJ/IF82kHzzfYloSHzizqvd2mV/o7zn5f7cpWktQwmq3H0spJHuYK/quClRk5oN3RE2VjU5+uk/R9VbidFby/1e6r6vbf7Lf12h+nT66u8a17A86953cC5FPluLi3k3Wc=
*/