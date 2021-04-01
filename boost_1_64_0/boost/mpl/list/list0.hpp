
#ifndef BOOST_MPL_LIST_LIST0_HPP_INCLUDED
#define BOOST_MPL_LIST_LIST0_HPP_INCLUDED

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

#include <boost/mpl/long.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/list/aux_/push_front.hpp>
#include <boost/mpl/list/aux_/pop_front.hpp>
#include <boost/mpl/list/aux_/push_back.hpp>
#include <boost/mpl/list/aux_/front.hpp>
#include <boost/mpl/list/aux_/clear.hpp>
#include <boost/mpl/list/aux_/O1_size.hpp>
#include <boost/mpl/list/aux_/size.hpp>
#include <boost/mpl/list/aux_/empty.hpp>
#include <boost/mpl/list/aux_/begin_end.hpp>
#include <boost/mpl/list/aux_/item.hpp>

namespace boost { namespace mpl {

template< typename Dummy = na > struct list0;

template<> struct list0<na>
    : l_end
{
    typedef l_end type;
};

}}

#endif // BOOST_MPL_LIST_LIST0_HPP_INCLUDED

/* list0.hpp
h3li4kujyQBkT/zY2wBxb7tDAnKP+/mTAtOz6A0rgxfM2Jti3cePx2HU3j3CCIOM4DgVQHmV1J+ofAGmgZoE2vUvNKyovJQfG+0hn4rlTM2obLWyO2vdgMR8CL5Nn0kwxqInBoLPZTVISN2YHXWwjA8JU8NSHmda7FE8Gj+cvg+x5pUGQFzRFxQdEtmC/8jBdwCiGwPqyaV0I3/359gWV4FTqG6dKueq1Q+261TruoJT6rJQklN/16HN0IdpUH6jxVxE8ZaAp32pEgmzR0t1OudWGOpZPVlBqaFjlrJAXCjtQ3t2kXUqmwKCYxY2imbYsAiPIGGfsMz4NcUKuyWmbv3KMIuv+ttmUCvF/fHV0fTj4m2JmxprGNBkPqLQnlTRQzgZKbiHAgg4UXrM7AAmizmTMIXY8mjZtQM5ul+mD3JR9gWESSJBSWAPJ44W8HskZ17Br3BYbLT17iKWvGXOZ6S0GG7DFLopoyfVkSLiKkpsK9656Vdkg0LIZO+MhjJSDpOwgYOMgI3lluX5BG2yIxhjctxrseBP/5PaSCrmmi4QPrGZiMVj/NPwmQ==
*/