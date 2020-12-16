
#ifndef BOOST_MPL_PROTECT_HPP_INCLUDED
#define BOOST_MPL_PROTECT_HPP_INCLUDED

// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/arity.hpp>
#include <boost/mpl/aux_/config/dtp.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    , int not_le_ = 0
    >
struct protect : T
{
#if BOOST_WORKAROUND(__EDG_VERSION__, == 238)
    typedef mpl::protect type;
#else
    typedef protect type;
#endif
};

#if defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
namespace aux { 
template< BOOST_MPL_AUX_NTTP_DECL(int, N), typename T >
struct arity< protect<T>, N > 
    : arity<T,N>
{ 
};
} // namespace aux
#endif

BOOST_MPL_AUX_NA_SPEC_MAIN(1, protect)
#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(1, 1, protect)
#endif

}}

#endif // BOOST_MPL_PROTECT_HPP_INCLUDED

/* protect.hpp
Of0PPr+XirdMcR3a/eQqLpzqvmn2GR6UetrffPEZqBPKjE3fpoa+IXYYL9WN+l7hxgb4U4I4fH06iAbL6V98IJJHohr30/jeLa+ATJyWc2MWSnIJSfwh5GL+LPum4GAqd1yYyzmFlMPren5qzV8HnIMvEHfSR+wfJtrA4CB84NYz5UY+jO8gjxSecsM1T8BZwx2H+dOdDvYvP7kYymE/3SFGshKb8NOozRugzXvYPSN5A7QHitPdFGmZnfh0QSh0GlXCxxMp10EP04aJAnwxc46jwIPPJ84RXxqcR5U37Unxl0KAm8bAHcpP5m5NAiOYXqfEZINVWn4yMYPhqgNq8fhL5oiROYwPKWq/LTqC3yVP9I/x4MP4/8c9XZcAEGC3L0YRl3S5LnhDjUrgqFpR5CF0bClYxfxnPVW6qpqsPYdGCwhU3Zi1OJUSRNH7IhYs9n3IFT6mn1i0WGNcJbUmwAdB1sllDZlRG6hY56hoL0vGtzH/MoO15apZkbL65kVfw1mF1vyCMP3r4HX5siH43utq1CJWcWABawJrAnyAYXugotZR0UrE+NulN+jEFoMYtfQWafl8DkVz8PozEeOvUc6QxDp1Xh2Sta2Biu2OCo1Zay/RhlpZw6mIfJweZNZambW2Eu3QRTq1Nnmjj+StMVCx1VERZt5aZ2kvX2TmDSeiOvNxqIZ505i39lnaOkmtXV5mLXlrCFQ0Oio6mTetRFtykZk3HIhryy9opX+ZtzDz1lqifUtSa9XPeaQEitYE+JBHfaCiwVHRRtT4s6Pn6NSWghqx6y1tzy/V6F/HNjJ2olagFWs5kpomb7uRkq4NVNSjS6HftgvNkuKYZWs+90UrS0pdyv5Ae/ZC2aXy+nzJ2+ZAxVr0KX/WVrv3QitvYW+pls+nwjTmjfoUYct8Sa1T5y1N8rYhULEZfQr9Flt5wxmlfJxOY96oT4GjUyW1NnnviOyF9YGKDehT6NeOeqoXGBud+TicyL1AfQoc7b5A9qn8nIOUtC5QsR59Cv2uv8AsKQ5/tOVzX7SxpGGWtLVY+6mk1qpL6paS7gpU1KFPod/vXmCVtNVb1J7PfdHOklKf4jvJUyQ1Td7JISXdHajYZZhp7gWJmOlHhcpMhaSZUtLmQMVuo0+3FSbSp7WFEX2aJSVtClQ0G326oDCRPr1EUmsLVDShC6HOyRZWcGiqMx/nbpgV6kJ8kPp42bgdE5IpNCEJNqXB5dFH6mk11l/QoqYqMtOTUdASK98VMz8qs8Vfui5QQEUuWv71F7VQNQR7HTLTk1HUEivfFSs/OrMl0hWP+0oifZz5FdnHR1h4uHYFmbu+nAhkfiBqYfAmurRHONdf2kIKQEDeITM9GfyA6HxXzPyoTFIkRgqFwAMFiSBwV4FE4BHuVgw8ykldUZCIkzpbMtd+hLsV45jyeY3TE/F5v5wufd4R7lYMi8qF5k9PxIUePF+60CPcrRhllbX++PxErPWq84+StVoH7eC0RKz1mWlHyVqtMcCMaYlY68nTjpK1WkOKR6YmYq3+qUfJWq0RSr+piVhr25SjZK3WgKdiSiLWOnPKUbJWa/zUPDkRa31s8lGyVms4NnFyItbaf/JRslZrdHfveYlY6/zzYkZ33zwvkehu4nlGdLfOW7TdW7TZW7SbAW0DsgbKcl7IoxmtPgdzIpu3jdQstoM+T+fa8hl5bQ7ibytsArO/5nOVTRTUegu2egs2eAuaGZY24KMB5VAurzTU6hOz+0Q2zRZpLwoewXO89nzGT7uDfMLTQDbYqRB1sdNiu7e00Vu63lsKcNnQy6WyvA174Lbrs7Xz5CPa6RFR4Cxo40dIfPY718DnVm9pg7e0zls=
*/