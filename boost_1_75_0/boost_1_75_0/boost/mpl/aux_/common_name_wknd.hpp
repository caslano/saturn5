
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
W/GmBfu00CxsG+hSgkPmd8j/VjJqhtoJdvQleb/N8OpKPFllIKwA3W0+9WuhlrzptdsXHi1DQXagt0qN4LSeu+ipXg+/0VYWnDuYY/0f4oR3Ze+mo9Sr9JJ3UeP3nrUTsnkbEZ42H7njffV0aHcYSJyRCVtqki09Hvf1IhuzSlgNdnWzfg6hqnCD1xfMlfMz2kj40KsLnv5C4ejTWcvXnBbbGb9a2fgT/8wukAVumyI2/22hspi65rcftr5zzVidWFWBLeCenYTMxfO4BJGkwuv/TDah3kV69pPK+gvlL62vcJ4RUVPQ7ZU++N7+Zx7f3+SBODeOuhZF0sdrwYaSu8M1jdXSz3fy1zX+cd8bpcG/qnwE4XgtBH4HtS+OKfy/eY6gW8d4NbjXE+8Ua7xS2YcRiAkd9rNGHNemqi61NGhM+5AWWPs8YeKryfLv4bnx1s3ZOLSj0LilBF8HHxYTk0L/ZO6HQud5/567S56hs0LgstKPSNiZ9nICa2M8TLYv/bkh+sKNalLi8ktV4/xypoNjK5tBXrgDJ/sMbCSKuPgTiWjzW8oUntPC8uIk+t+SHX8eJQgG5Bi5HZJnv64XQAVue+hvC4rNe0gSSgVmIhwsWplWT1PYhzo1ydsMDTSSIJbcOoFmdgUlId0JbsUcQH2e31SDt77vzF6m4ucFgh42YU57d6vLgZ5/GcMr0Kk9uBqoxtN4uAF8DaOU
*/