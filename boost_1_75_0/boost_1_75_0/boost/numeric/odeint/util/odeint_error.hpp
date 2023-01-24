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
VlL2X6K/91J4GWT5MelkEZd/JjeLeYnxUaFwIaYmX4EVRxFb0ckCqeODug9PfP5HYbbBZG2YGqOlE/Erva76bk9h23Zz/11fJGM/c8DKw3Zry/Kg7qow0KIyPeaYf7ax8pMT4kbIZKrKbvkXlibvDfPEid4KYZZ53FGTE0+n7zTanP9OHZouexMNdShVMkwQH/xZpgSIOiGPz36zIQ2+OFVx1m6X+oXujUPfNMVFO/aJBq8BHm3Xueh9tTp7VudPdUm2scNgsUlHNHlvImN943oMeXzZROpr2pPZwsQA9d789kMxPeso/pJ0lPvzgWMTgerkN3ej0OXPD/YW3Qp5hrSiukKfc8wavY991jNptHwyaXVR8z7/S/qjjPBhd53hxmcrx7vEJ++J7qI7G5bthgrCNWxSvyypV/2xC0k0vKlauJ4eanFm1ulGWubLwoqJPoKp5/sX7Yfq7ZiVjliy3Zu7n1vELVFBUlXVApWYwd9ujhfmSlylJbGDPW56b8ajogKQpUGVk1de2LMDVWzRgREqr0PG8T6fDHXzQtq6DkSpJf8OvTzxrFMKol3t/jPI7d0425drxU86qOIsriCgjhi62tR1O80SdD1mClv1KJxsaYhi23rs62kGL1uVHMwYws9UBGNtBiUVlEsi68AOgyrsnZn3dPW1bO3YgjtG6d6b96OPtxaEmWrVOausBly/O6NlBvSP6T7W4B73
*/