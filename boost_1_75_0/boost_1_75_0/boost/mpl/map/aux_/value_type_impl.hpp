
#ifndef BOOST_MPL_MAP_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/value_type_fwd.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost {
namespace mpl {

template<>
struct value_type_impl< aux::map_tag >
{
    template< typename Map, typename T > struct apply
        : second<T>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

/* value_type_impl.hpp
EEWX9QeR3TfO4ylctyA75LtjROhEEw3cOpdmR4d43C2kwl90kxKxvsuxIZqF+TxVK/WyWsvEkwglX4uyLvhi/lnbPU8R+EUbk+MldqrtjLH6XGIZISi5ZPSh5mfopdPig6VEPZemRBrRhC0KwJNSaHfKFUW+7D3JgVtiO8vB+CEnelv7d+/kHCRzNoFWsSev/OIeFXL7iOR2/+OALEt5+n6c6PCNmM3UN7WLt6Wkf4gdsMlnAqCmzk5Z/zqRplGu7VHSZriw6fM9YztwHOYP4Scl6Xn9K+77B9OOGRwT3kcSqa+umwng3hF7m0bebcf2bRnQ7HGdqYqD359j1Zbs+PDDPSxhcjp1q+zx1dbuWynSHJ3bNrEwR/bmBTt691Fo12XEQcSBPlSf8jLGXOeoXZy/xcZxfQd22rsrddYOQ1tnnez1bDsePbUodJEQxzuHCLpaneePDJbYy9u3kfjxu2UO8a2p3hIFMDSrPyoTzR/QZROvahF4afrId4laVXY8PeXWcV0NlFlXgBJJmbywMP65iFkfTa3/yKQYMZKjUK9yd8B001Xd/7LA98SITVa9lK40g1rXyRLYXZzQGxOv3U+j610fFX9lHC5fjf0ZjS5qxdm/UCAEcd9iEjNWerQYdi3Qa8YYUa3UZ3BAJDzoKjtUb8yp1WbrpOKs4hyeToJT6tu+V0lxwhg7daCHBsAosS27fWGAN/7Cgckv
*/