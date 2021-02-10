
#ifndef BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED
#define BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/void_fwd.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   include <boost/mpl/int.hpp>
#   include <boost/mpl/aux_/lambda_arity_param.hpp>
#   include <boost/mpl/aux_/template_arity_fwd.hpp>

namespace boost { namespace mpl {

template< 
      typename T = na
    , typename Tag = void_
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(
          typename Arity = int_< aux::template_arity<T>::value >
        )
    >
struct lambda;

}}

#else // BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#   include <boost/mpl/bool.hpp>

namespace boost { namespace mpl {

template< 
      typename T = na
    , typename Tag = void_
    , typename Protect = true_
    > 
struct lambda;

}}

#endif

#endif // BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED

/* lambda_fwd.hpp
20qqAFqWe9nYQ1gQ34cuW/m0Mhp5HXn+3F4Tl6lvtwn8WehFcSjYw/ZaKwugZCUh9USXsJbkNPIKj6SwOeS8LqAK55/KNFpfqFceYogG+aDxIBjlbf1hemQJxOva0rSNKd7oZJNL41rmfeJNEcpHU7z7Snq5kYLaX9ZqU5gNybVEI1rzwmP3eumLD76PK7C4DUCgDcuYyvSIEc1U7Odwo3jv03nxoBPov4LzQf/aiFZSwQ10/DXoidORJzW6X19T8AWq2q2WhBtsvXbyJyJzlcidq+xpNR4tFPvOhuWJSkyY0AdLFMIuXE6H7eJFZbhXYxtSHLUPUnygeCJ6FfXuKOQZR9HZ1c1ieT0fn4Vw89ubHz/Ob26XhFpgxXffQlx9JK374Zl+yDg+QyneMfLLhXptHT0wzgmW1H97fDAYjMJyPFQYZyzDqpsEOsSRjftjOB/IA6nv2RRZQ55vCqsh9NwvcMgY65BZ0SOba/dIxLvge9i/fOy9F5XLC5PS9Obt29l0CT4xZSvGDknZK9pHTBtwWSRUaeNI1dvVIZN/oz0+rm9dMWYMwsagd/3wYZITqT73ywMjCGpCqzaYbIV3F/f4rrDOr7o2ov0MirHOFBWcgc9G5+cPiLsYn/+cfnlxET0ZjYejp8++iuDx
*/