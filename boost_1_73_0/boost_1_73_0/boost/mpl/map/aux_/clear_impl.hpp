
#ifndef BOOST_MPL_MAP_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_CLEAR_IMPL_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/map/aux_/map0.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::map_tag >
{
    template< typename Map > struct apply
    {
        typedef map0<> type;
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
MBT0dRrz+dB4NZ9PPGPNVllgVAPFts7H7CrrjhEqlcKXo4jshOxYxVyUQ4s4TKBMAm7nOXSqb1CwKg0EJiHTfQeCzAFdLihDPBOI5wkKOVBcn3urEYfxBYBDY9mRLStT1wMSJBpWd7JmKYMf6Azdh9nwIwzGwf3cH+OR26aZiLW1yosShbaTycrMsPdxMnOH97iHQkK34GxTdj6CShzQKovitXE+1b6YfOhZcbTS/q1L2Egtafs62EvJdX7HvJBN+W4HNKlQa1nWhQ7Lm7QuNFyT+5lv3TaQaZaQmRCUKBPTm5be6AaIzCf0Pe2TaqLiHVzKyZ2dCnYgAw23x/DQCQvbOh8AtQMrAKIFE9GmQJpMiGyUDuiIdkgkNHZo5q9lyNVrw96XZ0tnXHHK444BwH83WJ3qsbSgyCCMFvrNoZct5+uZ8KLnOLpaHe55+NsL6vgBQDRxAIm1yryti4U7m3v345qBKWUpvH5jvTn6g6pLGK2c/cJYauI42jNdef9USmXz7GO8hIan11K3vQ+njJy8bK4Ye3hQvvB0z2Vf5R1yz8G96fPo0W2Mnr2nb4LTe2yGspk1H+vb4P2nrhiOfnx37ewIHw96G+/942AW0+asQa8WxbK5KFb9cE+b078QUs2+I2Ns60Qj6/xf
*/