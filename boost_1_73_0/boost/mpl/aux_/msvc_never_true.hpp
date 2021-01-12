
#ifndef BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

namespace boost { namespace mpl { namespace aux {

template< typename T >
struct msvc_never_true
{
    enum { value = false };
};

}}}

#endif // BOOST_MSVC

#endif // BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED

/* msvc_never_true.hpp
DPVVKSE5pLOW+Q5mPdZiAzZiQ57AxjyFTdiTzXguW3AIW3E023As24b1NrDCzLDed0L+1Baqhf7unuaryTN4HM/iSfwL/8LzmMyBTGcyr+UgzuBgzuQQPsih/Csv4LO8kM9xGFdwBD9jGqP6JD3kbwYr8GJW5WjW5Fg24CVsEeJ9eBlP5wQO5FVM5dUczWs5iZP4EK/jC7yRS3kLX+FtXMHbQ36tLxR+Q8cfQ35FYVVOP5f5
*/