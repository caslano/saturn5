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
tg92n0wm68D7/7Xxq4GpEl9fiGQZllaxpJFoXRWX1XiTfv3KE2HsnxCz9VwjfqW1qzw3rc6ww08ho7foUE+Hh3vZNtaxDfVq9+GhGRxSQoPvQOANQuC24OnTtGpCzP5sEUaU5PDGQCzeusPcpu/soPlplAwTuPF6RVpi/gxwi4goqN96KrC+7MyCYks19iSYGfgYzvQ7VzciqYQLMMAaNHFNNgUooHmVephcGKRst5iIbkeluSgVLp9kGr7MwfZl25YuwHXfHL8odGaTGjBIG9ngOdord2bhJDXlHqxRETdakyGs6bqYCKY2SZ4FhyPutsXSdTuK9kM4SIVg99+kV4lmFeyKmI4FOeXLR7txWZxLeN89wcRjMo6Rqdq4/m92e/mNtgtoFAGDoUW6IczbIXT2X4xSNlBPsBojetQ/1FZxihloJJaEiZgMfNB6dDVxGKOuzVRVtUWS7YJ1GCnDb5jfq4RY7RhOhVZOba9sHYpH3pRYQaC2TSQZr+6FFN3pBdQ7UBtKeEgzOSkzmU1h0Dv0/vxwdhvUQwBAkLGJwcR3JzRa23qtpVRftQ==
*/