
#ifndef BOOST_MPL_AUX_LAMBDA_SPEC_HPP_INCLUDED
#define BOOST_MPL_AUX_LAMBDA_SPEC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2007
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/void.hpp>
#include <boost/mpl/lambda_fwd.hpp>
#include <boost/mpl/int_fwd.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/lambda_arity_param.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   define BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(i, name) \
template< \
      BOOST_MPL_PP_PARAMS(i, typename T) \
    , typename Tag \
    > \
struct lambda< \
      name< BOOST_MPL_PP_PARAMS(i, T) > \
    , Tag \
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(int_<i>) \
    > \
{ \
    typedef false_ is_le; \
    typedef name< BOOST_MPL_PP_PARAMS(i, T) > result_; \
    typedef result_ type; \
}; \
/**/

#else

#   define BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(i, name) /**/

#endif

#endif // BOOST_MPL_AUX_LAMBDA_SPEC_HPP_INCLUDED

/* lambda_spec.hpp
Box87wRG7b5Hco6utIN/P1AHt5d6Kq0mOns9xUtsRMYGryZxLLfXl4HX1tnqw4bPRmiItf0T01ng5873A1r+D7kmLRJeOGBPC33jVlKmDxzxAO83oPtMrV9F2K4an8l8a95P1ZXQmU6Ec95fyiC+UHKM3o8yOPf8/eNhabUDoiidy0fW2Ym8eE0vMsEhnf6i/WAs8pWc/rE+LQSj5KgOe4PEH9331DH3J/lRB3vXzvjCzbFF1qVjtDuIfCEX01rVrnd73P3TYZSjnYr6Ppxb7LFoNDP60BD0Enty1KAhIXqJ9Bc6bDL6XcJoCgMAJZLDx+OzmzBtcUwIbbZXF2CcK8zruaO3UpZ+LCPilTNeFgINhvydO1sNj/WflRLjkEpuO8tkoOxYFLa/OPFcU7BEXx6tmxHNmerBUObQOjTwxPPofJMrdWXUcQoK96K8cLsoUwr2mUMLa+oepbmaycgvDErzWiuhyERc8vIavUdOkcBsuJme3twI/aG19xVJnz/t/MPW9bOeAbnNpL3q9Egdpzb/zocLm03rnu/Rt1Wzo0xzcB1OQ1ef/rliZgamQp+jOCR72VNH66z3RMJCVIVfRxoLjWemq7eYgvq2NLf2qpNttrIX8MWkeMYGLEBAXfaaWEQfZypmQ1dXHdDVHNEFxpkYKaeeUhwpPBDKmm99dFR5FMzBNxS39dhPOwgDYnwAyTeg5mtKqYysVr/z
*/