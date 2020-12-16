
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
NEPQeEBvlsODnRCHMCIdkcC1hwtH2iQhH6Ny47jqH3D0JBaEwNo3PXkcvffbUayN4yMApAq5joB0MLkHxSDH0gBWsKzi0IGCWxics5GwqkHLwBWOzoJjcpDDfEK49uXRyNGy/zVG4EO6as/ZMz04VhIjgo71O/zsJT6lpSSOhnwwdH+OWPho2GmZOJWPFh0aygSRJofy4TFpCg4TB20nJiiNPx0QM1QEIpQefDJMSFBiJBMmJ7GRMb1hek4ynI2WtmcQRto3OhILOE+HE4cAWizSRkP64DmfdvOE5DxXIMtIv0TbCx2GBHxu72PjgygkYGPjAJ7nMHbCqRID/vauJwySZ+5AklSY/wip0LIKyDSD0zAPAIvgDQrh+X8B5iQXwc9lsKrB2+JA0mSx4PnE+wVMT4u0BBhvqCgsRwHdaWEVWm4ppHsT5mMPsLQXlMEc7AbMzW7w5gWER0ceHQMqO+QDnf/8k+7bCSZEYi7KHYD5Bd9vAzQ6QYNgCb/uBD+CG/zheEjDCk0zFOIWzAOGwxHQNyaBPBAr/CZBrvuPMxG9l4cNNCuwBgLwFmhI/nhjUAkR+k03HlINgxhC0ThGgWUQIghJECa63zhZILvZgOGYAcf/Z/Fx5wS9JYhT2l4TBxyxvFIZkES5pMPJF39uBPOO6s3H3wwJYwghEbBswAYIkDWa+wHEQoCwbJAGSI3TdgWXjMP7N1sgPx+3zCwFhwCDpW0oOFYO3WjA7R73c9LEwvcaCSqMJ+IqtPo6GE/qyTRmAzamXAW37TW8A7WAC5ZvvMOfyAMcZ2GsQQJwDzYKkG47km4bjLGfYHz7gqWRC25uJ6QJtpcbO2MXmeJhz8K/fR9ET7rovBBNmGceFM8594LPT0HGfwkYc4kUmgGJQqsESydTaG1grYUotAVgOZHh80qYMMBnjZGQLPbMJcG4/RDiuCpCoTFFIQ4xiEMc4gCbJQt+Wd44HF3cHGDmgRxON+CxG0mXW55aOmBHaxHQeaW2FooLGgUW3ERwUxAXbT8EtH+HhcUkgSYdhMLuxDktqUJjKlBoJwaBHQz5U6TQaEqQfxXwg+3hu94PXxaHr6+BuXV8Yhq+wITKnIF8DsiDHvAzG8oOAXmeW0IU7Py9NjqkrwH5AWsN1hNsPVj6UN58UakgAykVmifg68EuGIbRK8FlakI5wPZ9xmOwSGnRl/Bm0SjzA3eWLD0WfnFU+8bfiV/iLD6NUw0w++ax7/6i5qPzvaW81GOsRmVGULdHX7LpPPx0sXqaxjw5pXv1/gQiiUyhCgmLiIqJS0hKSUuJUUREpSWFiBIEkrgwlSwuIkGgkqQlxaTIQsJEUYqwKJkoKSEuRRKiilEI0iKiBKowiSImLUUUlxASIUuSJITECOIiZIqkMBWQohJUorSUJEWMICxEFiWJiEuKC0tJEMmiVII0RUSIJCYkLSUqTiaISJAkhYkUMaoYSYQiLESkSouLSpElJAl/K3+Ev9P8/fOKGGjD0cBvxOfr//Y8ML1PHrC2MD7aEFzhXjwjgANQvwfBDjC2cEueL+B9eu7R44TTHHA4dFyFvPdvQiDPbLBcT8MBxt7XIG0PaXdIm0PaG9LWkHaGtLH/ivY1QPPPby+sv6u9+Pyd7cXnX9pefAbUXugUzLXG/W0fqTRaK5VmDZZ74fu9gDxo4GHpPXwQJhdsJRq2N97UP/xOOjgO/mHPB84i+ifVdxz2CxIJAv5Y7loWNI/lk35cL26AeQ+G5SO+3HPd5VUq/Wy3RkSx8fWbwasWPFe5r0NyF1kZXsYmiV/eby63fajXRJG0NcaU2tZNSgX3zOyUDUaJxX4OkDfxaBgbG+tV7NC0tDA5eNY=
*/