
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
IJcSjDyBBpt8BB2HIOfMFVK/JM/psVIXWdjI6NlBIsfjKCOtGmrdv2ttha2iSRCCxjqHUuBX+LHjPmLFuddXlr9BCa97yH5fyGF7Im+rJbutyFQH0PkZhaxQByRalIHrQpnp0isGk419DmcvH4rt4vkN7jmDnDk79gL8JJV/UtpuHvr+Vb9QSwMECgAAAAgALWdKUmxdfw10AQAAeAIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTkzVVQFAAG2SCRgbZJRb4IwEMffm/AdLpq9mLmKziWSjmRxi7JMMbN7Xlg5AhGpoXXGb7+D4nzYXqDHXf//390hLBqrEoMhE0WVaXrt8HzSdWpCtpRy0z5g8SLdocZDmShMIcckxdqw+cf7W7yRnzJavczj9XMko3jNomy40mmRFZgOt0WlkAl+1RXcWbE+bLH+xnpoipRKGvEzpdPEJlBplaPaPfbOaHqOhft3PkxG97DWFi767DmxGIDMj7fg+/B6LGE88mcwGgfjh2A6g8VKMmcTQNPt0LQBNyejSm2QEU/j2HB1BH2YlwVWtuNSbUB5dzNkubUHqr6Eokr26BBBHY3V+248oClfk4aB/+ckuLsqrNZlyMriy5/OJvTZxULp/T6pUucYcH6z
*/