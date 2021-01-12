
#ifndef BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/list/aux_/item.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef l_end type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED

/* clear.hpp
1b2+2dHrhp91Gm4wmW4NieuzPMIyaPnZ6sGmSJP1Z/3uXD7z0Jxlzsq+zb0NQ35iDEm5bsjLg6vbnrDGZZrGRUQ0VFtL0tf2te6oHW5If2hAeMiNN1j7PNFSvaKmyGxsMsT0ppjIE6ERLtNzt0VY7YnVIXG9BlgiB/QquX5QnHWczRBxfa8Qd8j8QavzLB2rQ2tvGkdx5RbDO8vSt5kH7w/Ji6ibvOVAeL97zdXjVj69xNo+
*/