
#ifndef BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>

namespace boost { namespace mpl { namespace aux {

struct v_iter_tag;

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
struct vector_tag;
#else
template< BOOST_MPL_AUX_NTTP_DECL(long, N) > struct vector_tag;
#endif

}}}

#endif // BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED

/* tag.hpp
nxfzIcBP37m7k1KnLKzXFHWyeXFKw196I+wN65s275AfXCbe3bq9qXVTy0YVX5kOHuOjYk63Lr5jmUpeN3euzqIhY2qqXdsoY8URswarPy25bfnyZSqXxdFFAHX1i2ulEY6VV+r1+NF5y9auwBQZmLJHut5/KSaluGNlbdPti1esZde/x4jFyZCOalLTql22eq3Kq4pDOXhBbmb+NZLXNVn7K01/OH4M+KBi/6nZ4sosSLe1dHTslUmV159/RQQ=
*/