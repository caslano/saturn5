// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_DEFAULT_COMPILE_POLICY_HPP
#define BOOST_MSM_BACK_DEFAULT_COMPILE_POLICY_HPP

#include <boost/mpl/bool.hpp>

namespace boost { namespace msm { namespace back
{
struct favor_runtime_speed 
{
    typedef int compile_policy;
    typedef ::boost::mpl::true_ add_forwarding_rows;
};

}}}// boost::msm::back
#endif // BOOST_MSM_BACK_DEFAULT_COMPILE_POLICY_HPP

/* default_compile_policy.hpp
eutPEGmrpbcFeP0e9A541JsEnuFB7w6PencC70886H3Po95TwPuRB713POp9ALzPPOitPkmkrZbeBuB1Ma6b3rhHvQTwdA96v+tR7yvAu9uD3qMe9b4PvGc96L3hUe8/gfexB722OSJttfTWAG8L47rpaR71wsCb9KB30qPebcC704Pe33jU+y7wnvKg96pHvTeB94EHvaZ5Im219NqBt4Fx3fT2edQbBV7Cg96XPerNA+8rHvQe8Kj3MPC+b9c=
*/