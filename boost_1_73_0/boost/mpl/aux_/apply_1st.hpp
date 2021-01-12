
#ifndef BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED
#define BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED

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

#include <boost/mpl/apply.hpp>

namespace boost { namespace mpl { namespace aux {

struct apply_1st
{
    template< typename Pair, typename T > struct apply
        : apply2<
              typename Pair::first
            , typename Pair::second
            , T
            >
    {
    };
};

}}}

#endif // BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED

/* apply_1st.hpp
Qxdch6VxK5bB7Vged2FFvIKV8AesjA/RFZXOVFWwAFbDQlgdX8ca6Io1sRnWwvZYG7thHeyLddGE7hiBDdCCjXABemI8NsHN2BR3YDM8gC3wC2yFp7E1XsY2+ADbonICeRMLoBc64VtYHtuhG3bC2uiNPtgFe2NXHII+OAq74UR8B2did4zDHrgYe+IK7I2rsS9+gv1wL/rhORyAv+NArMv5OhC90IQ9cRAOwGAcjCFowcE4
*/