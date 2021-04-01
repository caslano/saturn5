
#ifndef BOOST_MPL_INHERIT_FRONT_TO_BACK_HPP_INCLUDED
#define BOOST_MPL_INHERIT_FRONT_TO_BACK_HPP_INCLUDED

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

#include <boost/mpl/fold.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Types_)
    , typename BOOST_MPL_AUX_NA_PARAM(Node_)
    , typename Root_ = empty_base
    >
struct inherit_linearly
    : fold<Types_,Root_,Node_>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,inherit_linearly,(Types_,Node_,Root_))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit_linearly)

}}

#endif // BOOST_MPL_INHERIT_FRONT_TO_BACK_HPP_INCLUDED

/* inherit_linearly.hpp
XoC7pKng6SfoE/cZjHwTL+y7ihSegTr59rMXcpWmeXsX2SjueROLjNt63EMVVMNwVTCYct2tk3wWcVd69LTN3dgjnauupnyetULM2pj5a9wyhGj6JNrPKuTUllJDDeMDV+ppUjJ35o+2YK045iq9zuqiuHsnWhhIIeEEt7NE+QFeOt5TB6sko4HVSp7yhirLiF4eP62HuzJ/cCKtcDf9P7XUPXoPbSbMyaO25o/QBJPu3WkjZ2UWfijNWaeMj5qk7g0xVpnFEy+QtUF3xGJFY+V5R9JP/F7aZ+YHiMwmf7oMocUW+uaXNsdlrN2jA1v0e5iJwreP/ni9O+pWsXERHiWmocRaquWJY8ugUuKEjRmQgFa/dE4rw81aBTWg1icitnwXJWDYXeJhFmNMqat00g6mHI1yjgCyt5olUEazsR60AdGf6L+/Pl9iTiSXjo8mhbbS0SfZTZY7MGHfXN3erH1gv5K/6F/n9X43oCi6M0/m6CE5vDUbDIcmtIRXGu7O5LLq01BgKCgSmB8b06pc6JkES4sIKNuFq9bqOGtUmztJIQBTTwX7ozU4zQ==
*/