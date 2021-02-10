
#ifndef BOOST_MPL_AUX_UNWRAP_HPP_INCLUDED
#define BOOST_MPL_AUX_UNWRAP_HPP_INCLUDED

// Copyright Peter Dimov and Multi Media Ltd 2001, 2002
// Copyright David Abrahams 2001
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/ref.hpp>
#include <boost/mpl/aux_/config/gpu.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename F >
BOOST_MPL_CFG_GPU_ENABLED
inline
F& unwrap(F& f, long)
{
    return f;
}

template< typename F >
BOOST_MPL_CFG_GPU_ENABLED
inline
F&
unwrap(reference_wrapper<F>& f, int)
{
    return f;
}

template< typename F >
BOOST_MPL_CFG_GPU_ENABLED
inline
F&
unwrap(reference_wrapper<F> const& f, int)
{
    return f;
}

}}}

#endif // BOOST_MPL_AUX_UNWRAP_HPP_INCLUDED

/* unwrap.hpp
5CmsF2J9kbY+T1vf2NgASVmVSd0DZ+NojUAse0Mk+RPJmXiVtIe0uVCiW2mEaW4yIBVDprQBG0XBXhNNllBPT1wmDVuh5738fPnx8mtbY7hqd/p6cBPXGoFX1cOzdN09we/3xZswsgbD+OIa3Ck4q99k9TQSDRr9/YtsHAuNNR6df8VRoqayUDypPVVZjDBN7QQTrD2iEcrIkFBqB6EYK6mRiifW44DbIype5yBzLoRaIndY5ukM6vPGU4MlmAzBnn/IuIZ7RAmOzpRxWDSpY+s9VUYJVbQZXQHQzL/QfYudE5Hheyy02C0Jzj15IAghCBrIW73r3gwvBv0WOxECx+Te9DZbrLUsbg/g/2hgFbKYhERuErqoPvye+ZALJKDf7t80XuP7YymCbM/+nEgyXyXjLT8pvwFQSwMECgAAAAgALWdKUni/KGbvAgAAnAYAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDQ3VVQFAAG2SCRgxVXhattIEP6/4HcYVEKT0o2kJLSJqhiC42tCXNvESuHgwGxWo0hU2RXalR3fcW9z9wp9gbxYZyU7bqHpj/5oEVirj53Zb775Zh1bNFYKg30WFyrT9PqEq6WuU9NnF0kybX/g/TDpFlWtH1bs8nzM
*/