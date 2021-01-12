
#ifndef BOOST_MPL_AUX_COMMON_NAME_WKND_HPP_INCLUDED
#define BOOST_MPL_AUX_COMMON_NAME_WKND_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, < 0x561)
// agurt, 12/nov/02: to suppress the bogus "Cannot have both a template class 
// and function named 'xxx'" diagnostic
#   define BOOST_MPL_AUX_COMMON_NAME_WKND(name) \
namespace name_##wknd { \
template< typename > void name(); \
} \
/**/

#else

#   define BOOST_MPL_AUX_COMMON_NAME_WKND(name) /**/

#endif // __BORLANDC__

#endif // BOOST_MPL_AUX_COMMON_NAME_WKND_HPP_INCLUDED

/* common_name_wknd.hpp
eqVQ+W8G3+/L+Dt8Sj+8LdZl0lbqZIvn87PHpT+l5Jnf4hmU3wIpT+yGwWTefYChXKPpChhoovufKVDNfyb6MWp51cqzDAuKMlnU9THmvd8Afd6HGeJxalxf/vw+ah2i+aMTDsJm/Cc+wOHZEGozy/6XvmNgz38waSFKXPI/mDj13NY3VPKyV/LShlCQ0IJQnvWuaNLyEh3gZ+EzBvw3ICLQlPk+qmWZT3SAYd1lwmW5WXec
*/