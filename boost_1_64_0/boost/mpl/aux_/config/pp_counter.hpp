
#ifndef BOOST_MPL_AUX_CONFIG_PP_COUNTER_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_PP_COUNTER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_AUX_PP_COUNTER)
#   include <boost/mpl/aux_/config/msvc.hpp>
#   if BOOST_WORKAROUND(BOOST_MSVC, >= 1300)
#       define BOOST_MPL_AUX_PP_COUNTER() __COUNTER__
#   else
#       define BOOST_MPL_AUX_PP_COUNTER() __LINE__
#   endif
#endif

#endif // BOOST_MPL_AUX_CONFIG_PP_COUNTER_HPP_INCLUDED

/* pp_counter.hpp
xOL4Grwiqtf3FINWBZ+tm91hpJVtCdpo98zhoXmwYzotVKfm8G1OPwx6ccwsLuQVdbJ2XQYrD3OxMDsgbSEVbcy7Le6a8gVwi+nronxP5rh2c4YN5z+DXjxaUrntvW0WQWiqHMAClPxmu3g9YV3VBQHStpzx2Xms0r7JEjDiB8nBZ8vTOZyy2Gona8/U687YyPAMcd9OfQjfCRLKIFk82VqhlDUXc/grxQtzWVjOYFIqCqELhbsnBGtTrXup3RBSlqo4wrsQL65ygxM5bN7IORTKqoAhw0X7Bw2fViSt3xtWJc+mrQHz7dFK46eLCnBTfMt3pdOq7ghFyHDLRLppd8Qz4ZalulaUJ6V5CpbllzCbUyQQ0hS4YAUGbqm3IGnu3/mnsdtR7fuH0hlxeU1Eg+Mlk0P3MGv0iXfbD3NKXCLAMxSdURFEH83ov65EkkavH0E0lgwz4TsxGo3HsuLdpXOH6Y8Bd4aH71BMBK/B9ci+N/Ud8n9xkQs8gtLQRd92qyBwc2K/apIwzmQpfjC5WJY+poUBVQDWO231VrQsr2GfRdgcOFI1YugFfQ==
*/